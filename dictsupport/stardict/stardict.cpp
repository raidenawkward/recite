#include "stardict.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <dirent.h>

#include "dict_info.h"
#include "dict_idx.h"

using namespace std;

bool fileExists(const string file) {
	if (access(file.c_str(),0) == 0) {
		return true;
	}
    return false;
}

string detachFileFromPath(const string path) {
	int pos = path.rfind("/");
	if (pos >= 0)
		return path.substr(pos + 1);
	else
		return path;
}

string getFileExt(const string fileName) {
	int pos = fileName.rfind("/");
	if (pos >= 0)
		return fileName.substr(pos + 1);
	return string();
}

string getFileNackName(const string file) {
	string ret = detachFileFromPath(file);
	int dotpos = ret.rfind(".");
	if (dotpos >= 0) {
		return ret.substr(0,dotpos);
	}
	return ret;
}

string searchInDir(const string dir, const string fileExt) {
	DIR* dirp;
	struct dirent* direntp;
	dirp = opendir(dir.c_str());
	if( dirp != NULL ) {
		for(;;) {
			direntp = readdir(dirp);
			if( direntp == NULL )
				break;
			string file(direntp->d_name);
			if (getFileExt(file) == fileExt) {
				closedir(dirp);
				return file;
			}
		}
		closedir( dirp );
	}
	return string();
}

StarDict::StarDict() {

}

StarDict::StarDict(const string dir) {
	setDict(dir);
}

StarDict::~StarDict() {

}

bool StarDict::setDict(const string dir) {
	bool ret = false;
	if (!fileExists(dir)) {
		return ret;
	}
	_dictDir = dir;

	_ifo = searchInDir(dir,"ifo");
	if (_ifo.empty()) {
		return ret;
	}

	_idx = searchInDir(dir,"idx");
	if (_idx.empty()) {
		return ret;
	}

	_dict = searchInDir(dir,"dict");
	if (_dict.empty()) {
		return ret;
	}

	return  isDictInvalid();
}

string StarDict::getDictDir() {
	return _dictDir;
}

string StarDict::getResult(const string word) {

}

string StarDict::getIndexWord(int index) {

}

int StarDict::getWordIndex(const string word) {

}

string StarDict::getIndexResult(int index, string &indexWord) {

}

bool StarDict::isDictInvalid() {
	return isDictInvalid(_dictDir);
}

bool StarDict::isDictInvalid(const string dictDir) {
	bool ret = false;
	if (!fileExists(dictDir)) {
		return ret;
	}

	if (!isDICTFileInvalid(_dict)) {
		return ret;
	}

	if (!isIFOInvalid(_ifo)) {
		return ret;
	}

	if (!isIDXInvalid(_idx)) {
		return ret;
	}
	ret = true;
	return ret;
}

void StarDict::setIFO(const string ifo) {
	if (isIFOInvalid(ifo)) {
		_ifo = ifo;
	}
}

void StarDict::setIDX(const string idx) {
	if (isIDXInvalid(idx)) {
		_idx = idx;
	}
}

void StarDict::setDICT(const string dict) {
	if (isDICTFileInvalid(dict)) {
		_dict = dict;
	}
}

string StarDict::getIFO() {
	return _ifo;
}

string StarDict::getIDX() {
	return _idx;
}

string StarDict::getDICT() {
	return _dict;
}

bool StarDict::isIFOInvalid(const string ifo) {
	bool ret = false;
	if (!fileExists(ifo)) {
		return ret;
	}

	if (getFileNackName(ifo) != getFileNackName(_dict)) {
		return ret;
	}
	ret = true;
	return ret;
}

bool StarDict::isIDXInvalid(const string idx) {
	bool ret = false;
	if (!fileExists(idx)) {
		return ret;
	}
	if (getFileNackName(idx) != getFileNackName(_dict)) {
		return ret;
	}
	ret = true;
	return ret;
}

bool StarDict::isDICTFileInvalid(const string dict) {
	if (fileExists(dict)) {
		return true;
	}
	return false;
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
