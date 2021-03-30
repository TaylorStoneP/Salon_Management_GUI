#include "Staff.h"
working_period::working_period(week_day day, DateTime start, DateTime finish):m_day(day),m_start(start),m_finish(finish){}
working_period::~working_period() {}

Staff::Staff(	std::string				name,
				std::string				phone,
				bool					regular_hours,
				bool					fixed_fee,
				float					rate,
				llist<service*>			services,
				llist<Booking>			bookings,
				llist<working_period>	hours)
				:	m_services(services),
					m_bookings(bookings),
					m_name(name),
					m_phone(phone),
					m_regular_hours(regular_hours),
					m_fixed_fee(fixed_fee),
					m_rate(rate),
					m_hours(hours)
				{ LOG_ALLOCATION("Staff",this); }

Staff::~Staff() { LOG_DEALLOCATION("Staff", this); }

std::string Staff::To_String()
{
	std::string allServices = "";
	for (int i = 0; i < m_services.count(); i++) {
		allServices += m_services[i]->m_name;
		if (i != m_services.count() - 1)
			allServices += ",";
	}

	//returns name|phone|regular-hours?|fixed-fee?|rate|service1,service2,serviceN...|time1,time2,timeN...
	return m_name + "|" + m_phone + "|" + (m_regular_hours ? "REGULAR-HOURS" : "IRREGULAR-HOURS") + "|" + (m_fixed_fee ? "FIXED-FEE @ " LOG_POUND + std::to_string(m_rate) : "%-RETURN @ " + std::to_string(m_rate) + "%") + "|" + allServices;
}
std::string Staff::Hours_To_String()
{
	std::string allHours = "";
	for (int i = 0; i < m_hours.count(); i++) {
		allHours += to_string(m_hours[i].m_day) + "    \t";
		allHours += m_hours[i].m_start.To_String_Time() + "-";
		allHours += m_hours[i].m_finish.To_String_Time();
		allHours += (m_regular_hours ? ("") : (" " + m_hours[i].m_start.To_String_Date()));
		if (i != (m_hours.count() - 1))
			allHours += "\n";
	}

	//returns time1,time2,timeN...
	return allHours;
}

llist<service*> Staff::getServices() { return m_services; }
void Staff::setServices(llist<service*> data) {
	m_services = data;
}
void Staff::addService(service* data) { m_services.add_back(data); }
void Staff::addServices(llist<service*> data){
	for (int i = 0; i < data.count(); i++)
		m_services.add_back(data[i]);
}
llist<Booking>& Staff::getBookings(){return m_bookings;}
void Staff::addBooking(Booking& booking){
	booking.setMstaff(this);
	m_bookings.add_back(booking);
}
llist<working_period> Staff::getHours() { return m_hours; }
void Staff::setHours(llist<working_period> data) {
	m_hours = data;
}
void Staff::addHour(working_period data) {
	if (m_regular_hours)
	{
		data.m_start = DateTime(0, 0, 0, data.m_start.getHour(), data.m_start.getMinute(), 0);
		data.m_finish = DateTime(0, 0, 0, data.m_finish.getHour(), data.m_finish.getMinute(), 0);
	}
	m_hours.add_back(data);
}

std::string to_string(week_day day)
{
	switch (day)
	{
	case week_day::monday:
		return "Monday";
	case week_day::tuesday:
		return "Tuesday";
	case week_day::wednesday:
		return "Wednesday";
	case week_day::thursday:
		return "Thursday";
	case week_day::friday:
		return "Friday";
	case week_day::saturday:
		return "Saturday";
	case week_day::sunday:
		return "Sunday";
	default:
		return "Error day";
	}
}
