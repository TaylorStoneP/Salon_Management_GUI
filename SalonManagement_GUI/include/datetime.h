#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <time.h>
#include <chrono>
#include <ctime>
#include "debuglogger.h"
#include <string>
class DateTime {
	int m_year;
	int m_month;
	int m_day;
	int m_hour;
	int m_minute;
	int m_second;
public:
	DateTime();
	DateTime(const int year, const int month, const int day, const int hour, const int minute, const int second);
	DateTime(const int year, const int month, const int day, const int hour, const int minute);
	DateTime(const int month, const int day, const int hour, const int minute);
	DateTime(const int day, const int hour, const int minute);
	DateTime(const int hour, const int minute);
	DateTime(const std::time_t& time);

	~DateTime();

	std::string To_String() const;
	std::string To_String_Date() const;
	std::string To_String_Time() const;

	static DateTime Now();
	static DateTime Time_T_to_DateTime(const std::time_t& time);

	time_t to_time_t();

	tm* to_tm();

	int getYear() const;

	int getMonth() const;

	int getDay() const;

	int getHour() const;

	int getMinute() const;

	int getSecond() const;

	void setHour(int hour);

};

#endif