#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include "rcore.h"
#include "dictbase.h"
#include "stardict.h"


#define DEFAULT_DICT_PATH "dictsupport/dict/stardict-langdao-ec-gb-2.4.2/"


//#define DEBUG_DICT
//#define DEBUG_RHISTFILE
#define DEBUG_RINIFILE

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
#ifdef DEBUG_RINIFILE
	RIniFile *file = new RIniFile("/home/raiden/test.ini");
	//file->setValue("testkey1","value1");
	//file->setValue("testkey2",2);
	//file->save();
	/*vector<string> keys = file->getKeys();
	for (int i = 0; i < keys.size(); ++i) {
		string key = keys.at(i);
		printf("key[%d] : %s\n",i,key.c_str());
	}*/
	//printf("value : %s\n",file->getValue("testkey1").c_str());
	//file->remove("testkey1");
	//file->save();
	delete file;
#endif
	//argvsAnalyse(argc,argv);
	return 0;
}

