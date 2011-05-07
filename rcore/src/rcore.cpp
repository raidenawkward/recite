#include "rcore.h"

RCore::RCore()
	:_dict(NULL)
	,_dictType(DICTTYPE_INVALID)
{
}

RCore::~RCore() {
	clearDict();
}

bool RCore::loadDict(const string dict) {
	clearDict();

	// star dict checking
	if (!_dict) {
		StarDict *stardict = new StarDict();
		if (stardict->setDict(dict)) {
			if (stardict->isDictValid()) {
				_dict = stardict;
				setDictType(DICTTYPE_STARDICT);
			}
		}
	}
	// other dict checking
	// if (!_dict) { }
	return (_dict != NULL);
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
