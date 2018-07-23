#include <stdio.h>
#include <string.h>

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

