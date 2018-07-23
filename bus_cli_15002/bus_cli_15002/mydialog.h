#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>
#include "LedUtils.h"
#include "packet.h"
#include "system.h"
#include "uart.h"

class QUdpSocket;

namespace Ui {
    class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = 0);
    ~MyDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void cli_send_to_ser (QString curstation);

    void on_exit_button_clicked();

private:
    Ui::MyDialog *ui;
    QUdpSocket *sender;
public:
    int c_sid;
};

#endif // MYDIALOG_H
