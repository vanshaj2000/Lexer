#include<bits/stdc++.h>
#include "structures.h"
using namespace std;

bool isalpha1(char ch)//Checks if the character is a alphabet or not
{
    int v=ch;
	if(v>=65&&v<=90)//Normal ascii values are used
		return true;
	if(v>=97&&v<=122)
		return true;
	return false;
}
bool isdigit1(char ch)//Checks if the character is a digit or not
{
    int v=ch;
	if(v>=48&&v<=57)
		return true;
	return false;
}
bool isalnum1(char ch)//Checks if the character is an digit or a alphabet or none
{
    int v=ch;
	if(v>=65&&v<=90)
		return true;
	if(v>=97&&v<=122)
		return true;
	if(v>=48&&v<=57)
		return true;
	return false;
}
bool isdelim(char c,vector<char> &delim)//Checks if the character is a delimiter
{
	for(int i=0;i<delim.size();i++)
		if(delim[i]==c)
			return true;
	return false;
}
void getToken(struct Token* x,string &s,int start, vector<char> &delim)    //This function updates the value of Token object's end pointer value
{																			//The exact state diagram used is provided in the zip file
	int state=0;
	x->n=start;
	int val=s[x->n];
	while(state!=7)															//State 7 is our final state here
	{
		switch(state)														//Switch case used
		{
			case 0:															//This is the starting state, from here using our state diagram we observe where to go depending upon the starting character
			{
				if(isdelim(s[x->n],delim))									//If its a delimiter then simply go to final state as its always a seperate token
				{
					state=7;
					x->n++;
				}
				else if(isalpha1(s[x->n]))									//If its an alphabet then we go to state 1 to check if its a keyword or a user defined method or an identifier
				{
					state=1;
					x->n++;
				}
				else if(isdigit1(s[x->n]))									//If the starting is an integer then it has to be an integer or float literal
				{
					state=2;
					x->n++;
				}
				
				else if(s[x->n]=='+'||s[x->n]=='-'||s[x->n]=='*'||s[x->n]=='%'||s[x->n]=='?')	//If its a binary operator the we go to state 7 as they are always a seperate token in our language
				{
					state=7;
					x->n++;
				}
				else if(s[x->n]=='>'||s[x->n]=='<'||s[x->n]=='='||s[x->n]=='!'||s[x->n]==':'||s[x->n]=='&'||s[x->n]=='/') //If its a symbol that can have 2 of same type or can be a comment then we go to state 4
				{
					state=4;
					x->n++;
				}
				else if(val==34)											//If the starting symbol is " then we go to state 5 to handle string literal
				{
					state=5;
					x->n++;
					x->exit_code=1;
				}
				else
				{
					state=7;											//If its none of the above, that means its an illegal character and we need to show a lexical error
					x->n++;
					x->n=-1*(x->n);										//In order for main function to know that its a lexical error, the end pointer is delibrately made negative
					return;
				}
				break;
			}
			case 1:														//Here we just move forward till an alphanumeric character isnt found
			{
				while((x->n)<s.size()&&isalnum1(s[x->n]))
					x->n++;
				x->exit_code=2;
				state=7;
				break;
			}
			case 2:														//In this state we check for integer or float, if . is not encountered then we go to final state i.e. 7 otherwise to 3
			{
				while((x->n)<s.size()&&isdigit1(s[x->n]))
					x->n++;
				if(s[x->n]=='.')
				{
					state=3;
					x->n++;
				}
				else
				{
					state=7;
					x->exit_code=3;
				}
				break;
			}
			case 3:													//This state is entered if we encounter . and now it checks for a seperate integer literal that comes after . to create a float literal
			{
				while((x->n)<s.size()&&isdigit1(s[x->n]))
					x->n++;
				state=7;
				x->exit_code=4;
				break;
			}
			case 4:												//This state checks for comments or == or && operators
			{
				int p=x->n;
				if(s[p-1]=='=')
				{
					if(s[p]=='=')
						x->n++;
				}
				else if(s[p-1]=='&')
				{
					if(s[p]=='&')
						x->n++;
				}
				else if(s[p-1]=='/')
				{
					if(s[p]=='/')
						x->n=s.size()+1;
				}
				state=7;
				break;
			}
			case 5:										//this state is specifically made to handle string literals
			{
				while((x->n)<s.size()&&s[x->n]!='"')	//If we dont encounter a next " then we need to show a lexical error so we update x->n value to negative otherwise we make the whole string as a seperate token
					x->n++;
				if((x->n)>=s.size())
				{
					x->n=-1*(x->n);
					state=7;
					return;
				}
				else
				{
					x->exit_code=5;
					x->n++;
					state=7;
				}
			}
			default:
			{
			}
		}
	}
	return;
}
int typeToken(string &t,vector<string> &reserves)			//This function returns the token type
{
	for(int i=0;i<36;i++)															//If the token is a predifined keyword
	{
		if(t==reserves[i])
			return i;		
	}														//If its a new token that hasn't been encountered yet
	return -1;
}
