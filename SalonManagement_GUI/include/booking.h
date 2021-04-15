#ifndef BOOKING_H
#define BOOKING_H

#include <iostream>
#include "llist.h"
#include "datetime.h"
//forward declaration for Staff class.
class Staff;

//services struct.
struct service
{
	std::string     m_name;     //name of service.
	int             m_duration; //duration of service in minutes.
	float           m_cost;     //cost of service.

    //constructor - takes in a service name, duration and cost.
    service(std::string name = "unknown", int duration = -1, float cost = -1);  
    //destructor.
    ~service();
};

//Booking class.
class Booking
{
	std::string     m_name;     //name of customer.
	std::string     m_phone;    //phones number of customer.
    Staff*          m_staff;    //staff member assigned to booking.
	llist<service*> m_services; //list of services requested by customer.
	DateTime        m_timeSlot; //date and time of booking.
	bool            m_walkIn;   //indicator of whether the booking is a walk in or not.
	bool            m_paid;     //has the booking been paid or not?

public:
    //booking constructor - takes in various pieces of data of booking with defaults if not entered.
	Booking(    std::string name = "unknown", 
                std::string phone = "unknown", 
                Staff* staff = nullptr, 
                llist<service*> services = llist<service*>(), 
                DateTime timeSlot = DateTime(), 
                bool walkIn = false, 
                bool paid = false);
    //destructor.
    ~Booking();

    //Returns the booking in a string format.
    std::string to_string();

    //Returns the length in minutes of all services in booking - (duration of booking).
    int FullServiceDuration();

    //m_name getter.
    std::string getMname() const;
    //m_name setter.
    void setMname(std::string mname);

    //m_phone getter.
    std::string getMphone() const;
    //m_phone setter.
    void setMphone(std::string mphone);

    //m_services getter.
    llist<service*> getMservices() const;
    //m_services setter.
    void setMservices(llist<service*> mservices);

    //m_timeslot getter.
    DateTime getMtimeSlot() const;
    //m_timeslot setter.
    void setMtimeSlot(DateTime mtimeSlot);

    //m_walkin getter.
    bool getMwalkIn() const;
    //m_walkin setter.
    void setMwalkIn(bool mwalkIn);

    //m_paid getter.
    bool getMpaid() const;
    //m_paid setter.
    void setMpaid(bool mpaid);

    //m_staff getter.
    Staff* getMstaff() const;
    //m_staff setter.
    void setMstaff(Staff* staff);
};

#endif