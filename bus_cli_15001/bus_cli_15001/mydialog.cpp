#include "mydialog.h"
#include "ui_mydialog.h"
#include "led_public.h"
#include "LedUtils.h"
#include "packet.h"
#include "system.h"
#include "uart.h"
#include "convert.h"
#include "c_socket.h"
#include <stdio.h>
#include <QFile>
#include <QtXml>
#include <QProcess>
#include <QDebug>
#include <QtNetwork>
#include <vector>
using namespace std;

// 消息定义
typedef enum CMD
{
    CMD_SEND_CUR_STATION,
    CMD_SEND_CUR_STATION_REP,
    CMD_GET_BUS_POSITION,
    CMD_GET_BUS_POSITION_REP,
    CMD_EXIT_ERASE_DATA,
    CMD_EXIT_ERASE_DATA_REP,
    CMD_GET_BUS_XIANLU,
    CMD_GET_BUS_XIANLU_REP
} CMD_T;

// 公交信息
typedef struct bus_info
{
    CMD_T cmd;
    char cur_station[256];
    int bus_number;
    int bus_ID;
    char start_station[64];
    char end_station[64];
} bus_info_t;

// save bus position
static vector <string> g_vec_bus_position;

int number=0;
int count_station=0;
int which_way=0;
int shangxing_count=0;
int xiaxing_count=0;

vector<string> vecStation;

char CardHost[16] = "172.28.53.45";

static void command_process (QString curstation);
static int check_number ();

void doprint(BYTE* buffer, DWORD size)
{
    /////////////////////////////////////////////////////////////////////////////////////////////
    DWORD i;
    //´󓡽ۄ¿˽¾ݺͽṹ
    //SaveToFile();
    //printf("-------------   Дʾ˽¾۠  -------------\n");
    qDebug()<<"-------------   Дʾ˽¾۠  -------------";
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

    //====·¢̍ǰʼ°�
    size=DoBeginPacket(buffer, 0);
    SocketWrite(s, buffer, size, CardHost, 6666);
    usleep(100);
    size=SocketRead(s, buffer, 6144, ip, &port);
    if (size>0) printf("==>ǰʼ°�ɹ¦\n\n"); else printf("==>ǰʼ°�¬ʱ\n\n");

    //====·¢̍˽¾ݰ�
    K=GetDataPacketCount(stream);

    for (i=1; i<=K; i++)
    {
        size=DoDataPacket(stream, i, buffer, 0);
        SocketWrite(s, buffer, size, CardHost, 6666);
        usleep(100);
        size=SocketRead(s, buffer, 6144, ip, &port);
        if (size>0) printf("==>˽¾ݰ�̍³ɹ¦\n\n", i); else printf("==>˽¾ݰ�̍³¬ʱ\n\n", i);
    }

    //====·¢̍½⋸°�
    size=DoEndPacket(buffer, K+1, 0);
    SocketWrite(s, buffer, size, CardHost, 6666);
    usleep(100);
    size=SocketRead(s, buffer, 6144, ip, &port);
    if (size>0) printf("==>½⋸°�ɹ¦\n"); else printf("==>½⋸°�¬ʱ\n");

    CloseSocket(s);
}

void net_demo_string(char *str)
{
    BYTE stream[65536];
    //char str[]="中文123ADC";

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
    QFont font;
    font.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
    font.setPointSize(12);
    font.setBold(false);
    font.setUnderline(false);
    font.setWeight(50);
    font.setKerning(true);
    ui->listWidget->setFont(font);

    QFile file("bus_150.xml");
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
    /* init xiaxing  */
    xiaxing_count++;

    qDebug() << "vector";
    vector<string>::iterator itvec;
    for (itvec=vecStation.begin(); itvec!=vecStation.end(); itvec++)
    {
        QString str = itvec->c_str ();
        qDebug()<<str;
    }
    // connect service
    c_sid = socket_connect("127.0.0.1",2345);
    if(c_sid < 0)
    {
        qDebug() << "connect error";
        return;
    }
}

MyDialog::~MyDialog()
{
    delete ui;
}

/* 进入设置界面 */
void MyDialog::on_pushButton_clicked()
{
    accept();
}

