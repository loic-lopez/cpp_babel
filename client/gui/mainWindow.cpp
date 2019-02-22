#include "mainWindow.h"
#include "ui_mainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(400, 300);
    registerWin = new registerWindow;
    loginWin = new loginWindow;

    connect(registerWin, &registerWindow::toRegister, this, &MainWindow::show);
    connect(loginWin, &loginWindow::toLogin, this, &MainWindow::show);
    }

MainWindow::~MainWindow()
{
    delete ui;
    delete registerWin;
    delete loginWin;
}

void MainWindow::on_logInButton_clicked()
{
    loginWin->show();
    this->close();
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_registerButton_clicked()
{
    registerWin->show();
    this->close();
}
