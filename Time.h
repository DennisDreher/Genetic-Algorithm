#pragma once

#include <time.h>
#include <string>

static std::string TimeStamp()
{
	struct tm currentTime;
	__time64_t long_time;
	_time64(&long_time);
	_localtime64_s(&currentTime, &long_time);

	int sec = currentTime.tm_sec;				//second
	int min = currentTime.tm_min;				//minute
	int hour = currentTime.tm_hour;				//hour

	int day = currentTime.tm_mday;				//day
	int month = currentTime.tm_mon + 1;			//month
	int year = currentTime.tm_year + 1900;		//year

	std::string sTime;
	std::stringstream ss;

	//[hh:mm:ss]
	ss << "[" << hour << ":" << min << ":" << sec << "] ";

	//ss <<  hour << ":" << min << ":" << sec << " - " << day << "." << month << "." << year;
	sTime = ss.str();

	return sTime;
}