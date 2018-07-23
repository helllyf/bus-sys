#include <QDebug>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/types.h>
#include <linux/types.h>
#include <errno.h>
#include <iconv.h>
#include "convert.h"


int utf8togb2312(char *sourcebuf,size_t sourcelen,char *destbuf,size_t destlen)
{
        iconv_t cd;
        char **pin = &sourcebuf;
        char **pout = &destbuf;
        cd = iconv_open("gb2312","utf-8");
        if (cd==0) return -1;

        memset(destbuf,0,destlen);

        if (iconv(cd,pin,&sourcelen,pout,&destlen)==-1) return -1;

        iconv_close(cd);

        return 0;
}

int gb2312toutf8(char *sourcebuf, size_t sourcelen, char *destbuf, size_t destlen)
{
        iconv_t cd;
        char **source = NULL;
        char **dest = NULL;

        if( (cd = iconv_open("utf-8","gb2312")) ==0 )
                return -1;

        memset(destbuf,0,destlen);
        source = &sourcebuf;
        dest = &destbuf;

        if(-1 == iconv(cd, source, &sourcelen, dest, &destlen))
                return -1;

        iconv_close(cd);
        return 0;
}
int OpenUart(const char *dev)
{
        int fd = -1;

        if(NULL == dev){
                //DMB_LOG_ERROR_OUT("OpenUart: Line%d param error!\n", __LINE__);
                printf("OpenUart:device error.\n");
                return -1;
        }

        fd = open(dev, O_RDWR|O_NOCTTY|O_NONBLOCK);
        if(-1 == fd){
                //DMB_LOG_ERROR_OUT("OpenUart: Line%d Open uart error!\n", __LINE__);
                printf("OpenUart:Open uart error!\n");
                return -1;
        }
        printf("OpenUart fd:%d\n", fd);
        return fd;
}

int SetUart(int fd, int baud_rate, int databit, int stopbit, int parity)
{
        struct termios options;
        int res;
        int rate;

        switch(baud_rate){
                case 300:
                        rate = B300;
                        break;
                case 600:
                        rate = B600;
                        break;
                case 1200:
                        rate = B1200;
                        break;
                case 2400:
                        rate = B2400;
                        break;
                case 4800:
                        rate = B4800;
                        break;
                case 9600:
                        rate = B9600;
                        break;
                case 19200:
                        rate = B19200;
                        break;
                case 38400:
                        rate = B38400;
                        break;
                case 115200:
                        rate = B115200;
                        break;
                default:
                        rate = B38400;
                        break;
        }

        //tcgetattr(fd, &options);
        bzero(&options, sizeof(options));
        options.c_cflag &= ~CSIZE;

        switch (databit){
                case 7:
                        options.c_cflag |= CS7;
                        break;
                case 8:
                        options.c_cflag |= CS8;
                        break;
                default:
                        options.c_cflag |= CS8;
                        break;
        }

        switch(tolower(parity)){
                case 'n':
                        options.c_cflag &= ~PARENB;
                        options.c_iflag &= ~INPCK;
                        break;
                case 'o':
                        options.c_cflag |= (PARODD | PARENB);
                        options.c_iflag |= INPCK;
                        break;
                case 'e':
                        options.c_cflag |= PARENB;
                        options.c_cflag &= ~PARODD;
                        options.c_iflag |= INPCK;
                        break;
                case 's':
                        options.c_cflag &= ~PARENB;
                        options.c_cflag &= ~CSTOPB;
                        break;
                default:
                        options.c_cflag &= ~PARENB;
                        options.c_iflag &= ~INPCK;
                        break;
        }

        switch(stopbit){
                case 1:
                        options.c_cflag &= ~CSTOPB;
                        break;
                case 2:
                        options.c_cflag |= CSTOPB;
                        break;
                default:
                        options.c_cflag &= ~CSTOPB;
                        break;
        }

        options.c_cc[VTIME] = 1;
        options.c_cc[VMIN] = 0;
        options.c_cflag |= (CLOCAL|CREAD);
        options.c_oflag &= ~OPOST;
        options.c_iflag &= ~(IXON|IXOFF|IXANY);
        cfsetispeed(&options, rate);
        cfsetospeed(&options, rate);
        tcflush(fd, TCIFLUSH);

        res = tcsetattr(fd, TCSANOW, &options);
        if(0 != res){
                printf("SetUart: Line%d Setup uart error!\n", __LINE__);
                return -1;
        }

        return 0;
}
int tts_open_test(const char *dev_name, char *string)
{
        int ret = -1;
        int bound = 115200;
        //char cmd_data[16] = {0xFD, 0x00, 0x0A, 0x01, 0x00, 0xBF, 0xC6, 0xB4, 0xF3, 0xD1, 0xB6, 0xB7, 0xC9};//gb2312
        //char cmd_data[16] = {0xFD, 0x00, 0x0A, 0x01, 0x03, 0xD1, 0x79, 0x27, 0x59, 0xAF, 0x8B, 0xDE, 0x98};//unicode
        char cmd_data[128] = {0xFD, 0x00, 0x0A, 0x01, 0x00};

//	char buf_utf8[16] = "ËïÈ¨ÄãºÃ";
        char buf_gb2312[128] = {0};
   qDebug()<<"yuying paoyibian-------1";
        utf8togb2312(string, 16,buf_gb2312, 16);
   qDebug()<<"yuying paoyibian-------2";
        sprintf(&cmd_data[5], "%s", string);

        int data_len = 2 + strlen(string);
        int low = data_len & 0xff;
        int high = (data_len >> 8) & 0xff;

        cmd_data[1] = high;
        cmd_data[2] = low;


        int  send_len = 5 + strlen(string);

        int fd = -1;

        fd = OpenUart(dev_name);
        if(fd == -1){
                //lua_pushnumber(L, fd);
                return -1;
        }
        SetUart(fd,(int)bound,8,1,'n');

        printf("bound :%d\n", bound);

        ret = write(fd, cmd_data, send_len);
        printf("@@@write ret:%d\n", ret);

        memset(cmd_data, 0, sizeof(cmd_data));
        usleep(1000);

        ret = read(fd, cmd_data, 1);

        if(ret == 1){
                printf("read 0x%x ok\n", cmd_data[0]);
        }else{
                printf("read failed, ret:%d\n", ret);
        }

        close(fd);
    qDebug()<<"yuying paoyibian";
        return ret;
}
