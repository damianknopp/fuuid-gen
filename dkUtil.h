#include <ctype.h>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <map>
#include <exception>
using namespace std;

namespace dk{
#ifndef _DKUTIL_H
#define _DKUTIL_H

class dkUtil{
public:

///////////////////////////////////
//does a conversion from int to string
///////////////////////////////////
static inline string intToString(int i){
	std::ostringstream o;
	if(o << i){
		string buffer = o.str();
		return buffer;
	}
	//string buffer = "";
	//return buffer;
	__throw_invalid_argument("Invalid argument exception in intToString function.");
}//end intToString

//////////////////////////////////
//convert a primitive char value to a primitive int value
//////////////////////////////////
static inline int charToInt(char c) {
	int retInt = -1;
	if(isdigit(c)){
		char* charP = &c;
		retInt = (int)atoi(charP);
		charP = NULL;
		return retInt;
	}
	__throw_invalid_argument("Invalid argument exception in charToInt function: A non digit was passed in.");
}//end charToInt

///////////////////////////////////
//does a conversion from string to int
///////////////////////////////////
static inline int convertToInt(const std::string & str)
{
	std::stringstream io;
	int a;
	if(io << str)
	{
		io >> a;
		return a;
	}
	__throw_invalid_argument("Invalid argument exception in convertToInt function: A non digit was passed in.");
}//end charToInt

///////////////////////////////////
//does a conversion from string to int
///////////////////////////////////
static inline int convertToInt(const std::string & str)
{
	std::stringstream io;
	int a;
	if(io << str)
}//end convertToInt

////////////////////////////////
//returns true if string contains all digits
////////////////////////////////
static inline bool containsAllDigits(const string & str){
	for(unsigned int i = 0; i < str.length(); i++){
		if((isdigit(str[i]) == 0)){
			return false;
		}
	}
	return true;
}

/////////////////////////////////
//removes all trailing and leading whitespace
//test code prints out---> :hi:
//string str = "   hi   ";
//cout << ":" << str << ":" << endl;
//trim(str);
//cout << "After trim:" << str << ":" << endl;
////////////////////////////////
static inline void trim(std::string & str)
{
	//remove all trailing white spaces
	unsigned int end = str.length() - 1;
	bool done = false;
	while(!done){
//cout << "Checking :" << str[end] << ":" << " at pos " << end <<  endl;
		if( isspace( str[end] ) ){
	//cout << "Deleted" << endl;
			str.erase(str.length() - 1, 1);
			end = str.length() - 1;
		}
		else{
			done = true;
		}
	} 

	done = false;
	string::iterator i = str.begin();
	while(!done){
		if( isspace(*i) ){
			i++;
		}
		else{
			done = true;
		}
	}
	//remove all leading white spaces
	str.erase(str.begin(),i);
}//end trim

////////////////////////////////
//print the contents of a Container
///////////////////////////////
void printVector( const vector<string> & c )
{
	vector<string>::const_iterator itr;
	for( itr = c.begin(); itr != c.end(); itr++){
		cout << *itr << '\n';
	}
}

//////////////////////////////////////////////
//This is a c++ impl of the neary recursion!
//print all combinations from a list of lists
//the combinations contain one word from every 
//list.
//The following list of lists
// => | list1word1 | list1word2 |
// => | list2word1 | 
// => | list3word1 | list3word2 | 
// => | list4word1 | list4word2 | list4word3 | 
//gives:
//list1word1 list2word1 list3word1 list4word1
//list1word1 list2word1 list3word1 list4word2
//list1word1 list2word1 list3word1 list4word3
//
//list1word1 list2word1 list3word2 list4word1
//list1word1 list2word1 list3word2 list4word2
//list1word1 list2word1 list3word2 list4word3
//
//list1word2 list2word1 list3word1 list4word1
//list1word2 list2word1 list3word1 list4word2
//list1word2 list2word1 list3word1 list4word3
//
//list1word2 list2word1 list3word2 list4word1
//list1word2 list2word1 list3word2 list4word2
//list1word2 list2word1 list3word2 list4word3
//////////////////////////////////////////////
void
combination( vector<vector<string> > & vec, unsigned int count, string build, vector<string> & finalList)
{
	if( count >= vec.size() ){
		//cout << "adding:" << build << ":" << endl;
		finalList.push_back(build);
		return;
	}	
	for(unsigned int i = 0; ( count < vec.size() ) && ( i < ( ((vector<string>)vec[count]).size()) ); i++){
		combination(vec, count + 1, build + ((vector<string>)vec[count])[i] + " ", finalList);
	}
}//end combination

//////////////////////
//print a generic Container
////////////////////////
template<class Container>
static void dkUtil::printCont(const Container & cont)
{
	//this line gives warnings
	//Container::const_iterator itr;
	//use this instead
	typedef typename Container::const_iterator it;
	it itr;
	for(itr = cont.begin(); itr != cont.end(); itr++)
		cout << *itr << ' '; 
	cout << endl;
}//end printContainer

////////////////////////
//print a generic container of pairs
/////////////////////////
template<class Container>
static void dkUtil::printContPairs(const Container & cont)
{
	typedef typename Container::const_iterator it;
	it itr;
	for(itr = cont.begin(); itr != cont.end(); itr++){
		cout << itr->first << ":" << itr->second << endl;
	}
}

//////////////////////
//print a map 
////////////////////////
static void dkUtil::printMap(map<string, int> m){
	map<string, int>::iterator it;
	for(it = m.begin(); it != m.end(); it++){
		cout << it->first << " " << it->second << endl;
	}
}


//////////////////////
//string length comparator
//////////////////////
static bool dkUtil::stringLenComp(const string & s1, const string & s2){
	if(s1.length() > s2.length()){
		return true;
	}
	else{
		return false;
	}
}


///////////////////
//pair length comparator
///////////////////
static bool dkUtil::pairKeyLenComp(const pair<string, int> & p1, const pair<string, int> & p2){
	if(p1.first.length() > p2.first.length()){
		return true;
	}
	else{
		return false;
	}
}

///////////////////
//pair value comparator
///////////////////
static bool dkUtil::pairValueComp(const pair<string, int> & p1, const pair<string, int> & p2){
	if(p1.second > p2.second){
		return true;
	}
	else{
		return false;
	}
}

///////////////////////////
//
///////////////////////////
static vector<pair<string, int> > * dkUtil::copyToVector(const map<string, int> & m){
	map<string, int>::const_iterator it;
	vector<pair<string, int> > * v = new vector<pair<string, int> >();
	v->reserve(m.size());
	for(it = m.begin(); it != m.end(); it++){
		v->push_back(make_pair(it->first, it->second));
	}
	return v;
}


static vector<string> dkUtil::parseCommandLine(int argc, const char** argv){
	vector<string> args;
	for(int i = 0; i < argc; i++){
		args.push_back(argv[i]);
	}
	return args;
}

};//end dkUtil class
#endif
};//end dk namespace
