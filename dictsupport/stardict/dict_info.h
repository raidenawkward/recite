/*
 * =====================================================================================
 *
 *       Filename:  dict_info.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2011年02月16日 23时28分05秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  齐保元 (qby), qibaoyuan@126.com
 *        Company:  ict,gucas
 *
 * =====================================================================================
 */
#ifndef __DICT_INFO_H__
#define __DICT_INFO_H__
#define DEBUG
#define BUFFER_SIZE 500
#define IFO_EXT ".ifo"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
    char version[100];//版本
    int word_count;//单词数量
    int idx_file_size;//索引文件大小
    char book_name[100];//词典名称
    char same_type_per_seq[10];
    char other_info[1000];
}DICT_INFO;
DICT_INFO* get_dict_info(char* line);
static void parse_line(char* line,DICT_INFO* dict_info);


#ifdef __cplusplus
}// extern c
#endif

#endif
