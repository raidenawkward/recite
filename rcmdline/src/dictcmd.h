#ifndef DICTCMD_H
#define DICTCMD_H

#include "rcmd.h"


class DictCMD : public RCMD
{
public:
	DictCMD(int argc, char** argv);
	DictCMD(DictCMD& cmd);
	DictCMD(RParamList& cmd);
	~DictCMD();

	virtual void exec(RCore* core, RUI* ui);
};


#endif // DICTCMD_H
