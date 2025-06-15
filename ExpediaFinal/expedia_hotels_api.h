/*
 * expedia_hotels_api.h
 *
 *  Created on: Sep 22, 2020
 *      Author: moustafa
 */
#include<iostream>
using namespace :: std;
#include <vector>
#ifndef EXPEDIA_HOTELS_API_H_
#define EXPEDIA_HOTELS_API_H_

class HiltonRoom {
public:
	string room_type;
	int available;
	double price_per_night;
	string date_from;
	string date_to;
};

class HiltonHotelAPI {
public:
	static vector<HiltonRoom> SearchRooms(string country, string city, string from_date, string to_date, int adults, int children, int needed_rooms) {
		vector<HiltonRoom> rooms;

		rooms.push_back( { "Interior View", 6, 200.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "City View", 3, 300.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Deluxe View", 8, 500.0, "29-01-2022", "10-02-2022" });

		return rooms;
	}
};

class MarriottFoundRoom {
public:
	string room_type;
	int available;
	double price_per_night;
	string date_from;
	string date_to;
};

class MarriottHotelAPI {
public:
	static vector<MarriottFoundRoom> FindRooms(string from_date, string to_date, string country, string city, int needed_rooms, int adults, int children) {
		vector<MarriottFoundRoom> rooms;

		rooms.push_back( { "City View", 8, 320.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Interior View", 8, 220.0, "29-01-2022", "10-02-2022" });
		rooms.push_back( { "Private View", 5, 600.0, "29-01-2022", "10-02-2022" });

		return rooms;
	}
};
//////////////////////////////////////////////
class Room{
private:
	string room_type,date_from,date_to;
	int available,;
	double price;
public:
	void set_room_type(string rt){
		room_type=rt;
	}
	const string&get_room_type()const{
		return room_type;
	}
	void set_date_from(string date){
		date_from=date;
	}
	const string&get_date_from()const{
		return date_from;
	}
	void set_date_to(string date){
		date_to=date;
	}
	const string&get_date_to()const{
		return date_to;
	}
	void set_available(int avail){
		available=avail;
	}
	const int&get_available()const{
		return available;
	}
	void set_price(int p){
		price=p;
	}
	const int&get_price()const{
		return price;
	}
};
class Room_Details{
private:
	string from_date,to_date,country,city;
	int needed_rooms,adults,children;
public:
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
	void set_city(string c){
		city=c;
	}
	const string&get_city()const{
		return city;
	}
	void set_country(string count){
		country=count;
	}
	const string&get_country()const{
		return country;
	}
	void set_needed_rooms(int rooms){
		needed_rooms=rooms;
	}
	const int&get_needed_rooms()const{
		return needed_rooms;
	}
	void set_adults(int a){
		adults=a;
	}
	const int&get_adults_count()const{
		return adults;
	}
	void set_children(int ch){
		children=ch;
	}
	const int&get_children_count()const{
		return children;
	}
};


class IHotelManager{
protected:
	Room_Details room_details;
public:
	void set_room_details(Room_Details _room_details){
		room_details=_room_details;		
	}
	virtual vector<Room> search_rooms()=0;
};
class HiltonHotel:public IHotelManager{
public:
	virtual vector<Room> search_rooms()override{
		vector<HiltonRoom>hiltonRooms;
		vector<Room>rooms;
		hiltonRooms=HiltonHotelAPI::SearchRooms(room_details.get_country(),room_details.get_city(),room_details.get_from_date(),room_details.get_to_date(),room_details.get_adults_count(),room_details.get_children_count(),room_details.get_needed_rooms());
		for(auto room:hiltonRooms){
			Room R;
			R.set_date_from(room.date_from);
			R.set_date_to(room.date_to);
			R.set_available(room.available);
			R.set_price(room.price_per_night);
			R.set_room_type(room.room_type);
			rooms.push_back(R);
		}
		return rooms;
	}
};
class MarriottHotel : public IHotelManager{
public:
	virtual vector<Room> search_rooms()override{
		vector<Room>rooms;
		vector<MarriottFoundRoom>MarriotRooms=MarriottHotelAPI::FindRooms(room_details.get_from_date(),room_details.get_to_date(),room_details.get_country(),room_details.get_city(),room_details.get_needed_rooms(),room_details.get_adults_count(),room_details.get_children_count());
		for(auto room:MarriotRooms){
			Room R;
			R.set_date_from(room.date_from);
			R.set_date_to(room.date_to);
			R.set_available(room.available);
			R.set_price(room.price_per_night);
			R.set_room_type(room.room_type);
			rooms.push_back(R);
		}
		return rooms;
	}
};
#endif /* EXPEDIA_HOTELS_API_H_ */
