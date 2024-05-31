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
    , jumpHeight(50) // Altura del salto
    , jumpSpeed(5)   // Velocidad del salto
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    player = new QGraphicsRectItem(0, 0, 50, 50);
    player->setBrush(Qt::blue);
    player->setPos(100, 500); // Posición inicial en el borde inferior
    scene->addItem(player);

    // Create obstacles
    for (int i = 0; i < 5; ++i) {
        QGraphicsRectItem *obstacle = new QGraphicsRectItem(0, 0, 50, 50);
        obstacle->setBrush(Qt::red);
        int x = QRandomGenerator::global()->bounded(200, 700);
        int y = 500; // Obstáculos en el borde inferior
        obstacle->setPos(x, y);
        scene->addItem(obstacle);
        obstacles.append(obstacle);
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::movePlayer);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkCollisions);
    timer->start(100);
}

MainWindow::~MainWindow() {
    delete ui;
    delete timer;
    delete scene;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up && !isJumping) {
        isJumping = true;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Up && isJumping) {
        isJumping = false;
    }
}

void MainWindow::movePlayer() {
    player->moveBy(5, 0);  // Move player to the right

    if (isJumping) {
        player->moveBy(0, -jumpSpeed);
        if (player->y() <= 500 - jumpHeight) {
            isJumping = false;
        }
    } else if (player->y() < 500) {
        player->moveBy(0, jumpSpeed);
    }

    // Check if player reached the end
    if (player->x() > 750) {
        timer->stop();
        // Show message or take any other action
    }
}

void MainWindow::checkCollisions() {
    for (QGraphicsRectItem *obstacle : obstacles) {
        if (player->collidesWithItem(obstacle)) {
            playerLives--;
            // Reset player position
            player->setPos(100, 500);
            if (playerLives <= 0) {
                timer->stop();
                // Show message or take any other action
            }
            break;
        }
    }
}
