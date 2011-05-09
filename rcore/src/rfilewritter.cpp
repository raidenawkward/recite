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
