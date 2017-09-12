#include <iostream>
#include "Predicate.h"
using namespace std;

//for the datalog
Predicate::Predicate(string pred) {
	returnthis = pred;
}

string Predicate::toStringpred()
{
	return returnthis; //return whole Predicate
}
