#ifndef RECITER_H
#define RECITER_H


#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

#include "defines.h"
#include "rtime.h"
#include "rrecord.h"
#include "rindexgenerator.h"

string longToString(long l);

class RIndexList : public vector<long>
{
public:
	string generateListStr();
	int loadFromListStr(const string str);
	int count();

	void append(long l);
};

class RDiet : public RecordBase
{
public:
	RDiet(const string dir);
	RDiet(RDate& date,const string dir);

	bool insertIndex(long index);
	bool save();
	bool load(RDate& date);

	RIndexList& getList() { return _dietList; }
	RDate& getDate() { return _date; }

protected:
	void setDir(const string dir);

private:
	RDate _date;
	RIndexList _dietList;
	string _dir;
};



class Reciter
{
public:
	Reciter(const string dir, RDate date = RDate());

	RIndexList getIndexList();
	bool saveRecord();
	RDate getDate();
	bool setDate(RDate& date);


	void setIndexGenerator(IndexGeneratorBase* generator) { _indexGenerator = generator; }
	IndexGeneratorBase* getIndexGenerator() { return _indexGenerator; }

	void setDict(DictBase* dict) { _dict = dict; }
	DictBase* getDict() { return _dict; }

	long getNextIndex();
	long getPrevIndex();
	long getIndex(int index);
	int currentIndex();
	int wordCount();

protected:
	virtual void loadIndexGenerator();

private:
	RDiet *_diet;
	IndexGeneratorBase *_indexGenerator;
	DictBase* _dict;
	int _currentIndex;
};


#endif // RECITER_H
