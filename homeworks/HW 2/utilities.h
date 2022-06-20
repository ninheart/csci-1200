#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <iostream>
#include <string>
#include <algorithm> 
#include <iomanip>
#include <ostream>
#include <sstream>
#include <fstream>
#include <set>
#include "classInfo.h"
#include "Date.h"

//5 functions return the longest string for display purposes
int longestCourseName(std::vector<classInfo>& courses){
	//minimum length;
	int result = 11;
	for(uint i= 0; i < courses.size(); i++){
		if(courses[i].getTitle().size() > result){result = (int)courses[i].getTitle().size();}
	}
	return result;
}

int longestCRN(std::vector<classInfo>& courses){
	int result = 3;
	for(uint i= 0; i < courses.size(); i++){
		if(courses[i].getCRN().size() > result){result = (int)courses[i].getCRN().size();}
	}
	return result;
}

int longestCourseCode(std::vector<classInfo>& courses){
	int result = 9;
	for(uint i= 0; i < courses.size(); i++){
		if(courses[i].getCourse().size() > result){result = (int)courses[i].getCourse().size();}
	}
	return result;
}

int longestDept(std::vector<classInfo>& courses){
	int result = 4;
	for(uint i= 0; i < courses.size(); i++){
		if(courses[i].getDept().size() > result){result = (int)courses[i].getDept().size();}
	}
	return result;
}

int longestDayLength(std::vector<classInfo>& courses){
	int result = 0;
	for(uint i= 0; i < courses.size(); i++){
		if(courses[i].getDate().convertDate().size()> result){result = (int)courses[i].getDate().convertDate().size();}
	}
	return result;
}
//print function
void printByRoom(std::vector<classInfo>& classByRoom,int courseLength, int codeLength, int dayLength, int deptLength, std::ofstream& ostr){
	ostr<<std::left;
	ostr<<std::setw(deptLength)<<"Dept"<<"  "<<std::setw(codeLength)<<"Coursenum"<<"  "
	<<std::setw(courseLength)<<"Class Title"<<"  "<<std::setw(dayLength)
	<<"Day"<<"  "<<"Start Time"<<"  "<<"End Time"<<'\n';

	ostr<<std::string(deptLength,'-')<<"  "<<std::string(9,'-')<<"  "
	<<std::string(courseLength,'-')<<"  "<<std::string(dayLength,'-')<<"  "
	<<std::string(10,'-')<<"  "<<std::string(8,'-')<<'\n';
	
	for(uint i = 0; i < classByRoom.size(); ++i){	
		ostr<<std::setw(deptLength)<<classByRoom[i].getDept()<<"  "
		<<std::setw(9)<<classByRoom[i].getCourse()<<"  "
		<<std::setw(courseLength)<<classByRoom[i].getTitle()<<"  "
		<<std::setw(dayLength)<<classByRoom[i].getDate().convertDate()<<"  "
		<< std::setw(10)<<classByRoom[i].getStartTime()<<"  "
		<< std::setw(8)<<classByRoom[i].getEndTime()<<'\n';
		
	}
	ostr<<classByRoom.size()<<' '<<"entries"<<'\n';
	ostr<<'\n';
}
//for department option
void printByDept(std::vector<classInfo>& collection, int codeLength, int nameLength, int
dayLength, std::ofstream& ostr){
	
	ostr<<std::left;
	ostr<<std::setw(codeLength)<<"Coursenum"<<"  "
	<<std::setw(nameLength)<<"Class Title"<<"  "<<
	std::setw(dayLength)<<"Day"<<"  "<<"Start Time"
	<<"  "<<"End Time"<<'\n';

	ostr<<std::string(9,'-')<<"  "
	<<std::string(nameLength,'-')<<"  "<<std::string(dayLength,'-')<<"  "
	<<std::string(10,'-')<<"  "<<std::string(8,'-')<<'\n';

	for(uint i = 0; i < collection.size(); ++i){
		ostr<<std::setw(9)<<collection[i].getCourse()<<"  "<<
		std::setw(nameLength)<<collection[i].getTitle()<<"  "<<
		std::setw(dayLength)<<collection[i].getDate().convertDate()<<"  "<<
		std::setw(10)<<collection[i].getStartTime()<<"  "
		<< std::setw(8)<<collection[i].getEndTime()<<'\n';
	}
	ostr<<collection.size()<<' '<<"entries"<<'\n';
	ostr<<'\n';
}

