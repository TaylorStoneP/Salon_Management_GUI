#include "datetime.h"
#include <string>
#include "debuglogger.h"
DateTime::DateTime() :m_year(-1),m_month(-1),m_day(-1),m_hour(-1),m_minute(-1),m_second(-1) {}
DateTime::DateTime(const int year, const int month, const int day, const int hour, const int minute, const int second) :m_year(year), m_month(month), m_day(day), m_hour(hour), m_minute(minute), m_second(second) { LOG_ALLOCATION("DateTime", this); }
DateTime::DateTime(const int year,const int month, const int day, const int hour, const int minute)
{
    LOG_ALLOCATION("DateTime", this);
    *this = Now();
    m_year = year;
    m_month = month;
    m_day = day;
    m_hour = hour;
    m_minute = minute;
    m_second = 0;

}
DateTime::DateTime(const int month, const int day, const int hour, const int minute)
{
    LOG_ALLOCATION("DateTime", this);
    *this = Now();
    m_month = month;
    m_day = day;
    m_hour = hour;
    m_minute = minute;
    m_second = 0;
}
DateTime::DateTime(const int day, const int hour, const int minute)
{
    LOG_ALLOCATION("DateTime", this);
    *this = Now();
    m_day = day;
    m_hour = hour;
    m_minute = minute;
    m_second = 0;
}
DateTime::DateTime(const int hour, const int minute)
{
    LOG_ALLOCATION("DateTime", this);
    *this = Now();
    m_hour = hour;
    m_minute = minute;
    m_second = 0;
}
DateTime::DateTime(const std::time_t& time)
{
    LOG_ALLOCATION("DateTime", this);
    *this = Time_T_to_DateTime(time);
}

DateTime::~DateTime() { LOG_DEALLOCATION("DateTime", this); }

std::string DateTime::To_String() const
{
    //returns HH:MM:SS DD/MM/YYYY
    return (m_hour<10?"0"+std::to_string(m_hour):std::to_string(m_hour)) + ":" + (m_minute < 10 ? "0" + std::to_string(m_minute): std::to_string(m_minute)) + ":" + (m_second < 10 ? "0" + std::to_string(m_second): std::to_string(m_second)) + " " + (m_day < 10 ? "0" + std::to_string(m_day): std::to_string(m_day)) + "/" + (m_month < 10 ? "0" + std::to_string(m_month): std::to_string(m_month)) + "/" + (m_year < 10 ? "0" + std::to_string(m_year): std::to_string(m_year));
}
std::string DateTime::To_String_Date() const
{
    //returns HH:MM:SS DD/MM/YYYY
    return ((m_day < 10 ? "0" + std::to_string(m_day) : std::to_string(m_day)) + "/" + (m_month < 10 ? "0" + std::to_string(m_month) : std::to_string(m_month)) + "/" + (m_year < 10 ? "0" + std::to_string(m_year) : std::to_string(m_year)));
}
std::string DateTime::To_String_Time() const
{
    //returns HH:MM:SS DD/MM/YYYY
    return (m_hour < 10 ? "0" + std::to_string(m_hour) : std::to_string(m_hour)) + ":" + (m_minute < 10 ? "0" + std::to_string(m_minute) : std::to_string(m_minute)) + ":" + (m_second < 10 ? "0" + std::to_string(m_second) : std::to_string(m_second));
}
DateTime DateTime::Time_T_to_DateTime(const std::time_t& time)
{
    std::tm* localTime = std::localtime(&time);
    return { localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec };
}
DateTime DateTime::Now()
{
    return Time_T_to_DateTime(std::time(0));
}
int DateTime::getYear() const
{
    return m_year;
}

int DateTime::getMonth() const
{
    return m_month;
}

int DateTime::getDay() const
{
    return m_day;
}

int DateTime::getHour() const
{
    return m_hour;
}

int DateTime::getMinute() const
{
    return m_minute;
}

int DateTime::getSecond() const
{
    return m_second;
}

