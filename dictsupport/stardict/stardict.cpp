#include "stardict.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dict_info.h"
#include "dict_idx.h"


StarDict::StarDict()
{

}

StarDict::StarDict(const string dir)
{

}

StarDict::~StarDict()
{

}

bool StarDict::setDict(const string dir)
{
	return false;
}

string StarDict::getDictDir()
{

}

string StarDict::getResult(const string word)
{

}

string StarDict::getIndexWord(int index)
{

}

int StarDict::getWordIndex(const string word)
{

}










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
