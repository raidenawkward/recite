#ifndef CHECKCMD_H
#define CHECKCMD_H

#include "rcmd.h"

enum RTYPE_CHECKCMD {
	RTYPE_CHECKCMD_CHECK_WORD,
	RTYPE_CHECKCMD_CHECK_PHRASE,
	RTYPE_CHECKCMD_HELP,
	RTYPE_CHECKCMD_UNKNOWN,
	RTYPE_CHECKCMD_NOTCMD
};

class CheckCMD : public RCMD
{
public:
	CheckCMD(int argc, char** argv);
	CheckCMD(CheckCMD& cmd);
	CheckCMD(RParamList& params);
	~CheckCMD();

	virtual void exec(RCore* core,RUI* ui);

	RTYPE_CHECKCMD getCMD(const string str);
	int parseCMD();
	void doCommands();
	void showUnknownCMDs();

	void check(RParamList& list);
	void checkPhrase(RParamList& list);

private:
	vector<RTYPE_CHECKCMD> _cmdList;
    vector<RParamList> _paramLists;
	vector<string> _unParsed;
};


#endif // CHECKCMD_H
