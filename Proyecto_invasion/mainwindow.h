#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QTimer>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
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

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *player;
    QTimer *timer;
    QList<QGraphicsRectItem *> obstacles;
    int playerLives;
    bool isJumping;
    qreal jumpHeight;
    qreal jumpSpeed;
    qreal jumpMaxHeight; // Altura máxima del salto
    qreal originalPlayerY; // Posición original en Y del jugador
};

#endif // MAINWINDOW_H
