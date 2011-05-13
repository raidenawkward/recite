#ifndef RPROP_H
#define RPROP_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "rhistfile.h"

using namespace std;

class RPropItem : public pair<string,string>
{
public:
	RPropItem() {}
	RPropItem(const string prop,const string value);
	RPropItem(const string prop,int value);
	string prop();
	string value();

	void setProp(const string prop);
	void setValue(const string value);
	void setValue(int value);
};

class RPropSet : public vector<RPropItem>
{
public:
	RPropSet();
	RPropSet(RIniFile *file);

	bool addItem(RPropItem &item); //< false would be returned if no item found
	RPropItem getItem(const string key);
	RPropItem getItem(int index);

	bool setValue(const string key,const string value);
	bool setValue(const string key,int value);
	bool remove(const string key);
	bool remove(int index);

	string getStr(const string key);
	int getInt(const string key);
	int getIndex(const string key);//< -1 returns if not found

	bool saveToIni();
	bool saveToIni(RIniFile *file);
	void traverse();

protected:
	void loadFromIni(RIniFile* file);

protected:
	RIniFile *_ini;
};

#endif // RPROP_H
