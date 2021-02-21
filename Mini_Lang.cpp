/*
Vanshaj Aggarwal 2018A7PS0309H
Saksham Pandey 2018A7PS0259H
Surinder Singh Virk 2018A7PS0234H
Arpit Adlakha 2018A7PS0250H
*/
#include<bits/stdc++.h>
#include "includes/token_list.h"  //Importing our own header files from includes folder in zip file
#include "includes/panicRecovery.h"
using namespace std;
int main()
{
    ifstream read("pro.marjava.txt");               //Input stream opened to read from pro.marjava.txt
    ofstream write("tokens.txt");                   //Output stream opened to print the tokens in the tokens.txt file
    string s;                                       //As our language scans code line by line, this string will be the current line
    int line_i=1;                                   // to keep count of number of lines
    while(s!="$")
    {
        getline(read,s);                            //Input read into string s
        int i;                                      // start pointer
        int j=0;                                    // end pointer, we are using the 2 pointer buffer as discussed in the class
        while(j<s.size())                           //Tokenize till we reach the end
        {
            if(s=="$")                              //If we reach EOF i.e. $ for our language then exit
                break;
			i=j;
			while(s[i]==' ')                        //Skipping white spaces
				i++;
            struct Token t;                         //object t created for structure Token
			getToken(&t,s,i,delimiters);            //From here we get the ending value for end pointer for tokenization
			j=t.n;                                  //it is given to j
            if(j<0)                                 //Panic Recovery section
            {
                write<<"Error found in "<<" Line:"<<line_i<<endl;//Prints that there is an error
                int check=goPanic(abs(j),s);        //Calls the goPanic method in our panicRecovery header file.
                j=check;                            //It returns s.size() if there is not any delimeter present
                j++;                                //advances it
            }
            else if(j>s.size())                     /*This is the case when we enter comments i.e.//(2 consecutive slash bars)*/
                continue;
            else                                    //If there are no errors or comments, then we print the token in the tokens.txt file
            {
                string tt=s.substr(i,j-i);          //By string manipulation, we get the required token by using substr function
                int nt=typeToken(tt,reserves);//This gives us the token type which it gets from typeToken method in tokens_list header file
                if(nt==-1)
                    nt=36+t.exit_code;
                write<<"Token "<<nt<<", string "<<tt<<",Line Number "<<line_i<<endl;//Here we are writing the token in the tokens.txt file
            }
        }
        line_i++;                                   // incrementing line number at the end of every line
    }
    read.close();                                   //Closing the streams
    write.close();
    return 0;
}
