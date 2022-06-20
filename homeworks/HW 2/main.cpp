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
#include "utilities.h"

//below five functions determines the longest string when outputing the format


int main(int argc, char* argv[]){
	//input file, outputfile, room/dept
	if(argc < 4){
		std::cerr<<"not enough arguments"<<std::endl;
	}

	std::string inFile = argv[1];
	std::string outFile = argv[2];
	std::string option = argv[3];
	std::ifstream istr(inFile);
	std::ofstream ostr(outFile);
 std::string line;
	std::vector<classInfo> courses;

	while(getline(istr,line)){
		//crn, dept code, course code, course title, days, time, room
		std::istringstream iss(line);
		std::string token;
		std::vector<std::string> tokens;
		//sperate by white space
		while(getline(iss,token,' ')){
			tokens.push_back(token);
		}
		//separate days
		std::string days = tokens[4];
		for(uint i = 0; i < days.size(); ++i){
			classInfo c = classInfo(tokens[0],tokens[1],tokens[2],tokens[3],
			days[i],tokens[5],tokens[6],tokens[7]);
			courses.push_back(c);
		}
	}
	//alphabetically by room name
	//sorted by day of the week
	//sorted by start time
	//sorted by course code
	//sorted by dept name
	if(option == "room"){
		std::string specificRoom;
		if(argv[4]){
			specificRoom = argv[4];
		}else{
			specificRoom = "";
		}
		organizeCoursesByRoom(courses,specificRoom,ostr);
	}else if(option == "dept"){
		//fourth arugment is mandatory
		std::string specificDept;
		if(!argv[4]){
			std::cerr<<"please specify a department"<<std::endl;
		}
		specificDept = argv[4];
		organizeCoursesByDept(courses,specificDept,ostr);
	}else if(option == "custom"){
		//sort classes by weekdays
		customSchedule(courses,ostr);
	}else{
		std::cerr<<"invalid arugment";
	}
	
}