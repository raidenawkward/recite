#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rcore.h"
#include "dictbase.h"
#include "stardict.h"

void argvsAnalyse(int argc, char** argv);
void doCommand( const char* cmd, const char* param);
bool isCommandNeedParam(const char* cmd);
void commandError(const char* cmd);

int main(int argc, char** argv)
{
	RCore *core = new RCore();
	if (!core->loadDict("dictsupport/dict/stardict-langdao-ec-gb-2.4.2/")) {
		printf("error  when loading dict\n");
		exit(0);
	}
	for (int i = 1; i < argc; ++i) {
		printf("checking word %s\n",argv[i]);
		printf("%s\n",core->lookUpWord(argv[i]).c_str());
	}
	//argvsAnalyse(argc,argv);
	return 0;
}


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


void doCommand( const char* cmd, const char* param) {
	printf("executing command %s with param %s\n",cmd,param);
}


void commandError(const char* cmd) {
	printf("error with option \'%s\'\n",cmd);
	exit(-1);
}


bool isCommandNeedParam(const char* cmd)
{
	return true;
}
