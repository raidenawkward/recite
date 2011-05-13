#include "rrecord.h"
#include "defines.h"

RecordBase::RecordBase()
			:_ini(NULL) {
	_record = new RPropSet;
}

RecordBase::RecordBase(const string path) {
	_ini = NULL;
	_record = new RPropSet;
	setPath(path);
}

RecordBase::RecordBase(RIniFile* ini) {
	_ini = NULL;
	_record = new RPropSet;
	setIni(ini);
}

RecordBase::~RecordBase() {
	if (_record)
		delete _record;
}

void RecordBase::setPath(const string path) {
	_ini = new RIniFile(path);
}

void RecordBase::setIni(RIniFile* ini) {
	_ini = ini;
}

void RecordBase::setProp(RPropSet* prop) {
	if (_record)
		delete _record;
	_record = prop;
}

string RecordBase::getPath() {
	string ret;
	if (!_ini)
		return ret;
	return _ini->getPath();
}

bool RecordBase::save() {
	if (!_ini || !_record)
		return false;
	return _record->saveToIni(_ini);
}

bool RecordBase::save(const string path) {
	if (path.empty() || !_record)
		return false;
	setPath(path);
	return _record->saveToIni(_ini);
}

bool RecordBase::save(RIniFile* ini) {
	if (!ini || !_record)
		return false;
	setIni(ini);
	return _record->saveToIni(_ini);
}



//////////////////////  class DictRecord ////////////////////////



DictRecord::DictRecord()
			:RecordBase() {

}

DictRecord::DictRecord(const string path)
			:RecordBase(path) {

}

DictRecord::DictRecord(RIniFile* ini)
			:RecordBase(ini) {

}

void DictRecord::setDict(DictBase* dict) {
	_dict = dict;
	if (!_dict)
		return;
	if (!_dict->isDictValid())
		return;
	setDictPath(_dict->getDictPath());
	setDictWordCount(_dict->getWordCount());
	setDictName(_dict->getDictName());
}

DictBase* DictRecord::getDict() {
	return _dict;
}

void DictRecord::setDictPath(const string path) {
	if (!_record)
		return;
	_record->setValue(INI_KEY_DICT_PATH,path);
}

string DictRecord::getDictPath() {
	if (!_record)
		return string();
	return _record->getStr(INI_KEY_DICT_PATH);
}

void DictRecord::setDictMd5(const string md5) {
	if (!_record)
		return;
	_record->setValue(INI_KEY_DICT_MD5,md5);
}

string DictRecord::getDictMd5() {
	if (!_record)
		return string();
	return _record->getStr(INI_KEY_DICT_MD5);
}

void DictRecord::setDictWordCount(int count) {
	if (!_record)
		return;
	_record->setValue(INI_KEY_DICT_WORDCOUNT,count);
}

int DictRecord::getDictWordCount() {
	if (!_record)
		return 0;
	return _record->getInt(INI_KEY_DICT_WORDCOUNT);
}

void DictRecord::setDictName(const string name) {
	if (!_record)
		return;
	_record->setValue(INI_KEY_DICT_NAME,name);
}

string DictRecord::getDictName() {
	if (!_record)
		return string();
	return _record->getStr(INI_KEY_DICT_NAME);
}

void DictRecord::setDictStartDate(const string date) {
	if (!_record)
		return;
	_record->setValue(INI_KEY_DICT_STARTDATE,date);
}

string DictRecord::getDictStartDate() {
	if (!_record)
		return string();
	return _record->getStr(INI_KEY_DICT_STARTDATE);
}



//////////////////////  class UserRecord ////////////////////////


UserRecord::UserRecord()
			:RecordBase() {
}

UserRecord::UserRecord(const string path)
			:RecordBase(path) {

}

UserRecord::UserRecord(RIniFile* ini)
			:RecordBase(ini) {

}

UserRecord::~UserRecord() {

}

void UserRecord::setUserName(const string name) {
	if (!_record)
		return;
	_record->setValue(INI_KEY_USER_NAME,name);
}

string UserRecord::getUserName() {
	if (!_record)
		return string();
	return _record->getStr(INI_KEY_USER_NAME);
}

void UserRecord::setMail(const string mail) {
	if (!_record)
		return;
	_record->setValue(INI_KEY_USER_MAIL,mail);
}

string UserRecord::getMail() {
	if (!_record)
		return string();
	return _record->getStr(INI_KEY_USER_MAIL);
}

void UserRecord::setRegistDate(const string date) {
	if (!_record)
		return;
	_record->setValue(INI_KEY_USER_REGISTDATE,date);
}

string UserRecord::getRegistDate() {
	if (!_record)
		return string();
	_record->getStr(INI_KEY_USER_REGISTDATE);
}
