#include <iostream>
#include "datalogprogram.h"
#include "Scanner.h"
#include <string>
#include <sstream>
#include <fstream> 
using namespace std;

class parser {
private:
	Scanner scanner; //can access the deque of tokens
	datalogprogram dataprog; //can add to the keyword vectors
	
public:
	parser(){};
	~parser(){};
	static bool error_flag; //error flag
	void scanthis(string file_name, string file_out);
	//check if file is valid using the file scanner in scanner and will create deque of tokens

	string stringver(Token_type type); //string version of the id/keyword/etc
	void match(Token_type tokens); //see if the id/keyword/etc matches the string version
	
	void datalogProgram();
	
	void checkScheme();
	void checkFacts();
	void checkRules();
	void checkQueries();

	void SchemeList();
	void factList();
	void ruleList();
	void queryList();
	void scheme();
	void fact();
	void rule();
	void query();
	
	string predicateList();//will include the stringver
	string predicate();//will include the stringver
	string parameterList();//will include the stringver
	string parameter(); //will include stringver

	void print(string something, string file_out);

	//domain, SORT IN THE DOMAIN, print out current token for failure
};