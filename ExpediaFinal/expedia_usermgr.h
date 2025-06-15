#ifndef EXPEDIA_USERMGR_H_
#define EXPEDIA_USERMGR_H_
#include<iostream>
#include<map>
#include"expedia_user.h"
using namespace :: std;

class UserManager{
private:
    static UserManager* usermanager;
    UserManager(){}
public:
    map<string,User*> users;
    static UserManager*get_instance(){
        if(!usermanager)
            usermanager=new UserManager();
        return usermanager;
    }
    void add_user(User*user){
        users[user->get_user_name()]=user;
    }
    void add_card(string user_name,Payment_Card card){
        users[user_name]->add_card(card);
    }
    void print(){}
    
};
UserManager* UserManager::usermanager=nullptr;

#endif