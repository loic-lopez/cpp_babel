#include "loginWindow.h"
#include "ui_loginWindow.h"

loginWindow::loginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginWindow)
{
    ui->setupUi(this);
    this->setFixedSize(338, 234);
    this->ui->passwordLine->setEchoMode(QLineEdit::Password);
    this->ui->passwordLine->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText);
    chatWin = new chatGUI;
    connect(chatWin, &chatGUI::disconnect, this, &loginWindow::show);
}

loginWindow::~loginWindow()
{
    delete ui;
}

void loginWindow::on_cancel_clicked()
{
    this->close();
    emit toLogin();
}

void loginWindow::on_confirm_clicked()
{
    std::cout << ui->loginLine->text().toStdString() << std::endl;
    std::cout << ui->passwordLine->text().toStdString() << std::endl;
    chatWin->show();
    this->close();
}
