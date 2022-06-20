// -----------------------------------------------------------------
// HOMEWORK 7 WORD FREQUENCY MAPS
//
// You may use all of, some of, or none of the provided code below.
// You may edit it as you like (provided you follow the homework
// instructions).
// -----------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <random>
#include <cassert>

// ASSIGNMENT: FILL IN YOUR OWN MAP STRUCTURE
typedef std::map<std::string,std::map<std::string,int> > MY_MAP;
typedef std::map<std::string, MY_MAP> MY_MAP_3;

//helper map to keep tracking number of occurrences
typedef std::map<std::string,int> helper_mp;
typedef std::map<std::string, std::map<std::string,int> > helper_mp2;

// Custom helper function that reads the input stream looking for
// double quotes (a special case delimiter needed below), and white
// space.  Contiguous blocks of alphabetic characters are lowercased &
// packed into the word.
bool ReadNextWord(std::istream &istr, std::string &word) {
  char c;
  word.clear();
  while (istr) {
    // just "peek" at the next character in the stream
    c = istr.peek();
    if (isspace(c)) {
      // skip whitespace before a word starts
      istr.get(c);
      if (word != "") {
		// break words at whitespace
		return true;
      }
    } else if (c == '"') {
      // double quotes are a delimiter and a special "word"
      if (word == "") {
		istr.get(c);
		word.push_back(c);
      }
      return true;
    } else if (isalpha(c)) {
      // this a an alphabetic word character
      istr.get(c);
      word.push_back(tolower(c));
    } else {
      // ignore this character (probably punctuation)
      istr.get(c);
    }
  }
  return false;
}


// Custom helper function that reads the input stream looking a
// sequence of words inside a pair of double quotes.  The words are
// separated by white space, but the double quotes might not have
// space between them and the neighboring word.  Punctuation is
// ignored and words are lowercased.
std::vector<std::string> ReadQuotedWords(std::istream &istr) {
  // returns a vector of strings of the different words
  std::vector<std::string> answer;
  std::string word;
  bool open_quote = false;
  while (ReadNextWord(istr,word)) {
    if (word == "\"") {
      if (open_quote == false) { open_quote=true; }
      else { break; }
    } else {
      // add each word to the vector
      answer.push_back(word);
    }
  }
  return answer;
}


// Loads the sample text from the file, storing it in the map data
// structure Window specifies the width of the context (>= 2) of the
// sequencing stored in the map.  parse_method is a placeholder for
// optional extra credit extensions that use punctuation.
void LoadSampleText(MY_MAP &data, const std::string &filename, int window, 
const std::string &parse_method,helper_mp& helper, MY_MAP_3 &data2, 
helper_mp2& inner_helper) {
	// open the file stream
	std::ifstream istr(filename.c_str());
	if (!istr) { 
	std::cerr << "ERROR cannot open file: " << filename << std::endl; 
	exit(1);
	} 
	// verify the window parameter is appropriate
	if (window < 2) {
	std::cerr << "ERROR window size must be >= 2:" << window << std::endl;
	}
	// verify that the parse method is appropriate
	bool ignore_punctuation = false;
	if (parse_method == "ignore_punctuation") {
	ignore_punctuation = true;
	} else {
	std::cerr << "ERROR unknown parse method: " << parse_method << std::endl;
	exit(1);
	}

	std::string word, prevWord="", prevTwoWords = "";
	//
	// ASSIGNMENT:SETUP YOUR MAP DATA AS NEEDED
	//

	while (ReadNextWord(istr,word)) {
		// skip the quotation marks (not used for this part)
		if (word == "\"") continue;
		MY_MAP::iterator itr = data.find(word);
		//if we cannot find the word
		if (window == 2){
			if(itr == data.end()){
				//insert the word
				std::map<std::string,int> mp;
				data.insert(std::make_pair(word,mp));
				//easier to track occurrence of each word
				helper.insert(std::pair<std::string,int>(word,1));
			}else{
				helper[word]++;
			}
			//seen this word before and we need to add to the count of this word's previous word
			if(prevWord != ""){
				data[prevWord][word]+=1;
			}
			prevWord = word;
		}else if (window == 3){
			MY_MAP_3::iterator it = data2.find(word);
			if(it == data2.end()){
				//create a 2d map 
				MY_MAP small_map;
				data2.insert(std::make_pair(word,small_map));
				helper.insert(std::pair<std::string,int>(word,1));
			}else{
				helper[word]++;
			}
			if(prevWord != " "){
				if(data2[prevWord].find(word) != data2[prevWord].end()){
					inner_helper[prevWord][word]++;	
				}else{
					std::map<std::string,int> mp;
					data2[prevWord].insert(std::make_pair(word,mp));
					inner_helper[prevWord].insert(std::make_pair(word,1));
				}
			}
			if(prevTwoWords != " "){
				data2[prevTwoWords][prevWord][word]+=1;
			}
			//update previous words
			prevTwoWords = prevWord;
			prevWord = word;
		}
	}
}

