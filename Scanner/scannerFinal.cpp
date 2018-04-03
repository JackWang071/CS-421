#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>

#include <unordered_map>

using namespace std;

// Period DFA
// Done by: Jonathan
bool periodToken(string s) 
{
	string state = "q0";

	for (int i = 0; i < s.length(); i++) {
		if (state == "q0" && s[i] == '.') {
			state = "qf";
		}
		else {
			return false;
		}
	}

	if (state == "qf") {
		return true;
	}
}

// WordToken DFA 
// Done by:
// RE:
bool wordToken(string s) 
{
	char c;
	char prevc;
	bool stuck = false;

	string state = "q0";

	// Very large combination of states.
	string every[] = { "q0", "v", "s", "t", "spc", "nsc", "cs_h", "t_s", "spc_y" };
	// Common combination of states.
	string q0_v[] = { "q0", "v" };
	// All legitimate characters for this scanner.
	string vowels = "aeiouAEIOU";
	string v_n = "nN";
	string s_ = "sS";
	string c_ = "cC";
	string cs_h = "hH";
	string t_ = "tT";
	string t_s = "sS";
	string spc_cons = "bghkmnprBGHKMNPR";
	string spc_cons_y = "yY";
	string nonspc_cons = "djwyzDJWYZ";

	//
	for (int i = 0; i < s.length(); i++) {
		c = s[i];

		//Print the current character.
		//cout << "\t" << c << ": ";

		// Trs({q0, v, s, t, spc, nsc, cs_h, t_s, spc_y}, {'a', 'e', 'i', 'o', 'u'}) = v
		if ((find(begin(every), end(every), state) != end(every)) && vowels.find(c) != string::npos) {
			state = "v";
		}
		// Trs({v}, {'n'}) = q0
		else if ((state == "v") && v_n.find(c) != string::npos) {
			state = "q0";
		}
		// Trs({q0, v}, {'s'}) = s
		else if (find(begin(q0_v), end(q0_v), state) != end(q0_v) && s_.find(c) != string::npos) {
			state = "s";
		}
		// Trs({q0, v}, {'c'}) = c
		else if (find(begin(q0_v), end(q0_v), state) != end(q0_v) && c_.find(c) != string::npos) {
			state = "c";
		}
		// Trs({q0, v}, {'t'}) = t
		else if (find(begin(q0_v), end(q0_v), state) != end(q0_v) && t_.find(c) != string::npos) {
			state = "t";
		}
		// Trs({q0, v}, {'d', 'j', 'w', 'y', 'z'}) = nsc
		else if (find(begin(q0_v), end(q0_v), state) != end(q0_v) && nonspc_cons.find(c) != string::npos) {
			state = "nsc";
		}
		// Trs({q0, v}, {'b', 'g', 'h', 'k', 'm', 'n', 'p', 'r'}) = spc
		else if (find(begin(q0_v), end(q0_v), state) != end(q0_v) && spc_cons.find(c) != string::npos) {
			state = "spc";
		}
		// Trs({spc}, {'y'}) = spc_y
		else if (state == "spc" && spc_cons_y.find(c) != string::npos) {
			state = "spc_y";
		}
		// Trs({c}, {'s'}) = cs_h
		else if ((state == "c" || state == "s") && cs_h.find(c) != string::npos) {
			state = "cs_h";
		}
		// Trs({t}, {'s'}) = t_s
		else if (state == "t" && t_s.find(c) != string::npos) {
			state = "t_s";
		}
		//Error
		else {
			//cout << "\n\tStuck in state " << state << endl;
			stuck = true;
			break;
		}

		//Print the current state.
		//cout << state << endl;
	}
	if (!stuck && (state == "q0" || state == "v")) {
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
};

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
int scanner(tokenType& type, string& word)
{
	fin >> word;

	if(word == "eofm"){
		exit(0);
	}
	else if (wordToken(word)) {
		unordered_map<string,tokenType>::const_iterator pair = reservedWords.find(word);
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