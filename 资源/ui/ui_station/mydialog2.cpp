#include "mydialog2.h"
#include "ui_mydialog2.h"
#include <QtNetwork>

MyDIalog2::MyDIalog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDIalog2)
{
    receiver = new QUdpSocket(this);
    receiver->bind(45454, QUdpSocket::ShareAddress);
    connect(receiver, SIGNAL(readyRead()), this, SLOT(processPendingDatagram()));
    ui->setupUi(this);
    ui->LineEdit->setText(QObject::tr("东街口"));
    ui->LineEdit_2->setText(QObject::tr("22"));
}

MyDIalog2::~MyDIalog2()
{
    delete ui;
}

void MyDIalog2::processPendingDatagram()
{
    // 拥有等待的数据报
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        // 让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        datagram.resize(receiver->pendingDatagramSize());
        // 接收数据报，将其存放到datagram中
        receiver->readDatagram(datagram.data(), datagram.size());

        ui->LineEdit_3->setText(datagram.data());
    }
}
