#ifndef USERCMD_H
#define USERCMD_H

#include "rcmd.h"
#include "cmds.h"

enum RTYPE_USERCMD {
	RTYPE_USERCMD_SHOW_USER,
	RTYPE_USERCMD_SET_USER,
	RTYPE_USERCMD_SET_MAIL,
	RTYPE_USERCMD_SET_DICT,
	RTYPE_USERCMD_UNKNOWN
};

class UserCMD : public RCMD
{
public:
	UserCMD(int argc, char** argv);
	UserCMD(UserCMD& cmd);
	UserCMD(RParamList& list);
	~UserCMD();

	virtual void exec(RCore* core, RUI* ui);
};


#endif // USERCMD_H
