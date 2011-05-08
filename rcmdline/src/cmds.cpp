#include "cmds.h"


void argvsAnalyse(int argc, char** argv) {
	char cmd[512];
	char param[512];

	int i = 0;
	while (i < argc) {
		if (argv[i][0] == '-') {
			memset(cmd,0x00,512);
			strcpy(cmd,argv[i]);
			if (isCommandNeedParam(cmd)) {
				if (i + 1 < argc && argv[i + 1][0] != '-') {
					memset(param,0x00,512);
					strcpy(param,argv[++i]);
					doCommand(cmd,param);
				}
				else {
					commandError(cmd);
				}
			}
			else {
				doCommand(cmd,NULL);
			}
		}
		else {
			// do nothing without option
		}
		++i;
	}
	
}


void doCommand( const char* cmd, const char* param, ...) {
	va_list arg;
	string sarg;
	va_start(arg,param);
	sarg = string(va_arg(arg,const char*));
	va_end(arg);
	doCmd(cmd,sarg.c_str());
	printf("executing command %s with param %s\n",cmd,param);
}

bool doCmd(const char* cmd, const char* param) {
	return false;
}

void commandError(const char* cmd) {
	printf("error with option \'%s\'\n",cmd);
	exit(-1);
}


bool isCommandNeedParam(const char* cmd)
{
	return true;
}
