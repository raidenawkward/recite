#include "rhistfile.h"
#include <sys/stat.h>
#include <sys/types.h>

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

string getDirFromPath(const string path) {
	if (path.empty())
		return string();
	int length = path.length();
	int i = length - 1;
	for (; i >=0; --i) {
		char spliter = get_path_spliter();
		if (path[i] == spliter)
			break;
	}
	return path.substr(0,i);
}

char get_path_spliter() {
#ifdef WIN32
	char spliter = '\\';
#else
	char spliter = '/';
#endif
	return spliter;
}

rfile_error_t RHistFile::open(const string path, ropen_mode_t mode) {
	string dir = getDirFromPath(path);
	mkdir(dir.c_str(),S_IRWXU);
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
	if (!_stream->getline(ret,lineSize))
		return RERR_CANNOTREAD;
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



//////////////////// class RIniFile /////////////////////

#define RINIFILE_CHAR_EQ '='
#define RINIFILE_CHAR_SP ' '

RIniFile::RIniFile(const string file)
		:RHistFile(file)
{
	loadRecord();
}

RIniFile::~RIniFile() {
	close();
}

bool RIniFile::setValue(const string key, const string value) {
	if (key.empty()) {
		return false;
	}
	for (int i = 0; i < _record.size(); ++i) {
		pair<string,string> item = _record.at(i);
		if (item.first == key) {
			item.second = value;
			return true;
		}
	}
	pair<string,string> item(key,value);
	_record.push_back(item);
}

bool RIniFile::setValue(const string key, int value) {
	char temp[512];
	sprintf(temp,"%d",value);
	return setValue(key,string(temp));
}

string RIniFile::remove(const string key) {
	string ret;
	if (key.empty())
		return ret;
	vector<pair<string,string> >::iterator it = _record.begin();
	while (it != _record.end()) {
		pair<string,string> item = *it;
		if (item.first == key) {
			ret = item.second;
			_record.erase(it);
			return ret;
		}
		++it;
	}
	return ret;
}

string RIniFile::remove(int index) {
	string ret;
	int count = _record.size();
	if (index < 0 || index > count)
		return ret;
	int cur = 0;
	vector<pair<string,string> >::iterator it = _record.begin();
	while (it != _record.end()) {
		if (cur == index) {
			ret = (*it).second;
			_record.erase(it);
			return ret;
		}
		++cur;
		++it;
	}
	return ret;
}

string RIniFile::getValue(const string key) {
	string ret;
	if (key.empty())
		return ret;
	for (int i = 0; i < _record.size(); ++i) {
		pair<string,string> item = _record.at(i);
		if (item.first == key) {
			return item.second;
		}
	}
	return ret;
}

string RIniFile::getValue(int index,string &key) {
	string ret;
	if (index < 0 || index > _record.size())
		return ret;
	pair<string,string> item = _record.at(index);
	ret = item.second;
	key = item.first;
	return ret;
}

vector<string> RIniFile::getKeys() {
	vector<string> ret;
	for (int i = 0; i < _record.size(); ++i) {
		ret.push_back(_record.at(i).first);
	}
	return ret;
}

int RIniFile::getRecordCount() {
	return _record.size();
}

string make_ini_item(const string key, const string value) {
	string ret;
	if (key.empty())
		return ret;
	ret = key;
	ret += RINIFILE_CHAR_EQ;
	ret += value;
}

bool RIniFile::save() {
	int size = _record.size();
	if (!size) {
		return false;
	}
	this->open(ROPENMODE_WRITE);
	//reset();
	for (int i = 0; i < size; ++i) {
		pair<string,string> item = _record[i];
		string line = make_ini_item(item.first,item.second);
		writeLine(line);
	}
	//close();
	return true;
}

void RIniFile::clear() {
	_record.clear();
}

string peel_first_word(string& str) {
	string ret;
	if (str.empty())
		return ret;
	while (str.length()) {
		char ch = str[0];
		str.erase(0,1);
		if (ch == RINIFILE_CHAR_SP) {
			while (str[0] == RINIFILE_CHAR_SP) {
				str.erase(0,1);
			}
			return ret;
		} else if (ch == RINIFILE_CHAR_EQ) {
			ret += ch;
			return ret;
		} else {
			ret += ch;
			if (str[0] == RINIFILE_CHAR_EQ)
			return ret;
		}                       
	}
	return ret;
}

void peel_str_bothsides_quotesmark(string& str) {
	int length = str.length();
	if ((str[0] == '\"' && str[length - 1] == '\"')
		|| (str[0] == '\'' && str[length - 1] == '\'')) {
			str.erase(length - 1,1);
			str.erase(0,1);
	}
}

bool RIniFile::parseLine(const string line, string& key, string& value) {
	bool ret = false;
	if (line.empty())
		return ret;

	string line_to_parse = line;
	// get key
	key = peel_first_word(line_to_parse);
	// get 'equal'
	peel_first_word(line_to_parse);
	// get value
	value = peel_first_word(line_to_parse);
	peel_str_bothsides_quotesmark(value);
	if (key.empty() || value.empty()) {
		key.clear();
		value.clear();
		return ret;
	}
	ret = true;
	return ret;
}

int RIniFile::loadRecord() {
	string line;
	open(ROPENMODE_READ);
	while (readLine(line) != RERR_CANNOTREAD) {
		string key;
		string value;
		if (parseLine(line,key,value)) {
			pair<string,string> recordLine(key,value);
			_record.push_back(recordLine);
		}
	}
	close();
	return _record.size();
}

