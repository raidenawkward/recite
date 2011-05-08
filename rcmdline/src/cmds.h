#ifndef CMD_H
#define CMD_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <stdarg.h>

using namespace std;

enum RECITE_CMD {
	// user
	RECITE_CMD_SHOWCURRENTUSER,
	RECITE_CMD_CHANGECURRENTUSER,
	RECITE_CMD_SETUSERPASSWD,
	// show word
	RECITE_CMD_LOOKUPWORD,
	RECITE_CMD_SHOWWORDSTODAY,
	RECITE_CMD_SHOWNEXTWORDTODAY,
	RECITE_CMD_SHOWPREVWORDTODAY,
	// recite option
	RECITE_CMD_SETWORDSPERDAY,
	RECITE_CMD_SETDICT,
	RECITE_CMD_SHOWDICTINFO,
	// for reciting
	RECITE_CMD_ADDFORGETIVEWORD,
	RECITE_CMD_ADDEXTERNALNEWWORD,
	RECITE_CMD_CHECKWORDSRECITEDBEFORE,
	//
	RECITE_CMD_INVALID
};

int getCMDArguNum(RECITE_CMD cmd, int argc, char** argv) {

}

void argvsAnalyse(int argc, char** argv);
void doCommand( const char* cmd, const char* param,...);
bool doCmd(const char* cmd, const char* param);
bool isCommandNeedParam(const char* cmd);
void commandError(const char* cmd);




#endif // CMD_H
