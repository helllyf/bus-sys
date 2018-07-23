#include "mydialog.h"
#include "ui_mydialog.h"
#include "led_public.h"
#include "LedUtils.h"
#include "packet.h"
#include "system.h"
#include "uart.h"
#include "convert.h"
#include <stdio.h>
#include <QFile>
#include <QtXml>
#include <QProcess>
#include <QDebug>
#include <QtNetwork>
#include <vector>
using namespace std;

int number=0;
int count_station=0;
int gflag=0;
int which_way=0;

vector<string> vecStation;

char CardHost[16] = "172.28.53.45";

void doprint(BYTE* buffer, DWORD size)
{
    /////////////////////////////////////////////////////////////////////////////////////////////
    DWORD i;
    //打印节目数据和结构
    //SaveToFile();
    //printf("-------------   显示数据   -------------\n");
    qDebug()<<"-------------   显示数据   -------------";
    for (i=1; i<=size; i++)
    {
        //printf("0x%02x,", buffer[i-1]);
        qDebug()<<"0x"<<buffer[i-1];

        if ((i % 36)==0)
            //printf(" ");
            qDebug()<<" ";
        if ((i % 16)==0)
            //printf("\n");
            qDebug()<<"\n";
    }
    //printf("\n----------------------------------------\n");
    qDebug()<<"----------------------------------------";
    /////////////////////////////////////////////////////////////////////////////////////////////
}

void net_send(BYTE* stream)
{
    DWORD size;
    BYTE buffer[6144];
    SOCKET s;
    DWORD i, K;
    char ip[16];
    WORD port;

    s=InitSocket(9011);

    //====发送起始包====
    size=DoBeginPacket(buffer, 0);
    SocketWrite(s, buffer, size, CardHost, 6666);
    usleep(100);
    size=SocketRead(s, buffer, 6144, ip, &port);
    if (size>0) printf("==>起始包发送成功\n\n"); else printf("==>起始包发送超时\n\n");

    //====发送数据包====
    K=GetDataPacketCount(stream);

    for (i=1; i<=K; i++)
    {
        size=DoDataPacket(stream, i, buffer, 0);
        SocketWrite(s, buffer, size, CardHost, 6666);
        usleep(100);
        size=SocketRead(s, buffer, 6144, ip, &port);
        if (size>0) printf("==>数据包%lu发送成功\n\n", i); else printf("==>数据包%lu发送超时\n\n", i);
    }

    //====发送结束包====
    size=DoEndPacket(buffer, K+1, 0);
    SocketWrite(s, buffer, size, CardHost, 6666);
    usleep(100);
    size=SocketRead(s, buffer, 6144, ip, &port);
    if (size>0) printf("==>结束包发送成功\n"); else printf("==>结束包发送超时\n");

    CloseSocket(s);
}

void net_demo_string(char *str)
{
    BYTE stream[65536];
    //char str[]="中文123abABCCC";

    MakeRoot(stream);
    AddChapter(0x7fffffff, PLAY_MODE_WAIT);
    AddRegion(0, 0, 192, 80);
    AddLeaf(1000, PLAY_MODE_WAIT);
    AddStrings(0, 0, 64, 16, 1);
    AddChildString(str, FONT_SET_16, 0x00ff, 2, 0, 0, 0, 0, 0, 5000);

    doprint((BYTE*)stream, root->size);

    net_send(stream);
}

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    number = 0;
    vecStation.clear();

    ui->setupUi(this);
    /**/
    ui->listWidget->clear();
    QFile file("bus_.xml");
    if (!file.open(QIODevice::ReadOnly)) return ;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();

    QString curstation;
    QDomElement docElem = doc.documentElement();
    int flag=0,nn=0;
    QDomNode n = docElem.firstChild();
    while(!n.isNull())
    {
        if (n.isElement())
        {
            QDomElement e = n.toElement();

            QDomNodeList list = e.childNodes();
            if (flag == 1)
            {
                for(int i=0; i<list.count(); i++)
                {
                    QDomNode node = list.at(i);
                    if(node.isElement())
                    {
                        if (nn++ == 0)
                        {
                            ui->listWidget->addItem(new QListWidgetItem(QIcon("yuan.jpg"), node.toElement().text()));
                            curstation = node.toElement().text();
                            vecStation.push_back(curstation.toStdString());
                        }else
                        {
                            ui->listWidget->addItem("           " + node.toElement().text());
                            curstation = node.toElement().text();
                            vecStation.push_back(curstation.toStdString());
                        }
                    }
                }
            }
            else
            {
                QDomNode node_count = list.at(0);
                count_station = node_count.toElement().text().toInt();
                //qDebug()<<count;
            }
            flag++;
        }
        n = n.nextSibling();
    }

    qDebug() << "vector";
    vector<string>::iterator itvec;
    for (itvec=vecStation.begin(); itvec!=vecStation.end(); itvec++)
    {
        QString str = itvec->c_str ();
        qDebug()<<str;
    }

}

MyDialog::~MyDialog()
{
    delete ui;
}

/* 进入主界面时，转到槽，产生的代码 */
void MyDialog::on_pushButton_clicked()
{
    accept();
}

