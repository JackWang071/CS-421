#pragma once
#ifndef parser_H
#define parser_H

#include<iostream>
#include<string>
#include<vector>
using namespace std;

#include "scanner.h"

enum gentype { CONN, ACTR, DESC, OBJ, TO, ACTN, TNSE };
/*
CONN: CONNECTOR
ACTR: ACTOR
DESC: DESCRIPTION
OBJ: OBJECT
TO: TO
ACTN: ACTION
TNSE: TENSE
*/

struct word {
	string jp; //Japanese word
	string en; //English translation
	//Constructor
	word(string j, string e) {
		jp = j;
		en = e;
	}
};

class Parser {
private:
	bool token_available;
	tokentype saved_token;
	string saved_lexeme;
	Scanner scanner;
	gentype saved_gentype;
	vector<word> dictionary;
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

	void setupDict();
};


#endif // !parser_H
