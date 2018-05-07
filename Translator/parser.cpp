#ifndef parser_C
#define parser_C

#include "parser.h"

using namespace std;

//=================================================
// File parser.cpp written by Group Number: 4
//=================================================

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need the updated match and next_token (with 2 global vars)

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

Parser::Parser(string filename) {
	if (scanner.openfile(filename.c_str())) //file opened
	{
		fout.open("translated.txt");
		story();
	}
	else //file unable to be opened
	{
		cout << filename.c_str() << " was unable to be opened." << endl;
	}
}

void Parser::setupDict() {
	dictionary.insert("desu", "is");
	dictionary.insert("deshita", "was");
	dictionary.insert("watashi", "I/me");
	dictionary.insert("anata", "you");
	dictionary.insert("kare", "he/him");
	dictionary.insert("kanojo", "she/her");
	dictionary.insert("sore", "it");
	dictionary.insert("mata", "Also");
	dictionary.insert("soshite", "Then");
	dictionary.insert("shikashi", "However");
	dictionary.insert("dakara", "Therefore");

	//From lexicon
	dictionary.insert("daigaku", "college");
	dictionary.insert("kurasu", "class");
	dictionary.insert("hon", "book");
	dictionary.insert("tesuto", "test");
	dictionary.insert("ie", "home");
	dictionary.insert("isu", "chair");
	dictionary.insert("seito", "student");
	dictionary.insert("sensei", "teacher");
	dictionary.insert("tomodachi", "friend");
	dictionary.insert("jidoosha", "car");
	dictionary.insert("gyuunyuu", "milk");
	dictionary.insert("biiru", "beer");
	dictionary.insert("choucho", "butterfly");
	dictionary.insert("ryouri", "cooking");
	dictionary.insert("toire", "restroom");
	dictionary.insert("gohan", "meal");
	dictionary.insert("yasashii", "easy");
	dictionary.insert("muzukashii", "difficult");
	dictionary.insert("ureshii", "pleased");
	dictionary.insert("shiawase", "happy");
	dictionary.insert("kanashii", "sad");
	dictionary.insert("omoi", "heavy");
	dictionary.insert("oishii", "delicious");
	dictionary.insert("tennen", "natural");
	dictionary.insert("nakI", "cry");
	dictionary.insert("ikI", "go");
	dictionary.insert("tabE", "eat");
	dictionary.insert("ukE", "take");
	dictionary.insert("kakI", "write");
	dictionary.insert("yomI", "read");
	dictionary.insert("nomI", "drink");
	dictionary.insert("agE", "give");
	dictionary.insert("moraI", "receive");
	dictionary.insert("butsI", "hit");
	dictionary.insert("kerI", "kick");
	dictionary.insert("shaberI", "talk");
	dictionary.insert("yarI", "do");
	dictionary.insert("yorokobI", "enjoy");
}

// ** Need the updated match and next_token (with 2 global vars)
// Done by: Jonathan Tapia
tokentype Parser::next_token()
{
	if (!token_available)   // if there is no saved token from previous lookahead
	{
		scanner.scanner(saved_token, saved_lexeme);  // call scanner to grab a new token
		token_available = true;                  // mark that fact that you have saved it
	}

	return saved_token;    // return the saved token
}
bool Parser::match(tokentype expected)
{
	if (next_token() != expected)  // mismatch has occurred with the next token
	{
		syntaxerror1(expected, saved_lexeme);
		return false;
	}
	else  // match has occurred
	{
		token_available = false;  // eat up the token
		cout << "Matched " << tokenNames[(int)expected] << endl;
		return true;              // say there was a match
	}
}

// ** Done by: Jack Wang
void Parser::getEword() {
	string jt = saved_lexeme;
	try {
		saved_lexeme = dictionary.at(saved_lexeme);
	}
	catch (out_of_range oor) {
		saved_lexeme = jt;
	}
}

