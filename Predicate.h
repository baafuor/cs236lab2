#pragma once
#include <iostream>
#include <string>
#include "Parameter.h"
using namespace std;

class Predicate {
private:
	string returnthis;

public:
	Predicate(string pred);
	~Predicate(){};

	string toStringpred();
};