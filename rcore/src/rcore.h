#ifndef RCORE_H
#define RCORE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "rhistfile.h"
#include "rprop.h"
#include "dictbase.h"
#include "stardict.h"
#include "md5.h"
#include "rtime.h"
#include "rrecord.h"
#include "defines.h"

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

	static DictType checkDictType(const string path);

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

	bool addUser(const string name);
	bool delUser(const string name);

	bool setUserMail(const string mail);
	string getUserMail();

	bool setUserDict(const string dict);

	bool loadRecords();//< default record file
	bool loadRecords(const string path);//< dict, user...
	string getCoreRecordPath() { return _rcoreRecorePath; }

	bool saveRecords();
	bool saveRCoreRecord();
	bool saveUserRecord();
	bool saveDictRecord();

protected:
	bool loadRCoreRecord(const string path);
	bool loadUserRecord(const string path);
	bool loadDictRecord(const string path);

private:
	DictBase *_dict;
	DictType _dictType;

	string _rcoreRecorePath;
	RCoreRecord* _rcoreRecord;
	UserRecord* _userRecord;
	DictRecord* _dictRecord;
};


#endif // RCORE_H
