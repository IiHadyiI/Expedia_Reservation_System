#ifndef EXPEDIA_PROGRAM_INTERFACE_H_
#define EXPEDIA_PROGRAM_INTERFACE_H_
#include<iostream>
#include"expedia_reservation_manager.h"
#include"expedia_usermgr.h"
using namespace::std;

class ProgramInterface{
private:
    
public:
    static void main_menu(string user_name){
        int choise;
        UserManager*user_manager=UserManager::get_instance();
        while(true){
            cout << "Menu\n";
            cout << "\t1:View Profile\n";
            cout << "\t2:Make Itinerary\n";
            cout << "\t3:List my itineraries\n";
            cout << "\t4:Logout\n";
            cout << "\nEnter number in range 1 - 4: ";
            cin >> choise;
            switch (choise)
            {
            case 2:
                ProgramInterface::make_itinerary_menu(user_name);
                break;
            case 3:
                user_manager->users[user_name]->print_itineraries();
            default:
                break;
            }
        }
    }
    static void make_itinerary_menu(string user_name){
        int choise;
        Itinerary itinerary;
        bool loob=true;
        while(loob){
            cout << "Menu\n";
            cout << "\t1:Add Flight\n";
            cout << "\t2:Add Hotel\n";
            cout << "\t3:Done\n";
            cout << "\t4:cancel\n";
            cout << "\nEnter number in range 1 - 4: ";
            int num;
            cin >> num;
            Reservation_Manager*reservation_manager=Reservation_Manager::get_instance();
            UserManager*user_manager=UserManager::get_instance();
            switch (num)
            {
            case 1:
                reservation_manager->add_flight(user_name,itinerary);
                user_manager->users[user_name]->add_Itinerary(itinerary);
                break;
            case 3:
                reservation_manager->pay(user_name,itinerary);
            default:
                loob=false;
                break;
            }
        }
    }
};

#endif 