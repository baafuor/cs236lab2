#include <iostream>
#include "datalogprogram.h"
using namespace std;

datalogprogram::datalogprogram(){};
datalogprogram::~datalogprogram(){
	Schemes.clear();
	Facts.clear();
	Queries.clear();
	Rules.clear();
};

void datalogprogram::addscheme(string addme)
{
	Schemes.push_back(Predicate(addme));
}

void datalogprogram::addFact(string addme)
{
	Facts.push_back(Predicate(addme));
}

void datalogprogram::addQuery(string addme)
{
	Queries.push_back(Predicate(addme));
}

void datalogprogram::addRule(string addme)
{
	Rules.push_back(rule(addme));
}

void datalogprogram::addDomain(string addme)
{
	Domain.push_back(addme);
}

string datalogprogram::toString() //put the vectors into a file
{
	stringstream os;

	os << "Schemes(" << Schemes.size() << "):\n";
	for(unsigned int i = 0; i < Schemes.size(); i++)
	{
		os << "  " << Schemes[i].toStringpred() << endl;
	}
	os << "Facts(" << Facts.size() << "):\n";
	for(unsigned int i=0; i < Facts.size(); i++)
	{
		os << "  " << Facts[i].toStringpred() << endl;
	}
	os << "Rules(" << Rules.size() << "):\n";
	for(unsigned int i=0; i < Rules.size(); i++)
	{
		os << "  " << Rules[i].toString() << endl;
	}
	os << "Queries(" << Queries.size() << "):\n";
	for (unsigned int i=0; i < Queries.size(); i++)
	{
		os << "  " << Queries[i].toStringpred() << endl;
	}
	sort(Domain.begin(), Domain.end()); //sort the Domain alphabetically
	os << "Domain(" << Domain.size() << "):\n";
	for (unsigned int i=0; i < Domain.size(); i++)
	{
		os << "  " << Domain[i] << endl; //tostring or tostringpred?
	}

	return os.str();
}

bool datalogprogram::checkvector(string here) //check for doubles
{
	for (unsigned int i = 0; i < Domain.size(); i++)
	{
		if (here == Domain[i])
		{
			return true;
		}
	}
	return false;
}