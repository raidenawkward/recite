#include "rcore.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

string get_abs_path(const string file);
string get_name_from_path(const string path);

RCore::RCore()
	:_dict(NULL)
	,_rcoreRecord(NULL)
	,_dictRecord(NULL)
	,_userRecord(NULL)
	,_dictType(DICTTYPE_INVALID)
{
}

RCore::~RCore() {
	saveRCoreRecord();
	clearDict();
}

DictType RCore::checkDictType(const string path) {
	return DICTTYPE_STARDICT;
}

bool RCore::loadDict(const string dict) {
	clearDict();
	bool ret = false;
	// star dict checking
	DictType type = checkDictType(dict);
	switch (type) {
		case DICTTYPE_STARDICT:
		{
			StarDict *stardict = new StarDict();
			if (stardict->setDict(dict)) {
				if (stardict->isDictValid()) {
					setDictType(type);
					return loadDict(stardict);
				}
			}
		}
		break;
		case DICTTYPE_INVALID:
		default:
		break;
	}// switch
	return ret;
}

bool RCore::loadDict(const char* dict) {
	if (!dict)
		return false;
	return loadDict(string(dict));
}

bool RCore::loadDict(DictBase *dict) {
	if (!dict)
		return false;
	if (!dict->isDictValid())
		return false;
	clearDict();
	_dict = dict;
		return true;
}

string RCore::getDictName(const string dict) {
	DictType type = checkDictType(dict);
	switch (type) {
		case DICTTYPE_STARDICT:
		{
			StarDict *stardict = new StarDict();
			if (stardict->setDict(dict)) {
				if (stardict->isDictValid()) {
					return stardict->getDictName();
				}
			}
		}
		break;
		case DICTTYPE_INVALID:
		default:
		break;
	}// switch
	return string();

}

string RCore::getDictName() {
	string ret;
	if (isDictValid())
		ret = _dict->getDictName();
	return ret;
}

int RCore::getDictWordCount() {
	int ret = 0;
	if (isDictValid())
		ret = _dict->getWordCount();
	return ret;
}

string RCore::getDictPath() {
	string ret;
	if (isDictValid())
		ret = _dict->getDictPath();
	return ret;
}

string RCore::lookUpWord(const string word) {
	string ret;
	if (isDictValid())
		ret = _dict->getResult(word);
	return ret;
}

string RCore::lookUpWord(const char* word) {
	return lookUpWord(string(word));
}

string RCore::lookUpWord(int index) {
	string ret;
	if (index >=0
		&& index < getDictWordCount())
		ret = _dict->getIndexResult(index);
	return ret;
}

string RCore::getIndexWord(int index) {
	string ret;
	if (index >=0
		&& index < getDictWordCount())
		ret = _dict->getIndexWord(index);
	return ret;
}

bool RCore::isDictValid() {
	if (!_dict)
		return false;
	return _dict->isDictValid();
}

void RCore::setDictType(DictType type) {
	_dictType = type;
}

DictType RCore::getDictType() {
	return _dictType;
}

string RCore::getDictTypeStr() {
	string ret;
	switch (_dictType) {
		case DICTTYPE_STARDICT:
			ret = "Star Dict";
			break;
		case DICTTYPE_INVALID:
		default:
			ret = "Unknown dict";
			break;
	}
	return ret;
}

void RCore::clearDict() {
	if (_dict)
		delete _dict;
	_dict = NULL;
}

bool RCore::existUser(const string name) {
	return access(name.c_str(),0) == 0;
}

bool RCore::addUser(const string name) {
	if (!_rcoreRecord)
		return false;
	string path = _rcoreRecord->getUserRecordsDir() + name;
	if (existUser(path)) {
		return false;
	}
	path += get_path_spliter();
	path += "user.ini";
	if (!_userRecord) {
		_userRecord = new UserRecord();
	}
	_userRecord->setPath(path);
	if (_userRecord->getUserName() == name) {
		return false;
	}
	_userRecord->setUserName(name);
	saveUserRecord();
	return true;
}

bool RCore::switchUser(const string user) {
	if (!_rcoreRecord)
		return false;
	string path = _rcoreRecord->getUserRecordsDir() + user;
	if (!existUser(path)) {
		return false;
	}
	path += get_path_spliter();
	path += "user.ini";
	if (!_userRecord) {
		_userRecord = new UserRecord();
	}
	_userRecord->setPath(path);
	_rcoreRecord->setCurrentUser(user);
	saveUserRecord();
}

bool RCore::delUser(const string name) {
}

string RCore::getCurrentUser() {
	if (!_rcoreRecord)
		return string();
	return _rcoreRecord->getCurrentUser();
}

bool RCore::setCurrentUserMail(const string mail) {
	if (!_userRecord)
		return false;
	_userRecord->setMail(mail);
	return saveUserRecord();
}

string RCore::getCurrentUserMail() {
	return _userRecord->getMail();
}

string getDictRestoreName(const string dictPath) {
//mkdir(getDirFromPath(path).c_str(),S_IRWXU);
	return get_name_from_path(dictPath);
}

