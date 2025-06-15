#ifndef EXPEDIA_RESERVATION_H_
#define EXPEDIA_RESERVATION_H_
#include <iostream>
#include "expedia_payments_api.h"
#include "expedia_Flights.h"
using namespace :: std;

class Reservatoin{
private:
    bool is_paid;
public:
    virtual const int&get_cost()=0;
    virtual Reservatoin*clone()=0;
    virtual string to_String()=0;
};
class Flight_Reservation : public Reservatoin{
private:
    Flight flight;
    Flight_Details flight_details;
public:
    Flight_Reservation(Flight flight,Flight_Details flight_details)
    :flight(flight),flight_details(flight_details){}
    virtual const int&get_cost()override{
        return flight.get_price();
    }
    virtual Flight_Reservation*clone(){
        return new Flight_Reservation(*this);
    }
    virtual string to_String(){
        return flight.get_name() + " From: " + flight_details.get_from() + " Date: " + 
        flight_details.get_from_date() + " To: " + flight_details.get_to() + " Date: " + flight_details.get_to_date();
    }
};
class Itinerary{
private:
    vector<Reservatoin*>reservations;
public:
    void add_reservatoin(Reservatoin*resservation){
        reservations.push_back(resservation);
    }
    bool pay_resservatoin(IPaymentManager*iPaymentManager){
        bool success=true;
        for(auto res:reservations){
            success=success&iPaymentManager->withdrawMoney(res->get_cost());
        }
        return success;
    }
    void print_reservations(){
        for(auto res:reservations){
            cout << "Frist itinerary: \n\t";
            cout << res->to_String() << "\n";
        }
    }
};
#endif