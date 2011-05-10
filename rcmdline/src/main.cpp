#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rcore.h"
#include "dictbase.h"
#include "stardict.h"


#define DEFAULT_DICT_PATH "dictsupport/dict/stardict-langdao-ec-gb-2.4.2/"


//#define DEBUG_DICT
#define DEBUG_RHISTFILE

int main(int argc, char** argv) {
#ifdef DEBUG_DICT
	RCore *core = new RCore();
	if (!core->loadDict(DEFAULT_DICT_PATH)) {
		printf("error  when loading dict\n");
		exit(0);
	}
	for (int i = 1; i < argc; ++i) {
		printf("checking word \'%s\'\n",argv[i]);
		printf("%s\n",core->lookUpWord(argv[i]).c_str());
	}
#endif

#ifdef DEBUG_RHISTFILE
	RHistFile *file = new RHistFile("/home/test.test");
	file->open(ROPENMODE_WRITE);
	/*for (int i = 1; i < argc; ++i) {
		//file->writeLine(string(argv[i]),2);
		string line;
		file->readAll(line);
		printf("read :  %s\n",line.c_str());
	}*/
	string line = argv[2];
	file->write(line);
	file->close();
#endif
	//argvsAnalyse(argc,argv);
	return 0;
}

