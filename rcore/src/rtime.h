#ifndef RTIME_H
#define RTIME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <string>

using namespace std;

class RTime
{
public:
	RTime();
	RTime(time_t stamp);
	RTime(RTime& time);
	~RTime();

	int getYear();
	int getMonth();
	int getDay();
	int getHour();
	int getMinute();
	int getSecond();

	void setStamp(time_t stamp);
	time_t getStamp();

	string getTimeSerialString();// "20110514"
	long getTimeSerial();// 20110514

	bool operator > (RTime& time);
	bool operator < (RTime& time);
	bool operator == (RTime& time);
	bool operator != (RTime& time);

	RTime& operator = (RTime& time);

protected:
	void initTime(time_t stamp);

protected:
	int _year;
	int _month;
	int _day;
	int _hour;
	int _min;
	int _sec;
	time_t _stamp;
};


#endif // RTIME_H
