#include<iostream>
#include<fstream>
#include<string>
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

// The test driver to start the parser
// Done by  **
int main()
{
	//- opens the output file translated.txt
	//- opens the input file
	//- calls the <story> to start parsing
	//- closes the input file 
	//- closes traslated.txt

	string input; //input from the user
	string word; //word to be stored from the file

	cout << "Enter the filename: "; //getting the file name
	cin >> input;

	ofstream fileOut;
	fileOut.open("translated.txt");

	Parser test(input);

	fileOut.close();

	//- opens the input file
	//- calls the <story> to start parsing
	//- closes the input file 
	return 0;
}// end



