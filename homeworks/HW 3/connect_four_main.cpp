#include <iostream>
#include <string>
#include <cassert>
#include "Board.h"

void SimpleTest(); //Some basic tests
void StudentTest(); //Write your own test cases here

int main(){
	SimpleTest();
	std::cout << "Completed all simple tests." << std::endl;

	StudentTest();
	std::cout << "Completed all student tests." << std::endl;

	return 0;
}

// Do not modify this function - a fresh copy will be used on Submitty
void SimpleTest(){
	Board b("R","Y","." );

	std::cout << "Initial board:" << std::endl << b << std::endl;
	
	std::cout << "Row 0 has " << b.numTokensInRow(0) << std::endl;
	std::cout << "Row 4 has " << b.numTokensInRow(4) << std::endl;
	std::cout << "Row 5 has " << b.numTokensInRow(5) << std::endl;
	std::cout << "Column 0 has " << b.numTokensInColumn(0) << std::endl;
	std::cout << "Column 3 has " << b.numTokensInColumn(3) << std::endl;
	std::cout << "Column 4 has " << b.numTokensInColumn(4) << std::endl;
	
	b.insert(0,true);
	std::cout << "Second handout figure" << std::endl << b << std::endl;
	
	b.insert(1,false);

	b.insert(2,true);
	b.insert(3,true);
	std::cout << "Third handout figure" << std::endl << b;
	
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;
	
	b.insert(1,true);

	b.insert(1,false);
	b.insert(1,true);
	
	
	b.insert(1,false);
	
	
	b.insert(1,true);
	
	std::cout << "Fourth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;
	
	b.insert(4,true);

	std::cout << "Fifth handout figure" << std::endl << b;
	std::cout << "Dimensions are " << b.numRows() << " X " << b.numColumns()
			  << std::endl << std::endl;
	
	
	//Looks ugly if we don't make all tokens the same length, but not required
	Board b2("Puppy","Kitty","-----"); 
	
	std::string result;
	std::cout << "Starting a new board!" << std::endl;
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	
	
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	result = b2.insert(1,true);
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	
	result = b2.insert(1,true);
	
	std::cout << "Board is now" << std::endl << b2 << std::endl;
	if(result == "-----"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	
	
}

////////STUDENT CODE//////

//Write your own test cases here
void StudentTest(){

	std::cout<<"starting student tests"<<'\n';
	//test column winner
	Board b("chick","eyees","-_-_-");
	std::string result;
	result = b.insert(0,false);
	result = b.insert(1,false);
	result = b.insert(2,false);
	result = b.insert(3,false);
	std::cout<<b;
	if(result == "-_-_-"){
		std::cout << "No winner yet." << std::endl;
	}
	else{
		std::cout << "The winner is: " << result << std::endl;
	}
	//test copy constructor
	std::cout<<"testing copy constructor" << std::endl;
	Board a("White","Black","_____");
	a.insert(0,true);
	a.insert(0,false);
	a.insert(2,true);
	a.insert(6,true);
	a.insert(6,true);
	a.insert(10,false);
	std::cout<<a<<'\n';
	std::cout<<"make a copy"<<'\n';
	Board copy(a);
	std::cout<<copy;
	std::cout<<"insert to orginal, the copy shouldn't change"<<'\n';
	a.insert(3,true);
	std::cout<<"The orginal: "<<'\n';
	std::cout<<a<<'\n';
	std::cout<<"The copy: "<<'\n';
	std::cout<<copy<<'\n';
	assert(a.numTokensInColumn(3) == 1);
	assert(copy.numTokensInColumn(3) == 0);
	std::cout<<"another board"<<'\n';
	Board c("one","two","---");
	std::cout<<c<<'\n';
	std::cout<<"Testing assignment operator"<<'\n';
	copy = c;
	std::cout<<copy<<'\n';
	
}

