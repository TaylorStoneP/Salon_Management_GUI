#include "datetime.h"
#include <string>
#include "debuglogger.h"
DateTime::DateTime() :m_year(-1), m_month(-1), m_day(-1), m_hour(-1), m_minute(-1), m_second(-1) {}
DateTime::DateTime(const int year, const int month, const int day, const int hour, const int minute, const int second) : m_year(year), m_month(month), m_day(day), m_hour(hour), m_minute(minute), m_second(second) {  }
DateTime::DateTime(const int year, const int month, const int day, const int hour, const int minute)
{
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
    *this = Now();
    m_month = month;
    m_day = day;
    m_hour = hour;
    m_minute = minute;
    m_second = 0;
}
DateTime::DateTime(const int day, const int hour, const int minute)
{
    *this = Now();
    m_day = day;
    m_hour = hour;
    m_minute = minute;
    m_second = 0;
}
DateTime::DateTime(const int hour, const int minute)
{
    *this = Now();
    m_hour = hour;
    m_minute = minute;
    m_second = 0;
}
DateTime::DateTime(const std::time_t& time)
{
    *this = Time_T_to_DateTime(time);
}

DateTime::~DateTime() {}

std::string DateTime::To_String() const
{
    //returns HH:MM:SS DD/MM/YYYY
    return (m_hour < 10 ? "0" + std::to_string(m_hour) : std::to_string(m_hour)) + ":" + (m_minute < 10 ? "0" + std::to_string(m_minute) : std::to_string(m_minute)) + ":" + (m_second < 10 ? "0" + std::to_string(m_second) : std::to_string(m_second)) + " " + (m_day < 10 ? "0" + std::to_string(m_day) : std::to_string(m_day)) + "/" + (m_month < 10 ? "0" + std::to_string(m_month) : std::to_string(m_month)) + "/" + (m_year < 10 ? "0" + std::to_string(m_year) : std::to_string(m_year));
}
std::string DateTime::To_String_Date() const
{
    //returns DD/MM/YYYY
    return ((m_day < 10 ? "0" + std::to_string(m_day) : std::to_string(m_day)) + "/" + (m_month < 10 ? "0" + std::to_string(m_month) : std::to_string(m_month)) + "/" + (m_year < 10 ? "0" + std::to_string(m_year) : std::to_string(m_year)));
}
std::string DateTime::To_String_Time() const
{
    //returns HH:MM:SS
    return (m_hour < 10 ? "0" + std::to_string(m_hour) : std::to_string(m_hour)) + ":" + (m_minute < 10 ? "0" + std::to_string(m_minute) : std::to_string(m_minute)) + ":" + (m_second < 10 ? "0" + std::to_string(m_second) : std::to_string(m_second));
}
DateTime DateTime::Time_T_to_DateTime(const std::time_t& time)
{
    std::tm* localTime = std::localtime(&time); //Turns epoch time into tm time.
    return { localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday, localTime->tm_hour, localTime->tm_min, localTime->tm_sec };  //Uses tm time to create DateTime.
}
bool DateTime::operator>(DateTime& rhs)
{
    //Checks if lhs DateTime is greater than rhs DateTime or not.
    if (m_year > rhs.getYear())
        return true;
    else if (m_year == rhs.getYear())
    {
        if (m_month > rhs.getMonth())
            return true;
        else if (m_month == rhs.getMonth())
        {
            if (m_day > rhs.getDay())
                return true;
            else if (m_day == rhs.getDay())
            {
                if (m_hour > rhs.getHour())
                    return true;
                else if (m_hour == rhs.getHour())
                {
                    if (m_minute > rhs.getMinute())
                        return true;
                    else if (m_minute == rhs.getMinute())
                    {
                        if (m_second > rhs.getSecond())
                            return true;
                    }
                }
            }
        }
    }
    return false;
}
bool DateTime::operator<(DateTime& rhs)
{
    //Checks if lhs DateTime is smaller than rhs DateTime or not.
    if (m_year < rhs.getYear())
        return true;
    else if (m_year == rhs.getYear())
    {
        if (m_month < rhs.getMonth())
            return true;
        else if (m_month == rhs.getMonth())
        {
            if (m_day < rhs.getDay())
                return true;
            else if (m_day == rhs.getDay())
            {
                if (m_hour < rhs.getHour())
                    return true;
                else if (m_hour == rhs.getHour())
                {
                    if (m_minute < rhs.getMinute())
                        return true;
                    else if (m_minute == rhs.getMinute())
                    {
                        if (m_second < rhs.getSecond())
                            return true;
                    }
                }
            }
        }
    }
    return false;
}

