#ifndef MainWindow_H
#define MainWindow_H

#include <QMainWindow>
#include "registerWindow.h"
#include "loginWindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_logInButton_clicked();

    void on_exitButton_clicked();

    void on_registerButton_clicked();

private:
    Ui::MainWindow *ui;
    registerWindow *registerWin;
    loginWindow *loginWin;
};

#endif // MainWindow_H
