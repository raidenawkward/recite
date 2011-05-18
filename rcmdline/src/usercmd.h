#ifndef USERCMD_H
#define USERCMD_H

#include "rcmd.h"

enum RTYPE_USERCMD {
	RTYPE_USERCMD_UNKNOWN = 0,
	RTYPE_USERCMD_SHOW_USER,
	RTYPE_USERCMD_SET_USER,
	RTYPE_USERCMD_SWITCH_USER,
	RTYPE_USERCMD_DEL_USER,
	RTYPE_USERCMD_SET_MAIL,
	RTYPE_USERCMD_SET_DICT,
	RTYPE_USERCMD_HELP,
	RTYPE_USERCMD_NOTCMD
};

class UserCMD : public RCMD, RCMD_callback
{
public:
	UserCMD(int argc, char** argv);
	UserCMD(UserCMD& cmd);
	UserCMD(RParamList& list);
	~UserCMD();

	virtual void exec(RCore* core, RUI* ui);

	void doCommands();
	void showUnknownCMDs();
	int getCMD(const string str);

protected:
	void showInfo(RParamList& list);
	void setUser(RParamList& list);
	void switchUser(RParamList& list);
	void setMail(RParamList& list);
	void delUser(RParamList& list);
	void setDict(RParamList& list);

	void showHelpInfo(RParamList& list);
};


#endif // USERCMD_H
