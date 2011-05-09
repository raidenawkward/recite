#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rcore.h"
#include "dictbase.h"
#include "stardict.h"


#define DEFAULT_DICT_PATH "dictsupport/dict/stardict-langdao-ec-gb-2.4.2/"

int main(int argc, char** argv) {
	RCore *core = new RCore();
	if (!core->loadDict(DEFAULT_DICT_PATH)) {
		printf("error  when loading dict\n");
		exit(0);
	}
	for (int i = 1; i < argc; ++i) {
		printf("checking word \'%s\'\n",argv[i]);
		printf("%s\n",core->lookUpWord(argv[i]).c_str());
	}
	//argvsAnalyse(argc,argv);
	return 0;
}

