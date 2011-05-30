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
#include "reciter.h"

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
	static string getDictName(const string path);
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

	bool existUser(const string name);
	bool switchUser(const string name);
	bool addUser(const string name);
	bool delUser(const string name);
	string getCurrentUser();

	bool setCurrentUserMail(const string mail);
	string getCurrentUserMail();

	bool setUserDictDir(const string dict);

	bool loadRecords();//< default record file
	bool loadRecords(const string path);//< dict, user...

	string getCoreRecordPath() { return _rcoreRecorePath; }
	string getUserDir(const string user = string());// unimplemented
	string getUserDictDir(const string dictname, const string user = string());// unimplemented

	bool saveRecords();
	bool saveRCoreRecord();
	bool saveUserRecord();
	bool saveDictRecord();

	// for recite
	bool saveReciteRecord();
	int getNextWordToday();
	int getPrevWordToday();
	int getWordCountToday();
	int getWordCountHaveRecite();

	void getWordList(const RDate& date);

protected:
	bool loadRCoreRecord(const string path);
	bool loadUserRecord(const string path);
	bool loadDictRecord(const string path);

	// for recite
	int generateReciteList(const RDate& date);

private:
	DictBase *_dict;
	DictType _dictType;

	string _rcoreRecorePath;
	RCoreRecord* _rcoreRecord;
	UserRecord* _userRecord;
	DictRecord* _dictRecord;

	// for recite
	RDate _today;
};


#endif // RCORE_H
