#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

typedef string tokentype;

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// ** Done by: Jack Wang
void syntaxerror1(tokentype expected, string lexeme) {
	cout << "SYNTAX ERROR: expected " << expected << " but found " << lexeme << endl;
	exit(1);
}

void syntaxerror2(string functionName, string lexeme) {
	cout << "SYNTAX ERROR: unexpected " << lexeme << " found in " << functionName << endl;
	exit(1);
}

// ** Need the updated match and next_token (with 2 global vars)
 
// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Done by: Jonathan Tapia



// The test driver to start the parser
// Done by:  Marcus Jackson
int main()
{

  //- opens the input file
  //- calls the <story> to start parsing
  //- closes the input file 

}// end
//** should require no other input files!


