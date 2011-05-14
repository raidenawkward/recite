#include "rconsole.h"

RConsole::RConsole(int argc, char** argv)
		:_error(RERROR_NOERROR)
		,_rcore(NULL)
		,_rui(NULL)
		,_argc(argc)
		,_argv(argv) {
	initCore();
	initConfig();
	initUI();
	initDict();
}

RConsole::~RConsole() {
	if (_rcore)
		delete _rcore;
}

bool RConsole::initCore() {
	if (_rcore) {
		delete _rcore;
	}
	_rcore = new RCore();
}

bool RConsole::initUI() {
	RUI *ui = new RUI;
	setUI(ui);
	return true;
}

bool RConsole::initDict() {
	bool ret = _rcore->loadDict(SET_DEFAULT_DICT);
	if (!ret || !_rcore->isDictValid()) {
		setError(RERROR_INIT_FAILED);
	}
	return ret;
}

bool RConsole::initConfig() {
	bool ret = true;
	return ret;
}

RUI* RConsole::ui() {
	return _rui;
}

RTYPE_CMD RConsole::getCMD(int argc, char** argv) {
	return get_cmd(argc,argv);
}

int RConsole::exec() {
	RTYPE_CMD cmd = getCMD(_argc,_argv);
	doCommand(cmd,_argc,_argv);
	return _error;
}

void RConsole::doCommand(RTYPE_CMD cmd, int argc, char** argv) {
	if (argc - 2 <= 0) {
		// empty parameters
		setError(RERROR_TOO_FEW_PARAMS);
	}

	switch(cmd) {
	case RTYPE_CMD_LOOKUPWORD:
	{
		CheckCMD cmd(argc - 2,&argv[2]);
		cmd.exec(_rcore,_rui);
	}
		break;
	case RTYPE_CMD_INVALID:
		break;
	default:
		break;
	};
}
