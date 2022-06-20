#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <list>
class Item{
public:
//initialize item object
	Item(int time, std::string dish_name){
		this->name = dish_name;
		this->cookingTime = time;
	};
	std::string getName() const {return name;}
	int getTime() {return cookingTime;}
	void setTime(int time){
		cookingTime = time;
	}
private:
	std::string name;
	int cookingTime;
};
//sort by time then name 
bool compareItem(Item& a, Item& b){
	if(a.getTime()	< b.getTime()){return true;}
	else if(a.getTime() == b.getTime() && a.getName() < b.getName()){return true;}
	return false;
}

#endif