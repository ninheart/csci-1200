#ifndef hashtable_h
#define hashtable_h

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <algorithm>
#include "Movie.h"

// The hashtable is templated over both the type of key and the type
// of the hash function, a function object.
class hashTable{
private:
	//representation
	std::vector<std::pair<std::string, std::list<Movie*> > > m_table; 
	int m_size;
	float occupancy; 
public:
	hashTable(uint init_size = 100, float occupancy_ = 0.5): m_table(init_size), m_size(0), occupancy(occupancy_) {}
	void update_size(uint n){
		std::vector<std::pair<std::string, std::list<Movie*> > > n_table(n);
		m_table = n_table;
	}
	void update_occupancy(float n){
		occupancy = n;
	}
	//hash function from ds_set
	uint hashFunction(std::string key){
		uint hashCode = 1;
		std::string hashstring = key;
        for(uint i = 0; i < hashstring.length(); i++){
            hashCode ^= ((hashCode<<5)+hashstring[i]+(hashCode>>2));
        }
        return hashCode;
    }  

	uint find(std::string key){
		uint hashValue = hashFunction(key);
		uint index = hashValue % m_table.size();
		//check if hash value matches 
		if(hashValue == hashFunction(m_table[index].first)){
			return index;
		}else{
			//linear probing similar to insert 
			//loop until we find an empty bucket 
			while(!m_table[index].second.empty()){
				index++;
				if(hashValue == hashFunction(m_table[index].first)){
					return index;
				}
				//if we at the end of the table we go back to the beginning
				if(index == m_table.size()-1){
					index = 0;
				}
			}
			return -1;
		}
	}
	//inserting a key value pair 
	void insert(std::pair<std::string, Movie*> key){
		const float LOAD_FRACTION_FOR_RESIZE = occupancy; 
		if(m_size > LOAD_FRACTION_FOR_RESIZE*m_table.size()){
			resize_table(2*m_table.size());
		}
		//hash the key
		uint hashValue = hashFunction(key.first);
		//obtained the index 
		unsigned int index = hashValue % m_table.size();
		//haven't insert a key yet 
		if(m_table[index].second.empty()){
			//create a new value container 
			std::list<Movie*> temp; 
			temp.push_front(key.second);
			m_table[index] = std::make_pair(key.first, temp);
			m_size++;
		}
		//if the list is not empty and we're matching the query(the hash value).  
		else if(!m_table[index].second.empty() && hashValue == hashFunction(m_table[index].first)){
			//
			m_table[index].second.push_front(key.second);
			m_size++;
		}else{//handle collsion, not empty and hash value doesn't match
			bool flag = false;
			while(!m_table[index].second.empty()){
				index++;
				//if we find a matching query, insert the key 
				if(hashValue == hashFunction(m_table[index].first)){
					m_table[index].second.push_front(key.second);
					m_size++;
					flag = true;
					break;
				}
				//if we reach the end, start from 0
				if(index == m_table.size()-1){
					index = 0;
				}
			}
			//we found an empty bucket and perform insert 
			if(!flag && index < m_table.size()){
				std::list<Movie*> temp;
				temp.push_front(key.second);
				m_table[index] = std::make_pair(key.first,temp);
				m_size++;
			}
		}
	}

	void resize_table(int new_size){
		//create a new table with the new size
		std::vector<std::pair<std::string, std::list<Movie*> > > n_table(new_size);
		//a temp container that copies from m_table
		std::vector<std::pair<std::string, std::list<Movie*> > > temp;
		//copying..
		for(int i = 0; i < m_table.size(); i++){
			temp.push_back(m_table[i]);
		}
		//reassingn table 
		m_table = n_table;
		m_size = 0;
		//go over temp and rehash all the value
		for(int i = 0; i < temp.size(); i++){
			std::list<Movie*>::iterator it = temp[i].second.begin();
			for(;it != temp[i].second.end(); it++){
				insert(std::make_pair(temp[i].first,*it));
			}
		}
	}
	void print(){
		for(int i = 0; i < m_table.size();++i){
			std::cout<<i<<":   ";
			//std::cout<<m_table[i].second.size();
			std::list<Movie*>::iterator itr = m_table[i].second.begin();
			for(;itr!=m_table[i].second.end();++itr){
				std::cout<<(*itr)->get_title()<<"  ";
			}std::cout<<'\n';
		}
	}
	//standard output function 
	void print(uint index,std::map<std::string,std::string>& actors){
		std::cout<<"Printing "<<m_table[index].second.size()<<" result(s):"<<'\n';
		std::list<Movie*>::iterator itr = m_table[index].second.begin();	
		for(;itr!=m_table[index].second.end();++itr){
			std::cout<<(*itr)->get_title()<<'\n';
			std::cout<<(*itr)->get_year()<<'\n';
			std::cout<<(*itr)->get_runtime()<<'\n';
			std::cout<<(*itr)->get_genres().first;
			for(int i = 0; i < (*itr)->get_genres().first; i++){
				std::cout<<" "<<(*itr)->get_genres().second[i];
			}std::cout<<'\n';
			std::cout<<(*itr)->get_actors().first;
			for(int i = 0; i < (*itr)->get_actors().first; i++){
				std::cout<<" "<<actors.find((*itr)->get_actors().second[i])->second<<" ("<<(*itr)->get_roles().second[i]<<")";
			}std::cout<<'\n';

		}
	}
};

#endif