

#include "LOG.h"

QString LOG::GetTimeStamp(){


	QString str_year;
	QString str_month;
	QString str_day;
	QString str_hour;
	QString str_minute;
	QString str_second;
	QString str_msecond;
	QString str_dayofweek;
	QString time_;

	SYSTEMTIME sys;
	GetLocalTime( &sys );

	str_year = QString::number(sys.wYear);
	str_month = QString::number(sys.wMonth);
	str_day = QString::number(sys.wDay);
	str_hour = QString::number(sys.wHour);
	str_minute = QString::number(sys.wMinute);
	str_second = QString::number(sys.wSecond);
	str_msecond = QString::number(sys.wMilliseconds);
	str_dayofweek = QString::number(sys.wDayOfWeek);

	time_+=(str_year+"."+str_month+"."+str_day+"    "+" "+str_hour+" : "+str_minute+" : "+str_second+"se "+str_msecond+"ms     "+"DayogWeek: " +str_dayofweek );

	return time_;

}






QString LOG:: Log_record(QString message_)
{
	QString StringTime;
	QString tmp=GetTimeStamp();

	StringTime="["+tmp+"]"+message_;


	return StringTime;



}