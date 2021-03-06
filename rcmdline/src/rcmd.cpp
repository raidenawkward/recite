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
	return vector<string>::at(index);
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

bool RCMD::isCMD(const string str) {
	if (str.empty())
		return true;
	return str[0] == '-';
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

int RCMD::parseCMD(RCMD_callback* cb) {
	if (!cb)
		return 0;
	int i = 0;
	while(i < _paramList.size()) {
		string tmp = _paramList.at(i);
		int cmd = cb->getCMD(tmp);
		if (cmd != 0) {
			_cmdList.push_back(cmd);
			RParamList list;
			++i;
			while (i < _paramList.size()) {
				string next = _paramList.at(i);
				if (!RCMD::isCMD(next)) {
					list.push_back(next);
					++i;
				} else {
					break;
				}
			}
			_paramLists.push_back(list);
		} else {
			_unParsed.push_back(tmp);
			++i;
		}
	}
	return _cmdList.size();
}

RParamList& RCMD::getParamList() {
	return _paramList;
}

