#include "usercmd.h"

UserCMD::UserCMD(int argc, char** argv)
		:RCMD(argc,argv) {

}

UserCMD::UserCMD(UserCMD& cmd)
		:RCMD(cmd) {
}

UserCMD::UserCMD(RParamList& list)
		:RCMD(list) {
}

UserCMD::~UserCMD() {
}


int UserCMD::getCMD(const string str) {
	if (!RCMD::isCMD(str))
		return RTYPE_USERCMD_NOTCMD;
	if (str == CMD_USER_SET_USER_SHORT || str == CMD_USER_SET_USER)
		return RTYPE_USERCMD_SET_USER;
	if (str == CMD_USER_SWITCH_SHORT || str == CMD_USER_SWITCH)
		return RTYPE_USERCMD_SWITCH_USER;
	if (str == CMD_USER_SET_DICT || str == CMD_USER_SET_DICT_SHORT)
		return RTYPE_USERCMD_SET_DICT;
	if (str == CMD_USER_SET_MAIL_SHORT || str == CMD_USER_SET_MAIL)
		return RTYPE_USERCMD_SET_MAIL;
	if (str == CMD_USER_SHOW_SHORT || str == CMD_USER_SHOW)
		return RTYPE_USERCMD_SHOW_USER;
	if (str == CMD_USER_DEL_USER_SHORT || str == CMD_USER_DEL_USER)
		return RTYPE_USERCMD_DEL_USER;
	return RTYPE_USERCMD_UNKNOWN;
}

#if 0
int UserCMD::parseCMD() {
	int i = 0;
	while(i < _paramList.size()) {
		string tmp = _paramList.at(i);
		RTYPE_USERCMD cmd = getUserCMD(tmp);
		if (cmd != RTYPE_USERCMD_UNKNOWN) {
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

void UserCMD::doCommands() {
	for (int i = 0; i < _cmdList.size(); ++i) {
		RParamList params = _paramLists.at(i);
		switch (_cmdList.at(i)) {
			case RTYPE_USERCMD_SHOW_USER:
				showInfo(params);
				break;
			case RTYPE_USERCMD_SET_USER:
				setUser(params);
				break;
			case RTYPE_USERCMD_SWITCH_USER:
				switchUser(params);
				break;
			case RTYPE_USERCMD_DEL_USER:
				delUser(params);
				break;
			case RTYPE_USERCMD_SET_MAIL:
				setMail(params);
				break;
			case RTYPE_USERCMD_SET_DICT:
				setDict(params);
				break;
			case RTYPE_USERCMD_HELP:
				showHelpInfo(params);
				break;
			default:
				  break;
		}
	}
}

void UserCMD::showUnknownCMDs() {
	int count = _unParsed.size();
	if (count  == 0)
		return;
	_rui->show_warning("error when dealing with param : ");
	for (int i = 0; i < count; ++i) {
		_rui->show_msg(_unParsed.at(i).c_str());
	}
}

void UserCMD::exec(RCore* core, RUI* ui) {
	if (!core || !ui)
		return;
	setUI(ui);
	setCore(core);

	parseCMD(this);
	doCommands();
	showUnknownCMDs();
}

void UserCMD::showInfo(RParamList& list) {
	_rui->show_msg(string("current user : ") + _rcore->getCurrentUser());
	_rui->show_msg(string("mail : ") + _rcore->getCurrentUserMail());
	_rui->show_msg(string("current dict : ") + _rcore->getDictName());
}

void UserCMD::setUser(RParamList& list) {
	if (list.count() <= 0)
		return;
	if (_rcore->addUser(list.at(0))) {
		_rui->show_msg(string(MSG_CMD_ADDUSER_SUCCEED) + list.at(0));
	} else {
		_rui->show_msg(string(MSG_CMD_ADDUSER_FAILED) + list.at(0));
	}
}

void UserCMD::switchUser(RParamList& list) {
	if (list.count() != 1)
		return;
	if (_rcore->switchUser(list.at(0))) {
		_rui->show_msg(string(MSG_CMD_SWITCHUSER_SUCCEED) + list.at(0));
	} else {
		_rui->show_msg(string(MSG_CMD_SWITCHUSER_FAILED) + list.at(0));
	}
}

void UserCMD::setMail(RParamList& list) {
	if (list.count() <= 0) {
		_rui->show_error("input mail address");
		return;
	}
	string mail;
	for (int i = 0; i < list.count(); ++i) {
		mail += list.at(i);
		if (i > 1 && i != list.count())
			mail += " , ";
	}
	if (_rcore->setCurrentUserMail(mail)) {
		_rui->show_msg("mail set succeed");
	} else {
		_rui->show_warning("cannot set mail");
	}
}

void UserCMD::delUser(RParamList& list) {
}

void UserCMD::setDict(RParamList& list) {
	if (list.count() <= 0) {
		_rui->show_error("need dict dir path");
		return;
	}
	string newdict = list.at(0);
	if (_rcore->setUserDictDir(newdict))
		_rui->show_msg(string("loading dict ") + newdict + string(" succeed"));
	else
		_rui->show_warning(string("error when loading dict ") + newdict);
}

void UserCMD::showHelpInfo(RParamList& list) {
}
