#include <iostream>
#include "expedia_user.h"
#include "expedia_usermgr.h"
#include "expedia_reservation_manager.h"
#include "expedia_program_interface.h"
using namespace :: std;
class SingUp{
private:
    static SingUp*signup;
    SingUp(){}
    public:
    static SingUp*get_instance(){
        if(!signup)
            signup=new SingUp();
        return signup;
    }
    static void sign(){
        UserManager*UM=UserManager::get_instance();
        string user_name,password,name,email;
        cout << "Enter user_name: ";
        cin >> user_name;
        cout << "Enter password: ";
        cin >> password;
        cout << "Enter name: ";
        cin >> name;
        cout << "Enter e-mail: ";
        cin >> email;
        UM->add_user(new User(user_name,password,name,email));
        ProgramInterface::main_menu(user_name);
    }

};
class Main_Menu{
private:
    Main_Menu(){}
    static Main_Menu*menu;
public:
    static Main_Menu*get_instance(){
        if(!menu)
            menu=new Main_Menu();
        return menu; 
    }
    void load_menu(){
        int choise;
        string user_name;
        string password;
        while(true){
            cout << "Menu:\n";
            cout << "\t 1:login\n";
            cout << "\t 2:Sing Up\n";
            cout << "\nEnter number in range (1-2): ";
            cin >> choise;
            if(choise==2)
                SingUp::sign();
        }
    }
};

Main_Menu* Main_Menu::menu=nullptr;