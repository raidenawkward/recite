#include "cmds.h"

RTYPE_CMD get_cmd(int argc, char** argv) {
	string cmd = get_cmd_str(argc, argv);

	if (cmd.empty()) {
		return RTYPE_CMD_INVALID;
	}

	if (str_compair_partly(cmd,CMD_CHECK)) {
		return RTYPE_CMD_LOOKUPWORD;
	}

	if (str_compair_partly(cmd,CMD_DICT)) {
		return RTYPE_CMD_DICT;
	}

	if (str_compair_partly(cmd,CMD_USER)) {
		return RTYPE_CMD_USER;
	}

	return RTYPE_CMD_UNKNOWN;
}

string get_cmd_str(int argc, char** argv) {
	string ret;
	if (argc <= 0 || !argv)
		return ret;
	for (int i = 1; i < argc; ++i) {
		string tmp = string(argv[i]);
		if (tmp.empty())
			continue;
		if (tmp[0] != '-')
			return tmp;
	}
	return ret;
}

bool str_compair_partly(const string src, const string dst) {
	bool ret = true;
	for (int i = 0; i < src.size(); ++i) {
		if (src[i] != dst[i])
			return false;
	}
	return true;
}

#if 0
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

#endif // 0
