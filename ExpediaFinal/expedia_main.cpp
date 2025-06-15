#include<iostream>
#include"expedia_menu.h"
using namespace::std;

int main(){
    Main_Menu* main_menu=Main_Menu::get_instance();
    main_menu->load_menu();
    return 0;
}