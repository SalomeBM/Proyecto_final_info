#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Qlabel->setText("Invasion Ucrania");
}

MainWindow::~MainWindow()
{
    delete ui;
}
