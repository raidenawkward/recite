#ifndef USERCMD_H
#define USERCMD_H

#include "rcmd.h"

class UserCMD : public RCMD
{
public:
	UserCMD(int argc, char** argv);
	UserCMD(UserCMD& cmd);
	UserCMD(RParamList& cmd);
	~UserCMD();

	virtual void exec(RCore* core);
};


#endif // USERCMD_H