void NextWord(MY_MAP& data, bool random_flag,int length,std::vector<std::string>&all,
std::vector<std::string>& sentence){
	std::string start = sentence[0];
	std::string next ="";
	all.push_back(start);
	if(!random_flag){
		for(int i = 0; i < length; i++){
			//find the starting word in the MAP
			std::map<std::string,int>::iterator itr = data[start].begin();	
			int freq = 0;
			for(;itr!=data[start].end();++itr){
				if(itr->second > freq || (itr->second == freq && itr->first < next)){
					//make sure we have the max occurrence
					freq = itr->second;
					next = itr->first;
				}
			}
			//we find the next word and update the starting word
			all.push_back(next);
			start = next;
		}
	}else{
		for(int i = 0; i < length; ++i){
			//generate random number
			std::random_device rand_device;
			std::mt19937 generator(rand_device());
			uint random = 0;
			if(data[start].size() == 2 || data[start].size() == 1 || data[start].size() == 0){
				random = 0;
			}else{	
				std::uniform_int_distribution<int> dist(1,data[start].size()-1);
				random = dist(generator);
			}
			std::map<std::string,int>::iterator itr = data[start].begin();
			//iterate random number times 
			for(uint j = 0; j < random; ++j) itr++;
			next = itr->first;
			all.push_back(next);
			start = next;
		}
	}
}
//for window = 3
void NextWord2(MY_MAP_3& data, bool random, int length,std::vector<std::string>&all,
std::vector<std::string>& sentence){
	if(!random){
		std::string start = sentence[0], next, nextNext;
		int freq = 0;
		int temp = 0;
		//if the input is a single word
		if(sentence.size() == 1){
			temp = length+1;
			//locate inner map
			MY_MAP::iterator it = data[start].begin();
			for(;it != data[start].end();++it){
				int total =0;
				//we lock in the first inner map 
				std::map<std::string,int>::iterator temp = data[start][it->first].begin();
				for(;temp != data[start][it->first].end(); ++temp){
					//add up occurrences
					total += temp->second;
				}
				if(total > freq){
					//find the max occurrence
					freq = total;
					next = it->first;
				}
			}
		}else if (sentence.size() == 2){
			temp = length+2;
			next = sentence[1];
		}
		// generating words based on sentence length
		for(int j = 0; j < temp; j++){
			//after we lock in the next word we select the next next word. 
			int count = 0;
			std::map<std::string,int>::iterator itr = data[start][next].begin();
			for(;itr != data[start][next].end();++itr){
				if(itr->second > count){
					count = itr->second;
					nextNext = itr->first;
				}else if(itr->second == count && itr->first < nextNext){
					nextNext = itr->first;
				}
			}
			//push back the word
			all.push_back(start);
			//updating search window 
			start = next;
			next = nextNext;
		}
	}else{
		//random choice
		std::string start = sentence[0], next, nextNext;
		if(sentence.size() == 1){
			for(int j = 0; j < length+1; j++){
				//generating random numebr 
				std::random_device rand_device;
				std::mt19937 generator(rand_device());
				uint random = 0;
				//bound checking
				if(data[start].size() == 2 || data[start].size() == 1 || data[start].size() == 0){
					random = 0;
				}else{	
					std::uniform_int_distribution<int> dist(1,data[start].size()-1);
					random = dist(generator);
				}
				MY_MAP::iterator itr = data[start].begin();
				all.push_back(start);
				for (uint j = 0; j < random; ++j) itr++;
				start = itr->first;
			}
		}else if (sentence.size() == 2){
			next = sentence[1];
			for(int j = 0; j < length+2; j++){
				//after we lock in the next word we select the next next word. 
				std::map<std::string,int>::iterator itr = data[start][next].begin();
				std::random_device rand_device;
				std::mt19937 generator(rand_device());
				uint random = 0;
				if(data[start][next].size() == 2 || data[start][next].size() == 1 || data[start][next].size() == 0){
					random = 0;
				}else{	
					std::uniform_int_distribution<int> dist(1,data[start][next].size()-1);
					random = dist(generator);
				}
				for(uint k = 0; k < random; k++) itr++;
				nextNext = itr->first;
				all.push_back(start);
				start = next;
				next = nextNext;
			}
		}
		
	}
}

