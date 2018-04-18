#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

enum tokentype {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS,
	WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM};

string typenames[30] =
{
	"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS",
	"WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"
};

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// ** Done by: Jack Wang
void syntaxerror1(tokentype expected, tokentype lexeme) {
	cout << "SYNTAX ERROR: expected " << typenames[(int)expected] << " but found " << typenames[(int)lexeme] << endl;
	exit(1);
}

void syntaxerror2(string functionName, tokentype lexeme) {
	cout << "SYNTAX ERROR: unexpected " << typenames[(int)lexeme] << " found in " << functionName << endl;
	exit(1);
}

// ** Need the updated match and next_token (with 2 global vars)

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// ** Done by: Jonathan Tapia

// ** Done by: Jack Wang
void verb() {
	tokentype next = next_token();
	switch (next) {
	case WORD2: match(WORD2); break;
	default: syntaxerror2("verb()", next); break;
	}
}
// ** Done by: Jack Wang
void tense() {
	/*
	*masu: VERB
	*masen: VERBNEG
	*mashita: VERBPAST
	*masendeshita: VERBPASTNEG
	*/
	tokentype next = next_token();
	switch (next) {
	case VERB: match(VERB); break;
	case VERBNEG: match(VERBNEG); break;
	case VERBPAST: match(VERBPAST); break;
	case VERBPASTNEG: match(VERBPASTNEG); break;
	default: syntaxerror2("tense()", next); break;
	}
}




// The test driver to start the parser
// Done by:  Marcus Jackson
int main()
{

	//- opens the input file
	//- calls the <story> to start parsing
	//- closes the input file 

}// end
 //** should require no other input files!