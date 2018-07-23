#include "bus_ser_sys.h"

static pthread_mutex_t g_mutex;

// ĳ·����������λ��,�����·������಻����50��
static char all_xbus_position[50][64] = {0};

// ����ÿ������������Ϣ
static map<int, bus_info_t> g_map_bus_info;

// �������й�����·��Ϣ
vector<bus_Xianlu> vecBusXianlu;

// ���湫�������Ƽ���Ϣ
// exp ����:��ʼ�յ�վ�������Ƽ���Ϣ
static ser_bus_tuijian_msg_t ser_bus_tuijian_msg;



static int bus_num_sort_save (bus_info_t *cli_send_msg);

static int save_bus_info (bus_info_t *cli_send_msg);

static int get_bus_info (int bus_number);

static int map_erase_data (int bus_ID);

static void debug_print_xbus_curstation ();

static void debug_print_map ();

void* cli_process(void *arg)
{
    int c_sid = *(int*)arg;
    bus_info_t cli_send_msg, ser_rep_msg;
    int ret;

    while(1)
    {
        plog("wait");
		/* ��ȡ�ͻ��˵����� */
        ret = socket_read(c_sid, &cli_send_msg, sizeof(cli_send_msg));
        plog("wait end--->");
		/* ��ȡʧ�ܹر� */
        if(ret <= 0)
        {
            close(c_sid);
            return NULL;
        }

		/* �жϿͻ��˷��͵����� */
        switch(cli_send_msg.cmd)
        {
            case CMD_SEND_CUR_STATION:
            {
                ser_rep_msg.cmd = CMD_SEND_CUR_STATION_REP;
        		/* ���浱ǰ������Ϣ */
                pthread_mutex_lock(&g_mutex);
                save_bus_info(&cli_send_msg);
                pthread_mutex_unlock(&g_mutex);
                debug_print_map();
                // ��Ҫ��ʾ�Ƿ���ճɹ�
                socket_write(c_sid,&ser_rep_msg,sizeof(ser_rep_msg));

            }
            break;
            case CMD_GET_BUS_POSITION:
            {
				ser_rep_msg.cmd = CMD_GET_BUS_POSITION_REP;
                pthread_mutex_lock(&g_mutex);
				get_bus_info(cli_send_msg.bus_number);
                socket_write(c_sid, all_xbus_position, sizeof (all_xbus_position));
                pthread_mutex_unlock(&g_mutex);
                debug_print_xbus_curstation();
				}
            break;
            case CMD_EXIT_ERASE_DATA:
            {
            	ser_rep_msg.cmd = CMD_EXIT_ERASE_DATA_REP;
				pthread_mutex_lock(&g_mutex);
				map_erase_data(cli_send_msg.bus_ID);
				pthread_mutex_unlock(&g_mutex);
				debug_print_map();
				// ��Ҫ��ʾ�Ƿ���ճɹ�
                socket_write(c_sid,&ser_rep_msg,sizeof(ser_rep_msg));
            }
            break;
            case CMD_GET_BUS_XIANLU:
            {
				ser_rep_msg.cmd = CMD_GET_BUS_XIANLU_REP;
				pthread_mutex_lock(&g_mutex);
				
				pthread_mutex_unlock(&g_mutex);
            }
            default:
            break;
        }

    }

}

// ���Դ�ӡ���й�������Ϣ,��map�е�����
void debug_print_map ()
{
	printf ("*****service all bus positions*****\n");
	map<int, bus_info_t>::iterator itmap;
	for (itmap=g_map_bus_info.begin (); itmap!=g_map_bus_info.end (); itmap++)
	{
		printf ("%d->%d->%s\n", 
		itmap->second.bus_ID, itmap->second.bus_number,itmap->second.cur_station);
	}
}

void debug_print_xbus_curstation ()
{
	printf ("************current x bus***********\n");
	for (int i=0; i<50; i++)
	{
		if (all_xbus_position[i][0] == 0)
			break;
		printf ("%s\n", all_xbus_position[i]);
	}
}
int save_bus_info (bus_info_t *cli_send_msg)
{
	// �жϹ�������λ���ǲ��Ǹı䣬ʵʱ����
	// exp: bus ������,����һվ���ϵ�̨����
	
	pair<map<int, bus_info_t>::iterator, bool> ret;
	ret = g_map_bus_info.insert (make_pair (cli_send_msg->bus_ID, *cli_send_msg));
	if (true != ret.second)
	{
		ret.first->second = *cli_send_msg;
	}
	return 0;
}

int get_bus_info (int bus_number)
{
	memset (all_xbus_position, 0, sizeof (all_xbus_position));
	int xbus_count=0;
	map<int, bus_info_t>::iterator itmap;
	for (itmap=g_map_bus_info.begin (); itmap!=g_map_bus_info.end (); itmap++)
	{
		if (bus_number == itmap->second.bus_number)
		{	
			memcpy (all_xbus_position[xbus_count], itmap->second.cur_station, 64);
			xbus_count++;
		}
	}
	
	return 0;
}

int map_erase_data (int bus_ID)
{
	map<int, bus_info_t>::iterator itmap;
	
	itmap = g_map_bus_info.find (bus_ID);

	if (itmap != g_map_bus_info.end ())
	{
		g_map_bus_info.erase (itmap);
		return 0;
	}
	return 1;
}


