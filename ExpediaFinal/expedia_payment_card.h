#ifndef EXPEDIA_PAYMENT_CARDS_MANAGER_H_
#define EXPEDIA_PAYMENT_CARDS_MANAGER_H_
#include<iostream>
#include"expedia_payments_api.h"
#include"expedia_user.h"
using namespace :: std;

class Payment_Card{
private:
	string card_name;
	string name;
	string address;
	string id;
	string expiry_date;
	int ccv;
public:
    Payment_Card(string card_name,string name,string id,string expiry_date,int ccv,string address="")
    :card_name(card_name),name(name),id(id),expiry_date(expiry_date){}
	void set_name(string _name){
		name=_name;
	}
	const string&get_card_name()const{
		return card_name;
	}
	const string&get_name()const{
		return name;
	}
	void set_address(string _address){
		address=_address;
	}
	const string&get_adrees()const{
		return address;
	}
	void set_id(string _id){
		id=_id;
	}
	const string&get_id()const{
		return id;
	}
	void set_expiry_date(string _expiry_date){
		expiry_date=_expiry_date;
	}
	const string&get_expiry_date()const{
		return expiry_date;
	}
	void set_ccv(int _ccv){
		ccv=_ccv;
	}
	const int&get_ccv_date()const{
		return ccv;
	}
	const string to_String(){
		return  "Card Owner: " + get_name() + " Card number: " + get_id();
	}
};



#endif

