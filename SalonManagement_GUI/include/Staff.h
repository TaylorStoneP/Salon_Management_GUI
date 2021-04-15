#ifndef STAFF_H
#define STAFF_H
#include <iostream>
#include "debuglogger.h"
#include "llist.h"
#include "booking.h"
#include "datetime.h"


//easy usage of days of week.
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
//Returns a weekday as a string. 
std::string to_string(week_day);

//struct for storing a staff members shift. 
//If the staff member has regular hours, the week_day decides their working hours, 
//However if the staff does not, the date from the start and finish dates determines their working hours.
struct working_period
{
	week_day m_day;		//Weekday of shift, only relevant to staff members with regular hours.
	DateTime m_start;	//Date and Time of shift beginning.
	DateTime m_finish;	//Date and Time of shift end.
	//Full Constructor.
	working_period(week_day m_day = week_day::sunday, DateTime start = DateTime(), DateTime finish = DateTime());
	//Constructor - Takes in a start Date and Time and a shift length in hours.
	working_period(DateTime start, int duration);
	//destructor.
	~working_period();

	//Returns class as a readable string.
	std::string To_String(bool regular = false);
};

//Staff class.
class Staff
{
	llist<service*>			m_services;	//stores list of pointers to services practiced.
	llist<Booking>			m_bookings;	//stores all bookings for staff.
	llist<working_period>	m_hours;	//stores all bookings for staff.

public:
	std::string		m_name;				//name of staff member.
	std::string		m_phone;			//phone number of staff member.
	bool			m_regular_hours;	//determines whether the staff member's shifts work on a weekly basis or not.
	bool			m_fixed_fee;		//determines whether the staff member pays a fixed fee per hour of their shifts, or a percentage cut of their profits.
	float			m_rate;				//rate of either their fixed fee or percentage cut.

	//constructor - takes in various pieces of information for staff member with defaults.
	Staff(std::string		name = "unknown",
		std::string		phone = "unknown",
		bool			regular_hours = true,
		bool			fixed_fee = false,
		float			rate = -1.0f,
		llist<service*> services = llist<service*>(),
		llist<Booking>	bookings = llist<Booking>(),
		llist<working_period> hours = llist<working_period>());
	//destructor.
	~Staff();

	//returns staff member in string format.
	std::string To_String();
	//returns all shifts in a string format.
	std::string Hours_To_String();

	//services getter.
	llist<service*> getServices();
	//services setter.
	void			setServices(llist<service*> data);

	//adds service to their repertoire.
	void			addService(service* data);
	//adds multiple services to their repertoire.
	void			addServices(llist<service*> data);

	//bookings getter.
	llist<Booking>& getBookings();

	//bookings setter.
	void			CheckBooking(Booking& booking);
	//Adds booking to staff member.
	void			addBooking(Booking& booking);

	//hours getter
	llist<working_period> getHours();
	//hours setter
	void			setHours(llist<working_period> data);

	//adds hours to their schedule
	void			addHour(working_period data);

	//Returns a list of booking pointers during the period between the two dates.
	llist<Booking*> GetBookingsDuring(DateTime start, DateTime finish);

	//operator overloads.
	bool operator==(Staff& rhs);
};

#endif

