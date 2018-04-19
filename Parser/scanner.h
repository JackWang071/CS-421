#pragma once
#ifndef scanner_H
#define scanner_H

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <unordered_map>

using namespace std;

enum tokentype {
	ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS,
	WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM
};

class Scanner {
private:
	ifstream fin;
	unordered_map<string, tokentype> reservedWords;
	string tokenNames[30] =
	{
		"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS",
		"WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"
	};
public:
	Scanner();
	bool openfile(string filename);
	int scanner(tokentype& type, string& word);
	void setUpReservedWordsTable();
	bool periodToken(string s);
	bool wordToken(string s);

};

#endif // !scanner_H
