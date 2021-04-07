#include "file_management.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "data_handler.h"
void ReadAllDel(std::ifstream& stream, llist<std::string>& strings, char delimiter)
{
	std::string temp = "";
	while (std::getline(stream, temp, delimiter))
	{
		strings.add_back(temp);
	}
}
void ReadAllDel(std::stringstream& stream, llist<std::string>& strings, char delimiter)
{
	std::string temp = "";
	while (!stream.eof())
	{
		std::getline(stream, temp, delimiter);
		strings.add_back(temp);
	}
}

Booking BookingFromDataString(std::string string, llist<service>& allServices)
{
	llist<std::string> booking_attribs;
	std::stringstream bookings_stream(string);
	ReadAllDel(bookings_stream, booking_attribs, '-');
	//name		=	booking_attribs[0]; name
	//phone		=	booking_attribs[1]; phone
	//services	=	booking_attribs[2]; s1@s2@s3@s4...
	//timeslot	=	booking_attribs[3]; 00@00@00@00@00@0000 - HH@MM@SS@DD@@MM@YYYY
	//walkin	=	booking_attribs[4]; 0/1
	//paid		=	booking_attribs[5]; 0/1
	llist<std::string> booking_services;
	bookings_stream = std::stringstream(booking_attribs[2]);
	ReadAllDel(bookings_stream, booking_services, '@');
	llist<service*> booking_services_final;
	for (int k = 0; k < booking_services.count(); k++)
	{
		for (int m = 0; m < allServices.count(); m++)
		{
			if (booking_services[k] == allServices[m].m_name)
			{
				booking_services_final.add_back(&allServices[m]);
			}
		}
	}

	llist<std::string> booking_timeslot;
	bookings_stream = std::stringstream(booking_attribs[3]);
	ReadAllDel(bookings_stream, booking_timeslot, '@');
	DateTime booking_timeslot_final(std::stoi(booking_timeslot[5]),
		std::stoi(booking_timeslot[4]),
		std::stoi(booking_timeslot[3]),
		std::stoi(booking_timeslot[0]),
		std::stoi(booking_timeslot[1]),
		std::stoi(booking_timeslot[2]));
	return Booking(booking_attribs[0], booking_attribs[1], nullptr, booking_services_final, booking_timeslot_final, std::stoi(booking_attribs[4]), std::stoi(booking_attribs[5]));
}
std::string DataStringFromBooking(Booking& booking_mem)
{
	std::string indiv_booking = "";
	Booking booking = booking_mem;

	indiv_booking += booking.getMname() + "-";
	indiv_booking += booking.getMphone() + "-";

	std::string booking_services = "";
	for (int k = 0; k < booking.getMservices().count(); k++)
	{
		booking_services += booking.getMservices()[k]->m_name;
		booking_services += (k < booking.getMservices().count() - 1) ? "@" : "";
	}
	indiv_booking += booking_services + "-";

	indiv_booking += std::to_string(booking.getMtimeSlot().getHour()) + "@";
	indiv_booking += std::to_string(booking.getMtimeSlot().getMinute()) + "@";
	indiv_booking += std::to_string(booking.getMtimeSlot().getSecond()) + "@";
	indiv_booking += std::to_string(booking.getMtimeSlot().getDay()) + "@";
	indiv_booking += std::to_string(booking.getMtimeSlot().getMonth()) + "@";
	indiv_booking += std::to_string(booking.getMtimeSlot().getYear()) + "-";

	indiv_booking += std::to_string((int)booking.getMwalkIn()) + "-";
	indiv_booking += std::to_string((int)booking.getMpaid());
	return indiv_booking;
}

std::string DataStringFromStaff(Staff& staff_mem)
{
	std::string staff = "";
	staff += staff_mem.m_name + "+";
	staff += staff_mem.m_phone + "+";
	staff += std::to_string((int)staff_mem.m_regular_hours) + "+";
	staff += std::to_string((int)staff_mem.m_fixed_fee) + "+";
	staff += std::to_string(staff_mem.m_rate) + "+";

	std::string services = "";
	for (int j = 0; j < staff_mem.getServices().count(); j++)
	{
		services += staff_mem.getServices()[j]->m_name;
		services += (j < staff_mem.getServices().count() - 1) ? "|" : "";
	}
	staff += services + "+";

	std::string hours = "";
	for (int j = 0; j < staff_mem.getHours().count(); j++)
	{
		working_period hour = staff_mem.getHours()[j];
		std::string indiv_hour = "";
		indiv_hour += std::to_string((int)hour.m_day) + "-";
		indiv_hour += std::to_string(hour.m_start.getHour()) + ":";
		indiv_hour += std::to_string(hour.m_start.getMinute()) + ":";
		indiv_hour += std::to_string(hour.m_start.getSecond()) + "@";
		indiv_hour += std::to_string(hour.m_start.getDay()) + ":";
		indiv_hour += std::to_string(hour.m_start.getMonth()) + ":";
		indiv_hour += std::to_string(hour.m_start.getYear()) + "-";

		indiv_hour += std::to_string(hour.m_finish.getHour()) + ":";
		indiv_hour += std::to_string(hour.m_finish.getMinute()) + ":";
		indiv_hour += std::to_string(hour.m_finish.getSecond()) + "@";
		indiv_hour += std::to_string(hour.m_finish.getDay()) + ":";
		indiv_hour += std::to_string(hour.m_finish.getMonth()) + ":";
		indiv_hour += std::to_string(hour.m_finish.getYear());

		hours += indiv_hour;
		hours += (j < staff_mem.getHours().count() - 1) ? "|" : "";
	}
	staff += hours + "+";

	std::string bookings = "";
	for (int j = 0; j < staff_mem.getBookings().count(); j++)
	{
		bookings += DataStringFromBooking(staff_mem.getBookings()[j]);
		bookings += (j < staff_mem.getBookings().count() - 1) ? "|" : "";
	}
	staff += bookings;
	return staff;
}

