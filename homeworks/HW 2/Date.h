#ifndef DATE_H
#define DATE_H
#include <string>
class Date{

public:
	Date(){};
	Date(char day){
		this->day = day;
		//assign each day a value in order to sort them
		if(day == 'M'){this->v = 1;}
		else if(day == 'T'){this->v = 2;}
		else if(day == 'W'){this->v = 3;}
		else if(day == 'R'){this->v = 4;}
		else if(day == 'F'){this->v = 5;}
	};
	char getDate(){return day;}

	//for display purposes
	std::string convertDate(){
		std::string s;
		if(day == 'M'){s="Monday";}
		else if(day == 'T'){s= "Tuesday";}
		else if(day == 'W'){s= "Wednesday";}
		else if(day == 'R'){s= "Thursday";}
		else if(day == 'F'){s= "Friday";}
		return s;
	}

	int getDateValue(){return v;}	

private:
	char day;
	int v;
};

bool operator< (Date& a, Date& b){
	return a.getDateValue() < b.getDateValue();
}

bool operator == (Date& a, Date& b){
	return a.getDateValue() == b.getDateValue();
}

#endif