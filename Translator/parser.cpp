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
	setupDict();
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

// ** Done by: Jack Wang
//Hard-codes a number of Japanese words and English translations into the dictionary.
void Parser::setupDict() {
	dictionary["desu"] = "is";
	dictionary["deshita"] = "was";
	dictionary["watashi"] = "I/me";
	dictionary["anata"] = "you";
	dictionary["kare"] = "he/him";
	dictionary["kanojo"] = "she/her";
	dictionary["sore"] = "it";
	dictionary["mata"] = "Also";
	dictionary["soshite"] = "Then";
	dictionary["shikashi"] = "However";
	dictionary["dakara"] = "Therefore";

	//Added from lexicon.
	dictionary["daigaku"] = "college";
	dictionary["kurasu"] = "class";
	dictionary["hon"] = "book";
	dictionary["tesuto"] = "test";
	dictionary["ie"] = "home";
	dictionary["isu"] = "chair";
	dictionary["seito"] = "student";
	dictionary["sensei"] = "teacher";
	dictionary["tomodachi"] = "friend";
	dictionary["jidoosha"] = "car";
	dictionary["gyuunyuu"] = "milk";
	dictionary["biiru"] = "beer";
	dictionary["choucho"] = "butterfly";
	dictionary["ryouri"] = "cooking";
	dictionary["toire"] = "restroom";
	dictionary["gohan"] = "meal";
	dictionary["yasashii"] = "easy";
	dictionary["muzukashii"] = "difficult";
	dictionary["ureshii"] = "pleased";
	dictionary["shiawase"] = "happy";
	dictionary["kanashii"] = "sad";
	dictionary["omoi"] = "heavy";
	dictionary["oishii"] = "delicious";
	dictionary["tennen"] = "natural";
	dictionary["nakI"] = "cry";
	dictionary["ikI"] = "go";
	dictionary["tabE"] = "eat";
	dictionary["ukE"] = "take";
	dictionary["kakI"] = "write";
	dictionary["yomI"] = "read";
	dictionary["nomI"] = "drink";
	dictionary["agE"] = "give";
	dictionary["moraI"] = "receive";
	dictionary["butsI"] = "hit";
	dictionary["kerI"] = "kick";
	dictionary["shaberI"] = "talk";
	dictionary["yarI"] = "do";
	dictionary["yorokobI"] = "enjoy";
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

		if (expected == PERIOD) {
			fout << endl;
		}

		return true;              // say there was a match
	}
}

// ** Done by: Jack Wang
//Finds the English translation of the current saved_lexeme in the dictionary, if such a translation exists.
void Parser::getEword() {
	unordered_map<string, string>::const_iterator eword = dictionary.find(saved_lexeme);
	if (eword == dictionary.end()) {
		cout << "No English translation found for " << saved_lexeme << "." << endl;
		saved_eword = saved_lexeme;
	}
	else {
		saved_eword = eword->second;
		cout << "English translation of " << saved_lexeme << ": " << saved_eword << endl;
	}
	
	/*
	saved_eword = saved_lexeme;
	for (int i = 0; i < dictionary.size(); i++) {
		if (dictionary[i].key == saved_lexeme) {
			saved_eword = dictionary[i].value;
			cout << "English translation of " << saved_lexeme << ": " << saved_eword << endl;
		}
	}
	*/
}

