#ifndef LOG_H
#define LOG_H

#include <QString>
#include <windows.h>

class LOG{


public:
	
	QString GetTimeStamp();
	QString  Log_record(QString message_);


};




#endif