#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QPainter>
#include <QWidget>
#include <QTimer>
#include <QRandomGenerator>
#include <QPixmap>
#include <QMessageBox>



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
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void showVictoryMessage();

private slots:
    void addBlock();
    void moveYellowBlocks();

private:
    Ui::MainWindow *ui;
    QPixmap background;
    int x, y; // Posición del bloque azul
    QVector<QRect> blocks; // Vector de bloques adicionales
    QVector<QRect> yellowBlocks; // Vector de bloques amarillos
    QTimer *blockTimer; // Temporizador para añadir bloques
    QTimer *yellowBlockTimer; // Temporizador para mover bloques amarillos
    int totalBlocksGenerated; // Contador de bloques generados
};

#endif // MAINWINDOW_H
