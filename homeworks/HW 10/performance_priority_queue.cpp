#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <string>
#include <queue>


// defined in performance.cpp
void usage();

template<class T>
void pq_sort(std::priority_queue<T, std::vector<T>, std::greater<T> >& pq,
std::ostream& ostr,int output_count){
	output_count = 0;
	while(!pq.empty()){
		ostr<<pq.top()<<'\n';
		pq.pop();
		output_count++;
	}
}

template<class T> 
void pq_first_sorted(std::priority_queue<T, std::vector<T>, std::greater<T> >& pq,
std::ostream& ostr,int output_count, int optional_arg){
	output_count = 0;
	while(!pq.empty() && output_count < optional_arg){
		ostr<<pq.top()<<'\n';
		pq.pop();
		output_count++;
	}
}
//similar to list mode
template<class T>
void pq_mode(std::priority_queue<T, std::vector<T>, std::greater<T> >& pq,
std::ostream& ostr,int output_count){
	int maxOccurences = 1;	
	//since it's already sorted 
	T value;
	T current = pq.top();
	T previous;
	int count = 1;
	while(!pq.empty()){
		if(current == previous){
			//keep going
			count++;
		}else if(count > maxOccurences){
			maxOccurences = count;
			value = previous;
			count = 1;
		}else{
			count = 1;
		}
		//update pointers
		previous = current;
		pq.pop();
		current = pq.top();
		
	}
	ostr<<value<<"\n";
	output_count = 1;
}

void pq_closest_pair(std::priority_queue<int, std::vector<int>, std::greater<int> >& pq,
std::ostream& ostr,int output_count){
	int maxDiff = 55555;
	int current = pq.top(), previous, indexOne, indexTwo;
	//previous greater than current
	while(!pq.empty()){
		previous = current;
		pq.pop();
		current = pq.top();
		int diff = abs(current-previous);
		if(diff<maxDiff && diff > 0) {
			maxDiff = diff;
			indexOne = previous;
			indexTwo = current;
		}
	}
	ostr<<indexOne<<'\n';
	ostr<<indexTwo<<'\n';
	output_count = 2;
}



void priority_queue_test(const std::string &operation, const std::string &type,
                         std::istream &istr, std::ostream &ostr,
                         int &input_count, int &output_count, int optional_arg) {
							 
	if(type=="string"){
		//min heap
		std::priority_queue<std::string, std::vector<std::string>, std::greater<std::string> > pq;
		std::string s;
		input_count = 0;
		//int count = 0;
		while(istr>>s){
			pq.push(s);
			input_count++;
		}
		if      (operation == "sort")              { pq_sort              (pq,ostr,output_count); }
		//else if (operation == "remove_duplicates") { pq_remove_duplicates (pq,ostr,output_count); }
		else if (operation == "mode")              { pq_mode              (pq,ostr,output_count); }
		// "closest_pair" not available for strings
		else if (operation == "first_sorted")      { pq_first_sorted      (pq,ostr,output_count,optional_arg); }
		//else if (operation == "longest_substring") { pq_longest_substring (pq,ostr,output_count); }
		else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }	
	}else{
		assert (type == "integer");
		std::priority_queue<int,std::vector<int>, std::greater<int> > pq;
		int v;
		input_count = 0;
		//int count = 0;
		while(istr>>v){
			pq.push(v);
			input_count++;
		}
		if      (operation == "sort")              { pq_sort(pq,ostr,output_count); }
		//else if (operation == "remove_duplicates") { pq_remove_duplicates (pq,ostr,output_count); }
		else if (operation == "mode")              { pq_mode              (pq,ostr,output_count); }
		else if (operation == "closest_pair")      { pq_closest_pair      (pq,ostr,output_count); }
		else if (operation == "first_sorted")      { pq_first_sorted      (pq,ostr,output_count,optional_arg); }
	    else { std::cerr << "Error: Unknown operation: " << operation << std::endl; usage(); exit(0); }
	}
}
