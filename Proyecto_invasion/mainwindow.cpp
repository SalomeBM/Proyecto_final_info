#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , playerLives(3)
    , isJumping(false)
    , jumpHeight(0)
    , jumpSpeed(20)
    , jumpMaxHeight(200)
    , playerSpeed(5)
    , x(0)
    , y(750)
    , attemptsLeft(3)
    , totalBlocksGenerated(0)
    , currentLevel(0)
{
    ui->setupUi(this);

    // Preguntar al usuario por el nivel
    QStringList levels;
    levels << "Nivel 1" << "Nivel 2" << "Nivel 3";
    bool ok;
    QString level = QInputDialog::getItem(this, tr("Seleccionar nivel"), tr("Nivel:"), levels, 0, false, &ok);

    if (ok && !level.isEmpty()) {
        if (level == "Nivel 1") {
            currentLevel = 1;
            initializeLevel1();
        } else if (level == "Nivel 2") {
            currentLevel = 2;
            initializeLevel2();
        } else if (level == "Nivel 3") {
            currentLevel = 3;
            initializeLevel3();
        }
    } else {
        close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    if (timer) delete timer;
    if (scene) delete scene;
    if (blockTimer) delete blockTimer;
    if (yellowBlockTimer) delete yellowBlockTimer;
}

// Inicializar Nivel 1
void MainWindow::initializeLevel1()
{
    scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);

    player = new QGraphicsRectItem(0, 0, 50, 50);
    player->setBrush(Qt::blue);
    originalPlayerY = 400;
    player->setPos(100, originalPlayerY);
    scene->addItem(player);

    for (int i = 0; i < 5; ++i) {
        QGraphicsRectItem *obstacle = new QGraphicsRectItem(0, 0, 50, 50);
        obstacle->setBrush(Qt::red);
        int x = QRandomGenerator::global()->bounded(200, 700);
        int y = originalPlayerY;
        obstacle->setPos(x, y);
        scene->addItem(obstacle);
        obstacles.append(obstacle);
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::movePlayer);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkCollisions);
    timer->start(100);

    connect(ui->jumpButton, &QPushButton::pressed, this, &MainWindow::onJumpButtonPressed);
    connect(ui->jumpButton, &QPushButton::released, this, &MainWindow::onJumpButtonReleased);
}

void MainWindow::movePlayer()
{
    if (currentLevel != 1) return;

    player->setPos(player->x() + playerSpeed, player->y());

    if (isJumping && jumpHeight < jumpMaxHeight) {
        player->moveBy(0, -jumpSpeed);
        jumpHeight += jumpSpeed;
    } else if (!isJumping && player->y() < originalPlayerY) {
        player->moveBy(0, jumpSpeed);
    }

    centerOnPlayer();
    checkCollisions();
}

void MainWindow::checkCollisions()
{
    if (currentLevel != 1) return;

    for (QGraphicsRectItem *obstacle : obstacles) {
        if (player->collidesWithItem(obstacle)) {
            playerLives--;
            player->setPos(100, originalPlayerY);
            if (playerLives <= 0) {
                timer->stop();
            }
            break;
        }
    }

    if (!timer->isActive()) {
        timer->start(100);
    }
}

void MainWindow::onJumpButtonPressed()
{
    isJumping = true;
    jumpHeight = 0;
}

void MainWindow::onJumpButtonReleased()
{
    isJumping = false;
}

void MainWindow::centerOnPlayer()
{
    QPointF centerPoint = player->pos();
    ui->graphicsView->centerOn(centerPoint);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (currentLevel == 1) {
        if (event->key() == Qt::Key_Up && !isJumping) {
            isJumping = true;
            jumpHeight = 0;
        }
    } else if (currentLevel == 2) {
        if (event->key() == Qt::Key_Right) {
            if (x + blockSize + stepSize <= width()) {
                x += stepSize;
                update();
            }
        }
    } else if (currentLevel == 3) {
        switch (event->key()) {
        case Qt::Key_W:
            y -= 10;
            break;
        case Qt::Key_S:
            y += 10;
            break;
        case Qt::Key_A:
            x -= 10;
            break;
        case Qt::Key_D:
            x += 10;
            break;
        default:
            QMainWindow::keyPressEvent(event);
            return;
        }

        x = qMax(0, qMin(width() - 50, x));
        y = qMax(0, qMin(height() - 50, y));

        QRect blueBlock(x, y, 50, 50);
        for (int i = 0; i < blocks.size(); ++i) {
            if (blueBlock.intersects(blocks[i])) {
                blocks.remove(i);
                break;
            }
        }

        update();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    if (currentLevel == 1) {
        if (event->key() == Qt::Key_Up && isJumping) {
            isJumping = false;
        }
    }
}

// Inicializar Nivel 2
void MainWindow::initializeLevel2()
{
    setFixedSize(1380, 860);

    redBlocks.clear();
    for (int i = 0; i < 5; ++i) {
        Block block;
        block.x = rand() % width();
        block.y = rand() % height();
        block.dx = rand() % 5 + 1;
        block.dy = rand() % 5 + 1;
        block.isParabolic = rand() % 2;
        redBlocks.append(block);
    }

    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &MainWindow::updatePositions);
    updateTimer->start(10);
}

