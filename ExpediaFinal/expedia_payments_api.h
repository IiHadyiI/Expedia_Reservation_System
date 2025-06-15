/*
 * expedia_payments_api.h
 *
 *  Created on: Sep 18, 2020
 *      Author: moustafa
 */
using namespace :: std;
#ifndef EXPEDIA_PAYMENTS_API_H_
#define EXPEDIA_PAYMENTS_API_H_



using namespace std;

#include "json.hpp"
using namespace json;


class PayPalCreditCard {
public:
	string name;
	string address;
	string id;
	string expiry_date;
	int ccv;
};

class PayPalOnlinePaymentAPI {
public:
	void SetCardInfo(const PayPalCreditCard* const card) {
	}
	bool MakePayment(double money) {
		return true;
	}
};

class StripeUserInfo {
public:
	string name;
	string address;
};

class StripeCardInfo {
public:
	string id;
	string expiry_date;
};

class StripePaymentAPI {
public:
	bool static WithDrawMoney(StripeUserInfo user, StripeCardInfo card, double money) {
		return true;
	}
};

class SquarePaymentAPI {
public:
	bool static WithDrawMoney(string JsonQuery) {
		//cout << JsonQuery << "\n";
		json::JSON obj = JSON::Load(JsonQuery);
		return true;
	}
};
//////////////////////////////////
class Card{
private:
	string card_name;
	string name;
	string address;
	string id;
	string expiry_date;
	int ccv;
public:
	void set_name(string _name){
		name=_name;
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

class IPaymentManager{
protected:
	Card card;
public:
	void set_card_data(string name,string address,string expiry_date,string id,int ccv){
		card.set_name(name);
		card.set_address(address);
		card.set_expiry_date(expiry_date);
		card.set_id(id);
		card.set_ccv(ccv);
	}
	virtual bool withdrawMoney(double ammount)=0;
};

class PaypalPayment : public IPaymentManager{
private:
	PayPalOnlinePaymentAPI PaypalApi;
	PayPalCreditCard PaypalCard;
public:
	bool withdrawMoney(double ammount) override{
		PaypalCard.name=card.get_name();
		PaypalCard.address=card.get_adrees();
		PaypalCard.ccv=card.get_ccv_date();
		PaypalCard.expiry_date=card.get_expiry_date();
		PaypalCard.id=card.get_id();
		PaypalApi.SetCardInfo(&PaypalCard);
		return PaypalApi.MakePayment(ammount);
	}
};

class StripePayment : public IPaymentManager{
private:
	StripeCardInfo StripeCard;
	StripeUserInfo StripeUser;
public:
	bool withdrawMoney(double ammount) override{
		StripeCard.expiry_date=card.get_expiry_date();
		StripeCard.id=card.get_id();
		StripeUser.address=card.get_adrees();
		StripeUser.name=card.get_name();
		return StripePaymentAPI::WithDrawMoney(StripeUser,StripeCard,ammount);
	}
};
IPaymentManager*payment_factory(string company){
	if(company=="paypal")
		return new PaypalPayment();
	else
		return new StripePayment();
}
#endif /* EXPEDIA_PAYMENTS_API_H_ */
