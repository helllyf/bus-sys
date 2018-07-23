#ifndef BUS_SER_SYS_H__
#define BUS_SER_SYS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <map>
#include "mxml.h"
#include "c_socket.h"
using namespace std;

//调试打印
#define plog(fmt,args...) \
do \
{                  \
    time_t now = time(NULL); \
    tm *cur = localtime(&now);  \
	printf("\n%02d:%02d:%02d->[%s %d]:"fmt"\n",cur->tm_hour,cur->tm_min, \
	cur->tm_sec,__func__,__LINE__,##args);  \
	fflush(0); \
}while(0);


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

// 保存xml 信息,即公交线路信息
struct bus_Xianlu
{
	int xbus;
	vector<string> vecStations;
	char stations[30][64];
};

//为推荐路线定义的结构体
struct bus_xianlu_tuijian
{
	int start_bus_id;
	int end_bus_id;
	char bus_public[64];
};

typedef struct _ser_bus_tuijian_msg
{
	struct bus_xianlu_tuijian bus_xl_tj[3];
}ser_bus_tuijian_msg_t;

void LoadXml(void);

// 搜索符合条件的公交线路
void search_bus_xianlu (const char *start_station, const char *end_station);

void pth_mutex_init ();

void pth_mutex_destroy ();

void* cli_process(void *arg);


#endif //BUS_SER_SYS_H__

