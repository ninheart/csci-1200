#ifndef ORDER_H
#define ORDER_H
#include <string>
#include <list>

class Order{
public:
	Order(int id_,int minutes_,std::list <std::string> items_){
		this->id = id_;
		this->minutes = minutes_;
		this->items = items_;
	};
	int getID() const{return this->id;}
	int getTime() const{return this->minutes;}
	void setTime(int time){
		 minutes = time;
	}
	std::list<std::string> getItems() const{return this->items;}

private:
	std::list<std::string> items;
	int id;
	int minutes;
};
//sort orders by time then by id
bool sortOrders(Order& a, Order& b){
	if(a.getTime()<b.getTime()){return true;}
	else if(a.getTime()==b.getTime() && a.getID()<b.getID()){return true;}
	return false;
}

bool sortById(Order& a, Order& b){
	return(a.getID()<b.getID());
}

bool sortByTime(Order& a, Order& b){
	return(a.getTime()<b.getTime());
}

#endif