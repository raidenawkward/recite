#ifndef RRECORD_H
#define RRECORD_H

#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "dictbase.h"

using namespace std;


class RecordBase
{
public:
	RecordBase();
	RecordBase(const string path);

	void setPath(const string path);
	string getPath();

	virtual bool load();
	virtual bool load(const string path);
	virtual bool save();
	virtual bool save(const string path);

private:
	string _path;
};

class DictRecord : public RecordBase
{
public:
	DictRecord();
	DictRecord(const string recordPath);
	~DictRecord();

	void setDict(DictBase *dict);
	DictBase* getDict();

	bool save();
	bool save(const string recordPath);

private:
	DictBase *_dict;
};

class UserRecord : public RecordBase
{
public:
	UserRecord();
	~UserRecord();
};



#endif // RRECORD_H
