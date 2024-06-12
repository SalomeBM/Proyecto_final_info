#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QInputDialog>
#include <QRandomGenerator>
#include <QMessageBox>
#include <QPainter>
#include <QKeyEvent>
#include <QList>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void movePlayer();
    void checkCollisions();
    void onJumpButtonPressed();
    void onJumpButtonReleased();
    void updatePositions();
    void addBlock();
    void moveYellowBlocks();

private:
    Ui::MainWindow *ui;

    // Nivel 1
    QGraphicsScene *scene = nullptr;
    QGraphicsRectItem *player = nullptr;
    QList<QGraphicsRectItem*> obstacles;
    QTimer *timer = nullptr;
    int playerLives;
    bool isJumping;
    int jumpHeight;
    const int jumpSpeed;
    const int jumpMaxHeight;
    const int playerSpeed;
    int originalPlayerY;

    // Nivel 2
    struct Block {
        int x, y, dx, dy;
        bool isParabolic;
    };
    QList<Block> redBlocks;
    QTimer *updateTimer = nullptr;
    int x, y;
    const int blockSize = 50;
    const int redBlockSize = 50;
    const int stepSize = 20;
    int attemptsLeft;

    // Nivel 3
    QList<QRect> blocks;
    QList<QRect> yellowBlocks;
    QTimer *blockTimer = nullptr;
    QTimer *yellowBlockTimer = nullptr;
    int totalBlocksGenerated;

    // General
    int currentLevel;

    void initializeLevel1();
    void initializeLevel2();
    void initializeLevel3();
    void centerOnPlayer();
    void resetBlueBlock();
    void endGame();
    bool checkCollision(const Block &block);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // MAINWINDOW_H
