#include "checkcmd.h"

CheckCMD::CheckCMD(int argc, char** argv)
		:RCMD(argc,argv) {
}

CheckCMD::CheckCMD(CheckCMD& cmd)
		:RCMD(cmd) {
}

CheckCMD::CheckCMD(RParamList& params)
		:RCMD(params) {
}

CheckCMD::~CheckCMD() {
}

int CheckCMD::getCMD(const string str) {
	if (!RCMD::isCMD(str))
		return RTYPE_CHECKCMD_NOTCMD;
	if (str == CMD_CHECK_PHRASE_SHORT || str == CMD_CHECK_PHRASE)
		return RTYPE_CHECKCMD_CHECK_PHRASE;
	if (str == CMD_CHECK_WORD_SHORT || str == CMD_CHECK_WORD)
		return RTYPE_CHECKCMD_CHECK_WORD;
	return RTYPE_CHECKCMD_UNKNOWN;
}

#if 0
int CheckCMD::parseCMD() {
	int i = 0;
	while(i < _paramList.size()) {
		string tmp = _paramList.at(i);
		RTYPE_CHECKCMD cmd = getCMD(tmp);
		if (cmd != RTYPE_CHECKCMD_UNKNOWN) {
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
#endif

void CheckCMD::doCommands() {
	for (int i = 0; i < _cmdList.size(); ++i) {
		RParamList params = _paramLists.at(i);
		switch (_cmdList.at(i)) {
			case RTYPE_CHECKCMD_CHECK_WORD:
				check(params);
				break;
			case RTYPE_CHECKCMD_CHECK_PHRASE:
				checkPhrase(params);
				break;
			case RTYPE_CHECKCMD_HELP:
				break;
			default:
				check(params);
				break;
		}
	}
}

void CheckCMD::exec(RCore* core, RUI* ui) {
	if (!core)
		return;
	setCore(core);
	setUI(ui);
	if (!core->isDictValid()) {
		_rui->show_warning(MSG_CMD_CHECK_NODICT);
	}
	RCMD::parseCMD(this);
	doCommands();
	showUnknownCMDs();
}

void CheckCMD::check(RParamList& list) {
	for (int i = 0; i < _paramList.count(); ++i) {
		string word = _paramList.at(i);
			if (word[0] != '-' && word[0] != '/') {
			_rui->show_msg(string("checking ") + word + string(":"));
			_rui->show_check_result(_rcore->lookUpWord(word.c_str()));
			if (i != _paramList.count() - 1)
				_rui->show_check_result_spliter();
		}
	}
}

void CheckCMD::checkPhrase(RParamList& list) {
	string phrase;
	for (int i = 0; i < _paramList.count(); ++i) {
		string word = _paramList.at(i);
		if (word[0] != '-' && word[0] != '/') {
			phrase += word;
			if (i != _paramList.count() - 1)
				phrase += " ";
		}
	}
	_rui->show_msg(string("checking ") + phrase + string(":"));
	_rui->show_check_result(_rcore->lookUpWord(phrase.c_str()));
}

void CheckCMD::showUnknownCMDs() {
int count = _unParsed.size();
    if (count  == 0)
        return;
    _rui->show_warning("error when dealing with param : ");
	for (int i = 0; i < count; ++i) {
		_rui->show_msg(_unParsed.at(i).c_str());
	}
}
