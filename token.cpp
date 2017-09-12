#include "Token.h"

//define token
//enum & map

Token::Token(Token_type key2, string object2, int line_num2)
{
	//what place holders are representing
	keyty = key2;
	objectty = object2;
	line_num = line_num2;
};

string Token::toString()
{
	string temp; //temp will hold the concatenation
	//need to convert line_num to string
	stringstream ss;
	string type_this = map_1ring2rule[keyty];
	ss << line_num;
	temp = "(" + type_this + ",\"" + objectty + "\"," + ss.str() + ")\n"; //concatanate it
	return temp;
};

Token_type Token::pass_type() //pass the Token Type
{
	return keyty;
}

string Token::pass_string()
{
	return objectty;
}
