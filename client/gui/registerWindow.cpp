#include "registerWindow.h"
#include "ui_registerWindow.h"

registerWindow::registerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::registerWindow)
{
    ui->setupUi(this);
    this->setFixedSize(454, 317);
    this->ui->passwordLine->setEchoMode(QLineEdit::Password);
    this->ui->passwordLine->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText);
    this->ui->confirmPasswordLine->setEchoMode(QLineEdit::Password);
    this->ui->confirmPasswordLine->setInputMethodHints(Qt::ImhHiddenText|Qt::ImhNoAutoUppercase|Qt::ImhNoPredictiveText);
    chatWin = new chatGUI;
    connect(chatWin, &chatGUI::disconnect, this, &registerWindow::show);
}

registerWindow::~registerWindow()
{
    delete ui;
}

void registerWindow::on_cancelButton_clicked()
{
    this->close();
    emit toRegister();
}

void registerWindow::on_proceedButton_clicked()
{
    std::cout << ui->usernameLine->text().toStdString() << std::endl;
    std::cout << ui->passwordLine->text().toStdString() << std::endl;
    std::cout << ui->confirmPasswordLine->text().toStdString() << std::endl;
    std::cout << ui->nicknameLine->text().toStdString() << std::endl;
    chatWin->show();
    this->close();
}
