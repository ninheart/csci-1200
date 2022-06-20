#include <vector>
#include <fstream>
#include <iostream>
#include <string>
#include <ostream>


//replace function 
void replace(char remove, char sub, std::vector<std::vector<char> >& flat, std::vector<std::vector<char> >& res){
    uint height = flat.size();
    uint width = flat[0].size();
    for(uint i = 0; i < height;++i){
        for(uint j = 0; j < width;++j){
            if(flat[i][j] == remove){
                res[i][j] = sub;
            }
        }
    }
}

//dilation function
void dilation(char foreground, std::vector<std::vector<char> >& flat, std::vector<std::vector<char> >& vec){
    uint height = flat.size();
    uint width = flat[0].size();
    for(uint i = 0; i < height;++i){
        for(uint j = 0; j < width;++j){
            //check the foreground
            if(flat[i][j] == foreground){
                //check if it's possible to dilate within the boundaries
                if(flat[i-1][j] != foreground && i-1 >0){
                    vec[i-1][j] = foreground;
                }if(flat[i+1][j] != foreground && i+1 < height){
                    vec[i+1][j] = foreground;
                }if(flat[i][j-1] != foreground && j-1>0){
                    vec[i][j-1] = foreground;
                }if(flat[i][j+1] != foreground && j+1<width){
                    vec[i][j+1] = foreground;
                }
            }
        }
    }
}

void erosion(char foreground, char background, std::vector<std::vector<char> >& flat,
std::vector<std::vector<char> >& res){
    uint height = flat.size();
    uint width = flat[0].size();
    for(uint i = 0; i < height; ++i){
        for(uint j = 0; j < width; ++j){
            if(flat[i][j] == foreground){
                if(flat[i+1][j] == background || 
                flat[i-1][j] == background || 
                flat[i][j+1] == background ||
                flat[i][j-1] == background){
                    res[i][j] = background;
                }
            }
        }
    }
}

void outputToFile(std::vector<std::vector<char> >& res, std::ofstream& outfile){
    for(uint i = 0; i < res.size(); ++i){
        for(uint j = 0; j < res[i].size(); ++j){
            outfile<<res[i][j];
        }outfile<<'\n';
    }
}

int main(int argc, char* argv[]){
    //check input size
    if(argc < 4){
        std::cout<<"Invalide input size"<<'\n';
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];
    //open input file and output file
    std::ifstream istr(inputFile);
    std::ofstream outfile(outputFile);
    std::string line;
    //vector that stores input file
    std::vector<std::vector<char> > flat;
    
    while(getline(istr,line)){
        //store input file lines into a vector, line by line
        std::vector<char> vec;
        for(uint i = 0; i < line.size(); ++i){
            vec.push_back(line[i]);
        }
        flat.push_back(vec);
    }
    //make a copy of the original vector
    std::vector<std::vector<char> > res = flat;
    std::string command = argv[3];
    if(command == "replace"){
        char remove = argv[4][0];
        char sub = argv[5][0];
        //replace the target character
        replace(remove,sub,flat,res);
        //to output file
        outputToFile(res,outfile);
        //reset
        res = flat;
    }else if(command == "dilation"){
        char foreground = argv[4][0];
        dilation(foreground, flat,res);
        outputToFile(res,outfile);
        //reset
        res = flat;
    }else if(command=="erosion"){
        char foreground = argv[4][0];
        char background = argv[5][0];
        erosion(foreground,background,flat,res);
        outputToFile(res,outfile);
        res = flat;
    }else{
        std::cerr<<"invalid operation, please check your input"<<std::endl;
    } 
}






