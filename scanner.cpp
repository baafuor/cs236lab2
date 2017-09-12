#include "Scanner.h"

bool Scanner::check_error = false;
//scan file
//put tokens into deque
//print stuff

void Scanner::checkfile(string file_name, string file_out)
	{
		ifstream in;
		ifstream takeit;
		takeit.open(file_name); //open the file
		if (takeit.fail()) //failed
		{	
			return;
		}
		else //good to go			
		{
			scanme(takeit, file_out); //call the actual scann function	
		}
	}; 

	void Scanner::scanme(ifstream &takeit, string file_out)
	{
		count_line = 1; //initiated - keeps count of current line number
		char getthat = ' '; //keeps track of current char
		while (!takeit.eof() && Scanner::check_error != true) //while not end of file
		{
			takeit.get(getthat); //grab first char
			//cout << "getthat after .get: \"" << getthat << "\"" << endl;
			if (getthat == '\n' && takeit.peek() != EOF)
			{
				count_line++; //increment the line count
				//cout << "new line: " << count_line << endl;
			}
			/*if (takeit.peek() == EOF)
			{
				cout << "hi" << endl;
				if (getthat == '\n' && getthat != ' ')
				{
					cout << "no" << endl;
					causeIcan = 1;
				}
				else
				{
					causeIcan = 0;
				}
			}*/
			else if (!isspace(getthat) && getthat != '\n')
			{
				switch(getthat){
				// case ' ' ://Whitespace -- don't do anything with whitespace
				case '.' :
					deque_token.push_back(Token(PERIOD,".",count_line));
					break;

				case ',':
				//run comma scan
					deque_token.push_back(Token(COMMA,",",count_line));
					break;

				case '(' :
				//run L_PAREN scan
					deque_token.push_back(Token(LEFT_PAREN,"(",count_line));
					break;
	
				case ')' :
					deque_token.push_back(Token(RIGHT_PAREN,")",count_line));
					break;
				
				case '\?':
					deque_token.push_back(Token(Q_MARK,"?",count_line));
					break;
				
				case '*' :
					deque_token.push_back(Token(MULTIPLY,"*",count_line));
					break;

				case '+' :
					deque_token.push_back(Token(ADD,"+",count_line));
					break;

				case ':' :
					checkcolon(takeit, count_line, getthat);
					break;
				
				case '#' : //case for comments
					takeit.ignore(1000, '\n'); //ignore characters until newline (not a comment anymore)
					count_line++;
					//cout << "Comment here: " << count_line << endl;
					break;
				
				case '\'':
					readString(takeit, getthat, file_out);
					break;
				
				default: //handles IDs and keywords
					readID(takeit, getthat, file_out);
					break;
				}
			
			}
		}
		//finished scanning - insert ENDOF into the deque if fulfills conditions
		theend(takeit, count_line);
	}; 

	void Scanner::checkcolon(ifstream &takeit, int count_line, char getthat)
	{
		if (takeit.peek()=='-')
		{
			deque_token.push_back(Token(COLON_DASH,":-",count_line));
			takeit.get(getthat); //consume the dash
		}
		else
		{
			deque_token.push_back(Token(COLON,":",count_line));
		}
	};

	void Scanner::theend(ifstream &takeit, int count_line)
	{
		if (Scanner::check_error == true) //there's an error, don't do anything
		{
			return;
		}
		else
		{
			if (count_line != 1)
			{
				count_line++;
				//deque_token.push_back(Token(ENDOF,"",count_line));
				//cout << "increment - line: " << count_line << endl;
				//return;
			}
			/*
			else if (count_line != 1) //|| causeIcan != 1) //empty file
			{
				//count_line++;
				//cout << "Add more " << count_line << endl;
				//cout << "Incrementinggggg " << count_line << endl;
				//deque_token.push_back(Token(ENDOF,"",count_line));
			}*/

			deque_token.push_back(Token(ENDOF,"",count_line));
			
		}
		return;
	};

	void Scanner::readID(ifstream &takeit, char getthat, string file_out)
	{
		
		if (isalpha(getthat))
		{
			string fullID = "";
			fullID += getthat; //variable to hold the ID
			while (isalnum(takeit.peek())) //build the ID
			{
				takeit.get(getthat); //get what was peeked
				fullID += getthat; //build on the ID
			}

			//list keywords here
			if (fullID == "Queries")
			{
				deque_token.push_back(Token(QUERIES,"Queries",count_line));
				
			}
			else if (fullID == "Rules")
			{
				deque_token.push_back(Token(RULES,"Rules",count_line));
				
			}
			else if (fullID == "Facts")
			{
				deque_token.push_back(Token(FACTS,"Facts",count_line));
				
			}
			else if (fullID == "Schemes")
			{
				deque_token.push_back(Token(SCHEMES,"Schemes",count_line));
				
			}
			else
			{
				deque_token.push_back(Token(ID,fullID,count_line)); //push the ID into the deque
				
			}
			return;
		}
		else //not an ID
		{
			//yeahhhhh pull the error flag
			Scanner::check_error=true; 
		}
	}; 

	void Scanner::readString(ifstream &takeit, char getthat, string file_out)
	{
		//variable to check if it fulfills requirements to be a string
		bool error = false;

		string fullID = "";
		fullID += getthat; //to store the string for deque

			while(takeit.peek() != '\'') //build the string
			{
				if (takeit.eof()) //end of file
				{
					error = true; //not good
					break;
				}
				else if (takeit.peek() == '\n') //newline
				{
					error = true; //not good
					 break;
				}
				else //good to go
				{
					error = false; //good
					takeit.get(getthat);
					fullID += getthat;
				}
			}
			if (error == true) //it's not really a string
			{
				check_error = true;
			}
			else
			{
				takeit.get(getthat);
				fullID += getthat; //concatenate into full info

				deque_token.push_back(Token(STRING,fullID,count_line)); //push in the string
				
				return;
			}
	}; 
	
	void Scanner::print(string something, string file_out)
	{
		ofstream hello;
		hello.open(file_out); //open the file

		string printthis;
		int recordthis = deque_token.size(); 
		for (int i=deque_token.size(); i>0; i--) //load the deque into the string
		{
			Token hello = deque_token.front(); 
			printthis += hello.toString();
			deque_token.pop_front(); //call the next element
		}

		stringstream ss;
		ss << recordthis;

		if (check_error == false) //if the flag is false
		{
			printthis += "Total Tokens = " + ss.str() + '\n';
			hello << printthis;
		}
		else //yeah, there was an error in the code
		{
			stringstream ss;
			ss << count_line;
			string errorthis = "Input Error on line " + ss.str() + '\n';
			printthis += errorthis;
			hello << printthis;
		}

		hello.close(); //close the file

	};

	Token_type Scanner::return_type()
	{
		return deque_token[recordplace].pass_type();
	}

	string Scanner::return_string()
	{
		return deque_token[recordplace].pass_string();
	}

	void Scanner::increment()
	{
		recordplace++;
	}

