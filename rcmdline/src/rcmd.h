#ifndef RCMD_H
#define RCMD_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <vector>

using namespace std;

#include "cmds.h"
#include "rcore.h"
#include "rui.h"

class RParamList : public vector<string>
{
public:
	RParamList();
	void addParam(const string param);
	bool removeParam(const string param);
	bool removeParam(int index);

	bool existParam(const string param);
	int indexOf(const string param);//< -1 for not found
	string at(int index);
	int count();
};

class RCMD
{
public:
	RCMD(int argc, char** argv);
	RCMD(RCMD& cmd);
	RCMD(RParamList& params);
	virtual ~RCMD();

	static bool isCMD(const string str);

	RParamList& getParamList();
	virtual void exec(RCore* core, RUI* ui) = 0;

	void setUI(RUI* ui) { _rui = ui; }
    RUI* ui() { return _rui; }

    void setCore(RCore* core) { _rcore = core; }
	RCore* core() { return _rcore; }

protected:
	virtual int loadArgv(int argc,char** argv);

protected:
	RParamList _paramList;
	RCore *_rcore;
	RUI *_rui;
};

#endif // RCMD_H
