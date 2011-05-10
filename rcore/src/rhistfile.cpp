#include "rhistfile.h"

RHistFile::RHistFile()
		:_mode(ROPENMODE_READ)
		,_stream(NULL)
{
}

RHistFile::RHistFile(const string path)
        :_mode(ROPENMODE_READ)
        ,_stream(NULL)
{
	_path = path;
}

RHistFile::~RHistFile() {
	if (_stream)
		delete _stream;
}

rfile_error_t RHistFile::open(const string path, ropen_mode_t mode) {
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

rfile_error_t RHistFile::open(ropen_mode_t mode) {
	return this->open(_path,mode);
}

void RHistFile::close() {
	if (!isStreamOpenned())
		return;
	_stream->close();
}

bool RHistFile::isStreamOpenned() {
	if (!_stream)
		return false;
	return _stream->is_open();
}

int RHistFile::getFileSize() {
	int ret = 0;
	if (!isStreamOpenned())
		return ret;
	int temp = _stream->tellg();
	_stream->seekg(0, ios_base::end);
	ret = _stream->tellg();
	_stream->seekg(temp);
	printf("size : %d , %d\n",ret,temp);
	return ret;
}

rfile_error_t RHistFile::writeLine(const string &line) {
	if (!isStreamOpenned())
		return RERR_CANNOTWRITE;
	*_stream<<line<<endl;
	return RERR_OK;
}

rfile_error_t RHistFile::writeLine(const string &line,int times) {
	rfile_error_t ret = RERR_OK;
	for (int i = 0; i < times; ++i) {
		ret = this->writeLine(line);
	}
	return ret;
}

rfile_error_t RHistFile::write(const string &content) {
	if (!isStreamOpenned())
		return RERR_CANNOTWRITE;
	*_stream<<content;
	return RERR_OK;
}

rfile_error_t RHistFile::readLine(string &line, int lineSize) {
	if (!isStreamOpenned())
		return RERR_CANNOTREAD;
	char ret[lineSize];
	memset(ret,0x00,lineSize);
	_stream->getline(ret,lineSize);
	line = string(ret);
	return RERR_OK;
}

rfile_error_t RHistFile::readAll(string &content) {
	if (!isStreamOpenned())
        return RERR_CANNOTREAD;
	this->reset();
	content.clear();
	char buf[1024];
	while(!_stream->eof()) {
		_stream->getline(buf,getFileSize());
		content += buf;
	}
	return RERR_OK;
}

void RHistFile::reset() {
	if (!isStreamOpenned())
		return;
	_stream->clear();
	_stream->seekg(0,ios_base::beg);
}

int RHistFile::getStreamMode(ropen_mode_t mode) {
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
