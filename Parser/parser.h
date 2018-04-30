#pragma once
#ifndef parser_H
#define parser_H

#include<iostream>
#include<string>
using namespace std;

#include "scanner.h"

class Parser {
private:
	bool token_available;
	tokentype saved_token;
	string lexeme;
	Scanner scanner;
	string tokenNames[30] =
	{
		"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS",
		"WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"
	};
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
};


#endif // !parser_H
