#ifndef CHATGUI_H
#define CHATGUI_H

#include <QDialog>

namespace Ui {
class chatGUI;
}

class chatGUI : public QDialog
{
    Q_OBJECT

public:
    explicit chatGUI(QWidget *parent = 0);
    ~chatGUI();

signals:
    void disconnect();

private slots:

    void on_disconnectButton_clicked();
    void on_addContactButton_clicked();

private:
    Ui::chatGUI *ui;
};

#endif // CHATGUI_H
