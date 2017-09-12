#pragma once
#include <iostream>
#include <string>
#include "Predicate.h"
using namespace std;

class rule {
private:
	string inst;
public:
	rule(string rulez);
	~rule();

	string toString();
};