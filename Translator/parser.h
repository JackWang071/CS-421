#pragma once
#ifndef parser_H
#define parser_H

#include<iostream>
#include<string>
using namespace std;

#include "scanner.h"

enum gentype { CONN, ACR, DESC, OBJ, TO, ACN, TNS };
/*
Using abbreviated names because we're lazy.
CONN: CONNECTOR
ACR: ACTOR
DESC: DESCRIPTION
OBJ: OBJECT
TO: TO
ACN: ACTION
TNS: TENSE
*/

class Parser {
private:
	bool token_available;
	tokentype saved_token;
	string saved_lexeme;
	Scanner scanner;
	string tokenNames[30] =
	{
		"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS",
		"WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"
	};

	ofstream fout;
public:
	Parser(string filename);
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

	void getEword();
	void gen(gentype type);
};


#endif // !parser_H
