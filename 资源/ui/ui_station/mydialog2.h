#ifndef MYDIALOG2_H
#define MYDIALOG2_H

#include <QDialog>

class QUdpSocket;

namespace Ui {
    class MyDIalog2;
}

class MyDIalog2 : public QDialog
{
    Q_OBJECT

public:
    explicit MyDIalog2(QWidget *parent = 0);
    ~MyDIalog2();

private slots:
    void processPendingDatagram();

private:
    Ui::MyDIalog2 *ui;
    QUdpSocket *receiver;
};

#endif // MYDIALOG2_H
