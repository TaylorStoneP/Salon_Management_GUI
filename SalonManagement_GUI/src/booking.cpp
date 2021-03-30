#include "Staff.h"
#include "booking.h"

Booking::Booking(std::string name, 
                 std::string phone, 
                 Staff* staff, 
                 llist<service*> services, 
                 DateTime timeSlot, 
                 bool walkIn, 
                 bool paid) :m_name(name), 
                 m_phone(phone), 
                 m_staff(staff), 
                 m_services(services), 
                 m_timeSlot(timeSlot), 
                 m_walkIn(walkIn), 
                 m_paid(paid) { LOG_ALLOCATION("Booking", this); }
Booking::~Booking() { LOG_DEALLOCATION("Booking", this); }
std::string Booking::To_String()
{
    std::string allServices = "";
    for (int i = 0; i < m_services.count(); i++) {
        allServices += m_services[i]->m_name;
        if (i != m_services.count() - 1)
            allServices += ",";
    }
    //returns name|phone|staff|HH:MM:SS DD/MM/YY|service1,service2,serviceN...|paid?|walk-in?
    return m_name+"|"+m_phone+"|"+m_staff->m_name+"|"+m_timeSlot.To_String()+"|"+allServices+"|"+(m_paid==true?"PAID":"UNPAID")+"|"+(m_walkIn==true?"WALK-IN":"BOOKING");
}
std::string Booking::getMname() const
{
    return m_name;
}

void Booking::setMname(std::string mname)
{
    m_name = mname;
}

std::string Booking::getMphone() const
{
    return m_phone;
}

void Booking::setMphone(std::string mphone)
{
    m_phone = mphone;
}

llist<service*> Booking::getMservices() const
{
    return m_services;
}

void Booking::setMservices(llist<service*> mservices)
{
    m_services = mservices;
}

DateTime Booking::getMtimeSlot() const
{
    return m_timeSlot;
}

void Booking::setMtimeSlot(DateTime mtimeSlot)
{
    m_timeSlot = mtimeSlot;
}

bool Booking::getMwalkIn() const
{
    return m_walkIn;
}

void Booking::setMwalkIn(bool mwalkIn)
{
    m_walkIn = mwalkIn;
}

bool Booking::getMpaid() const
{
    return m_paid;
}

void Booking::setMpaid(bool mpaid)
{
    m_paid = mpaid;
}

Staff* Booking::getMstaff() const
{
    return m_staff;
}

void Booking::setMstaff(Staff* staff)
{
    m_staff = staff;
}

service::service(std::string name, int duration, float cost) :m_name{ name }, m_duration{ duration }, m_cost{ cost } { LOG_ALLOCATION("service", this); }
service::~service(){ LOG_DEALLOCATION("service", this); }