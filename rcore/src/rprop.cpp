#include "rprop.h"


RPropItem::RPropItem(const string prop, const string value) {
	setProp(prop);
	setValue(value);
}

RPropItem::RPropItem(const string prop, int value) {
	setProp(prop);
	setValue(value);
}

string RPropItem::prop() {
	return this->first;
}

string RPropItem::value() {
	return this->second;
}

void RPropItem::setProp(const string prop) {
	this->first = prop;
}

void RPropItem::setValue(const string value) {
	this->second = value;
}

void RPropItem::setValue(int value) {
	char str[32];
	memset(str,0x00,32);
	sprintf(str,"%d",value);
	this->second = string(str);
}



///////////////////////// class RPropSet ///////////////////////////


RPropSet::RPropSet()
		:_ini(NULL) {
}

RPropSet::RPropSet(RIniFile *file)
		:_ini(file) {
	loadFromIni(file);
}

void RPropSet::loadFromIni(RIniFile* file) {
	if (!file)
		return;
	for (int i = 0; i < file->getRecordCount(); ++i) {
		string key;
		string value;
		value = file->getValue(i,key);
		RPropItem item(key,value);
		addItem(item);
	}
}

int RPropSet::getIndex(const string key) {
	for (int i = 0; i < this->size(); ++i) {
		RPropItem item = this->at(i);
		if (item.prop() == key)
			return i;
	}
	return -1;
}

bool RPropSet::addItem(RPropItem &item) {
	int index = getIndex(item.prop());
	if (index < 0) {
		this->push_back(item);
		return true;
	}
	else {
		this->at(index).setValue(item.value());
		return false;
	}
}

RPropItem RPropSet::getItem(const string key) {
	for (int i = 0; i < this->size(); ++i) {
		RPropItem item = this->at(i);
		if (item.prop() == key) {
			return item;
		}
	}
	RPropItem empty;
	return empty;
}

RPropItem RPropSet::getItem(int index) {
	RPropItem empty;
	if (index < 0 || index >= this->size())
		return empty;
	RPropItem item = this->at(index);
	return item;
}

bool RPropSet::setValue(const string key,const string value) {
	RPropItem item(key,value);
	return addItem(item);
}

bool RPropSet::setValue(const string key, int value) {
	RPropItem item(key,value);
	return addItem(item);
}

bool RPropSet::remove(const string key) {
	int index = getIndex(key);
	return remove(index);
}

bool RPropSet::remove(int index) {
	if (index < 0 || index >= this->size())
		return false;
	this->erase(this->begin() + index);
	return true;
}

string RPropSet::getStr(const string key) {
	string ret = getItem(key).value();
	return ret;
}

int RPropSet::getInt(const string key) {
	string sret = getItem(key).value();
	return atoi(sret.c_str());
}

bool RPropSet::saveToIni() {
	return saveToIni(_ini);
}

bool RPropSet::saveToIni(RIniFile *ini) {
	if (!ini)
		return false;
	ini->clear();
	for (int i = 0; i < this->size(); ++i) {
		RPropItem item = this->at(i);
		ini->setValue(item.prop(),item.value());
	}
	return ini->save();
}

void RPropSet::traverse() {
	for (int i = 0; i < this->size(); ++i) {
		RPropItem item = this->at(i);
		printf("item %d : %s = %s\n",i,item.prop().c_str(),item.value().c_str());
	}
}
