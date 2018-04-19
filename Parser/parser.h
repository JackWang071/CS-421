#pragma once
#ifndef parser_H
#define parser_H

#include<iostream>
#include<string>
using namespace std;

#include "scanner.h"

class Parser {
private:
	string typenames[30] =
	{
		"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS",
		"WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"
	};
	bool token_available;
	tokentype saved_token;
	Scanner scanner;
public:
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
	void syntaxerror1(tokentype expected, tokentype lexeme);
	void syntaxerror2(string functionname, tokentype expected);

	int startup();
};


#endif // !parser_H
