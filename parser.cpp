#include <iostream>
#include "parser.h"
using namespace std;

bool parser::error_flag = false;

void parser::scanthis(string file_name, string file_out)
{
	scanner.checkfile(file_name, file_out);
}

string parser::stringver(Token_type tokens) //string version of the id/keyword/etc
{
	string this_lab = ""; //empty -- hold the string vers. 
	if (tokens == scanner.return_type())
	{
		this_lab = scanner.return_string();
		scanner.increment();
	}
	else
	{
		error_flag = true;
		// cout << "error @ stringver\n";
	}
	return this_lab;
} //DONE

void parser::match(Token_type type) //see if the id/keyword/etc matches token in the deque
{
	if (type == scanner.return_type()) //matches the token)
	{
		scanner.increment();
	} 
	else //does not match anything
	{
		// cout << "\n~~~~\n@ match error_flag is true\n";
		error_flag = true;
	}
} //DONE

	
void parser::datalogProgram()
{
	try
	{
		// cout << "Check for schemes\n";
		checkScheme();	
		if (error_flag == true)
		{
		 	return; //do nothing
		}
		// cout << "Check for facts\n";
		checkFacts();
		if (error_flag == true)
		{
			return;
		}
		// cout << "Check for rules\n";
		checkRules();
		if (error_flag == true)
		{
			return;
		}
		// cout << "Check for queries\n";
		checkQueries();
		if (error_flag == true)
		{
			return;
		}
		match(ENDOF);
		if (error_flag == true)
		{
			return;
		}
	}
	catch (Token_type invalid)
	{
		error_flag = true;
	}
	
}	

void parser::checkScheme()
{
	match(SCHEMES);
	if (error_flag != true)
	{
		match(COLON);
		if (error_flag != true)
		{
			scheme();
			SchemeList();
		}
		else
		{
			error_flag = true;
			return;
		}
	}
	else
	{
		error_flag = true;
		// cout << "error @ checkScheme\n";
		return;
	}
}

void parser::checkFacts()
{
	match(FACTS);
	// cout << "@checkFacts error is: " << boolalpha << error_flag << endl;
	if (error_flag != true)
	{
		// cout << "inside checkFiles" << endl;
		match(COLON);
		if (error_flag != true)
		{
			factList();
		}
	}
}
void parser::checkRules()
{
	match(RULES);
	if (error_flag != true)
	{
		match(COLON);
		if (error_flag != true)
		{
			ruleList();
		}
	}
}
void parser::checkQueries()
{
	match(QUERIES);
	if (error_flag != true)
	{
		match(COLON);
		if (error_flag != true)
		{
			query();
			queryList();
		}
	}	
}

void parser::SchemeList()
{
	if (scanner.return_type() == ID && error_flag == false) //prevents recrusion if error is true
	{
		scheme();
		if (error_flag == true) //prevents recursion if error found
		{
			return;
		}
		SchemeList();
	}
	
}

void parser::factList()
{
	// cout << "factlist is running" << endl;
	if (scanner.return_type() == ID && error_flag == false)
	{
		// cout << "inside the factlist" << endl;
		fact();
		if (error_flag == true)
		{
			return;
		}
		factList();
	}
}
	

void parser::ruleList()
{
	if (scanner.return_type() == ID && error_flag == false)
	{
		rule();
		if (error_flag == true)
		{
			return;
		}
		ruleList();
	}
}

void parser::queryList()
{
	if (scanner.return_type() == ID && error_flag == false)
	{
		query();
		if (error_flag == true)
		{
			return;
		}
		queryList();
	}
}

void parser::scheme()
{
	// cout << "\n****\nscheme ran\n";
	string scheme = "";
	scheme = predicate();
	dataprog.addscheme(scheme);
	return;
}

void parser::fact()
{
	// cout << "\n****\nfact ran\n";
	string fact = "";
	fact = predicate();
	if (error_flag == true)
	{
		return;
	}
	match(PERIOD); //see if there is a period there or not
	dataprog.addFact(fact); //add fact to the vector
}

