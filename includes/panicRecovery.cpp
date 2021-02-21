/*
Vanshaj Aggarwal 2018A7PS0309H
Saksham Pandey 2018A7PS0259H
Surinder Singh Virk 2018A7PS0234H
Arpit Adlakha 2018A7PS0250H
*/
#include<bits/stdc++.h>
using namespace std;

vector<char> delim1={'{','}','(',')','[',']',';',','};//delimiter array
bool isdelim1(char ch)   //simple function to check if character is a delimiter
{
	for(int i=0;i<delim1.size();i++)
	{
		if(delim1[i]==ch)
			return true;
	}
	return false;
}

int goPanic(int c,string &s)          //This is the panic recovery function, which increments end pointer to either end of string or to a well defined token which in our language we have chosen as any delimiter
{
    while(c!=s.size()&&!isdelim1(s[c]))
        c++;
    return c;
}