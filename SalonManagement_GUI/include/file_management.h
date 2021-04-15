#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H
#include "Staff.h"
#include "datetime.h"
#include "debuglogger.h"
#include "llist.h"
#include "booking.h"
#include <sstream>

//File management functions.

//Returns of a list of strings by separating a file stream using a given delimiter.
void ReadAllDel(std::ifstream& stream, llist<std::string>& return_string, char delimiter);
//Returns of a list of strings by separating a stringstream using a given delimiter.
void ReadAllDel(std::stringstream& stream, llist<std::string>& return_string, char delimiter);
//Reads in all staff members.
void ReadStaffMembers();
//Turns a string with all its information into a booking.
Booking BookingFromDataString(std::string string, llist<service>& allServices);
//Turns booking into a string with all its information.
std::string DataStringFromBooking(Booking& booking_mem);
//Turns staff into a string with all its information.
std::string DataStringFromStaff(Staff& staff_mem);
//Turns a string with all its information into a staff member.
Staff StaffFromDataString(std::string string, llist<service>& allServices);
//Saves all staff members with their bookings attatched
void SaveStaffMembers();
//Reads in all services.
void ReadServices();
//Saves all services.
void SaveServices();
#endif