// ** Done by: Marcus Jackson
void Parser::gen(gentype type) {
	switch (type) {
	case CONN:
		fout << "CONNECTOR:\t" + saved_lexeme + "\n"; break;
	case ACTR:
		fout << "ACTOR:\t" + saved_lexeme + "\n"; break;
	case DESC: 
		fout << "OBJECT:\t" + saved_lexeme + "\n"; break;
	case OBJ: 
		fout << "OBJECT:\t" + saved_lexeme + "\n"; break;
	case ACTN:
		fout << "ACTION:\t" + saved_lexeme + "\n"; break;
	case TO: 
		fout << "TO:\t\t" + saved_lexeme + "\n"; break;
	case TNSE:
		fout << "TENSE:\t" + tokenNames[(int)saved_token] + "\n"; break;
	default:
		fout << saved_lexeme + " "; break;
	}
}

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// ** Done by: Jack Wang
void Parser::syntaxerror1(tokentype expected, string lexeme) {
	cout << "SYNTAX ERROR: expected " << tokenNames[(int)expected] << " but found " << lexeme << endl;
	exit(1);
}
void Parser::syntaxerror2(string functionName, string lexeme) {
	cout << "SYNTAX ERROR: unexpected " << lexeme << " found in " << functionName << endl;
	exit(1);
}

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function

// ** Done by: Marcus Jackson
// <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
void Parser::tense()
{
	cout << "Processing <tense>" << endl;
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
			syntaxerror2("tense()", saved_lexeme);
	}
}

// <verb> ::= WORD2
void Parser::verb()
{
	cout << "Processing <verb>" << endl;
	switch (next_token())
	{
		case WORD2:
			match(WORD2); break;
		default:
			syntaxerror2("verb()", saved_lexeme);
	}
}

//<noun> ::= WORD1 | PRONOUN
void Parser::noun()
{
	cout << "Processing <noun>" << endl;
	switch (next_token())
	{
		case WORD1:
			match(WORD1); break;
		case PRONOUN :
			match(PRONOUN); break;
		default:
			syntaxerror2("noun()", saved_lexeme);
	}
}

//<afterObject> ::= <verb> <tense>PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
void Parser::afterObject()
{
	cout << "Processing <afterObject>" << endl;
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
			syntaxerror2("afterObject()", saved_lexeme);
	}
}

//<be> ::= IS | WAS
void Parser::be()
{
	cout << "Processing <be>" << endl;
	switch (next_token())
	{
		case IS :
			match(IS); break;

		case WAS :
			match(WAS); break;
		default:
			syntaxerror2("be()", saved_lexeme);
	}
}

//<afterNoun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <afterOject>
void Parser::afterNoun()
{
	cout << "Processing <afterNoun>" << endl;
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
			syntaxerror2("afterNoun()", saved_lexeme);
	}
}

//<afterSubject> ::= <verb> <tense> PERIOD | <noun> <afterNoun>
void Parser::afterSubject()
{
	cout << "Processing <afterSubject>" << endl;
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
			syntaxerror2("afterSubject()", saved_lexeme);
	}
}

//<s> ::= [CONNECTOR]<noun> SUBJECT <afterSubject>
void Parser::s()
{
	cout << "Processing <s>" << endl;
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
			syntaxerror2("s()", saved_lexeme);
	}
}

//<story> ::= <s> { <s> }
void Parser::story()
{
	cout << "Processing <story>" << endl;

	while (true) {
		s();
	}

	cout << "Successfully parsed <story>" << endl;
}

/*
// The test driver to start the parser
// Done by:  Marcus Jackson
int main()
{
	string input; //input from the user
	string word; //word to be stored from the file

	cout << "Enter the filename: "; //getting the file name
	cin >> input;

	Parser test(input);

				 //- opens the input file
				 //- calls the <story> to start parsing
				 //- closes the input file 
	return 0;

}// end
 //** should require no other input files!
 */

#endif // !parser_C