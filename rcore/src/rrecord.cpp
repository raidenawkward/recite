#include "rrecord.h"

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