bool DateTime::operator>=(DateTime& rhs)
    //Checks if lhs DateTime is greater than or equal to rhs DateTime or not.
{
    if (m_year > rhs.getYear())
        return true;
    else if (m_year == rhs.getYear())
    {
        if (m_month > rhs.getMonth())
            return true;
        else if (m_month == rhs.getMonth())
        {
            if (m_day > rhs.getDay())
                return true;
            else if (m_day == rhs.getDay())
            {
                if (m_hour > rhs.getHour())
                    return true;
                else if (m_hour == rhs.getHour())
                {
                    if (m_minute > rhs.getMinute())
                        return true;
                    else if (m_minute == rhs.getMinute())
                    {
                        if (m_second >= rhs.getSecond())
                            return true;
                    }
                }
            }
        }
    }
    return false;
}
bool DateTime::operator<=(DateTime& rhs)
{
    //Checks if lhs DateTime is smaller than or equal to rhs DateTime or not.
    if (m_year < rhs.getYear())
        return true;
    else if (m_year == rhs.getYear())
    {
        if (m_month < rhs.getMonth())
            return true;
        else if (m_month == rhs.getMonth())
        {
            if (m_day < rhs.getDay())
                return true;
            else if (m_day == rhs.getDay())
            {
                if (m_hour < rhs.getHour())
                    return true;
                else if (m_hour == rhs.getHour())
                {
                    if (m_minute < rhs.getMinute())
                        return true;
                    else if (m_minute == rhs.getMinute())
                    {
                        if (m_second <= rhs.getSecond())
                            return true;
                    }
                }
            }
        }
    }
    return false;
}
bool DateTime::operator==(DateTime& rhs)
{
    //Checks if lhs DateTime and rhs DateTime are equal.
    if (m_year == rhs.getYear() &&
        m_month == rhs.getMonth() &&
        m_day == rhs.getDay() &&
        m_hour == rhs.getHour() &&
        m_minute == rhs.getMinute() &&
        m_second == rhs.getSecond())
    {
        return true;
    }
    else
    {
        return false;
    }
}
time_t DateTime::to_time_t()
{
    tm temp;
    temp.tm_year = m_year - 1900;   //tm year is represented as years since 1900, hence the need to remove 1900 years from DateTime.
    temp.tm_mon = m_month - 1;      //tm months are represented from 0-11 whereas DateTime's months are represented from 1-12, thus 1 is removed.
    temp.tm_mday = m_day;
    temp.tm_hour = m_hour;
    temp.tm_min = m_minute;
    temp.tm_sec = m_second;
    return mktime(&temp);   //Converts tm to epoch time.
}
tm* DateTime::to_tm()
{
    
    time_t secs = to_time_t();  //First gets epoch time.
    tm* time = new tm();        
    time = localtime(&secs);    //Then turns epoch time into tm.
    return time;
}
DateTime DateTime::Now()
{
    return Time_T_to_DateTime(std::time(0)); //Gets current Date and Time.
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

void DateTime::setHour(int hour)
{
    m_hour = hour;
}

void DateTime::setDay(int day)
{
    m_day = day;
}

int DateTime::GetWeekDay()
{
    //Gets weekday from tm.
    //Ternary operation required as tm weekday start with 0 on sunday, whereas week_day enum starts with 0 on monday.
    return (to_tm()->tm_wday == 0 ? 6 : to_tm()->tm_wday - 1);
}

