#include "rcore.h"

RCore::RCore()
	:_dict(NULL)
	,_rcoreRecord(NULL)
	,_dictRecord(NULL)
	,_userRecord(NULL)
	,_dictType(DICTTYPE_INVALID)
{
}

RCore::~RCore() {
	clearDict();
}

DictType RCore::checkDictType(const string path) {
	return DICTTYPE_STARDICT;
}

bool RCore::loadDict(const string dict) {
	clearDict();

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
	return false;
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
	if (_dictRecord) {
		_dictRecord->setDictPath(_dict->getDictPath());
		_dictRecord->setDictName(_dict->getDictName());
		_dictRecord->setDictWordCount(_dict->getWordCount());
	}
	return true;
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

bool RCore::addUser(const string name) {
}

bool RCore::delUser(const string name) {
}

bool RCore::setUserMail(const string mail) {
}

string RCore::getUserMail() {
}

bool RCore::setUserDict(const string dict) {
}

bool RCore::loadRecords() {
	return loadRecords(RECORD_CORE_PATH);
}

bool RCore::loadRecords(const string path) {
	bool ret = false;
	if (path.empty())
		return ret;

	if (!loadRCoreRecord(path))
		return ret;

	string user_record_path = _rcoreRecord->getUserRecordDir() + _rcoreRecord->getCurrentUser();
#ifdef WIN32
	user_record_path += "\\user.ini";
#else
	user_record_path += "/user.ini";
#endif
	if (!loadUserRecord(user_record_path))
		return ret;

	_rcoreRecorePath = user_record_path;
	string dict_record_path = _userRecord->getCurrentDict();
	if (!loadDictRecord(dict_record_path))
		return ret;

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
	if (!_dictRecord)
		return false;
	return _dictRecord->save();
};

bool RCore::loadRCoreRecord(const string path) {
	if (_rcoreRecord) {
		delete _rcoreRecord;
	}
	_rcoreRecord = new RCoreRecord(path);
	return !_rcoreRecord->getUserRecordDir().empty();
}

bool RCore::loadUserRecord(const string path) {
	if (_userRecord) {
		delete _userRecord;
	}
	_userRecord = new UserRecord(path);
	return !_userRecord->getUserName().empty();
}

bool RCore::loadDictRecord(const string path) {
	if (_dictRecord) {
		delete _dictRecord;
	}
	_dictRecord = new DictRecord(path);
	return !_dictRecord->getDictPath().empty();
}
