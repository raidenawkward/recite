#ifndef RFILEWRITTER_H
#define RFILEWRITTER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <fstream>

using namespace std;

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
	RERR_CANNOTREAD
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

class RFileWritter
{
public:
	RFileWritter();
	RFileWritter(const string file);
	~RFileWritter();

	rfile_error_t open(ropen_mode_t mode = ROPENMODE_READ);
	rfile_error_t open(const string file, ropen_mode_t mode = ROPENMODE_READ);
	void close();
	bool isStreamOpenned();

	string getPath() { return _path; }

	rfile_error_t writeLine(const string &line);
	rfile_error_t writeLine(const string &line,int times = 1);
	rfile_error_t write(const string &content);
	rfile_error_t readLine(string &line);
	rfile_error_t read(string &content);

protected:
	int getStreamMode(ropen_mode_t mode);
private:
	string _path;
	rfile_prop_t _prop;
	ropen_mode_t _mode;
	fstream *_stream;
};

#endif // RFILEWRITTER_H
