#ifndef BOARD_H
#define BOARD_H
#include<iostream>
#include<ostream>
class Board{
public:
	Board(std::string one,std::string two,std::string background);
	//destructor
	~Board(); 
	//copy constructor
	Board(const Board& otherBoard);
	void operator=(const Board& otherBoard);
	//void operator<<(const Board& otherBoard);
	//memeber functions 
	int numRows() const;
	int numColumns() const;

	int numTokensInRow(int rowNumber);
	int numTokensInColumn(int colNumber);
	//copy data from old array to new array
	void copyData(std::string* data, int col);
	//expand the column
	void rightExpansion();
	//expand top
	void topExpansion(int col,std::string player);
	//fill in an array with data
	void copyAndFill(std::string* holder,int col,std::string player);
	//check if there's a connectFour 
	bool connectFour(std::string player);
	//insert function 
	std::string insert(int col, bool player);

	friend std::ostream& operator<<(std::ostream& os, Board& b);
	void clear();
private:
	std::string** m_data;
    int rows;
	int columns;  
	std::string playerOne;
	std::string playerTwo;
	std::string blankSpace;
};
//std::ostream& operator<<(std::ostream& os, Board& b);

#endif