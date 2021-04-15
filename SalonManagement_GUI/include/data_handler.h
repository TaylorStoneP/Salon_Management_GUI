#ifndef DATA_HANDLER_H
#define DATA_HANDLER_H

#include "llist.h"
#include "Staff.h"
#include "booking.h"

//Singleton Class.
//Keeps track of data used in main booking system.
//Can be accessed using data_handler::Get().
class data_handler
{
	llist<Staff> allStaff;			//list of all staff members.
	llist<service> allServices;		//list of all services.
	llist<std::string> data_queue;	//queue of strings of data if needed to be passed around.


	static data_handler* instance;	//the instance of the singleton.
	DateTime selected_date;			//Main data of program, all displayed staff are based on this value.

	//constructor.
	data_handler();			
	//Returns the instance.
	static data_handler* Get();		
public:
	//Returns a reference to the list of staff.
	static llist<Staff>& Get_Staff();		
	//Returns a reference to the list of services.
	static llist<service>& Get_Services();	
	//Returns a reference to the selected date.
	static DateTime& Get_Selected_Date();	

	//Use this to add a staff member to the program.
	static void Add_Staff(Staff& staff_in);	
	//Use this to add a service to the program
	static void Add_Service(service service_in);	
	//Returns a pointer to a service based on its name. nullptr if it doesn't exist.
	static service* Get_Service_By_Name(std::string name);	
	//Use this to add a booking to the program. Requires index of staff member in allStaff.
	static void Add_Booking(int index_of_staff, Booking& booking_in);	
	//Use this to add a string to the data queue. 
	static void Add_Queue(std::string in);
	//Use this to remove the first element in the data queue.
	static std::string Pop_Queue();
	//Use this to change the main programs date.
	static void Change_Date(DateTime date);
};

#endif