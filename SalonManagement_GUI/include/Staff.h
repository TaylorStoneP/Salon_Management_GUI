#ifndef STAFF_H
#define STAFF_H
#include <iostream>
#include "debuglogger.h"
#include "llist.h"
#include "booking.h"
#include "datetime.h"


//easy usage of days of week
enum class week_day
{
	monday,
	tuesday,
	wednesday,
	thursday,
	friday,
	saturday,
	sunday
};
std::string to_string(week_day);

struct working_period
{
	week_day m_day;
	DateTime m_start;
	DateTime m_finish;
	working_period(week_day m_day = week_day::sunday, DateTime start = DateTime(), DateTime finish = DateTime());
	working_period(DateTime start, int duration);
	~working_period();
};

//Staff class
class Staff
{
	llist<service*>			m_services;	//stores list of pointers to services practiced
	llist<Booking>			m_bookings;	//stores all bookings for staff
	llist<working_period>	m_hours;	//stores all bookings for staff

	//bookings setter

public:
	std::string		m_name;
	std::string		m_phone;
	bool			m_regular_hours;
	bool			m_fixed_fee;
	float			m_rate;

	//constructor - takes in various pieces of information for staff member with defaults
	Staff(std::string		name = "unknown",
		std::string		phone = "unknown",
		bool			regular_hours = true,
		bool			fixed_fee = false,
		float			rate = -1.0f,
		llist<service*> services = llist<service*>(),
		llist<Booking>	bookings = llist<Booking>(),
		llist<working_period> hours = llist<working_period>());
	//destructor
	~Staff();

	//returns staff member in string format
	std::string To_String();
	std::string Hours_To_String();

	int getStartWorking_Hours();

	//services getter
	llist<service*> getServices();
	//services setter
	void			setServices(llist<service*> data);

	//adds service to their repertoire
	void			addService(service* data);
	//adds multiple services to their repertoire
	void			addServices(llist<service*> data);

	//bookings getter
	llist<Booking>& getBookings();

	//bookings setter
	void			CheckBooking(Booking& booking);
	void			addBooking(Booking& booking);

	//bookings setter
	//void			addBooking(Booking& booking);

	//hours getter
	llist<working_period> getHours();
	//hours setter
	void			setHours(llist<working_period> data);

	//adds hours to their schedule
	void			addHour(working_period data);
};

#endif

