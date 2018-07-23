#include "user_app.h"
#include "ui_user_app.h"
#include "c_socket.h"
#include <string.h>
#include <string>
#include <vector>
#include <QDebug>
using namespace std;

// message define
typedef enum CMD
{
    CMD_SEND_CUR_STATION,
    CMD_SEND_CUR_STATION_REP,
    CMD_GET_METRO_POSITION,
    CMD_GET_METRO_POSITION_REP,
    CMD_EXIT_ERASE_DATA,
    CMD_EXIT_ERASE_DATA_REP,
    CMD_GET_METRO_XIANLU,
    CMD_GET_METRO_XIANLU_REP
} CMD_T;

// metro message
typedef struct metro_info
{
    CMD_T cmd;
    char cur_station[256];
    int metro_number;
    int metro_ID;
    char start_station[64];
    char end_station[64];
} metro_info_t;

//为推荐路线定义的结构体
struct metro_xianlu_tuijian
{
    int start_metro_id;
    int end_metro_id;
    char metro_public[64];
};

typedef struct _ser_metro_tuijian_msg
{
    struct metro_xianlu_tuijian metro_xl_tj[3];
}ser_metro_tuijian_msg_t;

// 保存地铁的推荐信息
// exp 传入:起始终点站，返回推荐信息
static ser_metro_tuijian_msg_t ser_metro_tuijian_msg;

// save metro position
static vector <string> g_vec_metro_position;

// 某路地铁的所在位置,假设该路地铁最多不超过5量
static char all_xmetro_position[5][64] = {0};
user_app::user_app(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::user_app)
{
    ui->setupUi(this);

    c_sid = socket_connect("127.0.0.1",2345);
    if(c_sid < 0)
    {
        qDebug() << "connect error";
        return;
    }
}

user_app::~user_app()
{
    delete ui;
}

void user_app::on_pushButton_clicked()
{
    listwidget_init();
    metro_info_t cli_send_msg;

    cli_send_msg.cmd = CMD_GET_METRO_POSITION;
    QString str = ui->lineEdit->text();
    cli_send_msg.metro_number = str.toInt();

    int ret;
    // 发给服务器
    socket_write(c_sid,&cli_send_msg,sizeof(cli_send_msg));
    // 等待服务的应答
    memset (&cli_send_msg, 0, sizeof (cli_send_msg));
    memset (all_xmetro_position, 0, sizeof (all_xmetro_position));
    ret = socket_read(c_sid,all_xmetro_position, sizeof (all_xmetro_position));
    if(ret <= 0)
    {
        socket_close(c_sid);
        qDebug() << "ser error\n";
    }
    int i;

    for (i=0; i<5; i++)
    {
       if (all_xmetro_position[i][0] == 0)
           break;
       char cur_station[64]={0};
       memcpy (cur_station, all_xmetro_position[i], 64);
       ui->listWidget->addItem("    " + str + "    " + cur_station);
    }
}

void user_app::listwidget_init ()
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

void user_app::listwidget_2_init ()
{
    ui->listWidget_2->clear();
    QFont font;
    font.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
    font.setPointSize(15);
    font.setBold(false);
    font.setUnderline(false);
    font.setWeight(50);
    font.setKerning(true);
    ui->listWidget_2->setFont(font);
}

void user_app::on_search_bustton_clicked()
{
    listwidget_2_init();
    metro_info_t cli_send_msg;

    memset (&cli_send_msg, 0, sizeof (cli_send_msg));
    cli_send_msg.cmd = CMD_GET_METRO_XIANLU;
    QString start_station = ui->lineEdit_2 ->text();
    strcpy (cli_send_msg.start_station, start_station.toStdString().c_str());

    QString end_station = ui->lineEdit_3 ->text();
    strcpy (cli_send_msg.end_station, end_station.toStdString().c_str());
    qDebug() << cli_send_msg.start_station << "  " <<cli_send_msg.end_station;
    int ret;
    // 发给服务器
    socket_write(c_sid,&cli_send_msg,sizeof(cli_send_msg));
    // 等待服务的应答
    memset (&cli_send_msg, 0, sizeof (cli_send_msg));
    memset (&ser_metro_tuijian_msg, 0, sizeof (ser_metro_tuijian_msg));
    ret = socket_read(c_sid,&ser_metro_tuijian_msg, sizeof (ser_metro_tuijian_msg));
    qDebug() <<"READ ";
    if(ret <= 0)
    {
        socket_close(c_sid);
        qDebug() << "ser error\n";
    }
    char metro_start[10] = {0};
    char metro_end[10] = {0};
    sprintf (metro_start, "%d", ser_metro_tuijian_msg.metro_xl_tj[0].start_metro_id);
    sprintf (metro_end, "%d", ser_metro_tuijian_msg.metro_xl_tj[0].end_metro_id);
    if (ser_metro_tuijian_msg.metro_xl_tj[0].start_metro_id && ser_metro_tuijian_msg.metro_xl_tj[0].end_metro_id)
    {
        if (ser_metro_tuijian_msg.metro_xl_tj[0].start_metro_id != ser_metro_tuijian_msg.metro_xl_tj[0].end_metro_id)
        {
            ui->listWidget_2->addItem(" 步行至" + start_station + ", 乘坐" + metro_start + "号地铁, 到" +
                                      ser_metro_tuijian_msg.metro_xl_tj[0].metro_public + ",");
            QString chengzuo = "乘坐";
            ui->listWidget_2->addItem(chengzuo + metro_end + "号地铁,到" + end_station);
        }
        else
        {
            ui->listWidget_2->addItem(" 步行至" + start_station + ", 乘坐" + metro_start +
                                      "号地铁, 到" + end_station);
        }

    }
}
