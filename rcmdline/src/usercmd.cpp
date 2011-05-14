#include "usercmd.h"

UserCMD::UserCMD(int argc, char** argv)
		:RCMD(argc,argv) {

}

UserCMD::UserCMD(UserCMD& cmd)
		:RCMD(cmd) {
}

UserCMD::UserCMD(RParamList& list)
		:RCMD(list) {
}

UserCMD::~UserCMD() {
}

void UserCMD::exec(RCore* core, RUI* ui) {

}
