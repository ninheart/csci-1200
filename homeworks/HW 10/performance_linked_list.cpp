#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <list>


// defined in performance.cpp
void usage();

template <class T>
void list_sort(std::list<T> &lst,std::ostream &ostr, int output_count){
	lst.sort();
	output_count = lst.size();
	for(typename std::list<T>::iterator i = lst.begin(); i != lst.end(); i++){
		ostr<<*i<<"\n";
	}
}

template <class T>
void list_remove_duplicates(std::list<T> &lst,std::ostream &ostr, int output_count){
	typename std::list<T>::iterator i = lst.begin(); 
	typename std::list<T>::iterator j;
	output_count = lst.size();
	for(;i != lst.end(); i++){
		for(j = lst.begin() = lst.begin(); j != i; j++){
			if(*j == *i){
				i = lst.erase(i);
				--i;
				break;
			}
		}
	}
	
	for(typename std::list<T>::iterator i = lst.begin(); i != lst.end(); i++){
		ostr<<*i<<"\n";
	}
}


template <class T>
void list_mode(std::list<T> &lst,std::ostream &ostr, int output_count){
	lst.sort();
	int current_count = 1;
	int mode = 0;
	typename std::list<T>::iterator itr_curr = lst.begin();
	itr_curr++;
	typename std::list<T>::iterator itr_prev = lst.begin();
	T value = *itr_curr;
	//going thourgh list 
	//track the value's occurance
	//update if it passes the max occurance. 
	for(;itr_curr != lst.end(); itr_curr++, itr_prev++){
		if(*itr_curr == *itr_prev){
			current_count++;
		}else if(current_count > mode){
			value = *itr_prev;
			mode = current_count;
			current_count = 1;
		}else{
			current_count=1;
		}
	}
	output_count = 1;
	ostr<<value<<'\n';
}

template <class T>
void list_first_sorted(std::list<T> &lst,std::ostream &ostr, int output_count, int optional_arg){

	lst.sort();
	output_count = optional_arg;
	typename std::list<T>::iterator itr = lst.begin();
	for(int i = 0; i < output_count; i++, itr++){
		ostr<<*itr<<'\n';
	}
}


void list_closest_pair(std::list<int> &lst,std::ostream &ostr, int output_count){
	assert(lst.size() >= 2);
	lst.sort();
	std::list<int>::iterator curr = lst.begin();
	curr++;
	std::list<int>::iterator prev = lst.begin();
	output_count = 2;
	int diff = 9999;
	int indexOne = 0;
	int indexTwo = 0;
	while(curr != lst.end()){
		//current will always greater than previous because it's sorted
		int dist = *curr - *prev;
		if(dist < diff && dist != 0) {
			diff = dist;
			indexOne = *curr; 
			indexTwo = *prev;
		} 
		++curr; ++prev;
	}
	output_count = 2;
	ostr<<indexTwo<<'\n';
	ostr<<indexOne<<'\n';
}

std::string list_twoString(std::string a, std::string b){
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


void list_longest_substring(std::list<std::string> &lst,std::ostream &ostr, int output_count){
	lst.sort();
	lst.unique();
	std::list<std::string>::iterator curr = lst.begin();
	std::list<std::string>::iterator next;
	std::string result = "";
	for(;curr != lst.end(); curr++){
		std::list<std::string>::iterator temp = curr;
		temp++;
		for(next = temp; next != lst.end(); next++){
			std::string s = list_twoString(*curr, *next);
			if(s.length() > result.length()) result = s;
		}
	}
	output_count = 1;
	ostr<<result<<'\n';
}


void list_test(const std::string &operation, const std::string &type,
                 std::istream &istr, std::ostream &ostr,
                 int &input_count, int &output_count, int optional_arg) {

	if(type == "string"){
		std::list<std::string> lst; 
		std::string s;
		input_count = 0;
		while (istr >> s) {
			lst.push_back(s);
			input_count++;
		}
		if      (operation == "sort")              { list_sort(lst,ostr,output_count); }
		else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
		else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
		// "closest_pair" not available for strings
		else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
		else if (operation == "longest_substring") { list_longest_substring (lst,ostr,output_count); }
		else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
	}else{
		assert (type == "integer");
		std::list<int> lst;
		int v;
		input_count = 0;
		while(istr>>v){
			lst.push_back(v);
			input_count++;
		}
		if      (operation == "sort")              { list_sort(lst,ostr,output_count); }
		else if (operation == "remove_duplicates") { list_remove_duplicates (lst,ostr,output_count); }
		else if (operation == "mode")              { list_mode              (lst,ostr,output_count); }
		else if (operation == "closest_pair")      { list_closest_pair      (lst,ostr,output_count); }
		else if (operation == "first_sorted")      { list_first_sorted      (lst,ostr,output_count,optional_arg); }
	    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
  	} 				 
	// HINT: For the string element type, declare your list like this:
	// std::list<std::string> lst;
}
