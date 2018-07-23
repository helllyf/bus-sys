#ifndef LEDUTILS_H
#define LEDUTILS_H


#include "system.h"

int adjusttime(BYTE* obuffer);
int getpower(BYTE* obuffer);
int setpower(BYTE* obuffer, int power);
int setbright(BYTE* obuffer, int bright);
int getboardparam(BYTE* obuffer);
int setboardparam(BYTE* obuffer, PBoardParam param);
int setcurchapter(BYTE* obuffer, int index);
int setcurleaf(BYTE* obuffer, int index);

void MakeRoot(BYTE* buffer);
void MakeRegion(BYTE* buffer, long chapterindex, long regionindex, long left, long top, long width, long height);
void MakeObject(BYTE* buffer, long chapterindex, long regionindex, long leafindex, long objectindex);
void AddChapter(DWORD time, WORD wait);
void AddRegion(long left, long top, long width, long height);
void AddLeaf(DWORD time, WORD wait);
void AddStrings(long left, long top, long width, long height, long transparent);
void AddChildString(char* string, long fontset, long color, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime);
void AddWindows(long left, long top, long width, long height, long transparent);
void AddChildWindow(BYTE* dibbuffer, long cx, long cy, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime);
void AddChildText(char* str, char* fontname, DWORD fontsize, DWORD fontcolor, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime);
void AddChildFontSetText(char* str, char* fontfile, unsigned long color, long inmethod, long inspeed, long outmethod, long outspeed, long stopmethod, long stopspeed, long stoptime);
void AddDateTime(long left, long top, long width, long height, long transparent);

//生成起始包数据
DWORD DoBeginPacket(BYTE* obuf, BYTE dstAddr);
//生成起始包数据，带密钥
DWORD DoBeginPacketEx(BYTE* obuf, BYTE dstAddr, DWORD key);
//生成所有数据包
DWORD DoAllDataPacket(BYTE* ibuf, BYTE* obuf, BYTE dstAddr);
//获取数据包数量
DWORD GetDataPacketCount(BYTE* ibuf);
//生成数据包
DWORD DoDataPacket(BYTE* ibuf, DWORD index, BYTE* obuf, BYTE dstAddr);
//生成结束包数据
DWORD DoEndPacket(BYTE* obuf, DWORD index, BYTE dstAddr);

extern PRoot root;

#endif // LEDUTILS_H
