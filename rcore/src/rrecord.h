#ifndef RRECORD_H
#define RRECORD_H

#include <stdlib.h>
#include <stdio.h>
#include <string>

#include "dictbase.h"
#include "rhistfile.h"
#include "md5.h"
#include "rprop.h"

using namespace std;


class RecordBase
{
public:
	RecordBase();
	RecordBase(const string path);
	RecordBase(RIniFile* ini);
	~RecordBase();

	void setPath(const string path);
	void setIni(RIniFile* ini);
	void setProp(RPropSet* prop);

	string getPath();
	RPropSet* getProps() { return _record; }

	virtual bool save();
	virtual bool save(const string path);
	virtual bool save(RIniFile* ini);

protected:
	RIniFile *_ini;
	RPropSet *_record;
};

class DictRecord : public RecordBase
{
public:
	DictRecord();
	DictRecord(const string path);
	DictRecord(RIniFile* ini);
	~DictRecord();

	void setDict(DictBase *dict);
	DictBase* getDict();

	void setDictPath(const string path);
	string getDictPath();

	void setDictMd5(const string md5);
	string getDictMd5();

	void setDictWordCount(int count);
	int getDictWordCount();

	void setDictName(const string dictName);
	string getDictName();

	void setDictStartDate(const string date);
	string getDictStartDate();

private:
	DictBase *_dict;
};

class UserRecord : public RecordBase
{
public:
	UserRecord();
	UserRecord(const string path);
	UserRecord(RIniFile* ini);
	~UserRecord();

	void setUserName(const string name);
	string getUserName();

	void setMail(const string mail);
	string getMail();

	void setRegistDate(const string date);
	string getRegistDate();
};



#endif // RRECORD_H
