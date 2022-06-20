#ifndef CLASSINFO_H
#define CLASSINFO_H

#include <vector>
#include <string>
#include <algorithm>

#include "Date.h"
//classinfo class stores a class's information, which includes
//CRN, name, week days, and etc

class classInfo{
public:
		//default constructor
	classInfo(){};

	classInfo(std::string CRN,std::string deptCode, std::string courseCode, std::string courseTitle,
			char date,std::string startTime, std::string endTime, std::string room) {
				this->CRN = CRN;
				this->deptCode = deptCode;
				this->courseCode = courseCode;
				this->courseTitle = courseTitle;
				this->date = Date(date);
				this->room = room;
				this->startTime = startTime;
				this->endTime = endTime;
			}

	//getters
	std::string getCRN() const{return CRN;}
	
	std::string getDept() const{return deptCode;};

	std::string getCourse() const{return courseCode;}

	std::string getTitle() const{return courseTitle;}

	std::string getStartTime() const{return startTime;}

	std::string getEndTime() const{return endTime;}

	std::string getRoom() const{return room;}

	std::string getAmOrPm() const;

	Date getDate() const{return date;}

	//compare course code
	int courseCodeToNum(){
		this->courseCode.erase(4,1);
		int code = std::stoi(courseCode);
		return code;
	}

	//custom course code for organize course by level
	int customCourseCode(){
		this->courseCode.erase(4,3);
		int levelCode = std::stoi(courseCode);
		return levelCode;
	}

	void print();

private:
	std::string CRN, deptCode, courseCode, courseTitle, startTime, endTime, room;
	Date date;


};

void classInfo::print(){
	std::cout<<getCRN()<<' '<<getDept()<<' '<<getCourse()<<' '<<
	getTitle()<<' '<<getDate().convertDate()<<' '<<getStartTime()<<' '<<
	getEndTime()<<' '<<getRoom();
}

std::string classInfo::getAmOrPm() const{
	return startTime.substr(5,6);
}

bool isEarlierThan(classInfo a, classInfo b){
	
	int aHour = stoi(a.getStartTime().substr(0,2));
	int aMinute = stoi(a.getStartTime().substr(3,2));
	int aDayValue = a.getDate().getDateValue();
	int aCourseCode = a.courseCodeToNum();	
	std::string aZone = a.getAmOrPm();
	if(aZone == "PM" && aHour != 12){
		aHour = aHour + 12;
	}
	
	
	int bHour = stoi(b.getStartTime().substr(0,2));
	int bMinute = stoi(b.getStartTime().substr(3,2));
	int bDayValue = b.getDate().getDateValue();
	int bCourseCode = b.courseCodeToNum();

	std::string bZone = b.getAmOrPm();
	if(bZone == "PM" && bHour != 12){
		bHour += 12;
	}
	
	//compare two date objects
	if(aDayValue < bDayValue){return true;}
	else if(aDayValue == bDayValue && aHour < bHour){return true;}

	else if(aDayValue == bDayValue && aHour == bHour 
	&& aMinute < bMinute){return true;}
	else if(aDayValue == bDayValue && aHour == bHour 
	&& aMinute == bMinute && aCourseCode < bCourseCode){return true;}

 else if(aDayValue == bDayValue && aHour == bHour 
	&& aMinute == bMinute && aCourseCode == bCourseCode 
	&& a.getDept() < b.getDept()){return true;}
	return false;
	
}

bool sortForDept(classInfo a, classInfo b){
	//sort by course code;
	//sort by date, then starting day
	int aCode = a.courseCodeToNum();
	int aHour = stoi(a.getStartTime().substr(0,2));
	int aMinute = stoi(a.getStartTime().substr(3,2));
	int aDayValue = a.getDate().getDateValue();
	std::string aZone = a.getAmOrPm();
	if(aZone == "PM" && aHour != 12){
		aHour = aHour + 12;
	}

	int bCode = b.courseCodeToNum();
	int bHour = stoi(b.getStartTime().substr(0,2));
	int bMinute = stoi(b.getStartTime().substr(3,2));
	int bDayValue = b.getDate().getDateValue();
	std::string bZone = b.getAmOrPm();
	if(bZone == "PM" && bHour != 12){
		bHour += 12;
	}

	if(aCode < bCode){return true;}
	else if(aCode == bCode && aDayValue<bDayValue){return true;}
	else if(aCode == bCode && aDayValue==bDayValue &&aHour > bHour) return true;
	else if(aCode == bCode && aDayValue==bDayValue &&aHour == bHour && aMinute > bMinute){return true;} 
	return false;

}



#endif 