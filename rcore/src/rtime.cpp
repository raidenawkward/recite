#include "rtime.h"

RTime::RTime() {
	time_t t = 0;
	_stamp = time(&t);
	initTime(_stamp);
}

RTime::RTime(time_t stamp) {
	_stamp = stamp;
	initTime(_stamp);
}

RTime::RTime(RTime& time) {
	_stamp = time.getStamp();
	initTime(_stamp);
}

RTime::~RTime() {

}

void RTime::initTime(time_t stamp) {
	time_t t = stamp;

	char str[64];
	memset(str,0x00,64);
	strftime(str,64,"%Y",localtime(&t));
	_year = atoi(str);

	memset(str,0x00,64);
	strftime(str,64,"%m",localtime(&t));
	_month = atoi(str);

	memset(str,0x00,64);
	strftime(str,64,"%d",localtime(&t));
	_day = atoi(str);

	memset(str,0x00,64);
	strftime(str,64,"%H",localtime(&t));
	_hour = atoi(str);

	memset(str,0x00,64);
	strftime(str,64,"%M",localtime(&t));
	_min = atoi(str);

	memset(str,0x00,64);
	strftime(str,64,"%S",localtime(&t));
	_sec = atoi(str);
}

void RTime::setStamp(time_t stamp) {
	initTime(stamp);
}

time_t RTime::getStamp() {
	return _stamp;
}

int RTime::getYear() {
	return _year;
}

int RTime::getMonth() {
	return _month;
}

int RTime::getDay() {
	return _day;
}

int RTime::getHour() {
	return _hour;
}

int RTime::getMinute() {
	return _min;
}

int RTime::getSecond() {
	return _sec;
}

string RTime::getTimeSerialString() {
	char tmp[64];
	memset(tmp,0x00,64);
	sprintf(tmp,"%d%d%d%d%d%d",_year,_month,_day,_hour,_min,_sec);
	return string(tmp);
}

long RTime::getTimeSerial() {
	return atol(getTimeSerialString().c_str());
}

bool RTime::operator > (RTime& time) {
	return (_stamp > time.getStamp());
}

bool RTime::operator < (RTime& time) {
	return (_stamp < time.getStamp());
}

bool RTime::operator == (RTime& time) {
	return (_stamp == time.getStamp());
}

bool RTime::operator != (RTime& time) {
	return (_stamp != time.getStamp());
}

RTime& RTime::operator = (RTime& time) {
	setStamp(time.getStamp());
	return *this;
}
