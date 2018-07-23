#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <vector>
#include "c_socket.h"
#include <string.h>
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
    CMD_TAKE,
    CMD_TAKE_REP,
    CMD_EVALUATION,
    CMD_EVALUATION_REP,
    CMD_GET_CALL,
    CMD_CALL_REP
} CMD_T;

// 消息载体
typedef struct genmsg
{
    CMD_T cmd;
    char content[1000];
} genmsg_t;




typedef struct evaluation
{
    char buf[255];
} evaluation_t;


// 服务窗口定义
typedef struct serice
{
    int c_service_sid;
    // 评价链表
    vector<evaluation_t>  evalu_list;
} service_t;




pthread_mutex_t g_mutex;
static int  g_num_generate = 0;
vector<int> g_call_list;
vector<int> g_call_vip_list;
char cur_station[256] = {0};




void* cli_process(void *arg)
{
    int c_sid = *(int*)arg;
    genmsg_t msg,msg_rep;
    int ret;


    while(1)
    {
        plog("wait");
		/* 读取客户端的请求 */
        ret = socket_read(c_sid,&msg,sizeof(msg));
        plog("wait end--->");
        if(ret <= 0)
        {
            close(c_sid);
            return NULL;
        }

        switch(msg.cmd)
        {
        	/* CMD_TAKE 可改为CMD_SEND 发送公交所在位置 */
            case CMD_TAKE:
            {
                msg_rep.cmd = CMD_TAKE_REP;
                // 生成号码
                pthread_mutex_lock(&g_mutex);
				memset (cur_station, 0, 256);
				memcpy (cur_station, msg.content, 1000);
			/* 以下就是数据处理部分 */	
                g_num_generate++;
                g_call_list.push_back(g_num_generate);
                //memcpy(msg_rep.content,&g_num_generate,sizeof(g_num_generate));
                pthread_mutex_unlock(&g_mutex);
                socket_write(c_sid,&msg_rep,sizeof(msg_rep));

            }
            break;
            case CMD_EVALUATION:
                break;

            case CMD_GET_CALL:
            {
				msg_rep.cmd = CMD_CALL_REP;
                pthread_mutex_lock(&g_mutex);
                if(g_call_list.size() > 0)
                {
                    vector<int>::iterator it = g_call_list.begin();
                    //*(int *)(msg_rep.content) = *it;
					memcpy (msg_rep.content, cur_station, 1000);
                    socket_write(c_sid,&msg_rep,sizeof(msg_rep));
                    g_call_list.erase(it);
                }
                pthread_mutex_unlock(&g_mutex);

            }
            break;
        }

    }

}




int main()
{
    int s_sid,c_sid;
    pthread_t pid;
    // 创建服务器监听套接字
    s_sid = socket_set_server(2345,10);

    pthread_mutex_init(&g_mutex,NULL);

    while(1)
    {
        plog("accept--->");
        c_sid = socket_accept(s_sid);
        if(c_sid > 0)
        {
            if(pthread_create(&pid,NULL,cli_process,(void *)&c_sid) != 0)
            {

            }
        }

    }


    pthread_mutex_destroy(&g_mutex);


}
