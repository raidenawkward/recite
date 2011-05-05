/*
 * =====================================================================================
 *
 *       Filename:  dict_idx.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  2011年02月17日 00时15分39秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  齐保元 (qby), qibaoyuan@126.com
 *        Company:  ict,gucas
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dict_info.h"
#include "dict_idx.h"
static void* get_words(char* filename,DICT_INFO* dict_info,WORD_IDX* word_idx)
{
    FILE* fd=fopen(filename,"rb");
    size_t nread=0;
    if(NULL==fd || dict_info==NULL)
    {
        return NULL;
    }
	printf("dict_info->idx_file_size = %d\n",dict_info->idx_file_size);

	//unsigned char buffer[dict_info->idx_file_size];
	// raidne fixed on 20110505
	unsigned char* buffer = (unsigned char*)malloc(sizeof(unsigned char*)*dict_info->idx_file_size);

    nread=fread(buffer,dict_info->idx_file_size,1,fd);
    unsigned char *head,*tail;
    head=tail=buffer;
    int it=0;
    int total=1;
    for(;it<dict_info->idx_file_size;it++)
    {
        if(*head=='\0')
        {
            strncpy((word_idx+total)->word,tail,head-tail+1);
            (word_idx+total)->offset=to_int(head+1);
            (word_idx+total)->length=to_int(head+5);
            total++;
            head+=9;
            tail=head;
            if(total==dict_info->word_count)
                break;
        }else{
            head++;
            continue;
        }
    }
}

inline static int to_int(unsigned char* from_int)
{
    return *(from_int+3)+(*(from_int+2)<<8)+(*(from_int+1)<<16)+(*from_int<<24);
}

WORD_IDX* get_idx(char* word,WORD_IDX *word_idx,DICT_INFO *dict_info)
{
    if(word==NULL || word_idx==NULL || dict_info==NULL)
    {
        return NULL;
    }
    int head=0,tail=dict_info->word_count;
    int mid;
    int i=0;
    while(head<tail-1)
    {
        mid=(head+tail)>>1;
        int cmp=strcasecmp(word,word_idx[mid].word);
        if(0==cmp)
        {
            return &word_idx[mid];
        }else if(0>cmp){
            tail=mid;
        }else{
            head=mid;
        }
    }
    return NULL;
}

#if 1

int main(int argc,char** argv)
{
    char* ifo_name="../dict/stardict-langdao-ec-gb-2.4.2/langdao-ec-gb.ifo";
    char* idx_name="../dict/stardict-langdao-ec-gb-2.4.2/langdao-ec-gb.idx";
    char* dict_name="../dict/stardict-langdao-ec-gb-2.4.2/langdao-ec-gb.dict";
    DICT_INFO* dict_info;
    dict_info=get_dict_info(ifo_name);
    WORD_IDX* idx=(WORD_IDX*)malloc(sizeof(WORD_IDX)*dict_info->word_count);

    get_words(idx_name,dict_info,idx);

    WORD_IDX* word=get_idx(argv[1],idx,dict_info);
    if(word==NULL){
        printf("<NULL>\n");
        exit(0);
    }
    printf("%s,%d,%d\n",word->word,word->offset,word->length);
    FILE* dict=fopen(dict_name,"r");
    if(NULL==dict)
    {
        printf("dict error!\n");
        return EXIT_FAILURE;
    }
    if(0!=fseek(dict,word->offset,SEEK_SET))
    {
        printf("seek error\n");
        return EXIT_FAILURE;
    }
    char explain[word->length+1];
    memset(explain,'\0',word->length+1);
    fread(explain,word->length,1,dict);
    printf("%s\n",explain);
    free(idx);
    return EXIT_SUCCESS;
}
#endif
