#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <ctype.h>
#include "tts.h"

#if 0
#include "lua.h"  
#include "lualib.h"
#include "luaconf.h"
#include "lauxlib.h" 

extern void utf8ToGb2312(const char* utf8, int len, char *temp);

static int fd = 0;
#endif
static int OpenUart(const char *dev)
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

static int SetUart(int fd, int baud_rate, int databit, int stopbit, int parity)
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

#if 0
int tts_init(lua_State *L)
{
	int devname_len;
	char *usb_dev = "/dev/ttyUSB0";
	char cmd_data[16];
	int ret = -1;
	char *dev_name = (char *)luaL_checklstring(L, 1, &devname_len);
	double bound = luaL_checknumber(L, 2);
	
	if(!strcmp(usb_dev, dev_name)){
		system("insmod /tmp/flashutils/program/usbserial.ko");
		system("insmod /tmp/flashutils/program/pl2303.ko");
	}
	
	if(fd == 0){
		fd = OpenUart(dev_name);
		printf("@@@open uart fd:%d\n", fd);
		if(fd == -1){
			lua_pushnumber(L, fd);
			return 1;
		}
		SetUart(fd,(int)bound,8,1,'n');	
		
		cmd_data[0] = 0xfd;
		cmd_data[1] = 0x00;
		cmd_data[2] = 0x01;
		cmd_data[3] = 0x21;
		ret = write(fd, cmd_data, 4);
		printf("@@@write ret:%d\n", ret);
		usleep(1000);
		memset(cmd_data, 0, sizeof(cmd_data));
		ret = read(fd, cmd_data, 1);
		printf("@@@read ret:%d\n", ret);

		if(ret == 1){
			printf("read 0x%x ok\n", cmd_data[0]);
			lua_pushnumber(L, 12);
		}else{
			lua_pushnumber(L, -1);
			return 1;
		}
	}
	return 0;
} 

int tts_close(lua_State *L){
	int error;
	error = close(fd);
	if(error == -1){
		printf("Close Device error!\n ");
		lua_pushnumber(L, error);
		return 1;
	}
	fd = 0;
	
	return 0;
}

int tts_send(lua_State *L){
	char cmd_data[1000];
    int str_len;
    char *str_data = (char *)luaL_checklstring(L, 1, &str_len);   //todo: lua return type
    double vol = luaL_checknumber(L, 2);
    double sleep_ms = luaL_checknumber(L, 3);
    char *str_out;
    char *tts_out;
    int outlen;
	if(fd == 0){
		printf("Device is not open.\n");
		return 0;
	}else{
		str_out = (char *)malloc(sizeof(char) * str_len * 4);
		tts_out = (char *)malloc(sizeof(char) * str_len * 4 + 4);
		memset(str_out, 0 ,str_len * 4);
		utf8ToGb2312(str_data,str_len,str_out);
		sprintf(tts_out, "[v%d]%s", (int)vol, str_out);
		outlen = strlen(tts_out);
		printf("lua_str is %s,trans_str is %s,trans_str is %d\n",str_data,tts_out,outlen);
		memset(cmd_data,0,1000);

		outlen += 2;
		cmd_data[0] = 0xfd;
		cmd_data[1] = (char)(outlen >> 8);
		cmd_data[2] = (char)outlen;
		cmd_data[3] = 0x01;
		cmd_data[4] = 0x00;

		memcpy(&cmd_data[5],tts_out,outlen - 2);

		usleep(((int)sleep_ms) * 1000);
		write(fd, cmd_data, outlen + 3);

		free(str_out);
		free(tts_out);
	}
	return 1;
}

int luaopen_tts_lib (lua_State* L) {
	static const struct luaL_Reg funcs[] = {
    	{"tts_init", tts_init},
		{"tts_send", tts_send},
    	{"tts_close", tts_close},
    	{NULL, NULL}
	};
	luaL_register(L, "tts_lib", funcs);
	return 1;
}
#endif
int tts_open_test(const char *dev_name, const char *string)
{
	int ret = -1;
	int bound = 115200;
	//char cmd_data[16] = {0xFD, 0x00, 0x0A, 0x01, 0x00, 0xBF, 0xC6, 0xB4, 0xF3, 0xD1, 0xB6, 0xB7, 0xC9};//gb2312
	//char cmd_data[16] = {0xFD, 0x00, 0x0A, 0x01, 0x03, 0xD1, 0x79, 0x27, 0x59, 0xAF, 0x8B, 0xDE, 0x98};//unicode
	char cmd_data[16] = {0xFD, 0x00, 0x0A, 0x01, 0x00};
	
//	char buf_utf8[16] = "孙权你好";
	char buf_gb2312[16] = {0};

	utf8togb2312(string, 16,buf_gb2312, 16);
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
	
	return ret;
}
/*
int main(int argc ,char *argv[])
{
	if(argc != 2){
		printf("usage:./tts string\n");
		return 0;
	}
	
	tts_open_test("/dev/ttyUSB0", argv[1]);

	return 0;
}
*/
