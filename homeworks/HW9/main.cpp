#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <list>
#include <fstream>
#include <vector>
#include <cmath>
#include "hashtable.h"
#include "Movie.h"

//pair to store genre, actors and roles 
typedef std::pair<int,std::vector<std::string> > pair_;

/*
These two functions are not required for your program, but may be helpful!
The recursive function will generate every combination of 0/1 for 6 positions
in a vector. Whenever pos == 6, the vector is complete.

Hint: There are 6 different "fields" in a query, this may be useful in constructing
your hash table.
**/
//query object 
class Query{
private:
    //it has all the information of a movie 
    std::string title, year, runtime;
    std::pair<int,std::vector<std::string> > genres,actors,roles;
public:
    Query(std::string t, std::string y, std::string r,std::pair<int,std::vector<std::string> > ge,std::pair<int,std::vector<std::string> > ac,std::pair<int,std::vector<std::string> > ro){
        title = t; year = y;runtime = r;
        genres = ge;actors = ac; roles = ro;
    }
    //concat all the strings 
    std::string concat(){
        std::string ans ="";
        ans+=title+year+runtime;
        ans+=std::to_string(genres.first);
        for(int i = 0; i < genres.first; i++){
            ans += genres.second[i];
        }
        ans+=std::to_string(actors.first);
        for(int i = 0; i < actors.first; i++){
            ans += actors.second[i];
        }
        ans+=std::to_string(roles.first);
        for(int i = 0; i < roles.first; i++){
            ans += roles.second[i];
        }
        return ans;
    }
};
void permute_filters(int pos, std::vector<int> filter,std::vector<std::vector<int> >& all){
	if(pos == 6){
		//Add other code here if you want to use the completed vectors
        all.push_back(filter);
		return;
	}
	filter.push_back(0);
	std::vector<int> filter_new = filter;
	filter_new.back() = 1;
	permute_filters(pos+1, filter_new,all);
	permute_filters(pos+1, filter,all);
}

//Driver function, feel free to modify to pass more arguments
void permute_filters(std::vector<std::vector<int> >& all){
		permute_filters(0, std::vector<int>(), all);
}

//generate different combination of query
Query generate_query(std::string title, std::string year, std::string runtime,
std::pair<int,std::vector<std::string> > genres, std::pair<int,std::vector<std::string> > actors, 
std::pair<int,std::vector<std::string> > roles,int index,std::vector<std::vector<int> >all){
    std::vector<std::string> emptyVec{};
    if(all[index][0] == 0){
        title = "?";
    }
    if(all[index][1] == 0){
        year = "?";
    }
    if(all[index][2] == 0){
        runtime = "?";
    }
    if(all[index][3] == 0){
        genres.first = 0;
        genres.second = emptyVec;
        
    }
    if(all[index][4] == 0){
        actors.first = 0;
        actors.second = emptyVec;
    }
    if(all[index][5] == 0){
        roles.first = 0;
        roles.second = emptyVec;
    }
    return Query(title,year,runtime,genres,actors,roles);
}

typedef std::pair<std::string, std::list<Movie> > KeyType;

int main(){
    //std::string title, year, runtime; 
    std::string input;
    //actor map
    std::map<std::string,std::string> actorMap;
    //movies vector, perform deletion later 
    std::vector<Movie*> movies; 
    //default size and occupancy
    int size = 0;
    float occupancy = 0.5;
    hashTable H_Table;
    //64 permutations, load all possible outcome
    std::vector<std::vector<int> > all_perm;
    permute_filters(all_perm);

    while(std::cin>>input){
        if(input == "table_size"){
            std::cin>>input;
            size = std::stoi(input);
            H_Table.update_size(size);
        }else if(input == "occupancy"){
            std::cin>>input;
            //convert to float 
            occupancy = std::stof(input);
            H_Table.update_occupancy(occupancy);
        }else if(input == "movies"){
            
            std::string fileName;
            std::cin>>fileName;
            std::string title,year, runtime;
            int num_genres, num_actors, num_roles;
            pair_ genres, actors, roles;
            std::ifstream file(fileName);
            std::string line; 
            
            while(file>>line){
                title = line;
                file>>line;
                year = line;
                file>>line;
                runtime = line;
                file>>line;
                num_genres = std::stoi(line);
                file>>line;//blank space
                std::vector<std::string> store_genre;
                for(int i= 0; i < num_genres; i++){
                    store_genre.push_back(line);
                    //query_list.push_back(line);
                    file>>line;
                }
                
                num_actors = std::stoi(line);
                file>>line;//blank space
                std::vector<std::string> store_actors;
                for(int i = 0; i < num_actors; i++){
                    store_actors.push_back(line);
                    //query_list.push_back(line);
                    file>>line;
                }
                num_roles = std::stoi(line);
                std::vector<std::string> store_roles;
                for(int i =0; i < num_roles; i++){
                    file>>line;
                    store_roles.push_back(line);
                    //query_list.push_back(line);
                }
                genres = std::make_pair(num_genres,store_genre);
                actors = std::make_pair(num_actors,store_actors);
                roles = std::make_pair(num_roles,store_roles);
                //create movie object
                Movie* movie = new Movie(title,year,runtime,genres,actors,roles);
                movies.push_back(movie);
                //64 permutations 
                for(int i = 0; i < 64; i++){
                    //generate query object 
                    Query q = generate_query(title,year,runtime,
                    genres,actors,roles,i, all_perm);  
                    //obtain concatenated string from query object 
                    std::string key = q.concat();
                    //insertion 
                    H_Table.insert(std::make_pair(key,movie));
                }
            }
        }else if(input == "query"){
            std::string title,year, runtime;
            int num_genres, num_actors, num_roles;
            pair_ genres, actors, roles;

            std::cin>>input;
            title = input;
            std::cin>>input;
            year = input;
            std::cin>>input;
            runtime = input;
            std::cin>>input;
        
            std::vector<std::string> store_genre;
            num_genres = std::stoi(input);
            std::cin>>input;
            
            for(int i= 0; i < num_genres; i++){
                    store_genre.push_back(input);
                    std::cin>>input;
            }
            num_actors = std::stoi(input);
            std::cin>>input;//blank space
            std::vector<std::string> store_actors;
            for(int i = 0; i < num_actors; i++){
                store_actors.push_back(input);
                std::cin>>input;
            }
            
            num_roles = std::stoi(input);
            std::vector<std::string> store_roles;
            for(int i =0; i < num_roles; i++){
                std::cin>>input;
                store_roles.push_back(input);
            }
            genres = std::make_pair(num_genres,store_genre);
            actors = std::make_pair(num_actors,store_actors);
            roles = std::make_pair(num_roles,store_roles);
            //create query object 
            Query q = Query(title,year,runtime,genres,actors,roles);
            std::string key = q.concat();
            uint i = H_Table.find(key);
            if(i == -1){
                std::cout<<"No results for query."<<'\n';
            }else{
                H_Table.print(i,actorMap);
            }
            
        }else if(input == "actors"){
            std::string file;
            std::cin>>file;
            std::ifstream input_file(file);
            std::string line;
            while(input_file>>line){
                std::string id;
                std::string name;
                id = line;
                input_file>>line;
                name = line;
                actorMap.insert(std::make_pair(id,name));
            }
        }else if(input == "quit"){
            break;
        }
        
    }
    //delete all the movie objects from the heap
    for(int i =0; i < movies.size(); ++i){
        delete movies[i];
    }
    
}