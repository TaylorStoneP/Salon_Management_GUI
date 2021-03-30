#ifndef FILE_MANAGEMENT_H
#define FILE_MANAGEMENT_H
#include "Staff.h"
#include "datetime.h"
#include "debuglogger.h"
#include "llist.h"
#include "booking.h"
#include <sstream>
void ReadAllDel(std::ifstream& stream, llist<std::string>& return_string, char delimiter);
void ReadAllDel(std::stringstream& stream, llist<std::string>& return_string, char delimiter);
void ReadStaffMembers(llist<Staff>& allStaff, llist<service>& allServices, llist<Booking*>& bookings);

#endif