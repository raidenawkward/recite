/*
 * =====================================================================================
 *
 *       Filename:  test_dict_info.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2011年02月17日 00时54分02秒
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

#if 0

int main(int argc,char**argv){
    DICT_INFO* dict=get_dict_info("../dict/sample/sample1.ifo");
    if(dict==NULL)
    {
        printf("error\n");
        exit(EXIT_FAILURE);
    }
    printf("version:%s\n",dict->version);
    printf("bookname:%s\n",dict->book_name);
    printf("wordcount:%d\n",dict->word_count);
    printf("idxfilesize:%d\n",dict->idx_file_size);
    printf("sts:%s\n",dict->same_type_per_seq);
    printf("%s",dict->other_info);
    free(dict);
    return EXIT_SUCCESS;
}
#endif
