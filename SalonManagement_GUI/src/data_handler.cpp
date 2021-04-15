#include "data_handler.h"
#include "CustomSetup.h"
data_handler* data_handler::instance = nullptr;

data_handler::data_handler()
{
	//Constructor - sets up default values.
	instance = this;
	selected_date = DateTime(0, 0);
}
data_handler* data_handler::Get()
{
	//If data_handler hasn't been constructed yet, create one, otherwise return already existing one.
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

DateTime& data_handler::Get_Selected_Date()
{
	return data_handler::Get()->selected_date;
}

void data_handler::Add_Staff(Staff& staff_in)
{
	llist<Staff>& allStaffRef = data_handler::Get()->Get_Staff();
	allStaffRef.add_back(staff_in);	
	for (int k = 0; k < staff_in.getBookings().count(); k++)
	{
		//Adds staff member to all bookings in staff member.
		allStaffRef[allStaffRef.count() - 1].getBookings()[k].setMstaff(&allStaffRef[allStaffRef.count() - 1]);
	}
	//Adds staff member to main window panel.
	Main_Event_Window::get()->add_row();
}

void data_handler::Add_Service(service service_in)
{
	llist<service>& allServicesRef = data_handler::Get()->Get_Services();
	allServicesRef.add_back(service_in);
}

service* data_handler::Get_Service_By_Name(std::string name)
{
	llist<service>& allServicesRef = data_handler::Get()->Get_Services();
	for (int i = 0; i < allServicesRef.count(); i++)
	{
		if (name == allServicesRef[i].m_name)
		{
			return &(allServicesRef[i]);
		}
	}
	return nullptr;
}

void data_handler::Add_Booking(int index_of_staff, Booking& booking_in)
{
	llist<Staff>& allStaffRef = data_handler::Get()->Get_Staff();
	allStaffRef[index_of_staff].addBooking(booking_in);
}

void data_handler::Add_Queue(std::string in)
{
	data_handler::Get()->data_queue.add_back(in);
}

std::string data_handler::Pop_Queue()
{
	return data_handler::Get()->data_queue.pop_at(0);
}

void data_handler::Change_Date(DateTime date)
{
	data_handler::Get()->selected_date = date;
}
