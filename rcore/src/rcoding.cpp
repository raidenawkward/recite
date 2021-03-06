#include "rcoding.h"

#define RCODING_UTF8_STR "utf-8"
#define RCODING_GB2312_STR "gb2312"

int code_convert(const char *from_charset,const char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen) {
	iconv_t cd;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset,from_charset);
	if (cd==0)
		return -1;
	memset(outbuf,0,outlen);
	if (iconv(cd,pin,&inlen,pout,&outlen)==-1)
		return -1;
	iconv_close(cd);
	return 0;
}

//UNICODE to GB2312
int unicode2gb2312(char *inbuf,size_t inlen,char *outbuf,size_t outlen) {
    return code_convert(RCODING_UTF8_STR,RCODING_GB2312_STR,inbuf,inlen,outbuf,outlen);
}
//GB2312 to UNICODE
int gb2312tounicode(char *inbuf,size_t inlen,char *outbuf,size_t outlen) {
	return code_convert(RCODING_GB2312_STR,RCODING_UTF8_STR,inbuf,inlen,outbuf,outlen);
}


bool isGB2312(const char* str) {
	unsigned char ch1;
	unsigned char ch2;

	if (strlen(str) >= 2) {
		ch1 = (unsigned char)str[0];
		ch2 = (unsigned char)str[1];

		if (ch1 >= 176 && ch1 <= 247 && ch2 >= 160 && ch2 <= 254)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool isGBK(const char* str) {
	unsigned char ch1;
	unsigned char ch2;

	if (strlen(str) >= 2) {
		ch1 = (unsigned char)str[0];
		ch2 = (unsigned char)str[1];
		if (ch1 >= 129 && ch1 <= 254 && ch2 >= 64 && ch2 <= 254)
			return true;
		else
			return false;
	}
	else
		return false;
}


