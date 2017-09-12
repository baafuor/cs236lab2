#pragma once
#include <iostream> 
#include <map>
#include <string>
#include <sstream> //for stringstream in token.cpp
using namespace std;

//list Token types with class enum
enum Token_type {COMMA, PERIOD, Q_MARK, LEFT_PAREN, RIGHT_PAREN, COLON, COLON_DASH, MULTIPLY, ADD, SCHEMES, FACTS, RULES, QUERIES, ID, STRING, COMMENT, WHITESPACE, UNDEFINED, ENDOF};

class Token
{
	private:
		map<Token_type,string> map_1ring2rule = { //made a map <key, type of object> nameofmap
			{COMMA, "COMMA"}, //prints COMMA
			{PERIOD, "PERIOD"},
			{Q_MARK, "Q_MARK"},
			{LEFT_PAREN, "LEFT_PAREN"},
			{RIGHT_PAREN, "RIGHT_PAREN"},
			{COLON, "COLON"},
			{COLON_DASH, "COLON_DASH"},
			{MULTIPLY, "MULTIPLY"},
			{ADD, "ADD"},
			{SCHEMES, "SCHEMES"},
			{FACTS, "FACTS"},
			{RULES, "RULES"},
			{QUERIES, "QUERIES"},
			{ID, "ID"},
			{STRING, "STRING"},
			{WHITESPACE, "WHITESPACE"},
			{UNDEFINED, "UNDEFINED"},
			{ENDOF, "EOF"}
		}; //defining the map

		Token_type keyty; //act as key for map
		string objectty; //object
		int line_num; //line number

	public:
		Token(){};
		virtual ~Token(){};
		Token(Token_type key2, string object2, int line_num2); //place holder variables
		virtual string toString();
		virtual Token_type pass_type();
		virtual string pass_string();
};