int main () {

  // ASSIGNMENT: THE MAIN DATA STRUCTURE
MY_MAP data;
MY_MAP_3 data2;
//two helper map to track occurrences
helper_mp helper;
helper_mp2 inner_helper;

bool map2 = false;
  // Parse each command
std::string command;    
while (std::cin >> command) {
	// load the sample text file
	if (command == "load") {
		std::string filename;
		int window;
		std::string parse_method;
		std::cin >> filename >> window >> parse_method;   
		if(window > 2) map2 = true;   
		LoadSampleText(data, filename,window, parse_method,helper,data2,inner_helper);
		std::cout<<"Loaded "<<filename<<" with window = "<<window<<" and parse method = "<<parse_method<<'\n';
		std::cout<<'\n';
	} 

	// print the portion of the map structure with the choices for the
	// next word given a particular sequence.
	//inner helper maps help me to print out occurrences of outter maps which don't have a value in the
	//nested map 
	else if (command == "print") {
		//the size of sentence is always 1 for window = 2
		std::vector<std::string> sentence = ReadQuotedWords(std::cin);
		if(!map2){
			assert(data.find(sentence[0]) != data.end());
			std::map<std::string,int>::iterator itr = data[sentence[0]].begin();
			helper_mp::iterator it = helper.find(sentence[0]);
			std::cout<<sentence[0]<<" ("<<it->second<<")"<<'\n';
			for(;itr!=data[sentence[0]].end();itr++){
				std::cout<<sentence[0]<<' '<<itr->first<<" ("<<itr->second<<")"<<'\n';
			}std::cout<<'\n';
		}else{
			if(sentence.size() == 1){
				helper_mp::iterator it = helper.find(sentence[0]);
				std::cout<<it->first<<" ("<<it->second<<")"<<'\n';
				MY_MAP::iterator itr = data2[sentence[0]].begin();
				for(;itr!=data2[sentence[0]].end();++itr){
					helper_mp2::iterator inner = inner_helper.find(itr->first);
					std::cout<<sentence[0]<<' '<<inner->first<<" ("<<inner_helper[sentence[0]][itr->first]<<")"<<'\n';
				}std::cout<<'\n';
			}else if(sentence.size() ==2){
				std::cout<<sentence[0]<<" "<<sentence[1]<<" ("<<inner_helper[sentence[0]][sentence[1]]<<")"<<'\n';
				std::map<std::string,int>::iterator itr = data2[sentence[0]][sentence[1]].begin();
				for(;itr!=data2[sentence[0]][sentence[1]].end();itr++){
					std::cout<<sentence[0]<<' '<<sentence[1]<<' '<<itr->first<<" ("<<itr->second<<")"<<'\n';
				}std::cout<<'\n';
			}
		}
	}

	// generate the specified number of words 
	else if (command == "generate") {
		std::vector<std::string> sentence = ReadQuotedWords(std::cin);
		// how many additional words to generate
		int length;
		std::cin >> length;
		std::string selection_method;
		std::cin >> selection_method;
		bool random_flag;
		if (selection_method == "random") {
			random_flag = true;
		} else {
			assert (selection_method == "most_common");
			random_flag = false;
		}
		//all vector to store selected words 
		std::vector<std::string> all;
		if(!map2){
			//window = 2
			NextWord(data,random_flag,length,all,sentence);
		}else{
			
			NextWord2(data2,random_flag,length,all,sentence);
		}
		//print out words 
		for(uint i =0; i < all.size(); i++){
			if(i != all.size() - 1)
				std::cout<<all[i]<<' ';
			else{
				std::cout<<all[i];
			}
		}std::cout<<'\n';
		std::cout<<'\n';
		
	} else if (command == "quit") {
		break;
	} else {
		std::cout << "WARNING: Unknown command: " << command << std::endl;
	}
	}
}
