#include <iostream>
#include "rule.h"
using namespace std;

//relates to datalogprogram and predicate

rule::rule(string rulez){
	inst = rulez;
}
rule::~rule(){}

string rule::toString(){
	return inst; //return object
}