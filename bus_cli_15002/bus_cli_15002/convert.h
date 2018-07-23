
#ifndef __CONVERT_H
#define __CONVERT_H


#define GB2312 "./font/GB2312.txt"

int utf8togb2312(char *sourcebuf,size_t sourcelen,char *destbuf,size_t destlen);
int gb2312toutf8(char *sourcebuf,size_t sourcelen,char *destbuf,size_t destlen);

#endif