void printCustomOutput(std::vector<std::vector<classInfo> >& weekdays,std::ofstream& ostr){
	ostr<<std::left;
	for(int i = 0; i < weekdays.size(); i++){
		if(i==0)ostr<<"Monday"<<'\n';
		else if(i==1)ostr<<"Tuesday"<<'\n';
		else if(i==2)ostr<<"Wednesday"<<'\n';
		else if(i==3)ostr<<"Thursday"<<'\n';
		else if(i==4)ostr<<"Friday"<<'\n';
		if(weekdays[i].size()==0){
			ostr<<"No class for today"<<std::endl;
			ostr<<'\n';
			continue;
		}
		for(int j = 0; j<weekdays[i].size(); ++j){
			classInfo c = weekdays[i][j];
			ostr<<c.getTitle()<<"  "<<c.getStartTime()<<" "<<c.getEndTime()<<'\n';
		}ostr<<'\n';
	}
}

void organizeCoursesByRoom(std::vector<classInfo>& courses, std::string room,std::ofstream& ostr){
	std::vector<classInfo> sorted;
	if(courses.size()==0){
		ostr<<"No data available."<<'\n';
	}else{
		if(room != ""){
			//gather data and push into a organzied array
			for(uint i = 0; i < courses.size(); ++i){
				if(courses[i].getRoom()==room){
					sorted.push_back(courses[i]);
				}
			}	
			if(sorted.size() == 0){
				ostr<<"No data available."<<'\n'; 
				
			}else{
				//sort the array by requirement
				std::sort(sorted.begin(), sorted.end(),isEarlierThan);
				//get the longest strings 
				int course_length = longestCourseName(sorted);
				int code_length = longestCourseCode(sorted);
				int day_length = longestDayLength(sorted);
				int dept_length = longestDept(sorted);
				ostr<<"Room"<<' '<<room<<'\n';
				//print them
				printByRoom(sorted,course_length,code_length,day_length,dept_length,ostr);
			}
		}else{
			//create a set so there's no duplicates
			std::set<std::string> rooms;
			for(uint i = 0; i < courses.size(); ++i){
				rooms.insert(courses[i].getRoom());
			}
			//set iterator
			std::set<std::string>::iterator itr = rooms.begin();
			//loop until itr ends
			for(;itr!=rooms.end();++itr){
				//each time we create a vector of objects
				std::vector<classInfo> classByRoom;
				for(uint i = 0; i < courses.size(); ++i){
					//if the room matches
					if(courses[i].getRoom() == *itr){
						classByRoom.push_back(courses[i]);
					}
				}
				//sort it
				std::sort(classByRoom.begin(), classByRoom.end(), isEarlierThan);
				
				if(classByRoom.size() > 0){ 	//if this room is valid
					ostr<<"Room"<<' '<<*itr<<'\n';
					int courseLength = longestCourseName(classByRoom);
					int codeLength = longestCourseCode(classByRoom);
					int dayLength = longestDayLength(classByRoom);
					int deptLength = longestDept(classByRoom);
					printByRoom(classByRoom,courseLength,codeLength,dayLength,deptLength, ostr);
				}else{
					ostr<<"No data available."<<'\n';
				}
			}
		}
	}
}

void organizeCoursesByDept(std::vector<classInfo>& courses, std::string dept,std::ofstream& ostr){
	std::vector<classInfo> collection;
	//find  the matching department 
	for(uint i=0;i<courses.size(); ++i){
		if(courses[i].getDept()==dept){
			collection.push_back(courses[i]);
		}
	}
	//sort by course code, days and time
	std::sort(collection.begin(), collection.end(),sortForDept);
	int courseNumLength = longestCourseCode(collection);
	int courseNamelength = longestCourseName(collection);
	int dayLength = longestDayLength(collection);
	if(collection.size()==0){
		ostr<<"No data available."<<'\n';
	}else{
		ostr<<"Dept"<<' '<<dept<<'\n';
		printByDept(collection,courseNumLength,courseNamelength,dayLength,ostr);
	}
	
}

void customSchedule(std::vector<classInfo>& courses,std::ofstream& ostr){
	std::vector<classInfo> selected = courses;
	
	//sort by week days
	std::vector<std::vector<classInfo> > weekdays(5);
	
	for(int j = 0; j < selected.size(); ++j){
		if(selected[j].getDate().convertDate() == "Monday"){
			weekdays[0].push_back(selected[j]);
		}else if(selected[j].getDate().convertDate() == "Tuesday"){
			weekdays[1].push_back(selected[j]);
		}else if(selected[j].getDate().convertDate() == "Wednesday"){
			weekdays[2].push_back(selected[j]);
		}else if(selected[j].getDate().convertDate() == "Thursday"){
			weekdays[3].push_back(selected[j]);
		}else if(selected[j].getDate().convertDate() == "Friday"){
			weekdays[4].push_back(selected[j]);
		}
	}
	
	for(int i = 0; i < weekdays.size(); ++i){
		std::sort(weekdays[i].begin(), weekdays[i].end(),isEarlierThan);
	}
	printCustomOutput(weekdays,ostr);
	

}

#endif