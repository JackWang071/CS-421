#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

#include "parser.h"

// CS421 File translator.cpp 

// ** Be sure to put the name of the programmer above each function
// ** Be sure to put the corresponding rule with semantic routines
//    above each function

// ** Additions to parser.cpp here:
//    getEword - using the current lexeme, look up the English word
//               in the Lexicon if it is there -- save the result   
//                 in saved_E_word
//    gen(line_type) - using the line type,
//                     display a line of an IR (saved_E_word or saved_token
//                     is used)

void switchstuff() {

	string key;
	string value;
	string token;
	int q1, q2;
	int tswitch = 0;
	vector<word> kv;
	
	ifstream fin;
	fin.open("a.txt");
	fin >> token;

	while (fin) {
		if (token != "=") {
			cout << token << ": ";
			if (tswitch == 0) {
				q1 = token.find("\"", 0);
				q2 = token.find("\"", q1 + 1);
				if (q1 >= 0 && q2 >= 0) {
					key = token.substr(q1, q2 - q1 + 1);
				}
				tswitch = 1;
				cout << key << endl;
			}
			else if (tswitch == 1) {
				q1 = token.find("\"", 0);
				q2 = token.find("\"", q1 + 1);
				if (q1 >= 0 && q2 >= 0) {
					value = token.substr(q1, q2 - q1 + 1);
				}
				tswitch = 0;
				kv.push_back(word(key, value));
				cout << value << endl;
			}
		}
		fin >> token;
	}
	fin.close();

	cout << "Read done." << endl;

	ofstream fout;
	fout.open("b.txt");
	for (int i = 0; i < kv.size(); i++) {
		fout << "\tdictionary.push_back(word(" << kv[i].key << ", " << kv[i].value << "));" << endl;
	}
	fout.close();

	cout << "Write done." << endl;
}


// The test driver to start the parser
// Done by  ** Jack Wang
int main()
{
	//switchstuff();
	//cin.clear(); cin.ignore(); cin.get();

	//- opens the output file translated.txt
	//- opens the input file
	//- calls the <story> to start parsing
	//- closes the input file 
	//- closes traslated.txt

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



