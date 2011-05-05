/*
 * =====================================================================================
 *
 *       Filename:  dict_info.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2011年02月16日 23时33分45秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  齐保元 (qby), qibaoyuan@126.com
 *        Company:  ict,gucas
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "dict_info.h"
DICT_INFO* get_dict_info(char* info_file)
{
    FILE* ifo;
    char* line;
    char buffer[BUFFER_SIZE];
    DICT_INFO* dict_info=(DICT_INFO*)malloc(sizeof(DICT_INFO));
    memset(dict_info->version,0,100);
    memset(dict_info->book_name,0,100);
    memset(dict_info->same_type_per_seq,0,10);
    memset(dict_info->other_info,0,1000);
    ifo=fopen(info_file,"r");
    if(NULL==ifo){
        fprintf(stderr,"%s",strerror(errno));
        return NULL;
    }
    while((line=fgets(buffer,BUFFER_SIZE,ifo))!=NULL){
        parse_line(line,dict_info);
    }
    fclose(ifo);
    return dict_info;
}

static void parse_line(char* line,DICT_INFO *dict_info){
    char* idx;

    if((idx=strchr(line,'='))!=NULL){
        if(strstr(line,"version")!=NULL){
            strcpy(dict_info->version,idx+1);
        }else if(strstr(line,"wordcount")!=NULL){
            dict_info->word_count=atoi(idx+1);
        }else if(strstr(line,"idxfilesize")!=NULL){
            dict_info->idx_file_size=atoi(idx+1);
        }else if(strstr(line,"bookname")!=NULL){
            strcpy(dict_info->book_name,idx+1);
        }else if(strstr(line,"sametypesequence")!=NULL){
            strcpy(dict_info->same_type_per_seq,idx+1);
        }else
            strcat(dict_info->other_info,line);
    }
}
