#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "llist.h"
#include "Staff.h"
#include "booking.h"

class data_handler
{
	llist<Staff> allStaff;
	llist<service> allServices;

	static data_handler* instance;
	data_handler();
	static data_handler* Get();
public:
	static llist<Staff>& Get_Staff();
	static llist<service>& Get_Services();

	static void Add_Staff(Staff& staff_in);
	static void Add_Service(service service_in);
	static void Add_Booking(int index_of_staff, Booking& booking_in);
};

#endif