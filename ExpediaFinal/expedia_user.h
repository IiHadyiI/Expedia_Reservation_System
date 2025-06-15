#include<iostream>
#ifndef EXPEDIA_user_H_
#define EXPEDIA_user_H_
#include"expedia_payments_api.h"
#include<vector>
#include"expedia_Reservatoin.h"
#include"expedia_payment_card.h"
using namespace::std;

class User{
private:
    string user_name,password,name,email;
    vector <Payment_Card>user_cards;
    vector<Itinerary>itineraries;
public:
    User(string user_name,string password,string name,string email)
    :user_name(user_name),password(password),name(name),email(email){}
    const string&get_user_name()const{
        return user_name;
    }
    const string&get_password()const{
        return password;
    }
    const string&get_name()const{
        return name;
    }
    const string&get_email()const{
        return email;
    }
    void add_card(Payment_Card card){
        user_cards.push_back(card);
    }
    Payment_Card get_card(int index){
        return user_cards[index];
    }
    const vector<Payment_Card>&get_cards()const{
        return user_cards;
    }
    void add_Itinerary(Itinerary itinerary){
        itineraries.push_back(itinerary);
    }
    const vector<Itinerary>&get_Itinerary()const{
        return itineraries;
    }
    const void print_itineraries(){
        for(auto itinerary:itineraries)
            itinerary.print_reservations();
    }
};

#endif