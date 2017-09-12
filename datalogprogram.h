#include <iostream>
#include "rule.h"
#include "Predicate.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

class datalogprogram {
private:
	vector <Predicate> Schemes;
	vector <Predicate> Facts;
	vector <rule> Rules;
	vector <Predicate> Queries;
	vector <string> Domain;

public:
	datalogprogram();
	~datalogprogram();

	void addscheme(string addme);
	void addFact(string addme);
	void addQuery(string addme);
	void addRule(string addme);
	void addDomain(string addme);

	string toString(); //for outputting vectors to a file
	bool checkvector(string here);
};