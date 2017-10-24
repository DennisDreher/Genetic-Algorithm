#include "MyLog.h"

std::fstream myLog;
std::stringstream ss;

#ifdef LOG_ENABLED

void OpenMyLog()
{
	myLog.open("MyLog.txt", std::ios::out);
	myLog << "Programmstart: " << TimeStamp() << std::endl;

	//ios::in		Zum Lesen
	//ios::out 		Zum Schreiben
	//ios::trunc 	Datei wird beim Öffnen geleert
	//ios::app 		Geschriebene Daten ans Ende anhängen
	//ios::ate 		Positionszeiger ans Ende setzen
}

void CloseMyLog()
{
	//MyLog::myLog << std::endl;
	//MyLog::myLog.close();

	myLog << "Programmende: " << TimeStamp() << std::endl;
	myLog.close();
}

std::string TimeStamp()
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
	ss << "[" << hour << ":" << min << ":" << sec << "]";

	sTime = ss.str();

	return sTime;
}

#else
void OpenMyLog(){}
void CloseMyLog(){}
std::string TimeStamp() { return 0; }
#endif