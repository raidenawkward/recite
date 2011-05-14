#include "checkcmd.h"

CheckCMD::CheckCMD(int argc, char** argv)
		:RCMD(argc,argv) {
}

CheckCMD::CheckCMD(CheckCMD& cmd)
		:RCMD(cmd) {
}

CheckCMD::CheckCMD(RParamList& params)
		:RCMD(params) {
}

CheckCMD::~CheckCMD() {
}

void CheckCMD::exec(RCore* core) {
	if (!core)
		return;
	if (!core->isDictValid()) {
		RUI::show_warning(MSG_CMD_CHECK_NODICT);
	}
	for (int i = 0; i < _paramList.count(); ++i) {
		string word = _paramList.at(i);
		if (word[0] != '-')
			RUI::show_check_result(core->lookUpWord(word.c_str()));
	}
}
