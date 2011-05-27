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
	Reciter();
};


#endif // RECITER_H