void parser::rule()
{
	// cout << "\n****\nrule ran\n";
	string rule = "";
	rule = predicate();
	rule += " ";
	rule += stringver(COLON_DASH);
	rule += " ";
	// if (error_flag == false)
	// {
		rule += predicate();
		if (error_flag == false)
		{
			rule += predicateList();
		}
		else
		{
			error_flag = true;
		}
		if (error_flag == true)
		{
			return;
		}
	// }
	// else 
	// {
	// 	error_flag = true;
	// }
	 // if (error_flag == true) { cout << "ERROR AT RULES\n"; return;}
	match(PERIOD); //this works

	dataprog.addRule(rule);
}

void parser::query()
{
	// cout << "\n****\nquery ran\n";
	string query = "";
	query = predicate();
	if (error_flag == true)
	{
		return;
	}
	match(Q_MARK);

	dataprog.addQuery(query);
}
	
string parser::predicateList(){
	//will include the stringver
	//call error flags (T) - epsilon is important
	string hello = "";
	if(COMMA == scanner.return_type())
	{
		hello = stringver(COMMA);
		if (error_flag == false)
		{
			hello += predicate();
			
			if (error_flag == false)
			{
				hello += predicateList();
			}
			else
			{
				error_flag = true;
			}
		}
		else
		{
			error_flag = true;
		}
	}
	return hello;
}


string parser::predicate(){//will include the stringver
	string predicatethis = "";
	if (ID == scanner.return_type() && error_flag == false)
	{
		predicatethis = stringver(ID);
		// cout << "(@id) predicate is: " << predicatethis << endl;
		if (LEFT_PAREN == scanner.return_type())
		{
			predicatethis += stringver(LEFT_PAREN);
			// cout << "(@left paren) predicate is: " << predicatethis << endl;
			if(error_flag == false)
			{
				predicatethis += parameter();
				// cout << "(@parameter) predicate is: " << predicatethis << endl;
					if(error_flag == false)
					{
						predicatethis += parameterList();
						// cout << "(@parameterList) predicate is: " << predicatethis << endl;
						if (error_flag == false && RIGHT_PAREN == scanner.return_type())
						{
							predicatethis += stringver(RIGHT_PAREN);
							// cout << "(@right paren) predicate is: " << predicatethis << endl;
						}
						else
						{
							error_flag = true;
							// cout << "error @ right paren\n";
						}
					}
					else
					{
						error_flag = true;
						// cout << "error @ parameterList\n";
					}
			}
			else
			{
				error_flag = true;
				// cout << "error @ parameter\n";
			}
		}
		else
		{
			error_flag = true;
			// cout << "error @ left paren\n";
		}
	}
	else
	{
		error_flag = true;
		// cout << "error @  ID\n";
	}
	return predicatethis;
}

string parser::parameterList(){//will include the stringver
	string parserthis = "";
	if(COMMA == scanner.return_type())
	{
		parserthis = stringver(COMMA);
		if (error_flag == false)
		{
			parserthis += parameter();
			if (error_flag == false)
			{
				parserthis += parameterList();
			}
			else
			{
				error_flag = true;
				// cout << "error @ parameterList of parameterList\n";
			}
		}
		else
		{
			error_flag = true;
			// cout << "error @ comma of parameterList\n";
		}
	}
	return parserthis;
}

string parser::parameter(){ //will include stringver
	string parameterthis = "";
	if(STRING == scanner.return_type()) //check if string
	{
		parameterthis = stringver(STRING);
		if (dataprog.checkvector(parameterthis) == false)
		{
			dataprog.addDomain(parameterthis);
		}
	}
	else if (ID == scanner.return_type()) //check if token
	{
		parameterthis = stringver(ID);
	}
	else //it's neither
	{
		error_flag = true;
		// cout << "(@parameter) error_flag is true\n";
	}
	return parameterthis;
}

void parser::print(string something, string file_out)
	{
		ofstream hello;
		hello.open(file_out); //open the file

		string printthis = "";

		// cout << "\n**********\n";
		// cout << "error_flag is..." << boolalpha << error_flag << endl;
		// cout << "**********\n";

		if (error_flag == false) //if the flag is false
		{
			// cout << "error_flag is false!\n";
			printthis = "Success!\n";
			string more = "";
			more = dataprog.toString();
			hello << printthis << more;
		}
		else //yeah, there was an error in the code
		{
			// cout << "error_flag is true!\n";
			printthis = "Failure!\n";
			printthis += "  " + scanner.deque_token[scanner.recordplace].toString();
			//Print the error
			hello << printthis;
		}

		hello.close(); //close the file
	}; //Done 