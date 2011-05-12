#ifndef RFILEWRITTER_H
#define RFILEWRITTER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>

using namespace std;


#define STREAM_LINE_SIZE 512

/// file prop
enum rfile_prop_t {
	RFILEPROP_NORMAL = 0,
	RFILEPROP_READONLY,
	RFILEPROP_HIDE,
	RFILEPROP_SYS,
	RFILEPROP_INVALID
};

/// I/O errors enum
enum rfile_error_t {
	RERR_OK = 0,       ///< no error
	RERR_FAIL,         ///< failed (unknown error)
	RERR_EOF,          ///< end of file reached
	RERR_NOTFOUND,     ///< file not found
	RERR_NOTIMPL,      ///< method is not implemented
	RERR_CANNOTWRITE,
	RERR_CANNOTREAD,
};

/// File open modes enum
enum ropen_mode_t {
	ROPENMODE_ERROR = 0,       ///< to indicate error state
	ROPENMODE_CLOSED,        ///< to indicate closed state
	ROPENMODE_READ,          ///< readonly mode, use for r/o mmap
	ROPENMODE_WRITE,         ///< writeonly mode
	ROPENMODE_APPEND,        ///< append (readwrite) mode, use for r/w mmap
	ROPENMODE_READWRITE      ///< readwrite mode
};

class RHistFile
{
public:
	RHistFile();
	RHistFile(const string file);
	virtual ~RHistFile();

	rfile_error_t open(ropen_mode_t mode = ROPENMODE_READ);
	rfile_error_t open(const string file, ropen_mode_t mode = ROPENMODE_READ);
	void close();
	void reset();
	bool isStreamOpenned();

	string getPath() { return _path; }
	int getFileSize();

	rfile_error_t writeLine(const string &line);
	rfile_error_t writeLine(const string &line,int times);
	rfile_error_t write(const string &content);
	rfile_error_t readLine(string &line, int lineSize = STREAM_LINE_SIZE);
	rfile_error_t readAll(string &content);

protected:
	int getStreamMode(ropen_mode_t mode);
private:
	string _path;
	ropen_mode_t _mode;
	fstream *_stream;
};

class RIniFile : public RHistFile
{
public:
	RIniFile(const string file);
	virtual ~RIniFile();

	// 'false' would be return if key is not found in ini
	// then new item would be created
	bool setValue(const string key, const string value);
	bool setValue(const string key, int value);
	string remove(const string key);//< value will be returned;
	string remove(int index);

	string getValue(const string key);
	string getValue(int index, string& key);

	vector<string> getKeys();

	int getRecordCount();
	bool save();

protected:
	bool parseLine(const string line, string& key, string& value);
	int loadRecord();
protected:
	vector<pair<string,string > > _record;
};

#endif // RFILEWRITTER_H