bool RCore::setUserDictDir(const string dictpath) {
	if (!_userRecord || !_dictRecord)
		return false;
	string dict = get_abs_path(dictpath);
	string dict_name = getDictName(dict);
	if (dict_name.empty())
		return false;
	_userRecord->setCurrentDict(dict);
	_userRecord->setCurrentDictName(dict_name);

	string dict_record_path = _rcoreRecord->getUserRecordsDir() + _rcoreRecord->getCurrentUser();

	dict_record_path += get_path_spliter();

	mkdir(dict_record_path.c_str(),S_IRWXU);// may useless code
	dict_record_path += getDictRestoreName(dictpath);
	mkdir(dict_record_path.c_str(),S_IRWXU);

	dict_record_path += get_path_spliter();
	dict_record_path += "dict.ini";

	DictRecord* tmp_dict_record = new DictRecord(dict_record_path);
	printf("dict record path : %s\n",dict_record_path.c_str());
	printf("dict record name : %s\n",_dictRecord->getDictName().c_str());
	if (_dictRecord->getDictPath().empty()
		|| _dictRecord->getDictName() != tmp_dict_record->getDictName()) {
		_dictRecord->save();
		delete _dictRecord;
		_dictRecord = tmp_dict_record;
	} else {
		delete tmp_dict_record;
	}
	loadDict(dict);
	saveDictRecord();
	saveUserRecord();
	return true;
}

bool RCore::loadRecords() {
	return loadRecords(RECORD_CORE_PATH);
}

bool RCore::loadRecords(const string path) {
	bool ret = false;
	if (path.empty())
		return ret;

	if (!loadRCoreRecord(path)) {
		return ret;
	}

	string user_record_path = _rcoreRecord->getUserRecordsDir() + _rcoreRecord->getCurrentUser();
	user_record_path += get_path_spliter();
	user_record_path += "user.ini";
	if (!loadUserRecord(user_record_path)) {
		;//return ret;
	}
	_rcoreRecorePath = user_record_path;
	string dict_record_path = _userRecord->getCurrentDict();

	if (!loadDictRecord(dict_record_path)) {
		//return ret;
		// currently do nothing
	}
	loadDict(dict_record_path);

	return true;
};

bool RCore::saveRecords() {
	bool ret = true;
	if (!saveRCoreRecord())
		ret = false;
	if (!saveUserRecord())
		ret = false;
	if (!saveDictRecord())
		ret = false;
	return ret;
}

bool RCore::saveRCoreRecord() {
	if(!_rcoreRecord)
		return false;
	return _rcoreRecord->save();
};

bool RCore::saveUserRecord() {
	if (!_userRecord)
		return false;
	return _userRecord->save();
};

bool RCore::saveDictRecord() {
	if (!_dictRecord || !_dict)
		return false;
	_dictRecord->setDictPath(_dict->getDictPath());
	_dictRecord->setDictName(_dict->getDictName());
	_dictRecord->setDictWordCount(_dict->getWordCount());
	return _dictRecord->save();
};

bool makeDefaultRCoreConfig(const string path,RCoreRecord* coreRecord = NULL) {
	mkdir(getDirFromPath(path).c_str(),S_IRWXU);
	mkdir (RECORD_DEFAULT_USER_DIR,S_IRWXU);
	RCoreRecord *record = new RCoreRecord(path);
	record->setUserRecordsDir(RECORD_DEFAULT_USER_DIR);
	record->setCurrentUser("guest");

	bool res = record->save();
	if (res && coreRecord) {
		coreRecord->setPath(path);
		return true;
	}
	return false;
}

bool RCore::loadRCoreRecord(const string path) {
	if (path.empty())
		return false;
	if (_rcoreRecord) {
		delete _rcoreRecord;
	}
	_rcoreRecord = new RCoreRecord(path);

	if (_rcoreRecord->getUserRecordsDir().empty()) {
		return makeDefaultRCoreConfig(path,_rcoreRecord);
	}
	return true;
}

bool makeDefaultUserConfig(const string path, UserRecord* recorder = NULL) {
	mkdir(RECORD_DEFAULT_USER_DIR,S_IRWXU);
	mkdir(getDirFromPath(path).c_str(),S_IRWXU);
	UserRecord *tmp_record = new UserRecord(path);
	if (tmp_record->save() && recorder) {
		recorder->setPath(path);
		return true;
	}
	return false;
}

bool RCore::loadUserRecord(const string path) {
	if (_userRecord) {
		delete _userRecord;
	}
	_userRecord = new UserRecord(path);
	if (_userRecord->getUserName().empty()) {
		return makeDefaultUserConfig(path,_userRecord);
	}
	return true;
}

bool RCore::loadDictRecord(const string path) {
	if (_dictRecord) {
		delete _dictRecord;
	}
	_dictRecord = new DictRecord(path);
	return !_dictRecord->getDictPath().empty();
}

string get_abs_path(const string file) {
	string ret = file;
	if (file.at(0) == get_path_spliter())
		return ret;
	ret = get_current_dir_name();
	ret += get_path_spliter();
	return ret + file;
}

string get_name_from_path(const string path) {
	int length = path.length();
	string tmp;
	for (int i = length - 1; i >= 0; --i) {
		char ch = path.at(i);
		if (ch == get_path_spliter() && i == length - 1) {
			continue;
		}
		if (ch == get_path_spliter()) {
			break;
		}
		tmp += ch;
	}
	if (tmp.empty()) {
		return tmp;
	}
	string ret;
	for (int j = tmp.length() - 1; j >=0; --j) {
		ret += tmp.at(j);
	}
	return ret;
}
