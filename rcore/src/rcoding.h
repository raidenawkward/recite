#ifndef RCODING_H
#define RCODING_H

#include <iconv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int unicode2gb2312(char *inbuf,size_t inlen,char *outbuf,size_t outlen);
int gb2312tounicode(char *inbuf,size_t inlen,char *outbuf,size_t outlen);

bool isGB2312(const char* str);
bool isGBK(const char* str);


int code_convert(const char *from_charset,const char *to_charset,char *inbuf,size_t inlen,char *outbuf,size_t outlen);

#endif // RCODING_H