void LoadXml(void)
{
    FILE *fp;
    mxml_node_t *tree = NULL;

    fp = fopen("xbus_all_station.xml", "r");
    tree = mxmlLoadFile(NULL, fp, NULL);
    fclose(fp);

	int i=0, xBus=0;;
    mxml_node_t *node; 
    const char *name, *prog;
	vecBusXianlu.reserve (3);
	
    /* ʹ������ */
    for (node = mxmlFindElement(tree, tree, "node", NULL, NULL, MXML_DESCEND);
                    node != NULL;
                    node = mxmlFindElement(node, tree, "node", NULL, NULL, MXML_DESCEND))
    {            
            prog = mxmlElementGetAttr(node, "prog");
            xBus = atoi (prog);
            //printf ("here 5:\n");
            switch (xBus)
            {
				case 22:
				{
					//printf ("here 22:\n");
					name = mxmlElementGetAttr(node, "name");
					string string = name;
					//printf ("%s\n", string.c_str ());
					vecBusXianlu[i].vecStations.push_back (string);
					vecBusXianlu[i].xbus = xBus;
					//printf ("here 22 end:\n");
				}
				break;
				case 14:
				{
					i=1;
					name = mxmlElementGetAttr(node, "name");
					vecBusXianlu[i].vecStations.push_back (name);
					vecBusXianlu[i].xbus = xBus;
				}
				break;
				case 113:
				{
					i=2;
					name = mxmlElementGetAttr(node, "name");
					vecBusXianlu[i].vecStations.push_back (name);
					vecBusXianlu[i].xbus = xBus;
				}
				break;
				default:
				break;
            }
    }

    mxmlDelete(tree);
}

// �������������Ĺ�����·
void search_bus_xianlu (const char *start_station, const char *end_station)
{	
	// ��սṹ��
	memset (&ser_bus_tuijian_msg, 0, sizeof (ser_bus_tuijian_msg));
	//vector<bus_Xianlu>::iterator itvecbusxianlu;
	vector<string>::iterator itvecstrstations;

	//�򵥵ض����ҵ��Ĺ���·�ߵ�����
	// ���Ӷ������������,����Ӧ�������
	vector<bus_Xianlu>::iterator itvec_find_start;
	vector<bus_Xianlu>::iterator itvec_find_end;
		
	//printf ("search 2\n");
	int way_count =0,i=0, find_start=-1, find_end=0;
	// �������й���
	for (; i!=3; i++)
	{	
		//printf ("search 3\n");
		// ������·������·
		for (itvecstrstations= vecBusXianlu[i].vecStations.begin ();
			 itvecstrstations!= vecBusXianlu[i].vecStations.end (); itvecstrstations++)
		{
			if (strcmp (start_station, itvecstrstations->c_str ()) == 0)
			{
			//	printf ("search 4\n");
				find_start = i;
			//	printf ("find start %d\n", find_start);
				ser_bus_tuijian_msg.bus_xl_tj[way_count].start_bus_id = vecBusXianlu[i].xbus;
			//	printf ("%d->ser_bus_tuijian_msg : %d\n", __LINE__, 
			//		ser_bus_tuijian_msg.bus_xl_tj[way_count].start_bus_id);
			}
			if (strcmp (end_station, itvecstrstations->c_str ()) == 0)
			{
				find_end = i;
				ser_bus_tuijian_msg.bus_xl_tj[way_count].end_bus_id = vecBusXianlu[i].xbus;
			//	printf ("%d->ser_bus_tuijian_msg : %d\n",  __LINE__, 
			//		ser_bus_tuijian_msg.bus_xl_tj[way_count].end_bus_id);
			}
		}
			 
	}
//	printf ("search 6\n");

	if (-1 != find_start)
	{
		vector<string>::iterator itvec_start_sta_xbus;
		vector<string>::iterator itvec_end_sta_xbus;
		for (itvec_start_sta_xbus= vecBusXianlu[find_start].vecStations.begin ();
			 itvec_start_sta_xbus!= vecBusXianlu[find_start].vecStations.end (); 
			 itvec_start_sta_xbus++)
		{
			for (itvec_end_sta_xbus= vecBusXianlu[find_end].vecStations.begin ();
				 itvec_end_sta_xbus!= vecBusXianlu[find_end].vecStations.end (); 
				 itvec_end_sta_xbus++)
			{
			//	printf ("search 8\n");
			//	printf ("start %s end %s\n", itvec_start_sta_xbus->c_str (), itvec_end_sta_xbus->c_str ());
				//if (strcmp (itvecstrstations->c_str (), itvec_end_sta_xbus->c_str ()) == 0)
				if (*itvec_start_sta_xbus == *itvec_end_sta_xbus)
				{
			//		printf ("search 10\n");
					strcpy (ser_bus_tuijian_msg.bus_xl_tj[0].bus_public, itvec_start_sta_xbus->c_str ());
			//		printf ("ser_bus_tuijian_msg public :%s\n", ser_bus_tuijian_msg.bus_xl_tj[0].bus_public);
					return ;
				}
			//	printf ("search 11\n");
			}
		}
	}
}

void test ()
{
	char start_station[] = "������·";
	char end_station[] = "ũ�ִ�ѧ";
	
//	printf ("search 1\n");
	search_bus_xianlu(start_station, end_station);
	
	printf ("start from :%s ->%d\nturn station :%s ->%d\nend station : %s\n", start_station,
	ser_bus_tuijian_msg.bus_xl_tj[0].start_bus_id, 
	ser_bus_tuijian_msg.bus_xl_tj[0].bus_public, 
	ser_bus_tuijian_msg.bus_xl_tj[0].end_bus_id,
	end_station);
}


void pth_mutex_init ()
{
	pthread_mutex_init (&g_mutex, NULL);
}

void pth_mutex_destroy ()
{
	pthread_mutex_destroy(&g_mutex);
}

