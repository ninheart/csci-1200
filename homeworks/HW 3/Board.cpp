#include<iostream>
#include<vector>
#include "Board.h"

//constructor
Board::Board(std::string tokenOne,std::string tokenTwo,std::string background){
	//at least 5x4 grid
	this-> rows = 5;
	this-> columns = 4;
	this->playerOne = tokenOne;
	this->playerTwo = tokenTwo;
	this->blankSpace = background;
	//create m_data
	this->m_data = new std::string*[columns];
	//initialize background
	for(int i = 0; i < columns; ++i){
		//create rows array
		m_data[i] = new std::string[rows];
		for(int j = 0; j < rows; ++j){
			//set to background character
			m_data[i][j] = background;
		}
	}
}

//copy constructor
Board::Board(const Board& otherBoard){
	rows = otherBoard.rows;
	columns = otherBoard.columns;
	m_data = new std::string*[this->columns];
	playerOne = otherBoard.playerOne;
	playerTwo = otherBoard.playerTwo; 
	blankSpace = otherBoard.blankSpace;
	for(int i = 0; i < columns; i++){
		
		m_data[i] = new std::string[rows];
		for(int j = 0; j < rows; j++){
			m_data[i][j] = otherBoard.m_data[i][j];
		}
		
	}
}

void Board::operator=(const Board& otherBoard){
	if(this == &otherBoard) return;
	
	for(int i = 0; i < columns; i++){
		delete[] m_data[i];
	}
	delete[] m_data;
	
	rows = otherBoard.rows;
	columns = otherBoard.columns;
	playerOne = otherBoard.playerOne;
	playerTwo = otherBoard.playerTwo;
	blankSpace = otherBoard.blankSpace;

	m_data = new std::string*[columns];
	for(int i = 0; i < columns; i++){

		m_data[i] = new std::string[rows];
		for(int j = 0; j < rows; j++){
			m_data[i][j] = otherBoard.m_data[i][j];
		}
	}
}

void Board::clear(){
	for(int i = 0; i < columns; i++){
		if(numTokensInColumn(i)>0){
			delete [] m_data[i];
		}
	}
}

Board::~Board(){
	for(int i = 0; i < columns; ++i){
		delete[] m_data[i];
	}
	delete[] m_data;
}

int Board::numRows() const{
	return this->rows;
}

int Board::numColumns() const{
	return this->columns;
}

int Board::numTokensInRow(int rowNumber) {
	//access row
	int count = 0;
	if(rowNumber > this->rows-1) return -1;
	for(int i = 0; i<this->columns; i++){
		if(m_data[i][rowNumber] == playerOne || m_data[i][rowNumber] == playerTwo){
			count++;
		}
	}
	return count;
}

int Board::numTokensInColumn(int colNumber){
	int count = 0;
	if(colNumber > this->columns-1) return -1;
	for(int i = 0; i < this->rows; ++i){
		if(m_data[colNumber][i] == playerOne || m_data[colNumber][i] == playerTwo){
			count++;
		}
	}
	return count;
}

//copy old column to new column
void Board::copyData(std::string* data, int col){
	//copy orginal column
	for(int i = 0; i < rows; ++i){
		//copy each column's data
		data[i] = m_data[col][i];
	}
}

void Board::rightExpansion(){
	//increase columns size by one
	this->columns++;
	//resize new m_data array
	//create a new m_data array
	std::string** newData = new std::string*[this->columns];
	//copy old data from m_data
	for(int i = 0; i < columns-1; ++i){
		newData[i] = m_data[i];
	}
	
	//set pointers to null so we can connect a new row array
	newData[columns-1] = nullptr;
	//create a new row array that has the size of rows. 
	std::string* temp = new std::string[rows];
	//fill in background character 
	for(int i = 0; i < rows; i++){
		temp[i] = blankSpace;
	}                                          
	//connect null to new row array
	newData[columns-1] = temp;
	//delete previous m_data array
	delete [] this->m_data;
	//reallocate. 
	this->m_data = newData;
}


