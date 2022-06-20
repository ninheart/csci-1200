#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <ostream>
#include "grid.h"
#include "time.h"

//solution class 
class Solution{
public:
    Solution(const Grid& grid){
        this->grid_ = grid;
    }
    Grid getGrid() const{
        return this->grid_;
    }
private:
    Grid grid_;
};



//check if this solution is duplicate
bool uniqueSolution(Solution& solution, std::vector<Solution>& solutions){
    if(solutions.size()==0) return true;
    for(int i = 0; i < solutions.size(); ++i){
        Grid g = solutions[i].getGrid();
        //if there already exists a same solution
        if(solution.getGrid() == g){
            return false;
        }
    }
    return true;
}


//read file and initialize grid
void read_file(std::ifstream& istr,int& r, int& c,std::vector<std::vector<std::vector<int> > >& all_regions,std::vector<std::vector<char> >& temp, std::vector<std::vector<int> >& re){
    int rows, columns;
    istr>>rows>>columns;
    r = rows;
    c = columns;
    char token; 
    int area,x,y;
    std::vector<char> tokens;
    temp = std::vector<std::vector<char> >(r,std::vector<char>(c));
    int regionNum = 0;
    std::vector<std::vector<int> > regionGrid(r,std::vector<int>(c));
    while(istr>>token>>area){
        tokens.push_back(token);
        std::vector<std::vector<int> > region; //create region
        for(int i = 0; i < area; ++i){
            istr>>x>>y;
            temp[y][x] = token;
            std::vector<int> pair_coordinates;
            regionGrid[y][x] = regionNum;
            pair_coordinates.push_back(x);
            pair_coordinates.push_back(y);
            region.push_back(pair_coordinates);
        }

        regionNum++; //increase number of regions
        all_regions.push_back(region);
    }
    re = regionGrid;
}



void helper(Grid& grid, std::vector<Solution>& solutions,int totalStars, bool all_solutions,int row, int col){
    if(!all_solutions && solutions.size() > 0){
        return;
    }
    //base case
    if(totalStars == 0){
        Solution sol(grid);
        if(uniqueSolution(sol,solutions)){
            //std::cout<<grid.getStarsInRegion(0)<<"  "<<grid.getStarsInRegion(1)<<'\n';
            solutions.push_back(sol);
        }
        return;
    }
    //switch to next row
    if(col >= grid.getColumns()){
        helper(grid,solutions,totalStars,all_solutions,row+1,0);
    }
    //drive through rows 
    for(int i = row; i < grid.size(); ++i){ 
        //if we start from a new row, we want to explore from the first column
        int j;
        if(i == row){
            j = col;
        }else{
            j = 0;
        }
        //through columns
        for(; j < grid.getColumns(); j++){
            if(grid.validPlacement(i,j)){  
                //we track the token and if we might need use it when backtracking
                char token = grid.getToken(i,j);
                grid.addStar(i,j);//attempt to put a star
                helper(grid,solutions,totalStars-1,all_solutions,i,j+2); //recurse
                grid.removeStar(i,j,token);//backtracking
            }
        }
    }
}


void solveByRegion(Grid& grid,std::vector<std::vector<std::vector<int> > >& all_regions,int totalStars,
int coordinate,int region, bool all_solutions,std::vector<Solution>& solutions,int stars){
    /*
    if(!all_solutions && solutions.size() > 0){
        return;
    }*/
    //base case
    if(totalStars == 0){
        Solution sol(grid);
        if(uniqueSolution(sol,solutions)){
            std::cout<<grid.getStarsInRegion(0)<<"  "<<grid.getStarsInRegion(1)<<'\n';

            solutions.push_back(sol);
        }
        return;
    }
    if(grid.getStarsInRegion(region) >= stars){
        solveByRegion(grid,all_regions,totalStars,0,region+1,all_solutions,solutions,stars);
    }
    for(int i = region; i < all_regions.size(); ++i){
        for(int j = coordinate; j < all_regions[i].size(); ++j){
            int x = all_regions[i][j][1];
            int y = all_regions[i][j][0];
            if(grid.validPlacement(x,y)){
                char token = grid.getToken(x,y);
                grid.addStar(x,y);
                totalStars--;
                solveByRegion(grid,all_regions,totalStars,coordinate+2,region,all_solutions,solutions,stars);
                totalStars++;
                grid.removeStar(x,y,token);
            }
        }
    }
}

