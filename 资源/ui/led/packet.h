#ifndef PACKET_H
#define PACKET_H

#include "system.h"
//#include "winsock.h"
#define SOCKET int
#define  PKC_BEGIN   0
#define  PKC_END     1
#define  PKC_DATA    2
#define  PKC_RESPOND 3
#define  PKC_ADJUST_TIME 6
#define  PKC_GET_PARAM   7
#define  PKC_SET_PARAM   8
#define  PKC_GET_POWER   9
#define  PKC_SET_POWER   10
#define  PKC_SET_BRIGHT  12

#define PKC_GET_CHAPTER_COUNT    66  //��ȡ��Ŀ����
#define PKC_GET_CURRENT_CHAPTER  67  //���õ�ǰ���ŵĽ�Ŀ
#define PKC_SET_CURRENT_CHAPTER  68  //���õ�ǰ���ŵĽ�Ŀ
#define PKC_GET_LEAF_COUNT       69  //��ȡҳ������
#define PKC_GET_CURRENT_LEAF     70  //���õ�ǰ���ŵ�ҳ��
#define PKC_SET_CURRENT_LEAF     71  //���õ�ǰ���ŵ�ҳ��

#define  PKP_LEADER  0x55
#define  PKP_SUFFIX  0xAA
#define  PKP_FILLCH  0xBB
#define  PKP_LENGTH  512
#define  PKP_MAX_LENGTH PKP_LENGTH*2+sizeof(TPKG_Header)*2

typedef struct PKG_HEADER{
  WORD   Command;
  BYTE   srcAddr;
  BYTE   dstAddr;
  DWORD  SerialNo;
}TPKG_Header, *PPKG_Header;

typedef struct PKG_HEADER_EX{
  WORD   Command;
  BYTE   srcAddr;
  BYTE   dstAddr;
  DWORD  SerialNo;
  DWORD  Key;
}TPKG_HeaderEx, *PPKG_HeaderEx;

typedef struct PKG_RESPOND{
  TPKG_Header  Header;
  WORD         Command;
  WORD         Result;
}TPKG_Respond, *PPKG_Respond;

extern WORD PackEx(BYTE *cbuf,WORD csize,BYTE *ibuf,BYTE *obuf,WORD size);
extern WORD Pack(BYTE *ibuf,BYTE *obuf,WORD size);
extern int dePack(BYTE *ibuf,BYTE *obuf,int size);

SOCKET InitSocket(int iport);
int CloseSocket(SOCKET s);
int SocketWrite(SOCKET s, char* buffer, DWORD size, char* ip, WORD port);
int SocketRead(SOCKET s, char* buffer, DWORD size, char* ip, WORD* port);

#endif // PACKET_H
