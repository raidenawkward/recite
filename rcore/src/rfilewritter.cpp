#include "rfilewritter.h"

RFileWritter::RFileWritter()
		:_mode(ROPENMODE_READ)
		,_stream(NULL)
{
}

RFileWritter::RFileWritter(const string path)
        :_mode(ROPENMODE_READ)
        ,_stream(NULL)
{
	_path = path;
}

RFileWritter::~RFileWritter() {
	if (_stream)
		delete _stream;
}

rfile_error_t RFileWritter::open(const string path, ropen_mode_t mode) {
	if (_stream) {
		delete _stream;
		_stream = NULL;
	}
	_path = path;
	if (path.empty()) {
		return RERR_NOTFOUND;
	}

	_stream = new fstream;
	int open_mode = getStreamMode(mode);
	
	_stream->open(_path.c_str(),(std::_Ios_Openmode)open_mode);

	return RERR_OK;
}

rfile_error_t RFileWritter::open(ropen_mode_t mode) {
	return this->open(_path,mode);
}

void RFileWritter::close() {
	if (!isStreamOpenned())
		return;
	_stream->close();
}

bool RFileWritter::isStreamOpenned() {
	if (!_stream)
		return false;
	return _stream->is_open();
}

rfile_error_t RFileWritter::writeLine(const string &line) {
	if (!isStreamOpenned())
		return RERR_CANNOTWRITE;
	*_stream<<line<<endl;
	return RERR_OK;
}

rfile_error_t RFileWritter::writeLine(const string &line,int times) {
	rfile_error_t ret = RERR_OK;
	for (int i = 0; i < times; ++i) {
		ret = this->writeLine(line);
	}
	return ret;
}

rfile_error_t RFileWritter::write(const string &content) {
	if (!isStreamOpenned())
		return RERR_CANNOTWRITE;
	*_stream<<content;
	return RERR_OK;
}

rfile_error_t RFileWritter::readLine(string &line, int lineSize) {
	if (!isStreamOpenned())
		return RERR_CANNOTREAD;
	char ret[lineSize];
	memset(ret,0x00,lineSize);
	_stream->getline(ret,lineSize);
	line = string(ret);
	return RERR_OK;
}

rfile_error_t RFileWritter::read(string &content) {
	if (!isStreamOpenned())
        return RERR_CANNOTREAD;
	*_stream>>content;
	return RERR_OK;
}

int RFileWritter::getStreamMode(ropen_mode_t mode) {
	int ret = ios::in;
	switch (mode) {
	case ROPENMODE_READ:
		ret = ios::in;
		break;
	case ROPENMODE_WRITE:
		ret = ios::out;
		break;
	case ROPENMODE_READWRITE:
		ret = ios::in | ios::out;
		break;
	case ROPENMODE_APPEND:
		ret = ios::out | ios::app;
		break;
	}
	return ret;
}
