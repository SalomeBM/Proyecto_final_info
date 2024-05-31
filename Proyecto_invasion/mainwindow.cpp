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
    , jumpSpeed(10)
    , jumpMaxHeight(100) // Altura máxima del salto
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

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
    player->moveBy(5, 0);  // Mover el jugador hacia la derecha

    if (isJumping) {
        if (jumpHeight < jumpMaxHeight) {
            player->moveBy(0, -jumpSpeed);
            jumpHeight += jumpSpeed;
        } else {
            isJumping = false;
        }
    } else if (player->y() < originalPlayerY) {
        player->moveBy(0, jumpSpeed);
    }

    // Comprobar si el jugador llegó al final
    if (player->x() > 750) {
        timer->stop();
        // Mostrar mensaje o realizar cualquier otra acción
    }
}

void MainWindow::checkCollisions() {
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
}

void MainWindow::onJumpButtonPressed() {
    isJumping = true;
    jumpHeight = 0;
}

void MainWindow::onJumpButtonReleased() {
    isJumping = false;
}
