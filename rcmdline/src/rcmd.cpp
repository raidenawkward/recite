#include "rcmd.h"

RParamList::RParamList() {
}

void RParamList::addParam(const string param) {
	if (existParam(param))
		return;
	this->push_back(param);
}

bool RParamList::removeParam(const string param) {
	bool ret = false;
	if (param.empty())
		return ret;
	vector<string>::iterator it = this->begin();
	do {
		if (*it == param) {
			this->erase(it);
			ret = true;
		} else
			++it;
	} while (it != this->end());
	return ret;
}

bool RParamList::removeParam(int index) {
	bool ret = false;
	if (index < 0 || index > this->size())
		return ret;
	vector<string>::iterator it = this->begin() + index;
	this->erase(it);
	return true;
}

bool RParamList::existParam(const string param) {
	return (indexOf(param) != -1);
}

int RParamList::indexOf(const string param) {
	int ret = -1;
	if (param.empty())
		return ret;
	for (int i = 0; i < this->size(); ++i) {
		if (this->at(i) == param)
			return i;
	}
	return ret;
}

string RParamList::at(int index) {
	if (index < 0 || index > this->size())
		return string();
	return this->at(index);
}

int RParamList::count() {
	return this->size();
}


//////////////////////////////////// class RCMD //////////////////////////////////



RCMD::RCMD(int argc, char** argv) {
	loadArgv(argc,argv);
}

RCMD::RCMD(RCMD& cmd) {
	_paramList = cmd.getParamList();
}

RCMD::RCMD(RParamList& params) {
	_paramList = params;
}

RCMD::~RCMD() {
}

int RCMD::loadArgv(int argc, char** argv) {
	if (!argc || !argv)
		return 0;
	_paramList.clear();
	for (int i = 0; i < argc; ++i) {
		_paramList.addParam(string(argv[i]));
	}
	return _paramList.size();
}

RParamList& RCMD::getParamList() {
	return _paramList;
}

