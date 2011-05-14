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

	virtual void exec(RCore* core);
};


#endif // DICTCMD_H
