#ifndef STARDICT_H
#define STARDICT_H


#include <stdlib.h>
#include <stdio.h>
#include "dictbase.h"


#define DICTPATH_LENGTH 1024



class StarDict : public DictBase
{
public:
	StarDict();
	StarDict(const string dir);

	virtual ~StarDict();

	bool setDict(const string dir);
	string getDictDir();
	string getResult(const string word);
	string getIndexWord(int index);
	int getWordIndex(const string word);
	string getIndexResult(int index, string &indexWord);

	bool isDictInvalid();
	bool isDictInvalid(const string dict);

private:
	void setDir(const string dir);
	void setIFO(const string ifo);
	void setIDX(const string idx);
	void setDICT(const string dict);

	string getIFO();
	string getIDX();
	string getDICT();

protected:
	virtual bool isIFOInvalid(const string ifo);
	virtual bool isIDXInvalid(const string idx);
	virtual bool isDICTInvalid(const string dict);

private:
	string _dictDir;
	string _ifo;
	string _idx;
	string _dict;
};


#endif // STARDICT_H
