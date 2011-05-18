#ifndef CHECKCMD_H
#define CHECKCMD_H

#include "rcmd.h"

enum RTYPE_CHECKCMD {
	RTYPE_CHECKCMD_UNKNOWN = 0,
	RTYPE_CHECKCMD_CHECK_WORD,
	RTYPE_CHECKCMD_CHECK_PHRASE,
	RTYPE_CHECKCMD_HELP,
	RTYPE_CHECKCMD_NOTCMD
};

class CheckCMD : public RCMD,RCMD_callback
{
public:
	CheckCMD(int argc, char** argv);
	CheckCMD(CheckCMD& cmd);
	CheckCMD(RParamList& params);
	~CheckCMD();

	virtual void exec(RCore* core,RUI* ui);

	int getCMD(const string str);
	void doCommands();
	void showUnknownCMDs();

	void check(RParamList& list);
	void checkPhrase(RParamList& list);
};


#endif // CHECKCMD_H
