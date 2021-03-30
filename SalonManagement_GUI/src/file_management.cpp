#include "file_management.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
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
void ReadStaffMembers(llist<Staff>& allStaff, llist<service>& allServices, llist<Booking*>& bookings)
{
	std::ifstream file("staff.txt", std::ios::in);
	if (!file.good())
		return;
	llist<std::string> staff;
	ReadAllDel(file, staff, '\n');
	for (int i = 0; i < staff.count(); i++) {
		std::stringstream staff_member(staff[i]);
		llist<std::string> staff_attribs;
		ReadAllDel(staff_member, staff_attribs, '+');
		//name =		staff_attribs[0];//""
		//phone =		staff_attribs[1];//""
		//hours =		staff_attribs[2];//0/1
		//fixedFee =	staff_attribs[3];//0/1
		//rate =		staff_attribs[4];//0.0
		//services =	staff_attribs[5];//""|""|""
		//hours =		staff_attribs[6];
		//bookings =	staff_attribs[7];
		
		std::stringstream services_stream(staff_attribs[5]);
		llist<std::string> services_list;
		llist<service*> services_final;
		llist<std::string> services_temp_copy;
		for (int j = 0; j < allServices.count();j++)
		{
			services_temp_copy.add_back(allServices[j].m_name);
		}
		ReadAllDel(services_stream,services_list,'|');
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
			hours_final.add_back(working_period((week_day)day,DateTime(	std::stoi(start_date[2]), 
																	std::stoi(start_date[1]), 
																	std::stoi(start_date[0]), 
																	std::stoi(start_time[0]), 
																	std::stoi(start_time[1]), 
																	std::stoi(start_time[2])),
														DateTime(	std::stoi(finish_date[2]),
																	std::stoi(finish_date[1]),
																	std::stoi(finish_date[0]),
																	std::stoi(finish_time[0]),
																	std::stoi(finish_time[1]),
																	std::stoi(finish_time[2]))));
		}
		allStaff.add_back(Staff(	staff_attribs[0],
							staff_attribs[1],
							std::stoi(staff_attribs[2]),
							std::stoi(staff_attribs[3]),
							std::stof(staff_attribs[4]),
							services_final,
							llist<Booking>(),
							hours_final));
	}
	file.close();
}
