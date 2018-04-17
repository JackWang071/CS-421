#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=================================================
// File parser.cpp written by Group Number: **
//=================================================

// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)

// ** Need the updated match and next_token (with 2 global vars)
 
// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function

//prototypes
void tense();
void verb();
void noun();
void afterObject();
void be();
void afterNoun();
void afterSubject();
void s();
void story();

// <tense> ::= VERBPAST | VERBPASTNEG | VERB | VERBNEG
void tense()
{
  cout << "Processing tense" << endl;

  switch(next_token())
    {
      Case VERBPAST:
	match(VERBPAST);break;
      Case VERPASTNEG:
	match(VERPASTNEG); break;
      Case VERB:
	match(VERB); break;
      Case VERBNEG:
	match(VERBNEG); break;
    }
}

// <verb> ::= WORD2
void verb()
{
  cout << "Processing verb" << endl;
  
  switch(next_token())
    {
      Case WORD2:
	match(WORD2); break;
    }
}

//<noun> ::= WORD1 | PRONOUN
void noun()
{
  cout << "Processing noun" << endl;
  
  switch(next_token())
    {
      Case WORD1:
	match(WORD1); break;
      Case PRONOUN:
	match(PRONOUN); break;
    }
}

//<afterObject> ::= <verb> <tense>PERIOD | <noun> DESTINATION <verb> <tense> PERIOD
void afterObject()
{
  cout << "Processing afterObject" << endl;
  
  switch(next_token())
    {
      Case WORD2:
	{
	  verb();
	  tense();
	  match(PERIOD);
	  break;
	}
      Case WORD1:
	{
	  noun();
	  match(DESTINATION);
	  verb();
	  tense();
	  match(PERIOD);
	  break;
	 
	}
      Case PRONOUN:
        {
          noun();
          match(DESTINATION);
          verb();
          tense();
          match(PERIOD);
          break;

        }

    }
}

//<be> ::= IS | WAS
void be()
{
  cout << "Processing be" << endl;
  
  switch(next_token())
    {
      Case IS:
	match(IS); break;

      Case WAS:
	match(WAS);break;
    }
}

//<afterNoun> ::= <be> PERIOD | DESTINATION <verb> <tense> PERIOD | OBJECT <afterOject>
void afterNoun()
{
  cout << "Processing afterNoun" << endl;
  
  switch(next_token())
    {
      Case IS:
	{
	  be();
	  match(PERIOD);
	  break;
	}

      Case WAS:
        {
          be();
          match(PERIOD);
          break;
        }

      Case DESTINATION:
	{
	  match(DESTINATION);
	  verb();
	  tense();
	  match(PERIOD);
	  break;
	}

      Case OBJECT:
	{
	  match(OBJECT);
	  afterObject();
	  break;
	}

    }
}

//<afterSubject> ::= <verb> <tense> PERIOD | <noun> <afterNoun>
void afterSubject()
{
  cout << "Processing afterSubject" << endl;
  
  switch(next)token())
  {
    Case WORD2:
      {
	verb();
	tense();
	match(PERIOD);
	break;
      }

    Case WORD1:
      {
	noun();
	afterNoun();
	break;
      }

    Case PRONOUN:
      {
        noun();
        afterNoun();
        break;
      }
  }
}

//<s> ::= [CONNECTOR]<noun> SUBJECT <afterSubject>
void s()
{
  cout << "Processing s" << endl;
  
  switch(next_token())
    {
      Case CONNECTOR:
	{
	  match(CONNECTOR);
	  noun();
	  match(SUBJECT);
	  afterSubject();
	}

      Case WORD1:
	{
	  noun();
	  match(SUBJECT);
	  afterSubject();
	}

      Case PRONOUN:
        {
          noun();
          match(SUBJECT);
          afterSubject();
        }
      
    default:
      syntax_error();

    }
  
}

//<story> ::= <s> { <s> }
void story()
{
  cout << "Processing story" << endl;

  s();
  
  while(true)
    {
      Case CONNECTOR:
	{
	  match(CONNECTOR);
	  noun();
	  match(SUBJECT);
	  afterSubject();
	  break;
	}

      Case WORD1:
	{
	  noun();
	  match(SUBJECT);
	  afterSubject();
	  break;
	}

      Case PRONOUN:
        {
          noun();
          match(SUBJECT);
          afterSubject();
          break;
        }
    default:
      syntax_error();
      
    }
}






// The test driver to start the parser
// Done by:  **
int main()
{
  fstream fin; //making the filestream
  string input; //input from the user

  string word; //word to be stored from the file

  cout << "Enter the filename:" << endl; //getting the file name
  cin >> input;

  fin.open(input.c_str(), fstream::in); //opening the file

  if(fin.is_open()) //file opened
  {
    while(fin >> word) //while there is a word store it
      {
	//story(word);
      }
  }
  else //file unable to be opened
    {
      cout << input.c_str() << " was unable to be opened." << endl;
      return 0;
    }

  fin.close(); //closing the file
  
  //- opens the input file
  //- calls the <story> to start parsing
  //- closes the input file 

}// end
//** should require no other input files!

