#pragma once

#include <Windows.h>	//needed for TRUE and FALSE
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>

extern std::fstream myLog;
extern std::stringstream ss;

void OpenMyLog();
void CloseMyLog();
std::string TimeStamp();

#define TIME_SPACE "          "

//enable to use the Log
#define LOG_ENABLED

//text of message types
#define MSG_INFORMATION		""
#define MSG_WARNING			"WARNING: "
#define MSG_ERROR			"ERROR: "

//message types
#define MSG_TYPE_NONE		0x0
#define MSG_TYPE_INFO		0x1
#define MSG_TYPE_WARNING	0x2
#define MSG_TYPE_ERROR		0x4

//which message types are logged
#define LOGGED_MSG_TYPES	(MSG_TYPE_INFO | MSG_TYPE_WARNING | MSG_TYPE_ERROR)

//get message type
#define GET_MSG_TYPE(type)	(((LOGGED_MSG_TYPES & type) == type) ? TRUE : FALSE)

#ifdef LOG_ENABLED
#define LOG_INFO(msg)				if(GET_MSG_TYPE(MSG_TYPE_INFO)){LOG1(MSG_INFORMATION, msg);}
#define LOG_INFO_CODE(msg, code)	if(GET_MSG_TYPE(MSG_TYPE_INFO)){LOG2(MSG_INFORMATION, msg, code);}
#define LOG_WARNING(msg)			if(GET_MSG_TYPE(MSG_TYPE_WARNING)){LOG1(MSG_WARNING, msg);}
#define LOG_WARNING_CODE(msg, code)	if(GET_MSG_TYPE(MSG_TYPE_WARNING)){LOG2(MSG_WARNING, msg, code);}
#define LOG_ERROR(msg)				if(GET_MSG_TYPE(MSG_TYPE_ERROR)){LOG1(MSG_ERROR, msg);}
#define LOG_ERROR_CODE(msg, code)	if(GET_MSG_TYPE(MSG_TYPE_ERROR)){LOG2(MSG_ERROR, msg, code);}
#else
#define LOG_INFO(msg)
#define LOG_INFO_CODE(msg, code)
#define LOG_WARNING(msg)
#define LOG_WARNING_CODE(msg, code)
#define LOG_ERROR(msg)
#define LOG_ERROR_CODE(msg, code)
#endif

//#define LOG1(msgType, msg)			myLog << TimeStamp() << msgType << msg << std::endl << TIME_SPACE << "File: " << __FILE__ << std::endl << TIME_SPACE << "Line: " << __LINE__ << std::endl
//#define LOG2(msgType, msg, code)	myLog << TimeStamp() << msgType << msg << std::endl << "File: " << __FILE__ << std::endl << "Line: " << __LINE__ << std::endl << "Errorcode: " << code << std::endl

#define LOG1(msgType, msg)			myLog << TimeStamp() << msgType << msg << std::endl
#define LOG2(msgType, msg, code)	myLog << TimeStamp() << msgType << msg << std::endl