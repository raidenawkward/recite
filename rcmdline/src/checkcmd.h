#ifndef CHECKCMD_H
#define CHECKCMD_H

#include "rcmd.h"

class CheckCMD : public RCMD
{
public:
	CheckCMD(int argc, char** argv);
	CheckCMD(CheckCMD& cmd);
	CheckCMD(RParamList& cmd);
	~CheckCMD();

	virtual void exec(RCore* core);
};


#endif // CHECKCMD_H
