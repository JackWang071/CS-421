#ifndef parser_C
#define parser_C

#include<iostream>
#include<string>

using namespace std;

//=================================================
// File parser.cpp written by Group Number: 4
//=================================================

enum tokentype {
	ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS,
	WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM
};

bool token_available;
tokentype saved_token;
string lexeme;
Scanner scanner;
string tokenNames[30] =
{
	"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS",
	"WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"
};

tokentype next_token();
bool match(tokentype expected);
void tense();
void verb();
void noun();
void afterObject();
void be();
void afterNoun();
void afterSubject();
void s();
void story();
void syntaxerror1(tokentype expected, string lexeme);
void syntaxerror2(string functionname, string lexeme);

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need the updated match and next_token (with 2 global vars)

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need the updated match and next_token (with 2 global vars)
// Done by: Jonathan Tapia

tokentype next_token()
{
	if (!token_available)   // if there is no saved token from previous lookahead
	{
		scanner.scanner(saved_token, lexeme);  // call scanner to grab a new token
		token_available = true;                  // mark that fact that you have saved it
	}

	return saved_token;    // return the saved token
}
bool match(tokentype expected)
{
	if (next_token() != expected)  // mismatch has occurred with the next token
	{
		syntaxerror1(expected, lexeme);
		return false;
	}
	else  // match has occurred
	{
		token_available = false;  // eat up the token
		return true;              // say there was a match
	}
}


// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// ** Done by: Jack Wang
void syntaxerror1(tokentype expected, string lexeme) {
	cout << "SYNTAX ERROR: expected " << tokenNames[(int)expected] << " but found " << lexeme << endl;
	cin.clear(); cin.get(); cin.ignore();
	exit(1);
}
void syntaxerror2(string functionName, string lexeme) {
	cout << "SYNTAX ERROR: unexpected " << lexeme << " found in " << functionName << endl;
	cin.clear(); cin.get(); cin.ignore();
	exit(1);
}

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function

// ** Done by: Marcus Jackson
// <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
void tense()
{
	cout << "Processing tense" << endl;
	switch(next_token())
	{
		case VERBPAST:
			match(VERBPAST); break;
		case VERBPASTNEG:
			match(VERBPASTNEG); break;
		case VERB:
			match(VERB); break;
		case VERBNEG:
			match(VERBNEG); break;
		default:
			syntaxerror2("tense()", lexeme);
	}
}

// <verb> ::= WORD2
void verb()
{
	cout << "Processing verb" << endl;
	switch (next_token())
	{
		case WORD2:
			match(WORD2); break;
		default:
			syntaxerror2("verb()", lexeme);
	}
}

//<noun> ::= WORD1 | PRONOUN
void noun()
{
	cout << "Processing noun" << endl;
	switch (next_token())
	{
		case WORD1:
			match(WORD1); break;
		case PRONOUN :
			match(PRONOUN); break;
		default:
			syntaxerror2("noun()", lexeme);
	}
}

//<afterObject> ::= <verb> <tense>PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
void afterObject()
{
	cout << "Processing afterObject" << endl;
	switch (next_token())
	{
		case WORD2 :
		{
			verb();
			tense();
			match(PERIOD);
			break;
		}
		case WORD1 :
		{
			noun();
			match(DESTINATION);
			verb();
			tense();
			match(PERIOD);
			break;

		}
		case PRONOUN :
		{
			noun();
			match(DESTINATION);
			verb();
			tense();
			match(PERIOD);
			break;

		}
		default:
			syntaxerror2("afterObject()", lexeme);
	}
}

//<be> ::= IS | WAS
void be()
{
	cout << "Processing be" << endl;
	switch (next_token())
	{
		case IS :
			match(IS); break;

		case WAS :
			match(WAS); break;
		default:
			syntaxerror2("be()", lexeme);
	}
}

//<afterNoun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <afterOject>
void afterNoun()
{
	cout << "Processing afterNoun" << endl;
	switch (next_token())
	{
		case IS :
		{
			be();
			match(PERIOD);
			break;
		}

		case WAS :
		{
			be();
			match(PERIOD);
			break;
		}

		case DESTINATION :
		{
			match(DESTINATION);
			verb();
			tense();
			match(PERIOD);
			break;
		}

		case OBJECT :
		{
			match(OBJECT);
			afterObject();
			break;
		}
		default:
			syntaxerror2("afterNoun()", lexeme);
	}
}

//<afterSubject> ::= <verb> <tense> PERIOD | <noun> <afterNoun>
void afterSubject()
{
	cout << "Processing afterSubject" << endl;
	switch (next_token())
	{
		case WORD2 :
		{
			verb();
			tense();
			match(PERIOD);
			break;
		}

		case WORD1 :
		{
			noun();
			afterNoun();
			break;
		}

		case PRONOUN :
		{
			noun();
			afterNoun();
			break;
		}
		default:
			syntaxerror2("afterSubject()", lexeme);
	}
}

//<s> ::= [CONNECTOR]<noun> SUBJECT <afterSubject>
void s()
{
	cout << "Processing s" << endl;
	switch (next_token())
	{
		case CONNECTOR :
		{
			match(CONNECTOR);
			noun();
			match(SUBJECT);
			afterSubject();
			break;
		}

		case WORD1 :
		{
			noun();
			match(SUBJECT);
			afterSubject();
			break;
		}

		case PRONOUN :
		{
			noun();
			match(SUBJECT);
			afterSubject();
			break;
		}

		default:
			syntaxerror2("s()", lexeme);
	}
}

//<story> ::= <s> { <s> }
void story()
{
	cout << "Processing story" << endl;
	s();

	while (true) {
		switch (next_token())
		{
		case CONNECTOR:
		{
			match(CONNECTOR);
			noun();
			match(SUBJECT);
			afterSubject();
			break;
		}

		case WORD1:
		{
			noun();
			match(SUBJECT);
			afterSubject();
			break;
		}

		case PRONOUN:
		{
			noun();
			match(SUBJECT);
			afterSubject();
			break;
		}
		default:
			syntaxerror2("story()", lexeme);
		}
	}
}

// The test driver to start the parser
// Done by:  Marcus Jackson
int main()
{
	string filename; //input from the user
	string word; //word to be stored from the file

	cout << "Enter the filename: "; //getting the file name
	cin >> filename;

	Parser test = Parser(input);

	if (scanner.startup(filename.c_str())) //file opened
	{
		story();
	}
	else //file unable to be opened
	{
		cout << filename.c_str() << " was unable to be opened." << endl;
	}

	//fin.close(); //closing the file

				 //- opens the input file
				 //- calls the <story> to start parsing
				 //- closes the input file 
	return 0;

}// end
 //** should require no other input files!

#endif // !parser_C