void MainWindow::updatePositions()
{
    if (currentLevel != 2) return;

    for (Block &block : redBlocks) {
        block.x += block.dx;
        block.y += block.dy;

        if (block.isParabolic) {
            block.dy += 1; // efecto parabólico
        }

        if (block.x < 0 || block.x + redBlockSize > width()) {
            block.dx = -block.dx;
        }
        if (block.y < 0 || block.y + redBlockSize > height()) {
            block.dy = -block.dy;
        }
    }

    QRect blueBlock(x + 30, height() - blockSize - 30, blockSize, blockSize);
    for (const Block &block : redBlocks) {
        QRect redBlock(block.x, block.y, redBlockSize, redBlockSize);
        if (blueBlock.intersects(redBlock)) {
            attemptsLeft--;
            if (attemptsLeft <= 0) {
                endGame();
                return;
            }
            resetBlueBlock();
        }
    }

    update();
}

bool MainWindow::checkCollision(const Block &block)
{
    QRect blueBlock(x + 30, height() - blockSize - 30, blockSize, blockSize);
    QRect redBlock(block.x, block.y, redBlockSize, redBlockSize);
    return blueBlock.intersects(redBlock);
}

void MainWindow::resetBlueBlock()
{
    x = 0;
    update();
}

void MainWindow::endGame()
{
    QMessageBox::information(this, "Game Over", "Has perdido todos tus intentos!");
    QApplication::quit();
}

// Inicializar Nivel 3
void MainWindow::initializeLevel3()
{
    setFixedSize(1380, 860);

    for (int i = 0; i < 5; ++i) {
        int blockX = 50 + i * 180;
        yellowBlocks.append(QRect(blockX + 100, 750, 50, 50));
    }

    blockTimer = new QTimer(this);
    connect(blockTimer, &QTimer::timeout, this, &MainWindow::addBlock);
    blockTimer->start(1000);

    yellowBlockTimer = new QTimer(this);
    connect(yellowBlockTimer, &QTimer::timeout, this, &MainWindow::moveYellowBlocks);
    yellowBlockTimer->start(50);
}

void MainWindow::addBlock()
{
    if (currentLevel != 3) return;

    int blockX = QRandomGenerator::global()->bounded(0, width() - 50);
    blocks.append(QRect(blockX, 0, 50, 50));
    totalBlocksGenerated++;
    update();
}

void MainWindow::moveYellowBlocks()
{
    if (currentLevel != 3) return;

    for (QRect &block : yellowBlocks) {
        block.moveTop(block.top() - 10);
        if (block.top() < 0) {
            block.moveTop(height());
        }
    }
    update();
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    if (currentLevel == 1) {
        painter.setBrush(Qt::blue);
        painter.drawRect(player->rect());
    } else if (currentLevel == 2) {
        painter.setBrush(Qt::blue);
        painter.setPen(Qt::blue);
        painter.drawRect(x + 30, height() - blockSize - 30, blockSize, blockSize);

        painter.setBrush(Qt::red);
        painter.setPen(Qt::red);
        for (const Block &block : redBlocks) {
            painter.drawRect(block.x, block.y, redBlockSize, redBlockSize);
        }
    } else if (currentLevel == 3) {
        painter.setBrush(Qt::blue);
        painter.setPen(Qt::blue);
        painter.drawRect(x, y, 50, 50);

        painter.setBrush(Qt::red);
        painter.setPen(Qt::red);
        for (const QRect &block : blocks) {
            painter.drawRect(block);
        }

        painter.setBrush(Qt::yellow);
        painter.setPen(Qt::yellow);
        for (const QRect &block : yellowBlocks) {
            painter.drawRect(block);
        }
    }
}
