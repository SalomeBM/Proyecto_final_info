#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QTimer>
#include <QRandomGenerator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , playerLives(3)
    , isJumping(false)
    , jumpHeight(0)
    , jumpSpeed(20) // Aumentar la velocidad del salto
    , jumpMaxHeight(200) // Aumentar la altura máxima del salto
    , playerSpeed(5)
    , level1Completed(false)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    QPixmap backgroundImage("C:/Users/Paola/OneDrive/Documentos/GitHub/Proyecto_final_info/Nivel1/fondo.png");

    scene->setSceneRect(0, 0, backgroundImage.width(), backgroundImage.height());
    ui->graphicsView->setFixedSize(backgroundImage.width(), backgroundImage.height());
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    background = new QGraphicsPixmapItem(backgroundImage);
    scene->addItem(background);
    background->setPos(0, 0);

    player = new QGraphicsRectItem(0, 0, 50, 50);
    player->setBrush(Qt::blue);
    originalPlayerY = 400; // Posición inicial en el borde inferior
    player->setPos(100, originalPlayerY);
    scene->addItem(player);

    // Crear obstáculos
    for (int i = 0; i < 5; ++i) {
        QGraphicsRectItem *obstacle = new QGraphicsRectItem(0, 0, 50, 50);
        obstacle->setBrush(Qt::red);
        int x = QRandomGenerator::global()->bounded(200, 700);
        int y = originalPlayerY; // Obstáculos en el borde inferior
        obstacle->setPos(x, y);
        scene->addItem(obstacle);
        obstacles.append(obstacle);
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::movePlayer);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkCollisions);
    timer->start(100);

    // Conectar señales del botón de salto
    connect(ui->jumpButton, &QPushButton::pressed, this, &MainWindow::onJumpButtonPressed);
    connect(ui->jumpButton, &QPushButton::released, this, &MainWindow::onJumpButtonReleased);
}

MainWindow::~MainWindow() {
    delete ui;
    delete timer;
    delete scene;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up && !isJumping) {
        isJumping = true;
        jumpHeight = 0;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up && isJumping) {
        isJumping = false;
    }
}

void MainWindow::movePlayer() {
    // Actualiza la posición del jugador
    player->setPos(player->x() + playerSpeed, player->y());

    // Mover jugador hacia arriba si está saltando
    if (isJumping && jumpHeight < jumpMaxHeight) {
        player->moveBy(0, -jumpSpeed);
        jumpHeight += jumpSpeed;
    } else if (!isJumping && player->y() < originalPlayerY) {
        // Caída del jugador
        player->moveBy(0, jumpSpeed);
    }

    // Ajusta la vista para seguir al jugador
    centerOnPlayer();

    // Chequear colisiones
    checkCollisions();
}

void MainWindow::centerOnPlayer() {
    // Centrar la vista en la posición actual del jugador
    QPointF centerPoint = player->pos();
    ui->graphicsView->centerOn(centerPoint);
}

void MainWindow::checkCollisions() {
    if (player->x() >= scene->width() - player->rect().width() && !level1Completed) {
        level1Completed = true;
        timer->stop(); // Detiene el temporizador después de ganar el nivel 1
        QMessageBox::information(this, "¡Nivel 1 completado!", "¡Felicidades! Has completado el nivel 1.");
        return;
    }

    for (QGraphicsRectItem *obstacle : obstacles) {
        if (player->collidesWithItem(obstacle)) {
            playerLives--;
            // Restablecer la posición del jugador
            player->setPos(100, originalPlayerY);
            if (playerLives <= 0) {
                timer->stop();
                // Mostrar mensaje o realizar cualquier otra acción
            }
            break;
        }
    }

    // Asegurarse de que el temporizador esté activo para continuar el movimiento
    if (!timer->isActive()) {
        timer->start(100);
    }
}

void MainWindow::onJumpButtonPressed() {
    isJumping = true;
    jumpHeight = 0;
}

void MainWindow::onJumpButtonReleased() {
    isJumping = false;
}
