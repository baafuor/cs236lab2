#pragma once
#include <iostream> 
#include <fstream>
#include <cctype> 
#include <deque>
#include <fstream>
#include "Token.h"
using namespace std;

class Scanner : public Token 
{//friend class = use private variables across
	friend class parser;	
	private:
		deque<Token> deque_token;
		string ID1;
		string String1;
		string comment1;
		int count_line; //count the lines
		int causeIcan = 0;
		int recordplace = 0; //record place in the deque

	public:
		Scanner(){};
		~Scanner(){};
		void checkfile(string file_name, string file_out); //is file valid?
		void scanme(ifstream &takeit, string file_out); //for scanning the file
		//functions to handle long words:
		void switchme(ifstream &takeit, char getthat, string file_out);
		void checkcolon(ifstream &takeit, int count_line, char getthat);
		void theend(ifstream &takeit,int count_line);
		void switchthis(ifstream &takeit, char getthat, string file_out);
		void readID(ifstream &takeit, char getthat, string file_out);
		void readString(ifstream &takeit, char getthat, string file_out);
		//print function
		void print(string something, string file_out);
		//error flag
		static bool check_error;

		Token_type return_type();
		string return_string();
		void increment();
};
