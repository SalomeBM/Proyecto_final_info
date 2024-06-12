#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , x(30), y(750) // Inicializamos la posición del bloque azul
    , totalBlocksGenerated(0) // Inicializamos el contador de bloques generados
{
    ui->setupUi(this);
    setFixedSize(1380, 860); // Fijamos el tamaño de la ventana

    // Crear 5 bloques amarillos fijos
    for (int i = 0; i < 5; ++i) {
        int blockX = 50 + i * 180; // Espaciado entre bloques amarillos
        yellowBlocks.append(QRect(blockX + 100, 750, 50, 50));
    }

    blockTimer = new QTimer(this);
    connect(blockTimer, &QTimer::timeout, this, &MainWindow::addBlock);
    blockTimer->start(1000); // Intentar añadir un bloque cada segundo

    yellowBlockTimer = new QTimer(this);
    connect(yellowBlockTimer, &QTimer::timeout, this, &MainWindow::moveYellowBlocks);
    yellowBlockTimer->start(50); // Mover bloques amarillos cada 100 ms
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setBrush(QBrush(Qt::blue));
    painter.drawRect(x, y, 50, 50); // Dibujamos el bloque azul

    painter.setBrush(QBrush(Qt::red));
    for (const QRect &block : blocks) {
        painter.drawRect(block); // Dibujamos los bloques adicionales
    }

    painter.setBrush(QBrush(Qt::yellow));
    for (const QRect &block : yellowBlocks) {
        painter.drawRect(block); // Dibujamos los bloques amarillos
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        y -= 10; // Mover hacia arriba
        break;
    case Qt::Key_S:
        y += 10; // Mover hacia abajo
        break;
    case Qt::Key_A:
        x -= 10; // Mover hacia la izquierda
        break;
    case Qt::Key_D:
        x += 10; // Mover hacia la derecha
        break;
    default:
        QMainWindow::keyPressEvent(event);
        return;
    }

    // Aseguramos que el bloque no se salga de los límites de la ventana
    x = qMax(0, qMin(width() - 50, x));
    y = qMax(0, qMin(height() - 50, y));

    // Comprobar colisiones con bloques rojos
    QRect blueBlock(x, y, 50, 50);
    for (int i = 0; i < blocks.size(); ++i) {
        if (blueBlock.intersects(blocks[i])) {
            blocks.remove(i);
            break;
        }
    }

    update(); // Redibujar la ventana
}

void MainWindow::addBlock()
{
    if (totalBlocksGenerated < 5) { // Solo añadir bloques si hemos generado menos de 5 en total
        int blockX = QRandomGenerator::global()->bounded(width() - 50);
        int blockY = QRandomGenerator::global()->bounded(height() - 50);
        blocks.append(QRect(blockX, blockY, 50, 50));
        totalBlocksGenerated++;
        update();
    }
    if (totalBlocksGenerated == 5) { // Detener el temporizador una vez que se hayan generado 5 bloques
        blockTimer->stop();
    }
}

void MainWindow::moveYellowBlocks()
{
    for (int i = 0; i < 5; ++i) {
        yellowBlocks[i].moveLeft(yellowBlocks[i].left() - 10); //Mover 10 pixeles
        if (yellowBlocks[i].left() < -50) {
            yellowBlocks[i].moveLeft(width()); // Si el bloque sale de la pantalla, lo movemos a la derecha
        }
    }

    update(); // Redibujar la ventana

}
