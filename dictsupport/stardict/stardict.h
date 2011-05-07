#ifndef STARDICT_H
#define STARDICT_H


#include <stdlib.h>
#include <stdio.h>
#include "dictbase.h"
#include "dict_idx.h"


class StarDict : public DictBase
{
public:
	StarDict();
	StarDict(const string dir);

	virtual ~StarDict();

	bool setDict(const string dir);
	string getDictPath();
	string getResult(const string word);

	string getIndexWord(int index);
	int getWordIndex(const string word);

	string getIndexResult(int index, string &indexWord);
	string getIndexResult(int index);

	bool isDictValid();
	bool isDictValid(const string dictDir);

	int getWordCount();
	string getDictName();

	string getIFO();
	string getIDX();
	string getDICT();
private:
	void setIFO(const string ifo);
	void setIDX(const string idx);
	void setDICT(const string dict);

	WORD_IDX* getWordIndexInDict(const string word);
	string getIndexWord(WORD_IDX* wordIndex);

protected:
	virtual bool isIFOValid(const string ifo);
	virtual bool isIDXValid(const string idx);
	virtual bool isDICTFileValid(const string dict);

private:
	string _dictDir;
	string _ifo;
	string _idx;
	string _dict;
	WORD_IDX* _wordIndex;
	DICT_INFO* _dictInfo;
};


#endif // STARDICT_H
