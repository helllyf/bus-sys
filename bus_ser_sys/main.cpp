#include <stdio.h>
#include <stdlib.h>
#include "bus_ser_sys.h"

int main()
{
    int s_sid,c_sid;
    pthread_t tid;
	pth_mutex_init();
	
	//加载所有公交线路，即xml文件
	LoadXml ();

    // 创建服务器监听套接字
    s_sid = socket_set_server (2345,10);

    while(1)
    {
        plog("accept--->");
        c_sid = socket_accept(s_sid);
        if(c_sid > 0)
        {
            if(pthread_create(&tid,NULL,cli_process,(void *)&c_sid) != 0)
            {
				
            }
        }
    }

	pth_mutex_destroy();

	return 0;
}