// ** Done by: Marcus Jackson
// Outputs the internal representation of each Japanese word in a sentence. 
void Parser::gen(gentype type) {
	switch (type) {
	case CONN:
		fout << "CONNECTOR:\t" << saved_eword << endl; break;
	case ACTR:
		fout << "ACTOR:\t" << saved_eword << endl; break;
	case DESC: 
		fout << "DESCRIPTION:\t" << saved_eword << endl; break;
	case OBJ: 
		fout << "OBJECT:\t" << saved_eword << endl; break;
	case ACTN: 
		fout << "ACTION:\t" << saved_eword << endl; break;
	case TO:
		fout << "TO:\t" << saved_eword << endl; break;
	case TNSE:
		fout << "TENSE:\t" << tokenNames[(int)saved_token] << endl; break;
	default:
		fout << saved_eword << endl; break;
	}
}

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// ** Done by: Jack Wang
void Parser::syntaxerror1(tokentype expected, string lexeme) {
	cout << "SYNTAX ERROR: expected " << tokenNames[(int)expected] << " but found " << lexeme << endl;

	cin.clear(); cin.ignore(); cin.get();
	
	exit(1);
}
void Parser::syntaxerror2(string functionName, string lexeme) {
	cout << "SYNTAX ERROR: unexpected " << lexeme << " found in " << functionName << endl;

	cin.clear(); cin.ignore(); cin.get();

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
		case PRONOUN:
			match(PRONOUN); break;
		default:
			syntaxerror2("noun()", saved_lexeme);
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

//<afterObject> ::= <verb> <tense>PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
/*
Case 1: <after object> ::= <verb> #getEword# #gen (ACTION)# <tense> #gen(TENSE)# PERIOD
Case 2: <after object> ::= <noun> #getEword# DESTINATION #gen(TO)#
<verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD
*/
void Parser::afterObject()
{
	cout << "Processing <afterObject>" << endl;
	switch (next_token())
	{
	case WORD2:
	{
		verb(); getEword(); gen(ACTN);
		tense(); gen(TNSE);
		match(PERIOD);
		break;
	}
	case WORD1:
	{
		noun(); getEword();
		match(DESTINATION); gen(TO);
		verb(); getEword(); gen(ACTN);
		tense(); gen(TNSE);
		match(PERIOD);
		break;
	}
	case PRONOUN: //same rules as WORD1
	{
		noun(); getEword();
		match(DESTINATION); gen(TO);
		verb(); getEword(); gen(ACTN);
		tense(); gen(TNSE);
		match(PERIOD);
		break;

	}
	default:
		syntaxerror2("afterObject()", saved_lexeme);
	}
}

//<afterNoun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <afterOject>
/*
Case 1: <after noun> ::= <be> #gen(DESCRIPTION)# #gen(TENSE)# PERIOD
Case 2: <after noun> ::= DESTINATION #gen(TO)# <verb> #getEword# #gen(ACTION)# 
						<tense> #gen(TENSE)# PERIOD
Case 3: <after noun> ::= OBJECT #gen(OBJECT)# <verb> #getEword# #gen (ACTION)# 
						<tense> #gen(TENSE)# PERIOD
Case 4: <after noun> ::= OBJECT #gen(OBJECT)# <noun> #getEword# DESTINATION #gen(TO)# 
						<verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD
*/
void Parser::afterNoun()
{
	cout << "Processing <afterNoun>" << endl;
	switch (next_token())
	{
		case IS :
		{
			be(); gen(DESC); gen(TNSE);
			match(PERIOD);
			break;
		}

		case WAS : //same rules as IS
		{
			be(); gen(DESC); gen(TNSE);
			match(PERIOD);
			break;
		}

		case DESTINATION :
		{
			match(DESTINATION); gen(TO); 
			verb(); getEword(); gen(ACTN);
			tense(); gen(TNSE);
			match(PERIOD);
			break;
		}

		case OBJECT :
		{
			match(OBJECT); gen(OBJ);
			afterObject();
			break;
		}
		default:
			syntaxerror2("afterNoun()", saved_lexeme);
	}
}

//<afterSubject> ::= <verb> <tense> PERIOD | <noun> <afterNoun>
/*
Case 1: <after noun> :: = <be> #gen(DESCRIPTION)# #gen(TENSE)# PERIOD
Case 2: <after noun> :: = DESTINATION #gen(TO)# <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD
Case 3: <after noun> :: = OBJECT #gen(OBJECT)# <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD
Case 4: <after noun> :: = OBJECT #gen(OBJECT)# <noun> #getEword# DESTINATION #gen(TO)# <verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD
*/
void Parser::afterSubject()
{
	cout << "Processing <afterSubject>" << endl;
	switch (next_token())
	{
		case WORD2 :
		{
			verb(); getEword(); gen(ACTN);
			tense(); gen(TNSE);
			match(PERIOD);
			break;
		}

		case WORD1 :
		{
			noun(); getEword();
			afterNoun();
			break;
		}

		case PRONOUN : //same rules as WORD1
		{
			noun(); getEword();
			afterNoun();
			break;
		}
		default:
			syntaxerror2("afterSubject()", saved_lexeme);
	}
}

//<s> ::= [CONNECTOR]<noun> SUBJECT <afterSubject>
/*
Case 1: <s> ::=  [CONNECTOR #getEword# #gen(CONNECTOR)#] <noun> #getEword# SUBJECT #gen(ACTOR)# 
					<verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD
Case 2: <s> ::=  [CONNECTOR #getEword# #gen(CONNECTOR)#] <noun> #getEword# SUBJECT #gen(ACTOR)# 
					<noun> #getEword# <be> #gen(DESCRIPTION)# #gen(TENSE)# PERIOD
Case 3: <s> ::=  [CONNECTOR #getEword# #gen(CONNECTOR)#] <noun> #getEword# SUBJECT #gen(ACTOR)# 
					<noun> #getEword# DESTINATION #gen(TO)# <verb> #getEword# #gen(ACTION)# 
					<tense> #gen(TENSE)# PERIOD
Case 4: <s> ::=  [CONNECTOR #getEword# #gen(CONNECTOR)#] <noun> #getEword# SUBJECT #gen(ACTOR)# 
					<noun> #getEword# OBJECT #gen(OBJECT)# <verb> #getEword# #gen(ACTION)# 
					<tense> #gen(TENSE)# PERIOD
Case 5: <s> ::=  [CONNECTOR #getEword# #gen(CONNECTOR)#] <noun> #getEword# SUBJECT #gen(ACTOR)# 
					<noun> #getEword# OBJECT #gen(OBJECT)# <noun> #getEword# DESTINATION #gen(TO)# 
					<verb> #getEword# #gen(ACTION)# <tense> #gen(TENSE)# PERIOD
*/
void Parser::s()
{
	cout << "Processing <s>" << endl;
	switch (next_token())
	{
		case CONNECTOR :
		{
			match(CONNECTOR); getEword(); gen(CONN);
			noun(); getEword();
			match(SUBJECT); gen(ACTR);
			afterSubject();
			break;
		}

		case WORD1 :
		{
			noun(); 
			getEword();
			match(SUBJECT);
			gen(ACTR);
			afterSubject();
			break;
		}

		case PRONOUN :
		{
			noun(); 
			getEword(); 
			match(SUBJECT);
			gen(ACTR);
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

	fout.close();

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