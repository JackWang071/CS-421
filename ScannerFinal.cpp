#include <iostream>
#include <fstream>
#include <string>

#include <unordered_map>

using namespace std;

// Period DFA
// Done by: Jonathan
bool periodToken(string s) 
{
	string state = "q0";

	for (int i = 0; i < s.length(); i++) {
		if (state = "q0" && s[i] = '.') {
			state = "qf";
		}
		else {
			return false;
		}
	}

	if (state = "qf") {
		return true;
	}
}

// WordToken DFA 
// Done by:
// RE:
bool wordToken(string s) 
{
	char c;

	string state = "q0";
	/* 
		Possible states:
		q0 (c == 'n')
		v (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
		c (c == 'c')
		s (c == 's')
		cs_h (c == 'h')
		t (c == 't')
		t_s (c == 's')
		spc (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' || c == 'n' || c == 'p' || c == 'r')
		spc_y (c == 'y')
		nsc (c == 'd' || c == 'j' || c == 'w' || c == 'y' || c == 'z')
	*/

	for (int i = 0; i < s.length(); i++) {
		c = s[i];
		cout << c << ": ";

		// Trs({q0, v, s, t, spc, nsc, cs_h, t_s, spc_y}, {'a', 'e', 'i', 'o', 'u'}) = v
		if ((state == "q0" || state == "v" || state == "s" || state == "t" || state == "spc" || state == "nsc" || state == "cs_h" || state == "t_s" || state == "spc_y")
			&& (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')) 
		{
			state = "v";
		}
		// Trs({v}, {'n'}) = q0
		else if (state == "v" && c == 'n') {
			state = "q0";
		}
		// Trs({q0, v}, {'s'}) = s
		else if ((state == "q0" || state == "v") && c == 's') {
			state = "s";
		}
		// Trs({q0, v}, {'c'}) = c
		else if ((state == "q0" || state == "v") && c == 'c') {
			state = "c";
		}
		// Trs({q0, v}, {'t'}) = t
		else if ((state == "q0" || state == "v") && (c == 't')) {
			state = "t";
		}

		else if ((state == "q0" || state == "v") && (c == 'd' || c == 'j' || c == 'w' || c == 'y' || c == 'z')) {
			state = "nsc";
		}

		else if ((state == "q0" || state == "v") && (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' || c == 'n' || c == 'p' || c == 'r')) {
			state = "spc";
		}

		else if (state == "spc" && c == 'y') {
			state = "spc_y";
		}

		else if ((state == "c" || state == "s") && c == 'h') {
			state = "cs_h";
		}

		else if (state == "t" && c == 's') {
			state = "t_s";
		}

		else {
			cout << "\nStuck in state " << state;
			break;
		}

		cout << state << endl;
	}
	if (state == "q0" || state == "v") {
		return true;
	}
	return false;
}

// --------------------------------------------------------------

ifstream fin;
enum tokenType {ERROR, WORD1, WORD2, PERIOD, VERB, VERBNEG, VERBPAST, VERBPASTNEG, IS, 
WAS, OBJECT, SUBJECT, DESTINATION, PRONOUN, CONNECTOR, EOFM};
unordered_map<string, tokenType> reservedWords;

string tokenNames[30] = 
{
	"ERROR", "WORD1", "WORD2", "PERIOD", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "IS", 
	"WAS", "OBJECT", "SUBJECT", "DESTINATION", "PRONOUN", "CONNECTOR", "EOFM"
}

void setUpReservedWordsTable()
{
	reservedWords["masu"] = VERB;
	reservedWords["masen"] = VERBNEG;
	reservedWords["mashita"] = VERBPAST;
	reservedWords["masendeshita"] = VERBPASTNEG;
	reservedWords["desu"] = IS;
	reservedWords["deshita"] = WAS;
	reservedWords["o"] = OBJECT;
	reservedWords["wa"] = SUBJECT;
	reservedWords["ni"] = DESTINATION;

	reservedWords["watashi"] = PRONOUN;
	reservedWords["anata"] = PRONOUN;
	reservedWords["kare"] = PRONOUN;
	reservedWords["kanojo"] = PRONOUN;
	reservedWords["sore"] = PRONOUN;

	reservedWords["mata"] = CONNECTOR;
	reservedWords["soshite"] = CONNECTOR;
	reservedWords["shikashi"] = CONNECTOR;
	reservedWords["dakara"] = CONNECTOR;

	reservedWords["eofm"] = EOFM;

}


// Scaner processes only one word at a time
// Done by: Jonathan
void scanner(tokenType& type, string& word)
{
	fin >> word;

	if (wordToken(word)) {
		auto pair = reservedWords.find(word);
		if (pair == reservedWords.end()) {
			//Not found

			if (word.back() == 'I' || word.back() == 'E') {
				type = WORD2;
			}
			else {
				type = WORD1;
			}
		}
		else {
			//Is found
			type = pair->second;
		}
	}

	else if (periodToken(word)) {
		type = PERIOD;
	}

	else {
		cout << "Lexical error" << endl;
		type = ERROR;
	}
}

int main() 
{
	tokenType type;
	string word;
	string fileName;

	setUpReservedWordsTable();

	cout << "Enter the input file name: ";
	cin >> fileName;

	fin.open(fileName.c_str());

	while (true) {
		scanner(type, word);
		cout << "Type is: " << tokenNames[type] << endl;
		cout << "Word is: " << word << endl; 
	}

	fin.close();
}