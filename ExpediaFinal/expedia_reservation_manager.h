#include<iostream>
#ifndef EXPEDIA_FLIGHTS_H_
#define EXPEDIA_FLIGHTS_H_
#include"expedia_Flights.h"
#include"expedia_usermgr.h"
#include "expedia_Reservatoin.h"
#include "expedia_payments_api.h"
#include "expedia_payment_card.h"
using namespace :: std;

class Reservation_Manager{
private:
    IPaymentManager*iPaymentManager;
    static Reservation_Manager*reservatoin_manager;
    string from,to,from_date,to_date;
    int adults,children,infants;
    Flight_Manager*flight_manager=Flight_Manager::get_instance();
    UserManager*user_manager=UserManager::get_instance();
    vector<Flight>flights;
public:
    static Reservation_Manager*get_instance(){
        if(!reservatoin_manager)
            reservatoin_manager=new Reservation_Manager();
        return reservatoin_manager;
    }
    void add_flight(string user_name,Itinerary&itinerary){
        Flight_Details flight_details;
        cout << "Enter from: ";
        cin >> from;
        flight_details.set_from(from);
        cout << "Enter From Date (dd-mm-yy): ";
        cin >> from_date;
        flight_details.set_from_date(from_date);
        cout << "Enter to: ";
        cin >> to;
        flight_details.set_to(to);
        cout << "Enter To Date (dd-mm-yy): ";
        cin >> to_date;
        flight_details.set_to_date(to_date);
        cout << "Enter number of adults: ";
        cin >> adults;
        flight_details.set_adults(adults);
        cout << "Enter number of children: ";
        cin >> children;
        flight_details.set_childern(children);
        cout << "Enter number of infants: ";
        cin >> infants;
        flight_details.set_infants(infants);
        Flight_Manager*flight_manager=Flight_Manager::get_instance();
        flights=flight_manager->search_flights(flight_details);
        for(int i=0;i<flights.size();i++)
            cout << i+1 << flights[i].to_String() << "\n";
        cout << "Enter -1 to cancel or number in range 1-" << flights.size() << ": ";
        int num;
        cin >> num;
        if(num!=-1)
            itinerary.add_reservatoin(new Flight_Reservation(flights[num-1],flight_details));
    }
    void pay(string user_name,Itinerary&itinerary){
        bool done=false;
        while(!done){
            vector<Payment_Card>cards=user_manager->users[user_name]->get_cards();
            for(int i=0;i<cards.size();i++){
                cout << i+1 << "-" << cards[i].to_String() << "\n";
            }
            if(!cards.empty()){
                cout << "Choose card or (11) to Add new card:";
            }
            else
                cout << "11-Enter new card: ";
            int choise;
            cin >> choise;
            if(cards.empty()||choise==11){
                cout << "Enter card_name";
                string card_name;
                cin >> card_name;
                cout << "Enter name: ";
                string name;
                cin >> name;

                cout << "Enter address: ";
                string address;
                cin>>address;

                cout << "Enter id: ";
                string id;
                cin >> id;

                cout << "Enter expiry date: ";
                string expiry_date;
                cin >> expiry_date;

                cout << "Etner ccv: ";
                int ccv;
                cin >> ccv;

                Payment_Card user_card(card_name,name,id,expiry_date,ccv,address);
                user_manager->add_card(user_name,user_card);
            }
            
            else{
                Payment_Card customer_card=user_manager->users[user_name]->get_card(choise-1);
                iPaymentManager =payment_factory(customer_card.get_card_name());
                iPaymentManager->set_card_data(customer_card.get_name(),customer_card.get_adrees(),customer_card.get_expiry_date(),customer_card.get_id(),customer_card.get_ccv_date());
                if(itinerary.pay_resservatoin(iPaymentManager))
                    cout << "Payment done succefuly !n\n";
                done=true;
            }
        }
    }
};
Reservation_Manager*Reservation_Manager::reservatoin_manager=nullptr;
#endif