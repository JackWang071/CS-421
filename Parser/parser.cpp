#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)

// ** Need the updated match and next_token (with 2 global vars)

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function

//prototypes
void tense();
void verb();
void noun();
void afterObject();
void be();
void afterNoun();
void afterSubject();
void s();
void story();
void syntaxerror1(tokentype expected, tokentype lexeme);
void syntaxerror2(string functionname, tokentype expected);

enum tokentype {
	ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS,
	WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM
};

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


// ** Done by: Marcus Jackson
// <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
void tense()
{
	cout << "Processing tense" << endl;
	tokentype type = next_token();
	switch (type)
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
			syntaxerror2("tense()", type);
	}
}

// <verb> ::= WORD2
void verb()
{
	cout << "Processing verb" << endl;
	tokentype type = next_token();
	switch (type)
	{
		case WORD2:
			match(WORD2); break;
		default:
			syntaxerror2("verb()", type);
	}
}

//<noun> ::= WORD1 | PRONOUN
void noun()
{
	cout << "Processing noun" << endl;
	tokentype type = next_token();
	switch (type)
	{
		case WORD1:
			match(WORD1); break;
		case PRONOUN :
			match(PRONOUN); break;
		default:
			syntaxerror2("noun()", type);
	}
}

//<afterObject> ::= <verb> <tense>PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
void afterObject()
{
	cout << "Processing afterObject" << endl;
	tokentype type = next_token();
	switch (type)
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
			syntaxerror2("afterObject()", type);
	}
}

//<be> ::= IS | WAS
void be()
{
	cout << "Processing be" << endl;
	tokentype type = next_token();
	switch (type)
	{
		case IS :
			match(IS); break;

		case WAS :
			match(WAS); break;
		default:
			syntaxerror2("be()", type);
	}
}

//<afterNoun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <afterOject>
void afterNoun()
{
	cout << "Processing afterNoun" << endl;
	tokentype type = next_token();
	switch (type)
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
			syntaxerror2("afterNoun()", type);
	}
}

//<afterSubject> ::= <verb> <tense> PERIOD | <noun> <afterNoun>
void afterSubject()
{
	cout << "Processing afterSubject" << endl;
	tokentype type = next_token();
	switch (type)
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
			syntaxerror2("afterSubject()", type);
	}
}

//<s> ::= [CONNECTOR]<noun> SUBJECT <afterSubject>
void s()
{
	cout << "Processing s" << endl;
	tokentype type = next_token();
	switch (type)
	{
		case CONNECTOR :
		{
			match(CONNECTOR);
			noun();
			match(SUBJECT);
			afterSubject();
		}

		case WORD1 :
		{
			noun();
			match(SUBJECT);
			afterSubject();
		}

		case PRONOUN :
		{
			noun();
			match(SUBJECT);
			afterSubject();
		}

		default:
			syntaxerror2("s()", type);

	}

}

//<story> ::= <s> { <s> }
void story()
{
	cout << "Processing story" << endl;
	s();

	tokentype type;
	while (true) {
		type = next_token();
		switch (type)
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
			syntaxerror2("story()", type);
		}
	}
	
}






// The test driver to start the parser
// Done by:  Marcus Jackson
int main()
{
	fstream fin; //making the filestream
	string input; //input from the user

	string word; //word to be stored from the file

	cout << "Enter the filename:" << endl; //getting the file name
	cin >> input;

	fin.open(input.c_str(), fstream::in); //opening the file

	if (fin.is_open()) //file opened
	{
		while (fin >> word) //while there is a word store it
		{
			//story();
		}
	}
	else //file unable to be opened
	{
		cout << input.c_str() << " was unable to be opened." << endl;
		return 0;
	}

	fin.close(); //closing the file

				 //- opens the input file
				 //- calls the <story> to start parsing
				 //- closes the input file 

}// end
 //** should require no other input files!