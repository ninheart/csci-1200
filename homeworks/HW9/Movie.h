#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <list>
#include <fstream>
#include <vector>
#include <cmath>
typedef std::pair<int,std::vector<std::string> > pair_;
class Movie{
public:
    Movie(std::string t, std::string y, std::string r, 
            pair_ genres_, pair_ actors_, 
            pair_ roles_){
        this->title = t;
        this->year = y;
        this->runtime = r;
        this->genres = genres_;
        this->actors = actors_;
        this->roles = roles_; 
    };
    std::string get_title() const { return title;}
    std::string get_year() const { return year;}
    std::string get_runtime() const { return runtime;}
    pair_ get_genres() const{return genres;}
    pair_ get_actors() const{return actors;}
    pair_ get_roles() const{return roles;}
    
    
private: 
    std::string title, year, runtime;
    pair_ genres, actors, roles;
};
#endif