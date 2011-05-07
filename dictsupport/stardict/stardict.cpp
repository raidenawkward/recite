#include "stardict.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <dirent.h>

#include "dict_info.h"

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
	int pos = fileName.rfind(".");
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
				return dir + string("/") + file;
			}
		}
		closedir( dirp );
	}
	return string();
}

StarDict::StarDict() {
	_wordIndex = NULL;
	_dictInfo = NULL;
}

StarDict::StarDict(const string dir) {
	_wordIndex = NULL;
	_dictInfo = NULL;
	setDict(dir);
}

StarDict::~StarDict() {
	if (_wordIndex)
		free(_wordIndex);
}

bool StarDict::setDict(const string dir) {
	bool ret = false;
	if (_wordIndex) {
		free(_wordIndex);
		_wordIndex = NULL;
	}
	if (_dictInfo) {
		free(_dictInfo);
		_dictInfo = NULL;
	}
	
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

	_dictInfo = get_dict_info((char*)_ifo.c_str());
	_wordIndex = (WORD_IDX*)malloc(sizeof(WORD_IDX)*_dictInfo->word_count);

	return  isDictInvalid();
}

string StarDict::getDictDir() {
	return _dictDir;
}

WORD_IDX* StarDict::getWordIndexInDict(const string wordToCheck) {
	get_words((char*)_idx.c_str(),_dictInfo,_wordIndex);
	WORD_IDX* word = get_idx((char*)wordToCheck.c_str(),_wordIndex,_dictInfo);
	return word;
}

string StarDict::getIndexWord(WORD_IDX* index) {
	if (index == NULL) {
		return string(DICT_EMPTY_RESULT);
	}

	FILE* fp_dict = fopen(_dict.c_str(),"r");
	if(fp_dict == NULL) {
		return string(DICT_EMPTY_RESULT);
	}

	if(fseek(fp_dict,index->offset,SEEK_SET)) {
		return string(DICT_EMPTY_RESULT);
	}
	char explain[index->length + 1];
	memset(explain,'\0',index->length + 1);
	fread(explain,index->length,1,fp_dict);
	return string(explain);
}

string StarDict::getResult(const string wordToCheck) {
	// word_index is one of _wordIndex, need not to free
	WORD_IDX* word_index = getWordIndexInDict(wordToCheck);
	string ret = getIndexWord(word_index);
	return ret;
}

string StarDict::getIndexWord(int index) {
	string ret;
	if (!_dictInfo)
			return ret;
	if (index < 0 || index > _dictInfo->word_count)
		return ret;
	WORD_IDX* word_index = &_wordIndex[index];
	ret = string(word_index->word);
	return ret;
}

int StarDict::getWordIndex(const string word) {
	int head = 0;
	int tail = 0;
	int mid = 0;
	while (head < tail - 1) {
		mid = (tail + head) >> 1;
		int cmp = strcasecmp(word.c_str(), _wordIndex[mid].word);
		if (cmp == 0) {
			return mid;
		} else if (cmp < 0) {
			tail = mid;
		} else {
			head = mid;
		}
	}
	return -1;
}

string StarDict::getIndexResult(int index, string &indexWord) {
	indexWord = getIndexWord(index);
	if (!indexWord.empty()) {
		return getResult(indexWord);
	}
	return string();
}

string StarDict::getIndexResult(int index) {
	return getResult(getIndexWord(index));
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

	ret = (_wordIndex && _dictInfo);

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

int StarDict::getWordCount() {
	if (_dictInfo)
		return _dictInfo->word_count;
	return 0;
}

string StarDict::getDictName() {
	string ret;
	if (_dictInfo)
		return _dictInfo->book_name;
	return ret;
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

#if 0
int main(int argc, char** argv) {
	StarDict *stardict = new StarDict("../dict/stardict-langdao-ec-gb-2.4.2/");

	DictBase *base = stardict;

	if (!base->isDictInvalid()) {
		printf("dict invalid !\n");
		return -1;
	}
	printf("ifo : %s\nidx : %s\ndict : %s\n",stardict->getIFO().c_str(),stardict->getIDX().c_str(),stardict->getDICT().c_str());

	/*for (int i = 1; i < argc; ++i) {
		printf("searching : %s\n",argv[i]);
		string result = base->getResult(string(argv[i]));
		printf("result : \n");
		printf("%s\n",result.c_str());
	}*/
	printf("dict name : %s\n",base->getDictName().c_str());

	for (int i = 100; i < 109; ++i) {
		printf("checking index(%d) : %s\n",i,base->getIndexWord(i).c_str());
		printf("%s\n",base->getIndexResult(i).c_str());
	}
	return 0;
}

#endif
