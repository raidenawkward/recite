#ifndef DICTBASE_H
#define DICTBASE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>


using namespace std;

#define DICT_EMPTY_RESULT "<NULL>"

class DictBase
{
public:
	DictBase();
	virtual ~DictBase();

	virtual bool setDict(const string dict) = 0;
	virtual string getDictDir() = 0;
	virtual string getResult(const string word) = 0;
	virtual string getIndexWord(int index) = 0;
	virtual int getWordIndex(const string word) = 0;
	virtual string getIndexResult(int index, string &indexWord) = 0;
	virtual string getIndexResult(int index) = 0;

	virtual int getWordCount() = 0;
	virtual string getDictName() = 0;

	virtual bool isDictInvalid() = 0;
	virtual bool isDictInvalid(const string dict) = 0;
};


#endif //define DICTBASE_H
