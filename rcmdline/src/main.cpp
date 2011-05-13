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
//#define DEBUG_RINIFILE
#define DEBUG_RPROP
void test_rprop() {
	RPropSet *set = new RPropSet;
	RPropItem item1("key1","value1");
	RPropItem item2("key2",222);
	set->addItem(item1);
	set->addItem(item2);
	set->traverse();
	//set->remove("key1");
	//set->traverse();
	RIniFile *ini = new RIniFile("/home/test.ini");
	if (!set->saveToIni(ini))
		printf("cannot save !!\n");
}

void test_dict(int argc, char** argv) {
	RCore *core = new RCore();
	if (!core->loadDict(DEFAULT_DICT_PATH)) {
		printf("error  when loading dict\n");
		exit(0);
	}
	for (int i = 1; i < argc; ++i) {
		printf("checking word \'%s\'\n",argv[i]);
		printf("%s\n",core->lookUpWord(argv[i]).c_str());
	}
}

void test_histfile(int argc, char** argv) {
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
}

void test_inifile() {
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
}

int main(int argc, char** argv) {
#ifdef DEBUG_DICT
	test_dict(argc,argv);
#endif

#ifdef DEBUG_RHISTFILE
	test_histfile(argc,argv);
#endif
#ifdef DEBUG_RINIFILE
	test_inifile();
#endif
#ifdef DEBUG_RPROP
	test_rprop();
#endif
	//argvsAnalyse(argc,argv);
	return 0;
}

