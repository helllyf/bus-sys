#include "user_widget.h"
#include "ui_user_widget.h"
#include "c_socket.h"
#include <string.h>
#include <string>
#include <vector>
#include <QDebug>
using namespace std;

// 消息定义
typedef enum CMD
{
    CMD_SEND_CUR_STATION,
    CMD_SEND_CUR_STATION_REP,
    CMD_GET_BUS_POSITION,
    CMD_GET_BUS_POSITION_REP
} CMD_T;

// 公交信息
typedef struct bus_info
{
    CMD_T cmd;
        char cur_station[256];
        int bus_number;
        int bus_ID;
} bus_info_t;

// save bus position
static vector <string> g_vec_bus_position;

// 某路公交的所在位置,假设该路公交最多不超过50量
static char all_xbus_position[50][64] = {0};

user_widget::user_widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::user_widget)
{
    ui->setupUi(this);

    c_sid = socket_connect("127.0.0.1",2345);
    if(c_sid < 0)
    {
        qDebug() << "connect error";
        return;
    }
}

user_widget::~user_widget()
{
    delete ui;
}

void user_widget::on_enter_clicked()
{
    listwidget_init();
    bus_info_t cli_send_msg;
    char buffer[256]= {0};
    cli_send_msg.cmd = CMD_GET_BUS_POSITION;
    QString str = ui->lineEdit->text();
    cli_send_msg.bus_number = str.toInt();

    int ret;
    // 发给服务器
    socket_write(c_sid,&cli_send_msg,sizeof(cli_send_msg));
    // 等待服务的应答
    memset (&cli_send_msg, 0, sizeof (cli_send_msg));
    memset (all_xbus_position, 0, sizeof (all_xbus_position));
    ret = socket_read(c_sid,all_xbus_position, sizeof (all_xbus_position));
    if(ret <= 0)
    {
        socket_close(c_sid);
        qDebug() << "ser error\n";
    }
    int i;

    for (i=0; i<50; i++)
    {
       if (all_xbus_position[i][0] == 0)
           break;
       char cur_station[64]={0};
       memcpy (cur_station, all_xbus_position[i], 64);
       ui->listWidget->addItem("    " + str + "    " + cur_station);
    }
}

void user_widget::listwidget_init ()
{
    ui->listWidget->clear();
    QFont font;
    font.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
    font.setPointSize(15);
    font.setBold(false);
    font.setUnderline(false);
    font.setWeight(50);
    font.setKerning(true);
    ui->listWidget->setFont(font);
}
