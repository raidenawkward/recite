#ifndef DICTBASE_H
#define DICTBASE_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class DictBase
{
public:
	DictBase(){};
	virtual ~DictBase(){};

	virtual bool setDict(const char* dict) = 0;
	virtual char* getDictDir() = 0;
	virtual char* getResult(const char* word) = 0;
	virtual char* getIndexWord(int index) = 0;
};


#endif //define DICTBASE_H