/* 下行 */
void MyDialog::on_pushButton_8_clicked()
{
    if (xiaxing_count == 0)
    {
        qDebug() << "nihaode";
        if (number == -1)
        {
            ui->label_2->setText(tr ("下行"));
            which_way = 0;
            number++;
        }
    }
    xiaxing_count++;
    return ;
}

/* 上行 */
void MyDialog::on_pushButton_5_clicked()
{
    if (shangxing_count == 0)
    {
        qDebug() << "shang xing";
        if (number == count_station)
        {
            ui->label_2->setText(tr ("上行"));
            which_way = 1;
            number--;
        }
    }
    shangxing_count++;
    return ;
}

/* call station */
void MyDialog::on_pushButton_4_clicked()
{
    if (check_number() == 1)
        return ;

    qDebug() << number << "number";
    // 清空
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
    // led and music
    command_process(curstation);

    // send to service
    cli_send_to_ser(curstation);

    if (check_number() == 1)
        return ;
}

void MyDialog::cli_send_to_ser (QString curstation)
{
    bus_info_t cli_send_msg;
    cli_send_msg.cmd = CMD_SEND_CUR_STATION;
    cli_send_msg.bus_number = 150;
    cli_send_msg.bus_ID = 15001;
    memcpy(cli_send_msg.cur_station, curstation.toStdString().c_str(), 256);
    int ret;
    // send to service;
    socket_write(c_sid, &cli_send_msg, sizeof (cli_send_msg));

    //wait service reply
    ret = socket_read(c_sid, &cli_send_msg, sizeof (cli_send_msg));
    if (ret <=0)
    {
        socket_close(c_sid);
        qDebug() << "ser error!";
        ui->label_3->setText(tr ("发送失败"));
        return ;
    }
    ui->label_3->setText(tr ("发送成功"));
    return ;
}

int  check_number ()
{
    if ((count_station) == number || number == -1)
    {
        shangxing_count=0;
        xiaxing_count=0;
        return 1;
    }
    return 0;
}

void command_process (QString curstation)
{
    QString command;
    QString next_station;
    int next_station_number;
    if (xiaxing_count >= 1)
    {
        next_station_number = number+1;
    }
    else
    {
        next_station_number = number-1;
    }
    vector<string>::iterator itvec;
    int i;
    for (itvec=vecStation.begin(), i=0; itvec!=vecStation.end(); itvec++, i++)
    {
        if (next_station_number == i)
        {
            next_station = itvec->c_str ();
        }
    }
    if (number == 0)
    {
        // start station
        if (next_station_number != -1)
            command =  curstation + _config_1()+ _config_2() + next_station;
        // start station turn end station
        else
            command =  curstation + _config_3();
    }
    else if (number != (count_station-1))
    {
        command =  curstation + _config_1() + "  " + _config_2() + next_station ;
    }
    else if (number == (count_station-1))
    {
        // end station turn start station
        if (next_station_number != (number+1))
            command =  curstation + _config_1()+ _config_2() + next_station;
        // end station
        else
            command =  curstation + _config_3();
    }

    qDebug()<<command;
    /* yuying */
 //    tts_open_test("/dev/ttyUSB0", (char *)command.toStdString().c_str());
    /* net_demo_string */
    /* string shuld be utf-8 */
 //    net_demo_string((char *)command.toStdString().c_str());
    //qDebug()<<"net_demo_string";

    /* count station number */
    if (which_way == 0)
    {
        number++;
    }
    else
    {
        number--;
    }
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

void MyDialog::on_exit_button_clicked()
{
    bus_info_t cli_send_msg;
    cli_send_msg.cmd = CMD_EXIT_ERASE_DATA;
    cli_send_msg.bus_ID = 15001;
    int ret;
    // send to service;
    socket_write(c_sid, &cli_send_msg, sizeof (cli_send_msg));

    //wait service reply
    ret = socket_read(c_sid, &cli_send_msg, sizeof (cli_send_msg));
    if (ret <=0)
    {
        socket_close(c_sid);
        qDebug() << "ser error!";
        ui->label_3->setText(tr ("发送失败"));
        return ;
    }
    ui->label_3->setText(tr ("发送成功"));
    return ;
}
