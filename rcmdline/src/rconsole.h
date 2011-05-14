#ifndef RCONSOLE_H
#define RCONSOLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;

#include "rcore.h"
#include "stardict.h"
#include "checkcmd.h"
#include "usercmd.h"
#include "dictcmd.h"
#include "define.h"
#include "cmds.h"

class RConsole
{
public:
	RConsole(int argc, char** argv);

	int exec();

	static RTYPE_CMD getCMD(int argc, char** argv);
	bool initDict();
	bool initConfig();
private:
	RCore *_rcore;
};

#endif //RCONSOLE_H
