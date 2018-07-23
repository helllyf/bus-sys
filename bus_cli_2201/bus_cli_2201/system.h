#ifndef SYSTEM_H
#define SYSTEM_H


typedef   unsigned short  WORD;
typedef   unsigned char   BYTE;
typedef   unsigned long   DWORD;

//#define   NULL ((void *)0)

#define CK_PLAY_ALWAYS    0
#define CK_PLAY_PERDAY    1
#define CK_PLAY_PERIOD    2

//��˫ɫ����
#define LED_MONO			1
#define LED_DOUBLE			2

//��ʾ��������
#define ROOT_UPDATE           0x13  //������λ������
#define ROOT_FONTSET          0x14  //�����ֿ�
#define ROOT_PLAY             0x21  //��Ŀ���ݣ����浽RAM�����綪ʧ
#define ROOT_DOWNLOAD         0x22  //��Ŀ���ݣ����浽Flash
#define ROOT_PLAY_CHAPTER     0x23  //������߸���ĳһĻ
#define ROOT_PLAY_REGION      0x25  //������߸���ĳһ����
#define ROOT_PLAY_LEAF        0x27  //������߸���ĳһҳ��
#define ROOT_PLAY_OBJECT      0x29  //������߸���ĳһ����
//#define ROOT_PLAY             0xB1  //��Ŀ���ݣ����浽RAM�����綪ʧ
//#define ROOT_DOWNLOAD         0xB2  //��Ŀ���ݣ����浽Flash
//#define ROOT_PLAY_CHAPTER     0xB3  //������߸���ĳһĻ
//#define ROOT_PLAY_REGION      0xB5  //������߸���ĳһ����
//#define ROOT_PLAY_LEAF        0xB7  //������߸���ĳһҳ��
//#define ROOT_PLAY_OBJECT      0xB9  //������߸���ĳһ����

#define ACTMODE_INSERT        0x00
#define ACTMODE_REPLACE       0x01

#define ID_CHAPTER            0x3F
#define ID_REGION             0x3E
#define ID_LEAF               0x30
#define ID_WINDOW             0x31
#define ID_DCLOCK             0x32
#define ID_STRING             0x33
#define ID_EFFECT             0x34
#define ID_FONTSET            0xEE
#define ID_PIXELS             0x36
#define ID_PIXELSET           0x37
#define ID_MOVIE              0x38
#define ID_COUNTDOWN          0x39
#define ID_COUNTUP            0x3A
#define ID_WINDOWS            0x3B
#define ID_STRINGS            0x3C

#define ID_TEMPERATURE        0x50
#define ID_HUMIDITY           0x51
#define ID_NOISE              0x52
#define ID_IMPORT             0x53
#define ID_ACLOCK             0x60
#define ID_CAMPAIGNTIME       0x61

#define PLAY_MODE_NORMAL      0x00  //����ʱ���л��������Ƿ񲥷����
#define PLAY_MODE_WAIT        0x01  //�ȴ����������

#define FONT_SET_16           0x0
#define FONT_SET_24           0x1

#define BITMAP_RED            1
#define BITMAP_GREEN          2
#define BITMAP_YELLOW         3
#define BITMAP_COLOR          4

#define DF_YEAR               1
#define DF_MONTH              2
#define DF_DAY                3
#define DF_WEEK               4
#define DF_HOUR               5
#define DF_MINUTE             6
#define DF_SECOND             7
#define DF_USER               8
#define DF_FLICKER            9
#define DF_CHNDATE            10
#define DF_CHNMONTH           10
#define DF_CHNDAY             11

typedef struct _RECT{
  long left;
  long top;
  long right;
  long bottom;
}TRect, *PRect;

typedef struct TIMESTAMP{
  long time;
  long date;
}TTimeStamp, *PTimeStamp;

typedef struct FONTSET{
  WORD  id;             //�����ʶ
  WORD  width;          //������
  DWORD size;           //�����ֽ���
  BYTE  name[16];       //�ַ�������
}TFontSet;
typedef TFontSet * PFontSet;

//������ͷ��
typedef struct ROOT{
  WORD  id;              //����������
  WORD  color;           //��ʶ��˫ɫ����ʾ����
  DWORD size;            //�����������ֽ���(���������ֽ����͸�Ԫ�ر����ֽ���֮��)
  DWORD count;           //�Ӷ�������
  long  survive;         //����ʱ�䳤��
  WORD  flag;            //��־
  WORD  Reserved;
}TRoot, *PRoot;

