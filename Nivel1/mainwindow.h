#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void movePlayer();
    void checkCollisions();
    void onJumpButtonPressed();
    void onJumpButtonReleased();
    void centerOnPlayer();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *player;
    QList<QGraphicsRectItem*> obstacles;
    QTimer *timer;
    int playerLives;
    bool isJumping;
    int jumpHeight;
    int jumpSpeed;
    int jumpMaxHeight;
    int playerSpeed = 5;
    int originalPlayerY;
};

#endif // MAINWINDOW_H
