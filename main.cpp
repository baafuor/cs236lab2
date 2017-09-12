#include <iostream> 
#include "Token.h"
#include "parser.h"
using namespace std;

int main(int argc, char* argv[])
{
	parser Parser = parser(); //make a new parser
	string filename = argv[1];
	string filename2 = argv[2];
	
	Parser.scanthis(filename, filename2);
	Parser.datalogProgram();
	Parser.print(filename, filename2);
}
