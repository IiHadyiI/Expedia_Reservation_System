#include<iostream>
#include<vector>
#include<map>
#include<functional>
#include<string>
#include<memory>
#ifndef EXPEDIA_FLIGHT_H_
#define EXPEDIA_FLIGHT_H_

#include"expedia_flights_api.h"
using namespace::std;
enum Flight_Companies{AirCnada_Airlins,Turkish_Airlines};
class Flight{
private:
    string airline_name;
    int price;
    string from_date;
    string to_date;
public:
    void set_name(string _airline_name){
        airline_name=_airline_name;
    }
    const string&get_name()const{
        return airline_name;
    }
    void set_price(int p){
        price=p;
    }
    const int&get_price()const{
        return price;
    }
    void set_from_date(string from){
        from_date=from;
    }
    const string&get_from_date()const{
        return from_date;
    }
    void set_to_date(string to){
        to_date=to;
    }
    const string&get_to_date()const{
        return to_date;
    }
    string to_String(){
        return "AirLine: " + get_name() + " const: " + to_string(price) +  " Departure Date " + get_from_date() +
                " Arrival date " + get_to_date();
    }   
};
class Canada_Flight : public Flight{
private:
    AirCanadaFlight canada_flight;
};
class Turkish_Flight: public Flight{
private:
    TurkishFlight turkish_flight;
};
class Flight_Details{
private:
    string from , from_date , to , to_date;
    int adults , childern , infants;
public:
    void set_from(string f){
        from = f;
    }
    const string&get_from()const{
        return from;
    }
    void set_to(string t){
        to = t;
    }
    const string&get_to()const{
        return to;
    }
    void set_from_date(string f){
        from_date = f;
    }
    const string&get_from_date()const{
        return from_date;
    }
    void set_to_date(string t){
        to_date = t;
    }
    const string&get_to_date()const{
        return to_date;
    }
    void set_adults(int a){
        adults = a;
    }
    const int&get_adults()const{
        return adults;
    }
    void set_childern(int ch){
        childern = ch;
    }
    const int&get_children()const{
        return childern;
    }
    void set_infants(int inf){
        infants = inf;
    }
    const int&get_infants()const{
        return infants;
    }
};
class Flight_System_Apis{
protected:
    Flight_Details flight_details;
public:
    void set_data(Flight_Details _flight_details){
        flight_details=_flight_details;
    }
    virtual vector<Flight> GetAvailableFlights()=0;
    virtual bool ReserveFlight(const Flight&flight)=0;
};

class Turkish_System : public Flight_System_Apis{
private:
    TurkishAirlinesOnlineAPI turkish_api;
    Turkish_System(){}
    static Turkish_System* turkish_system;
public:
    static Turkish_System* get_instance(){
        if(!turkish_system)
            turkish_system=new Turkish_System();
        return turkish_system;
    }
	virtual vector<Flight> GetAvailableFlights()  override {
        turkish_api.SetFromToInfo(flight_details.get_from_date(),flight_details.get_from(),flight_details.get_to_date(),flight_details.get_to());
        turkish_api.SetPassengersInfo(flight_details.get_infants(),flight_details.get_children(),flight_details.get_adults());
        vector<Flight> flights;
        vector<TurkishFlight>turkish_flights;
		turkish_flights=turkish_api.GetAvailableFlights();
        for(auto&flight:turkish_flights){
            Flight F;
            F.set_name("Turkish_Airlines");
            F.set_price(flight.cost);
            F.set_from_date(flight.datetime_from);
            F.set_to_date(flight.datetime_to);
            flights.push_back(F);
        }
		return flights;
	}

	bool ReserveFlight(const Flight&chosen_flight) {
        TurkishCustomerInfo info;
        TurkishFlight flight;
        flight.cost=chosen_flight.get_price();
        flight.datetime_from=chosen_flight.get_from_date();
        flight.datetime_to=chosen_flight.get_to_date();
		return TurkishAirlinesOnlineAPI::ReserveFlight(info,flight);
	}
};
Turkish_System*Turkish_System::turkish_system=nullptr;
class Canada_System : public Flight_System_Apis{
private:
    Canada_System(){}
    static Canada_System*canada_system;
    AirCanadaOnlineAPI canada_api;
    int children = flight_details.get_children()+flight_details.get_infants();
public:
    static Canada_System*get_instance(){
        if(!canada_system)
            canada_system=new Canada_System();
        return canada_system;
    }
    virtual vector<Flight> GetAvailableFlights() override{
		vector<Flight> flights;
        vector<AirCanadaFlight>Canada_flights;
        Canada_flights = AirCanadaOnlineAPI::GetFlights(flight_details.get_from(),flight_details.get_from_date(),flight_details.get_to(),flight_details.get_to_date(),flight_details.get_adults(),children);
		for(auto flight:Canada_flights){
            Flight F;
            F.set_name("AirCanada Arilines");
            F.set_price(flight.price);
            F.set_from_date(flight.date_time_from);
            F.set_to_date(flight.date_time_to);
            flights.push_back(F);
        }
		return flights;
	}
	bool ReserveFlight(const Flight&flight) override{
        AirCanadaFlight Canada_flight;
        AirCanadaCustomerInfo info;
        Canada_flight.price=flight.get_price();
        Canada_flight.date_time_from=flight.get_from_date();
        Canada_flight.date_time_to=flight.get_to_date();
		return canada_api.ReserveFlight(Canada_flight,info); 
    }
};
Canada_System* Canada_System::canada_system=nullptr;

Flight_System_Apis* Flight_Factory(int company){
    map<int,Flight_System_Apis*>factory_map={
        {Flight_Companies::AirCnada_Airlins,  Turkish_System::get_instance()},
        {Flight_Companies::Turkish_Airlines, Canada_System::get_instance()}
    };
    return factory_map[company];
}

class Flight_Manager {
private:
    vector<Flight_System_Apis*>flight_systems;
    vector<Flight>available_flights;
    static Flight_Manager*flight_manager;
    Flight_Manager(){
        flight_systems.push_back(Flight_Factory(Flight_Companies::AirCnada_Airlins));
        flight_systems.push_back(Flight_Factory(Flight_Companies::Turkish_Airlines));
    }
public:
    static Flight_Manager*get_instance(){
        if(!flight_manager)
            flight_manager=new Flight_Manager();
        return flight_manager;
    }
    vector<Flight> search_flights(Flight_Details flight_details){
        for(auto flight_sys:flight_systems){
            flight_sys->set_data(flight_details);
            vector<Flight> available_flights_2=(flight_sys->GetAvailableFlights());
            available_flights.insert(available_flights.begin(),available_flights_2.begin(),available_flights_2.end());
        }
        return available_flights;
    }
    bool reserve_flight(Flight flight){
        if(flight.get_name()=="AirCanada Airlines")
            return Flight_Factory(Flight_Companies::AirCnada_Airlins)->ReserveFlight(flight);
        else if (flight.get_name()=="Turkish Airlines")
            return Flight_Factory(Flight_Companies::Turkish_Airlines)->ReserveFlight(flight);
    }
};
Flight_Manager*Flight_Manager::flight_manager=nullptr;

#endif