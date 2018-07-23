#ifndef SYSTEM_H
#define SYSTEM_H


typedef   unsigned short  WORD;
typedef   unsigned char   BYTE;
typedef   unsigned long   DWORD;

//#define   NULL ((void *)0)

#define CK_PLAY_ALWAYS    0
#define CK_PLAY_PERDAY    1
#define CK_PLAY_PERIOD    2

//单双色类型
#define LED_MONO			1
#define LED_DOUBLE			2

//显示数据命令
#define ROOT_UPDATE           0x13  //更新下位机程序
#define ROOT_FONTSET          0x14  //下载字库
#define ROOT_PLAY             0x21  //节目数据，保存到RAM，掉电丢失
#define ROOT_DOWNLOAD         0x22  //节目数据，保存到Flash
#define ROOT_PLAY_CHAPTER     0x23  //插入或者更新某一幕
#define ROOT_PLAY_REGION      0x25  //插入或者更新某一窗口
#define ROOT_PLAY_LEAF        0x27  //插入或者更新某一页面
#define ROOT_PLAY_OBJECT      0x29  //插入或者更新某一对象
//#define ROOT_PLAY             0xB1  //节目数据，保存到RAM，掉电丢失
//#define ROOT_DOWNLOAD         0xB2  //节目数据，保存到Flash
//#define ROOT_PLAY_CHAPTER     0xB3  //插入或者更新某一幕
//#define ROOT_PLAY_REGION      0xB5  //插入或者更新某一窗口
//#define ROOT_PLAY_LEAF        0xB7  //插入或者更新某一页面
//#define ROOT_PLAY_OBJECT      0xB9  //插入或者更新某一对象

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

#define PLAY_MODE_NORMAL      0x00  //按照时间切换，不管是否播放完成
#define PLAY_MODE_WAIT        0x01  //等待自身播放完成

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
  WORD  id;             //对象标识
  WORD  width;          //点阵宽度
  DWORD size;           //对象字节数
  BYTE  name[16];       //字符集名称
}TFontSet;
typedef TFontSet * PFontSet;

//数据流头部
typedef struct ROOT{
  WORD  id;              //数据流类型
  WORD  color;           //标识单双色等显示类型
  DWORD size;            //整个数据流字节数(包含数据字节数和该元素本身字节数之和)
  DWORD count;           //子对象数量
  long  survive;         //存在时间长度
  WORD  flag;            //标志
  WORD  Reserved;
}TRoot, *PRoot;

//部分节目更新操作数据结构声明
typedef struct CUSTOMACTION{
  TRoot header;          //数据流头部
  WORD  actionmode;      //操作模式(插入/替换)
  WORD  chapterindex;    //在哪个章节插入或者替换
  WORD  regionindex;     //在哪个区域窗插入或者替换
  WORD  leafindex;       //在哪个页面插入或者替换
  WORD  objectindex;     //在哪个位置插入或者替换控件
  WORD  reserved;
}TCustomAction, *PCustomAction;

//节目数据结构体
typedef struct CHAPTER{
  WORD  id;             //标识，用于数据校验
  WORD  no;             //节目编号(在节目替换时，根据此编号替换)
  WORD  wait;           //是否等待播放完成(=1等待; =0到时间就切)
  WORD  repeat;         //节目播放次数
  WORD  count;          //逻辑窗口数量
  WORD  Reserved;
  DWORD time;
  DWORD size;           //标识该节目字节数(包含数据字节数和该元素本身字节数之和)
  WORD  kind;           //播放计划类型0=始终播放；1=按每日起止时间播放；3=按指定的起止日期时间播放
  WORD  week;           //星期日到六哪天有效
  TTimeStamp fromtime;  //开始时间
  TTimeStamp totime;    //结束时间
}TChapter, *PChapter;

//区域窗数据结构体
typedef struct REGION{
  WORD  id;             //标识，用于数据校验
  WORD  no;             //逻辑窗口编号(在逻辑窗口替换时，根据此编号替换)
  WORD  over;           //节目是否播放完成(当mode为等待对象播放完成时，此字段有效。对计算机此字段无效)
  WORD  count;          //页面数目
  DWORD size;           //标识该逻辑窗口字节数(包含数据字节数和该元素本身字节数之和)
  TRect rect;           //逻辑窗口位置大小
  WORD  Reserved1;
  WORD  Reserved2;
}TRegion, *PRegion;

