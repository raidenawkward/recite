#ifndef RCORE_H
#define RCORE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "dictbase.h"
#include "stardict.h"

using namespace std;

enum DictType {
	DICTTYPE_STARDICT,
	DICTTYPE_INVALID
};

class RCore
{
public:
	RCore();
	~RCore();

	bool loadDict(const string dict);
	bool loadDict(const char* dict);
	bool loadDict(DictBase* dictBase);

	string getDictName();
	int getDictWordCount();
	string getDictPath();

	string lookUpWord(const char* word);
	string lookUpWord(const string word);
	string lookUpWord(int index);
	string getIndexWord(int index);

	bool isDictValid();

	DictBase* getDict();
	void setDictType(DictType type);
	DictType getDictType();
	string getDictTypeStr();
	void clearDict();

private:
	DictBase *_dict;
	DictType _dictType;
};


#endif // RCORE_H
