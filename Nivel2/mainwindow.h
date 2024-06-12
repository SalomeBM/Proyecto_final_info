#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QPixmap>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updatePositions();

private:
    int x; // Posición x del bloque azul
    const int blockSize = 50; // Tamaño del bloque azul
    const int stepSize = 10; // Tamaño del paso al mover el bloque
    const int finishLine = 900; // Posición final del nivel
    int attemptsLeft; // Intentos restantes

    struct Block {
        int x, y;
        int dx, dy;
        bool isParabolic;
    };

    QVector<Block> redBlocks; // Bloques rojos
    QPixmap background;
    const int redBlockSize = 20; // Tamaño de los bloques rojos
    QTimer *timer; // Temporizador para actualizar posiciones
    void initializeRedBlocks(); // Inicializar bloques rojos
    bool checkCollision(const Block &block); // Verificar colisión
    void resetBlueBlock(); // Reiniciar el bloque azul
    void endGame(); // Finalizar el juego
};

#endif // MAINWINDOW_H
