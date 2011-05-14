#ifndef CHECKCMD_H
#define CHECKCMD_H

#include "rcmd.h"

class CheckCMD : public RCMD
{
public:
	CheckCMD(int argc, char** argv);
	CheckCMD(CheckCMD& cmd);
	CheckCMD(RParamList& params);
	~CheckCMD();

	virtual void exec(RCore* core,RUI* ui);
};


#endif // CHECKCMD_H
