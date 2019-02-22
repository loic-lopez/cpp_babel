#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include <iostream>
#include "chatGUI.h"

namespace Ui {
class loginWindow;
}

class loginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit loginWindow(QWidget *parent = 0);
    ~loginWindow();

signals:
    void toLogin();

private slots:
    void on_cancel_clicked();

    void on_confirm_clicked();

private:
    Ui::loginWindow *ui;
    chatGUI *chatWin;
};

#endif // LOGINWINDOW_H