//this function increase each columns' height if 
//the column is filled with strings. 
void Board::topExpansion(int col, std::string player){
	//a temp integer
	int currentHeight = rows+1;
	//go through m_data 
	for(int i = 0; i < columns; ++i){
		//create a new column that has the height 
		//of the new height. 
		std::string* newHeight = new std::string[currentHeight];
		//perform copy for old data
		for(int j = 0; j < rows; ++j){
			newHeight[j] = m_data[i][j];
		}
		//delete old data array
		delete[] m_data[i];
		//connect pointer to new data array
		m_data[i] = newHeight;
	}
	//increase row by one
	rows++;
	//fill the new row with characters
	for(int i = 0; i < columns; ++i){
		//check the column, if it matches insert(col),
		//then fill that position with player's token. 
		if(i == col){
			m_data[i][currentHeight-1] = player;
		}else{
			//fil 
			m_data[i][currentHeight-1] = blankSpace;
		}
	}
}
//the function check  connectFour
//first it goes through horizontally(columns), check if there's a connectFour for each index
//then it goes through vertically(rows), check if there's a connectFour. 
//when there's no connectFour for columns and rows, return false, otherwise return true. 
bool Board::connectFour(std::string player){
	//check the row
	for(int i = 0; i < columns; ++i){
		//set a flag to exit the loop
		bool flag = true;
		//go through the rows 
		for(int j = 0; j< rows; ++j){
			//if there's a single match
			if(m_data[i][j] == player){		
				//the goal is to count four times
				int count = 0;
				//expand four times to check a connectFour 
				for(int k = 0; k < 4; ++k){
					//if it's in the row boundary
					if(j+k < rows){
						if(m_data[i][j+k]==player){count++;}
					}else{
						//if it's out of the bound, skip the index. 
						flag = false;
						break;
					}
					
				}
				//break the loop
				if(!flag) break;
				//if counts four tiems 
				if(count == 4) {
					return true;
				}else{
					//reset count
					count = 0;
				}				
			}
		}
	}
	//after checking horizontally, 
	//check in each column see if there's a connectFour
	for(int i = 0; i < rows; ++i){
		bool f = true;
		for(int j = 0; j < columns; ++j){
			if(m_data[j][i] == player){
				int count = 0;
				for(int k = 0; k < 4; ++k){
					if(j+k < columns){
						if(m_data[j+k][i] == player){count++;}
					}else{
						//break 
						f=false;
						break;
					}
				}
				//break
				if(!f) break;	
				//connect four!	
				if(count == 4){
					return true;
				}else{
					count = 0;
				}
			}
		}
	}
	//if there's no connectFour return false
	return false;
}

//this function fill in a new array that replaces the old array. 
//it copies old data to the new array and delete the old array. 
void Board::copyAndFill(std::string* holder, int col,std::string player){
	//the bottom tracks the stack in each column, which is equal to 
	//numTokensInColumn(col).
	int bottom = numTokensInColumn(col);
	//call copyData to perform copy operation. 
	copyData(holder,col);
	holder[bottom] = player;
	delete[] m_data[col];
	m_data[col] = holder;
}

std::string Board::insert(int col, bool player){
	//true = player 1, false = player 2
	if(player){
		//player one inserting
		//find the column 
		//create new array
		if(col >= this->columns){ //the column is full
			//expand to the right
			//find difference between new col num and current column
			int diff = col - columns;
			//in case it's skipping columns, go in a for loop
			//we could right expansion multiple times like in the gap test
			for(int i = 0; i <= diff; i++){
				rightExpansion();	
			}
			// create a temp array. 
			std::string* holder = new std::string[rows];
			// fill the array. 
			copyAndFill(holder,col,playerOne);

		}else if(m_data[col][rows-1] != blankSpace){
			//we only have to expand row number. 
			//call topExpansion. 
			topExpansion(col,playerOne);
		}else{//we don't have to do any expansion,
			//we just have to insert the token		
			std::string* holder = new std::string[rows];
			//find the filling 
			copyAndFill(holder,col,playerOne);
		}
		//check if there's a connect four
		if(connectFour(playerOne)){
			//if there is, return the token. 
			return playerOne;
		}
		
	}else{
		//player two inserting
		if(col >= this->columns){ //the column is full
			int diff = col - columns;
			//in case it's skipping columns, go in a for loop
			for(int i = 0; i < diff+1; i++){
				rightExpansion();	
			}
			std::string* holder = new std::string[rows];
			copyAndFill(holder,col,playerTwo);

		}else if(m_data[col][rows-1] != blankSpace){
			topExpansion(col,playerTwo);
		}else{
			std::string* holder = new std::string[rows];
			copyAndFill(holder,col,playerTwo);
		}
		if(connectFour(playerTwo)){
			return playerTwo;
		}
	}
	//check connect four 
	//
	return blankSpace;
}
//aka print function
std::ostream& operator<<(std::ostream& os, Board& b){
	for(int i = b.numRows()-1; i>=0; --i){
		for(int j = 0; j<b.numColumns(); ++j){
			if(j == b.numColumns()-1){
				//if it's the last in the line, don't create a blank space
				os<<b.m_data[j][i];
			}else{
				os<<b.m_data[j][i]<<' ';
			}
		}os<<'\n';
	}
	
	return os;
};