#ifndef CONVERT_H
#define CONVERT_H


#define GB2312 "./font/GB2312.txt"

int utf8togb2312(char *sourcebuf,size_t sourcelen,char *destbuf,size_t destlen);
int gb2312toutf8(char *sourcebuf,size_t sourcelen,char *destbuf,size_t destlen);
int OpenUart(const char *dev);
int SetUart(int fd, int baud_rate, int databit, int stopbit, int parity);
int tts_open_test(const char *dev_name, char *string);

#endif // CONVERT_H
