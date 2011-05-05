/*
 * =====================================================================================
 *
 *       Filename:  dict_idx.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2011年02月17日 00时10分38秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  齐保元 (qby), qibaoyuan@126.com
 *        Company:  ict,gucas
 *
 * =====================================================================================
 */
#ifndef __DICT_IDX_H__
#define __DICT_IDX_H__
#include "dict_info.h"
#define DEBUG
#define TRUE 1
#define IDX_EXT "idx"
typedef struct
{
    char word[100];
    int offset;
    int length;
}WORD_IDX;
static void* get_words(char* filename,DICT_INFO* dict_info,WORD_IDX* word_idx);
WORD_IDX *get_idx(char* word,WORD_IDX* word_idx,DICT_INFO* dict_info);
inline static int to_int(unsigned char* from_int);
#endif