//页面数据结构体
typedef struct LEAF{
  WORD  id;             //页面编号(在页面替换时，根据此编号替换)
  WORD  no;
  WORD  wait;           //是否等待播放完成(=1等待; =0到时间就切)
  WORD  serial;         //是否串行方式播放
  WORD  count;          //对象数目
  WORD  Reserved;
  DWORD time;           //页面显示时间
  DWORD size;           //标识该页面字节数(包含数据字节数和该元素本身字节数之和)
  WORD  Reserved1;
  WORD  Reserved2;
}TLeaf, *PLeaf;

//对象通用属性结构体
typedef struct OBJECT{
  WORD  id;             //对象标识
  BYTE  transparent;    //是否透明
  BYTE  border;
  DWORD size;           //对象字节数
  TRect rect;           //对象显示区域
}TObject, *PObject;

//多播放对象数据结构，后面跟多个TWindow对象或者多个TString对象
typedef struct WINDOWS{
  TObject     object;     //对象的一般定义
  BYTE        method;     //动作方式
  BYTE        speed;      //动作速度
  WORD        count;      //包含的的Window数量
}TWindows;
typedef TWindows * PWindows;

//内码文字对象
typedef struct STRING{
  WORD        id;
  BYTE        inMethod;   //引入方式
  BYTE        outMethod;  //引出方式
  BYTE        stopMethod; //停留方式
  BYTE        reserved;
  WORD        inSpeed;    //引入速度
  WORD        outSpeed;   //引出速度
  WORD        stopSpeed;  //停留速度(例如为闪烁时，表示闪烁速度)
  DWORD       stoptime;   //停留时间
  long        stopx;      //停留位置
  DWORD       size;       //数据长度
  DWORD       color;      //字符颜色
  WORD        fontset;    //字符集(一般情况 0=16点阵 1=24点阵)
  WORD        Reserved;
}TString;
typedef TString * PString;

//图片对象，后面跟着一个点阵TPixels
typedef struct WINDOW{
  WORD        id;
  BYTE        inMethod;   //引入方式
  BYTE        outMethod;  //引出方式
  BYTE        stopMethod; //停留方式
  BYTE        reserved;
  WORD        inSpeed;    //引入速度
  WORD        outSpeed;   //引出速度
  WORD        stopSpeed;  //停留速度(例如为闪烁时，表示闪烁速度)
  DWORD       stoptime;   //停留时间
  long        stopx;      //停留位置
  DWORD       size;       //数据长度
}TWindow;
typedef TWindow * PWindow;

//点阵数据结构定义
typedef struct PIXELS{
  WORD   id;            //对象标识
  WORD   bits;          //每象素位数
  long   width;         //点阵宽度
  long   height;        //点阵高度
  DWORD  size;          //对象大小
}TPixels;
typedef TPixels * PPixels;

//点阵集数据结构定义（点阵集包含多个点阵）
typedef struct PIXELSET{
  WORD   id;            //对象标识
  WORD   count;         //TPixels对象数目
  DWORD  size;          //对象字节数
}TPixelSet;
typedef TPixelSet * PPixelSet;

//日期时间对象格式的最大数量
#define MAX_DATETIME_FORMAT  32

//日期时间对象格式
typedef struct DCFORMAT{
        BYTE Format;
        BYTE Index;
}TDCFormat, *PDCFormat;

//日期时间对象
typedef struct DClock{
  TObject     object;        //对象的一般定义
  WORD        type;
  WORD        reserved;
  TTimeStamp  basetime;
  TTimeStamp  fromtime;
  TTimeStamp  totime;
  long        yearoffset;    //年偏移量
  long        monthoffset;   //月偏移量
  long        dayoffset;     //日偏移量
  long        timeoffset;    //时间偏移量(毫秒)
  TDCFormat   formats[MAX_DATETIME_FORMAT];  //显示格式
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
  //如果server_host=0，则server_domain有效
  BYTE   serverDomain[32];
  //显示屏的密钥，用于屏蔽密钥不符的数据包，阻止非法用户向显示屏上发送信息
  DWORD  key;
  DWORD  pkp_length;                        //+32+4+4=176
  //对应的bin文件名
  char   bin_name[32];                      //+32=208
  //////////////////////////////////////////////////////
  //光感相关参数
  BYTE   light_sense;
  BYTE   light_sense_auto;
  WORD   light_sense_reserved;
  WORD   light_sense_split_val[8];
  BYTE   light_sense_bright_val[8];         //+28=236
  //////////////////////////////////////////////////////
  //双卡时钟同步受控端IP地址
  BYTE   TimeSyncIP[IP_ADDRESS_LENGTH];		//+4=240
  //////////////////////////////////////////////////////
  //自动重启参数
  BYTE   auto_reset_enabled;
  BYTE   auto_reset_type;
  BYTE   auto_reset_hour;
  BYTE   auto_reset_minute;
}TBoardParam, *PBoardParam;

#endif // SYSTEM_H