#if 0
/* 下一站 */
void MyDialog::on_pushButton_8_clicked()
{
    gflag = 0;
    // 先清空显示
    ui->listWidget->clear();
    QFile file("bus_.xml");
    if (!file.open(QIODevice::ReadOnly)) return ;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomElement c;
    QString curstation;

    int flag=0, count=0;
    QDomNode n = docElem.firstChild();

    while(!n.isNull())
    {
        if (n.isElement())
        {
            QDomElement e = n.toElement();

            QDomNodeList list = e.childNodes();
            if (flag == 1)
            {
                for(int i=0; i<list.count(); i++)
                {
                    QDomNode node = list.at(i);
                    if(node.isElement())
                    {
                        if (i == number)
                        {   qDebug()<<number;
                            ui->listWidget->addItem(new QListWidgetItem(QIcon("yuan.jpg"), node.toElement().text()));
                            curstation = node.toElement().text();
                            qDebug()<<"next station"<<curstation;
                        }
                        else{
                            ui->listWidget->addItem("           " + node.toElement().text());
                        }
                    }
                }
            }
            else
            {
                QDomNode node_count = list.at(0);
                count = node_count.toElement().text().toInt();
                //qDebug()<<count;
            }

            flag++;
        }
        n = n.nextSibling();
    }
    //char command[256] = {0};
    QString command;
    command = _config_2() + curstation ;
    qDebug()<<command;
    /* yuying */
    //    tts_open_test("/dev/ttyUSB0", (char *)command.toStdString().c_str());
    /* net_demo_string */
    /* string shuld be utf-8 */
    //    net_demo_string((char *)command.toStdString().c_str());
    qDebug()<<"net_demo_string";
    /* maybe change */
    if (count == number)
    {
        return ;
    }
    number++;
}
#endif //0

/* xia xing */
void MyDialog::on_pushButton_8_clicked()
{
   qDebug() << "nihaode ";
    which_way = 0;
}

/* 上一站 */
void MyDialog::on_pushButton_5_clicked()
{
    which_way = 1;
}

#if 0
/* call station */
void MyDialog::on_pushButton_4_clicked()
{
    // 先清空显示
    //ui->listWidget->clear();
    QFile file("bus_.xml");
    if (!file.open(QIODevice::ReadOnly)) return ;
    QDomDocument doc;
    if (!doc.setContent(&file))
    {
        file.close();
        return ;
    }
    file.close();

    QDomElement docElem = doc.documentElement();
    QDomElement c;
    QString curstation;

    int flag=0, count=0, cur_number=number-1;
    if (gflag == 1)
    {
        cur_number=number;
    }
    QDomNode n = docElem.firstChild();

    while(!n.isNull())
    {
        if (n.isElement())
        {
            QDomElement e = n.toElement();

            QDomNodeList list = e.childNodes();
            if (flag == 1)
            {
                for(int i=0; i<list.count(); i++)
                {
                    QDomNode node = list.at(i);
                    if(node.isElement())
                    {
                        if (i == cur_number)
                        {   qDebug()<<"current station "<<number;
                            //ui->listWidget->addItem(new QListWidgetItem(QIcon("yuan.jpg"), node.toElement().text()));
                            curstation = node.toElement().text();
                            qDebug()<<curstation;
                        }
                        else{
                            //ui->listWidget->addItem("           " + node.toElement().text());
                        }
                    }
                }
            }
            else
            {
                QDomNode node_count = list.at(0);
                count = node_count.toElement().text().toInt();
                //qDebug()<<count;
            }

            flag++;
        }
        n = n.nextSibling();
    }
    QString command;
    command = curstation + _config_1();
    qDebug()<<command;
    if ((count == number) || (0 == number))
    {
        command = curstation + _config_3();
        qDebug()<<"ending"<<command;
    }
    qDebug()<<command;
    /* yuying */
    tts_open_test("/dev/ttyUSB0", (char *)command.toStdString().c_str());
    /* net_demo_string */
    /* string shuld be utf-8 */
    net_demo_string((char *)command.toStdString().c_str());
    qDebug()<<"current station  "<<"net_demo_string";
}
#endif //0

/* call station */
void MyDialog::on_pushButton_4_clicked()
{
    qDebug() << "nimeide";
    /* check number */
    if ((count_station-1) == number)
    {
        return ;
    }

    if (which_way == 0)
    {
        number++;
    }
    else
    {
        number--;
    }
    gflag = 0;
    // 先清空显示
    ui->listWidget->clear();


    QString curstation, tem_station;
    int i=0;
    vector<string>::iterator itvec;

    for (itvec=vecStation.begin(); itvec!=vecStation.end(); itvec++, i++)
    {
        if (number == i)
        {
            curstation = itvec->c_str ();
            ui->listWidget->addItem(new QListWidgetItem(QIcon("yuan.jpg"), curstation));
        }
        else
        {
            tem_station = itvec->c_str ();
            ui->listWidget->addItem("           " + tem_station);
        }
    }
    QString command;
    command = _config_2() + curstation ;
    qDebug()<<command;
    /* yuying */
    //    tts_open_test("/dev/ttyUSB0", (char *)command.toStdString().c_str());
    /* net_demo_string */
    /* string shuld be utf-8 */
    //    net_demo_string((char *)command.toStdString().c_str());
    qDebug()<<"net_demo_string";
}
/* offset */
void MyDialog::on_pushButton_6_clicked()
{
    char command[256] = {0};
    strcpy(command, _config_4());
    qDebug()<<command;
    /* yuying */
    tts_open_test("/dev/ttyUSB0", command);
    /* net_demo_string */
    /* string shuld be utf-8 */
    net_demo_string(command);
    qDebug()<<"offset "<<"net_demo_string";
}

/* protect */
void MyDialog::on_pushButton_7_clicked()
{
    char command[256] = {0};
    strcpy(command, _config_5());
    qDebug()<<command;
    /* yuying */
    tts_open_test("/dev/ttyUSB0", command);
    /* net_demo_string */
    /* string shuld be utf-8 */
    net_demo_string(command);
    qDebug()<<"protect "<<"net_demo_string";
}
