#ifndef GRID_H
#define GRID_H


class Grid{
public:
    Grid(){}
    //grid initalization
    Grid(int x, int y,std::vector<std::vector<std::vector<int> > >& all_regions,std::vector<std::vector<char> >& grid, int& stars,std::vector<std::vector<int> >& re){
        this->numberRegions = all_regions.size();
        this->regions = all_regions;
        this->starsPerZone = stars;
        this->rows = x;
        this->columns = y;
        this->grid_ = grid;
        this->regionGrid = re;
        std::vector<int> temp(all_regions.size(),0);
        this->starInRegion = temp;
    }
    //copy constructor

    //equal operator 
    Grid& operator=(const Grid& other){
        rows = other.rows;
        columns = other.columns;
        numberRegions = other.numberRegions;
        starsPerZone = other.starsPerZone;
        regions = other.regions;
        grid_ = other.grid_;
        return* this;
    }

    bool validPlacement(int row, int col);

    int getRegion(int row, int col){
        return regionGrid[row][col];
    }
    int getStarsInRegion(int region){
        return starInRegion[region];
    }

    int size() const{
        return grid_.size();
    }
    int getColumns() const{
        return this->columns;
    }
    int getRows() const{
        return this->rows;
    }
    int getStarsInRow(int row){
        int count = 0;
        for(int i = 0; i < columns; i++){
            if(grid_[row][i] == '@') count++;
        }
        return count;
    }
    
    char getToken(int row, int col) const{
        return grid_[row][col];
    }

    void addStar(int row, int col);


    void removeStar(int row, int col, char token);


    void print(std::ofstream& ostr){
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < columns; ++j){
               ostr<<grid_[i][j];
            }ostr<<'\n';
        }ostr<<'\n';
    }

    bool operator==(Grid& rhs){
        for(int i = 0; i < rows; ++i){
            for(int j = 0; j < columns; ++j){
                if(grid_[i][j] != rhs.grid_[i][j]) return false;
            }
        }
        return true;
    }

private:
    int rows;
    int columns;
    int numberRegions;
    int starsPerZone;

    std::vector<std::vector<std::vector<int> > > regions;
    std::vector<std::vector<char> > grid_;
    std::vector<int> starInRegion;
    std::vector<int> starLoc;
    std::vector<std::vector<int> > regionGrid;
};


bool Grid::validPlacement(int row, int col){
    //check bounds;
    if(row < 0 || row >= rows || col < 0 || col >= columns) return false;

    //check row
    int rowCount = 0;
    for(int i = 0; i < rows; ++i){
        if(grid_[i][col] == '@') rowCount++;
    }
    
    if(rowCount >= starsPerZone) return false;

    //check cols
    int colCount = 0;
    for(int i = 0; i < columns;++i){
        if(grid_[row][i] == '@') colCount++;
    }
    
    if(colCount >= starsPerZone) return false;

    //check diagonally
    
    if(col-1 >= 0 && grid_[row][col-1] == '@') return false;
    if(row-1 >= 0 && grid_[row-1][col] == '@') return false;
    if(row+1 < grid_.size() && grid_[row+1][col] == '@') return false;
    if(col+1 < grid_[0].size() && grid_[row][col+1] == '@') return false;

    if(row+1 < grid_.size() && col+1<grid_[0].size() && grid_[row+1][col+1] == '@') return false;
    if(row+1 < grid_.size() && col-1>=0 && grid_[row+1][col-1] == '@') return false;
    if(row-1 >= 0 && col-1>=0 && grid_[row-1][col-1] == '@') return false;
    if(row-1 >= 0 && col+1<grid_[0].size() && grid_[row-1][col+1] == '@') return false;
    
    //check region
    int searchRegion = regionGrid[row][col];
    if(starInRegion[searchRegion] >= starsPerZone) return false;

    return true;
}
//add a star to the grid
void Grid::addStar(int row, int col){
    grid_[row][col] = '@';
    this->starLoc.push_back(row);
    this->starLoc.push_back(col);
    starInRegion[getRegion(row,col)]+=1;
    
}
//remove a star from the grid
void Grid::removeStar(int row, int col,char token){
    grid_[row][col] = token;
    //std::cout<<starInRegion[getRegion(row,col)]<<'\n';
    this->starLoc.pop_back();
    this->starLoc.pop_back();
    starInRegion[getRegion(row,col)]-=1;
    //std::cout<<starInRegion[getRegion(row,col)]<<'\n';
}


#endif