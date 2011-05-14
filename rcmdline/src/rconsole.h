#ifndef RCONSOLE_H
#define RCONSOLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;

#include "rcore.h"
#include "rrecord.h"
#include "stardict.h"
#include "checkcmd.h"
#include "usercmd.h"
#include "dictcmd.h"
#include "define.h"
#include "cmds.h"
#include "rui.h"

class RConsole
{
public:
	RConsole(int argc, char** argv);
	~RConsole();

	int exec();

	static RTYPE_CMD getCMD(int argc, char** argv);
	void doCommand(RTYPE_CMD cmd,int argc, char** argv);
	bool initUI();
	bool initCore();
	bool initDict();
	bool initConfig();

	void setUI(RUI* ui) { _rui = ui; }
	RUI* ui();

	RERROR getError() { return _error; }
	void setError(RERROR error) { _error = error; }

private:
	RCore *_rcore;
	RERROR _error;

	int _argc;
	char** _argv;

	DictRecord* _dictRecord;
	UserRecord* _userRecord;
	RUI* _rui;
};

#endif //RCONSOLE_H
