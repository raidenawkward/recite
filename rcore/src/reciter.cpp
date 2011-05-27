#include "reciter.h"
#include <sstream>

string longToString(long l) {
	stringstream ss;
	string ret;
	ss << l;
	ss >>ret;
	return ret;
}

string RIndexList::generateListStr() {
	string ret;
	if (!count())
		return ret;
	for (int i = 0; i < count(); ++i) {
		string item = longToString(this->at(i));
		if (item.empty())
			continue;
		ret += item;
		if (i != count() - 1)
			ret += ' ';
	}
	return ret;
}

int RIndexList::loadFromListStr(const string str) {
	if (str.empty())
		return 0;
	this->clear();
	stringstream ss(str);
	string item;
	while(getline(ss,item,' ')) {
		this->push_back(atol(item.c_str()));
	}
	return count();
}

int RIndexList::count() {
	return this->size();
}

void RIndexList::append(long l) {
	this->push_back(l);
}



/////////////////////  class RDiet /////////////////////

RDiet::RDiet(const string dir)
	:RecordBase()
	,_dir(dir) {
	load(_date);
}

RDiet::RDiet(RDate& date, const string dir)
	:RecordBase()
	,_dir(dir) {
	load(date);
}

bool RDiet::insertIndex(long index) {
	if (index < 0 || _dir.empty())
		return false;
	_dietList.append(index);
	return true;
}

void RDiet::setDir(const string dir) {
	if (dir.empty())
		return;
	_dir = dir;
}

bool RDiet::save() {
	if (_dir.empty() || !_record)
		return false;
	string path = _dir;
	path += _date.getDateSerialString();

	string list_str = _dietList.generateListStr();
	_record->setValue(RDIET_LIST_KEY,list_str);

	return RecordBase::save(path);
}

bool RDiet::load(RDate& date) {
	if (_dir.empty())
		return false;
	_date = date;
	string path = _dir;
	path += _date.getDateSerialString();
	RecordBase::setPath(path);
	if (!_record)
		return false;
	string list_str = _record->getStr(RDIET_LIST_KEY);
	_dietList.loadFromListStr(list_str);
	return (_record->size() != 0);
}



/////////////////////  class Reciter /////////////////////