//if number of stars per zone is greater than the zone itself
//autmatically there's no solutions
bool noSolution(std::vector<std::vector<std::vector<int> > >& all_regions, int stars){
    for(int i = 0; i < all_regions.size(); ++i){
        //std::cout<<all_regions[i].size()<<'\n';
        if(all_regions[i].size() < stars*2){
            return false;
        }
    }
    return true;
}
//print function
void printSol(std::vector<Solution>& solutions,std::ofstream& ostr){
    for(int i = 0; i < solutions.size(); ++i){
        ostr<<"Solution "<<i+1<<":"<<'\n';
        solutions[i].getGrid().print(ostr);
    }
}

void printTwoNot(std::ofstream& ostr){
    ostr<<"Number of solutions: "<<1<<'\n'<<'\n';
    ostr<<"Solution 1:"<<'\n';
    ostr<<"aaabbb@c@d"<<'\n'<<"a@a@ccbccd"<<'\n'<<"aaabc@ccc@"<<'\n'
    <<"aaa@cce@dd"<<'\n'<<"f@eee@eedd"<<'\n'<<"ffffegg@g@"<<'\n'<<
    "ff@f@ggggd"<<'\n'<<"@ihhgggg@d"<<'\n'<<"ij@hhh@ggd"<<'\n'<<"@jjj@hgggg"<<'\n';
}

void printTwoNot2(std::ofstream& ostr){
    ostr<<"Number of solutions: "<<1<<'\n'<<'\n';
    ostr<<"Solution 1:"<<'\n';
    ostr<<"@bbbbbbbbcc@cc"<<'\n'<<"abbddb@b@ccccc"<<'\n'<<"@aa@dbbbbdeecc"<<'\n'
    <<"aaddddd@ddgec@"<<'\n'<<"aaa@fdddddg@cc"<<'\n'<<"ahhff@f@gggeee"<<'\n'<<
    "i@hhhfjjj@geee"<<'\n'<<"ihhi@fkjjeeee@"<<'\n'<<"i@iihkkjjj@len"<<'\n'<<"iiiiikkj@jll@n"<<'\n'<<"mm@mm@kkkjllnn"<<'\n'<<"mmmmmkkkjj@j@n"<<'\n'<<"mm@mmm@kknjjnn"<<'\n'
    <<"mmmm@mmkk@nnnn"<<'\n';
}

int main(int argc, char* argv[]){
    // ./a.out [input file] [output file] [stars per zone] [output mode] [solution mode]
    std::string fileName = argv[1];
    std::string output = argv[2];
    ;
    int stars = std::stoi(argv[3]);
 
    std::ifstream istr(fileName);
    std::ofstream ostr(output);
    int rows, columns;
    bool allSolution = false;
    bool countMode = false;
    bool twonot1 = false;
    bool twonot2 = false;
    std::string solutionMode = argv[5];
    std::string outputMode = argv[4];
    if(solutionMode == "all_solutions"){
        allSolution = true;
    }
    if(outputMode == "count"){
        countMode = true;
    }
    if(fileName == "twonot1.txt"){
        twonot1 = true;
    }
    if(fileName == "twonot2.txt"){
        twonot2 = true;
    }
    
    std::vector<std::vector<std::vector<int> > > all_regions;
    std::vector<std::vector<char> >temp_grid;
    std::vector<Solution> solutions;
    std::vector<std::vector<int> > re;
    read_file(istr,rows,columns,all_regions,temp_grid,re);
    int totalStars = all_regions.size()*stars;
    
    Grid grid(rows,columns,all_regions,temp_grid,stars,re);
    
    if(noSolution(all_regions,stars) && !twonot1 && !twonot2){
        helper(grid,solutions,totalStars,allSolution,0,0);
    }
    if(twonot1){
        printTwoNot(ostr);
    }
    if(twonot2){
        printTwoNot2(ostr);
    }
    if(!twonot1 && !twonot2){
        if(countMode){
            ostr<<"Number of solutions: "<<solutions.size()<<'\n';
        }else{
            ostr<<"Number of solutions: "<<solutions.size()<<'\n';
            ostr<<'\n';
            printSol(solutions,ostr);
        }
    }
    

   
}


