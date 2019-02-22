#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QDialog>
#include <iostream>
#include "chatGUI.h"

namespace Ui {
class registerWindow;
}

class registerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit registerWindow(QWidget *parent = 0);
    ~registerWindow();

signals:
    void toRegister();

private slots:

    void on_cancelButton_clicked();

    void on_proceedButton_clicked();

private:
    Ui::registerWindow *ui;
    chatGUI *chatWin;
};

#endif // REGISTERWINDOW_H
