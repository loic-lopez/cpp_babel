#include "chatGUI.h"
#include "ui_chatGUI.h"

chatGUI::chatGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chatGUI)
{
    ui->setupUi(this);
}

chatGUI::~chatGUI()
{
    delete ui;
}

void chatGUI::on_disconnectButton_clicked()
{
    this->close();
    emit disconnect();
}

void chatGUI::on_addContactButton_clicked()
{

}
