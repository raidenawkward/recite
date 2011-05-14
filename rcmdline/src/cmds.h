#ifndef CMD_H
#define CMD_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdarg.h>

using namespace std;

#include "define.h"

enum RTYPE_CMD {
	RTYPE_CMD_USER,//< user cmd
	RTYPE_CMD_LOOKUPWORD,//< checking cmd
	RTYPE_CMD_DICT,	//< recite option
	RTYPE_CMD_INVALID
};


RTYPE_CMD get_cmd(int argc, char** argv);

// returns true if src is heading parts of dst on case sensitivly
bool str_compair_partly(const string src, const string dst);

string get_cmd_str(int argc, char** argv);

//void argvsAnalyse(int argc, char** argv);

#endif // CMD_H
