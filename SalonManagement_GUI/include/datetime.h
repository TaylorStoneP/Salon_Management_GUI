#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
#include <time.h>
#include <chrono>
#include <ctime>
#include "debuglogger.h"
#include <string>

//Date and Time class.
class DateTime {
	int m_year;	
	int m_month;
	int m_day;
	int m_hour;
	int m_minute;
	int m_second;
public:
	//default constructor.
	DateTime();
	//Full constructor.
	DateTime(const int year, const int month, const int day, const int hour, const int minute, const int second);
	DateTime(const int year, const int month, const int day, const int hour, const int minute);
	DateTime(const int month, const int day, const int hour, const int minute);
	DateTime(const int day, const int hour, const int minute);
	DateTime(const int hour, const int minute);
	//Constructor - Takes in epoch seconds as time_t.
	DateTime(const std::time_t& time);

	//destructor.
	~DateTime();

	//Returns DateTime as a full string.
	std::string To_String() const;
	//Returns DateTime as only a date string.
	std::string To_String_Date() const;
	//Returns DateTime as only a time string.
	std::string To_String_Time() const;

	//Returns a DateTime of the current date and time.
	static DateTime Now();
	//Converts epoch seconds of time_t to DateTime.
	static DateTime Time_T_to_DateTime(const std::time_t& time);

	//operator overloads.
	bool operator>(DateTime& rhs);
	bool operator<(DateTime& rhs);
	bool operator>=(DateTime& rhs);
	bool operator<=(DateTime& rhs);
	bool operator==(DateTime& rhs);

	//Converts DateTime to epoch seconds as time_t.
	time_t to_time_t();

	//Converts DateTime to tm class.
	tm* to_tm();

	//year getter.
	int getYear() const;
	//month getter.
	int getMonth() const;
	//day getter.
	int getDay() const;
	//hour getter.
	int getHour() const;
	//minute getter.
	int getMinute() const;
	//second getter.
	int getSecond() const;
	//hour setter.
	void setHour(int hour);
	//day setter.
	void setDay(int day);

	//Returns the current weekday - Monday = 0, Sunday = 6.
	int GetWeekDay();

};

#endif