Staff StaffFromDataString(std::string string, llist<service>& allServices)
{
	std::stringstream staff_member(string);
	llist<std::string> staff_attribs;
	ReadAllDel(staff_member, staff_attribs, '+');
	//name =		staff_attribs[0];//""
	//phone =		staff_attribs[1];//""
	//reghours =	staff_attribs[2];//0/1
	//fixedFee =	staff_attribs[3];//0/1
	//rate =		staff_attribs[4];//0.0
	//services =	staff_attribs[5];//""|""|""
	//hours =		staff_attribs[6];
	//bookings =	staff_attribs[7];

	std::stringstream services_stream(staff_attribs[5]);
	llist<std::string> services_list;
	llist<service*> services_final;
	llist<std::string> services_temp_copy;
	for (int j = 0; j < allServices.count(); j++)
	{
		services_temp_copy.add_back(allServices[j].m_name);
	}
	ReadAllDel(services_stream, services_list, '|');
	for (int j = 0; j < services_list.count(); j++) {
		services_final.add_back(&(allServices[services_temp_copy.search(services_list[j])]));
	}

	std::stringstream hours_stream(staff_attribs[6]);
	llist<std::string> hours_list;
	llist<working_period> hours_final;
	ReadAllDel(hours_stream, hours_list, '|');
	for (int j = 0; j < hours_list.count(); j++) {
		int day = 0;
		llist<std::string> start;
		llist<std::string> start_time;
		llist<std::string> start_date;
		llist<std::string> finish;
		llist<std::string> finish_time;
		llist<std::string> finish_date;
		std::stringstream hours_substream(hours_list[j]);
		llist<std::string> hours_sublist;
		ReadAllDel(hours_substream, hours_sublist, '-');
		day = std::stoi(hours_sublist[0]);

		std::stringstream start_stream(hours_sublist[1]);
		std::stringstream finish_stream(hours_sublist[2]);

		ReadAllDel(start_stream, start, '@');
		ReadAllDel(finish_stream, finish, '@');

		std::stringstream start_time_stream(start[0]);
		std::stringstream start_date_stream(start[1]);
		std::stringstream finish_time_stream(finish[0]);
		std::stringstream finish_date_stream(finish[1]);
		ReadAllDel(start_time_stream, start_time, ':');
		ReadAllDel(start_date_stream, start_date, ':');
		ReadAllDel(finish_time_stream, finish_time, ':');
		ReadAllDel(finish_date_stream, finish_date, ':');
		hours_final.add_back(working_period((week_day)day, DateTime(std::stoi(start_date[2]),
			std::stoi(start_date[1]),
			std::stoi(start_date[0]),
			std::stoi(start_time[0]),
			std::stoi(start_time[1]),
			std::stoi(start_time[2])),
			DateTime(std::stoi(finish_date[2]),
				std::stoi(finish_date[1]),
				std::stoi(finish_date[0]),
				std::stoi(finish_time[0]),
				std::stoi(finish_time[1]),
				std::stoi(finish_time[2]))));
	}

	llist<std::string> bookings_list;
	std::stringstream bookings_stream(staff_attribs[7]);
	ReadAllDel(bookings_stream, bookings_list, '|');
	llist<Booking> all_read_bookings;
	for (int j = 0; j < bookings_list.count(); j++)
	{
		all_read_bookings.add_back(BookingFromDataString(bookings_list[j], allServices));
	}
	Staff staff_out(staff_attribs[0],
		staff_attribs[1],
		std::stoi(staff_attribs[2]),
		std::stoi(staff_attribs[3]),
		std::stof(staff_attribs[4]),
		services_final,
		llist<Booking>(),
		hours_final);
	for (int k = 0; k < all_read_bookings.count(); k++)
	{
		staff_out.addBooking(all_read_bookings[k]);
	}
	return staff_out;
}

void ReadStaffMembers(llist<Staff>& allStaff, llist<service>& allServices)
{
	std::ifstream file("staff.txt", std::ios::in);
	if (!file.good())
		return;
	llist<std::string> staff;
	ReadAllDel(file, staff, '\n');
	for (int i = 0; i < staff.count(); i++) {
		Staff indiv_staff = StaffFromDataString(staff[i], allServices);
		data_handler::Add_Staff(indiv_staff);
	}
	file.close();
}

void SaveStaffMembers(llist<Staff>& allStaff)
{
	std::ofstream file("staff.txt", std::ofstream::trunc);

	std::string all_staff_string = "";
	for (int i = 0; i < allStaff.count(); i++)
	{
		all_staff_string += DataStringFromStaff(allStaff[i]);
		all_staff_string += (i < allStaff.count() - 1) ? "\n" : "";
	}
	file << all_staff_string;
	file.close();
}
