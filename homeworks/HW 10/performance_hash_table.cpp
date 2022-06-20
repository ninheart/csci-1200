#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>


// defined in performance.cpp
void usage();



template <class T> 
void hash_sort(std::unordered_map<T,int>& mp, std::ostream& ostr, int output_count){
	//find the min value; 
	//treat it as a stack, pop the min value 

	typename std::unordered_map<T,int>::iterator itr;
	output_count = 0;
	while(mp.size()>0){
		itr= mp.begin();
		T minValue = itr->first;

		typename std::unordered_map<T,int>::iterator temp = itr;
		//go over the map and find a smaller value
		for(;itr!=mp.end();itr++){
			if(itr->first < minValue){
				minValue = itr->first;
				temp = itr;
			}
		}
		
		for(int i = 0; i < temp->second; i++){
			ostr<<minValue<<'\n';
			output_count++;
		}

		mp.erase(temp);
	}
}

template <class T>
void hash_first_sorted(std::unordered_map<T,int>& mp, std::ostream& ostr, int output_count, int optional_arg){
	typename std::unordered_map<T,int>::iterator itr;
	output_count = 0;

	while(mp.size()>0 && output_count < optional_arg){
		itr= mp.begin();
		T minValue = itr->first;
		typename std::unordered_map<T,int>::iterator temp = itr;
		for(;itr!=mp.end();itr++){
			if(itr->first < minValue){
				minValue = itr->first;
				temp = itr;
			}
		}
		for(int i = 0; i < temp->second && output_count < optional_arg; i++){
			ostr<<minValue<<'\n';
			output_count++;
		}
		mp.erase(temp);
	}
}
//similar to all other mode functions 
template <class T>
void hash_mode(std::unordered_map<T,int>& mp, std::ostream& ostr, int output_count){
	int maxOccurance = 0; 
	T value;
	typename std::unordered_map<T,int>::iterator itr = mp.begin();
	for(;itr!=mp.end();itr++){
		if(itr->second>maxOccurance){
			maxOccurance = itr->second;
			value = itr->first;
		}
	}
	ostr<<value<<'\n';
	output_count = 1;
}

void hash_closest_pair(std::unordered_map<int,int>& mp, std::ostream& ostr, int output_count){
	std::unordered_map<int,int>::iterator itr = mp.begin();
	int maxDiff = 500;
	int indexOne = 0, indexTwo = 0;
	for(;itr != mp.end();itr++){
		std::unordered_map<int,int>::iterator next = itr; 
		next++;
		for(;next != mp.end();next++){
			int diff = abs(next->first - itr->first);
			if(diff < maxDiff && diff != 0){
				maxDiff = diff;
				indexOne = itr->first;
				indexTwo = next->first;
			}
		}
	}
	ostr<<indexOne<<'\n'<<indexTwo<<'\n';
	output_count = 2;
}
//compare two string 
std::string hash_twoString(std::string a, std::string b){
	int len = 0;
	int beginning = 0;
	for(int i = 0; i < a.size(); i++) {
		for(int j = 0; j < b.size(); j++) {
			int k = 0;
			//if we in range and character matches 
			while((i+k)<a.length() && (j+k)<b.length() && a[i+k] == b[j+k]){
				k++;
			}
			if(k > len){
				len = k; 
				beginning = i;
			}
		}
	}
	std::string result = a.substr(beginning,len);
	return result;
}

void hash_longest_substring(std::unordered_map<std::string,int>& mp, std::ostream& ostr, int output_count){
	std::string result ="";
	std::unordered_map<std::string,int>::iterator curr = mp.begin();
	for(;curr!=mp.end();curr++){
		std::unordered_map<std::string,int>::iterator temp = curr;
		++temp;
		for(; temp!=mp.end();++temp){
			std::string s = hash_twoString(curr->first,temp->first);
			if(s.length() > result.length()) {result = s;}
		}
	}
	ostr<<result<<'\n';
	output_count = 1;
}

void hash_table_test(const std::string &operation, const std::string &type,
                     std::istream &istr, std::ostream &ostr,
                     int &input_count, int &output_count, int optional_arg) {


	if(type=="string"){
		std::unordered_map<std::string,int> mp;
		std::string s;
		input_count = 0;
		int count = 0;

		while(istr>>s){
			
			//the only way to "Remove duplicates" is to output the input when reading it
			//which I think it's a meanless operation, but submitty wants it. 
			if(mp.find(s) == mp.end()){
				if(operation == "remove_duplicates"){
					ostr<<s<<'\n';
					count++;
				}
			}
			mp[s]++;
			input_count++;
		}
		if      (operation == "sort")              { hash_sort              (mp,ostr,output_count); }
		else if (operation == "remove_duplicates") {output_count = count; }
		else if (operation == "mode")              { hash_mode              (mp,ostr,output_count); }
		// "closest_pair" not available for strings
		else if (operation == "first_sorted")      { hash_first_sorted      (mp,ostr,output_count,optional_arg); }
		else if (operation == "longest_substring") { hash_longest_substring (mp,ostr,output_count); }
		else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }	
	}else{
		std::unordered_map<int,int> mp;
		int v;
		input_count = 0;
		int count = 0;
		while(istr>>v){
			if(operation == "remove_duplicates" && mp.find(v) == mp.end()){
				ostr<<v<<'\n';
				count++;
			}
			mp[v]++;
			input_count++;
		}
		if      (operation == "sort")              { hash_sort(mp,ostr,output_count); }
		else if (operation == "remove_duplicates") { output_count = count; }
		if (operation == "mode")              { hash_mode              (mp,ostr,output_count); }
		else if (operation == "closest_pair")      { hash_closest_pair      (mp,ostr,output_count); }
		else if (operation == "first_sorted")      { hash_first_sorted      (mp,ostr,output_count,optional_arg); }
	    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
	}
}
