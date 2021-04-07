#include "data_handler.h"

data_handler* data_handler::instance = nullptr;

data_handler::data_handler()
{
	instance = this;
}
data_handler* data_handler::Get()
{
	if (instance == nullptr)
	{
		instance = new data_handler();
	}
	return instance;
}

llist<Staff>& data_handler::Get_Staff()
{
	return data_handler::Get()->allStaff;
}

llist<service>& data_handler::Get_Services()
{
	return data_handler::Get()->allServices;
}

void data_handler::Add_Staff(Staff& staff_in)
{
	llist<Staff>& allStaffRef = data_handler::Get()->Get_Staff();
	allStaffRef.add_back(staff_in);
	for (int k = 0; k < staff_in.getBookings().count(); k++)
	{
		allStaffRef[allStaffRef.count() - 1].getBookings()[k].setMstaff(&allStaffRef[allStaffRef.count() - 1]);
	}
}

void data_handler::Add_Service(service service_in)
{
	llist<service>& allServicesRef = data_handler::Get()->Get_Services();
	allServicesRef.add_back(service_in);
}

void data_handler::Add_Booking(int index_of_staff, Booking& booking_in)
{
	llist<Staff>& allStaffRef = data_handler::Get()->Get_Staff();
	allStaffRef[index_of_staff].addBooking(booking_in);
}
