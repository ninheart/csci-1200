#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <set>
#include <map>


// defined in performance.cpp
void usage();

template<class T>
void bst_sort(std::map<T,int>&mp, std::ostream& ostr,int output_count){
	typename std::map<T,int>::iterator itr = mp.begin();
	output_count = mp.size();
	for(;itr!=mp.end();itr++){
		for(int i = 0; i < itr->second; i++){
			ostr<<itr->first<<'\n';
		}
	}
}

template<class T>
void bst_remove_duplicates(std::map<T,int>&mp, std::ostream& ostr,int output_count){
	typename std::map<T,int>::iterator itr = mp.begin();
	output_count = mp.size();
	for(;itr!=mp.end();itr++){
		ostr<<itr->first<<'\n';
	}
}

template<class T>
void bst_first_sorted(std::map<T,int>&mp, std::ostream& ostr,int output_count,int optional_arg){
	typename std::map<T,int>::iterator itr = mp.begin();
	output_count = 0;
	for(;output_count < optional_arg;itr++){
		for(int i = 0; i < itr->second && output_count < optional_arg; i++){
			ostr<<itr->first<<'\n';
			output_count++;
		}
	}
}

template <class T>
void bst_mode(std::map<T,int>&mp, std::ostream& ostr,int output_count){
	int maxOccurance = 0; 
	T value;
	typename std::map<T,int>::iterator itr = mp.begin();
	//since the strucutre is already sorted, we can just keep going checking
	//each key's value;
	for(;itr!=mp.end();itr++){
		if(itr->second>maxOccurance){
			maxOccurance = itr->second;
			value = itr->first;
		}
	}
	ostr<<value<<'\n';
	output_count = 1;
}

//integer only
void bst_closest_pair(std::map<int,int>mp, std::ostream& ostr, int output_count){
	std::map<int,int>::iterator first = mp.begin();
	first++;
	std::map<int,int>::iterator second = mp.begin();
	int maxDiff = 9999; //set a large value 
	int indexOne = 0, indexTwo = 0;
	while(first!=mp.end()){
		int diff = first->first - second->first;
		if(diff < maxDiff){
			maxDiff = diff;
			indexOne = first->first;
			indexTwo = second->first;
		}
		first++;
		second++;
	}
	ostr<<indexTwo<<'\n';
	ostr<<indexOne<<'\n';
	output_count = 2;
}

std::string bst_twoString(std::string a, std::string b){
	int len = 0;
	int beginning = 0;
	for(int i = 0; i < a.size(); i++) {
		//std::string sub = a.substr(i,)
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

//string only 
void bst_longest_substring(std::map<std::string,int> mp, std::ostream& ostr,int output_count){
	output_count = 1;
	std::string result ="";
	std::map<std::string,int>::iterator curr = mp.begin();
	std::map<std::string,int>::iterator next;
	for(;curr!=mp.end();curr++){
		std::map<std::string,int>::iterator temp = curr;
		temp++; 
		for(next = temp; next!=mp.end();next++){
			std::string s = bst_twoString(curr->first,next->first);
			if(s.length() > result.length()) result = s;
		}
	}
	ostr<<result<<'\n';
}


void bst_test(const std::string &operation, const std::string &type,
              std::istream &istr, std::ostream &ostr,
              int &input_count, int &output_count, int optional_arg) {
	if(type=="string"){
		std::map<std::string,int> mp;
		std::string s;
		input_count = 0;
		int count = 0;
		while(istr>>s){
			std::map<std::string,int>::iterator it = mp.find(s);
			mp[s]++;
			if(it == mp.end()){
				if(operation == "remove_duplicates"){
					ostr<<s<<'\n';
					count++;
				}
			}
			input_count++;
		}
		if      (operation == "sort")              { bst_sort              (mp,ostr,output_count); }
		else if (operation == "remove_duplicates") {output_count = count; }
		else if (operation == "mode")              { bst_mode              (mp,ostr,output_count); }
		// "closest_pair" not available for strings
		else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg); }
		else if (operation == "longest_substring") { bst_longest_substring (mp,ostr,output_count); }
		else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }	
	}else{
		assert (type == "integer");
		std::map<int,int> mp;
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
		if      (operation == "sort")              { bst_sort(mp,ostr,output_count); }
		else if (operation == "remove_duplicates") { output_count = count; }
		else if (operation == "mode")              { bst_mode              (mp,ostr,output_count); }
		else if (operation == "closest_pair")      { bst_closest_pair      (mp,ostr,output_count); }
		else if (operation == "first_sorted")      { bst_first_sorted      (mp,ostr,output_count,optional_arg); }
	    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
	}
}