//���ֽ�Ŀ���²������ݽṹ����
typedef struct CUSTOMACTION{
  TRoot header;          //������ͷ��
  WORD  actionmode;      //����ģʽ(����/�滻)
  WORD  chapterindex;    //���ĸ��½ڲ�������滻
  WORD  regionindex;     //���ĸ����򴰲�������滻
  WORD  leafindex;       //���ĸ�ҳ���������滻
  WORD  objectindex;     //���ĸ�λ�ò�������滻�ؼ�
  WORD  reserved;
}TCustomAction, *PCustomAction;

//��Ŀ���ݽṹ��
typedef struct CHAPTER{
  WORD  id;             //��ʶ����������У��
  WORD  no;             //��Ŀ���(�ڽ�Ŀ�滻ʱ�����ݴ˱���滻)
  WORD  wait;           //�Ƿ�ȴ��������(=1�ȴ�; =0��ʱ�����)
  WORD  repeat;         //��Ŀ���Ŵ���
  WORD  count;          //�߼���������
  WORD  Reserved;
  DWORD time;
  DWORD size;           //��ʶ�ý�Ŀ�ֽ���(���������ֽ����͸�Ԫ�ر����ֽ���֮��)
  WORD  kind;           //���żƻ�����0=ʼ�ղ��ţ�1=��ÿ����ֹʱ�䲥�ţ�3=��ָ������ֹ����ʱ�䲥��
  WORD  week;           //�����յ���������Ч
  TTimeStamp fromtime;  //��ʼʱ��
  TTimeStamp totime;    //����ʱ��
}TChapter, *PChapter;

//�������ݽṹ��
typedef struct REGION{
  WORD  id;             //��ʶ����������У��
  WORD  no;             //�߼����ڱ��(���߼������滻ʱ�����ݴ˱���滻)
  WORD  over;           //��Ŀ�Ƿ񲥷����(��modeΪ�ȴ����󲥷����ʱ�����ֶ���Ч���Լ�������ֶ���Ч)
  WORD  count;          //ҳ����Ŀ
  DWORD size;           //��ʶ���߼������ֽ���(���������ֽ����͸�Ԫ�ر����ֽ���֮��)
  TRect rect;           //�߼�����λ�ô�С
  WORD  Reserved1;
  WORD  Reserved2;
}TRegion, *PRegion;

//ҳ�����ݽṹ��
typedef struct LEAF{
  WORD  id;             //ҳ����(��ҳ���滻ʱ�����ݴ˱���滻)
  WORD  no;
  WORD  wait;           //�Ƿ�ȴ��������(=1�ȴ�; =0��ʱ�����)
  WORD  serial;         //�Ƿ��з�ʽ����
  WORD  count;          //������Ŀ
  WORD  Reserved;
  DWORD time;           //ҳ����ʾʱ��
  DWORD size;           //��ʶ��ҳ���ֽ���(���������ֽ����͸�Ԫ�ر����ֽ���֮��)
  WORD  Reserved1;
  WORD  Reserved2;
}TLeaf, *PLeaf;

//����ͨ�����Խṹ��
typedef struct OBJECT{
  WORD  id;             //�����ʶ
  BYTE  transparent;    //�Ƿ�͸��
  BYTE  border;
  DWORD size;           //�����ֽ���
  TRect rect;           //������ʾ����
}TObject, *PObject;

//�ಥ�Ŷ������ݽṹ����������TWindow������߶��TString����
typedef struct WINDOWS{
  TObject     object;     //�����һ�㶨��
  BYTE        method;     //������ʽ
  BYTE        speed;      //�����ٶ�
  WORD        count;      //�����ĵ�Window����
}TWindows;
typedef TWindows * PWindows;

//�������ֶ���
typedef struct STRING{
  WORD        id;
  BYTE        inMethod;   //���뷽ʽ
  BYTE        outMethod;  //������ʽ
  BYTE        stopMethod; //ͣ����ʽ
  BYTE        reserved;
  WORD        inSpeed;    //�����ٶ�
  WORD        outSpeed;   //�����ٶ�
  WORD        stopSpeed;  //ͣ���ٶ�(����Ϊ��˸ʱ����ʾ��˸�ٶ�)
  DWORD       stoptime;   //ͣ��ʱ��
  long        stopx;      //ͣ��λ��
  DWORD       size;       //���ݳ���
  DWORD       color;      //�ַ���ɫ
  WORD        fontset;    //�ַ���(һ����� 0=16���� 1=24����)
  WORD        Reserved;
}TString;
typedef TString * PString;

//ͼƬ���󣬺������һ������TPixels
typedef struct WINDOW{
  WORD        id;
  BYTE        inMethod;   //���뷽ʽ
  BYTE        outMethod;  //������ʽ
  BYTE        stopMethod; //ͣ����ʽ
  BYTE        reserved;
  WORD        inSpeed;    //�����ٶ�
  WORD        outSpeed;   //�����ٶ�
  WORD        stopSpeed;  //ͣ���ٶ�(����Ϊ��˸ʱ����ʾ��˸�ٶ�)
  DWORD       stoptime;   //ͣ��ʱ��
  long        stopx;      //ͣ��λ��
  DWORD       size;       //���ݳ���
}TWindow;
typedef TWindow * PWindow;

//�������ݽṹ����
typedef struct PIXELS{
  WORD   id;            //�����ʶ
  WORD   bits;          //ÿ����λ��
  long   width;         //������
  long   height;        //����߶�
  DWORD  size;          //�����С
}TPixels;
typedef TPixels * PPixels;

//�������ݽṹ���壨���󼯰����������
typedef struct PIXELSET{
  WORD   id;            //�����ʶ
  WORD   count;         //TPixels������Ŀ
  DWORD  size;          //�����ֽ���
}TPixelSet;
typedef TPixelSet * PPixelSet;

//����ʱ������ʽ���������
#define MAX_DATETIME_FORMAT  32

//����ʱ������ʽ
typedef struct DCFORMAT{
        BYTE Format;
        BYTE Index;
}TDCFormat, *PDCFormat;

//����ʱ�����
typedef struct DClock{
  TObject     object;        //�����һ�㶨��
  WORD        type;
  WORD        reserved;
  TTimeStamp  basetime;
  TTimeStamp  fromtime;
  TTimeStamp  totime;
  long        yearoffset;    //��ƫ����
  long        monthoffset;   //��ƫ����
  long        dayoffset;     //��ƫ����
  long        timeoffset;    //ʱ��ƫ����(����)
  TDCFormat   formats[MAX_DATETIME_FORMAT];  //��ʾ��ʽ
}TDClock;
typedef TDClock * PDClock;

typedef struct _RGB{
  BYTE   r;
  BYTE   g;
  BYTE   b;
}TRGB;
typedef TRGB * PRGB;

#define ETHER_ADDRESS_LENGTH 6
#define IP_ADDRESS_LENGTH    4

typedef struct BOARDPARAM{
  WORD   width;
  WORD   height;
  WORD   type;
  WORD   frequency;
  DWORD  flag;
  DWORD  uart;								//+2+2+2+2+4+4=16
  BYTE   mac[ETHER_ADDRESS_LENGTH];
  BYTE   ip[IP_ADDRESS_LENGTH];
  BYTE   gateMAC[ETHER_ADDRESS_LENGTH];
  BYTE   serverIP[IP_ADDRESS_LENGTH];		//+6+4+6+4=36
  BYTE   brightness;
  BYTE   importflag;
  BYTE   rootcount;
  BYTE   disconnect_sec;
  DWORD  rom_size;
  long   left;
  long   top;								//+4+4+4+4=52
  WORD   scan_mode;
  WORD   server_port;
  WORD   line_order;
  WORD   oe_time;
  WORD   shift_freq;
  WORD   refresh_freq;						//+2+2+2+2+2+2=64;
  BYTE   GateIP[IP_ADDRESS_LENGTH];
  BYTE   ipMask[IP_ADDRESS_LENGTH];			//+4+4=72
  BYTE   name[32];
  DWORD  ident;
  DWORD  address;							//+32+4+4=112
  DWORD  pkp_rx_timeo;
  DWORD  pkp_tx_timeo;
  DWORD  pkp_tx_repeat;
  BYTE   dnsIP[IP_ADDRESS_LENGTH];
  BYTE   dnsMAC[ETHER_ADDRESS_LENGTH];
  WORD   ReportTime;						//+12+4+6+2=136
  //���server_host=0����server_domain��Ч
  BYTE   serverDomain[32];
  //��ʾ������Կ������������Կ���������ݰ�����ֹ�Ƿ��û�����ʾ���Ϸ�����Ϣ
  DWORD  key;
  DWORD  pkp_length;                        //+32+4+4=176
  //��Ӧ��bin�ļ���
  char   bin_name[32];                      //+32=208
  //////////////////////////////////////////////////////
  //�����ز���
  BYTE   light_sense;
  BYTE   light_sense_auto;
  WORD   light_sense_reserved;
  WORD   light_sense_split_val[8];
  BYTE   light_sense_bright_val[8];         //+28=236
  //////////////////////////////////////////////////////
  //˫��ʱ��ͬ���ܿض�IP��ַ
  BYTE   TimeSyncIP[IP_ADDRESS_LENGTH];		//+4=240
  //////////////////////////////////////////////////////
  //�Զ���������
  BYTE   auto_reset_enabled;
  BYTE   auto_reset_type;
  BYTE   auto_reset_hour;
  BYTE   auto_reset_minute;
}TBoardParam, *PBoardParam;

#endif // SYSTEM_H
