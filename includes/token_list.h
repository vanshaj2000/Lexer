/*
Vanshaj Aggarwal 2018A7PS0309H
Saksham Pandey 2018A7PS0259H
Surinder Singh Virk 2018A7PS0234H
Arpit Adlakha 2018A7PS0250H
*/
#pragma once
#include<bits/stdc++.h>
#include "structures.h"         //To avoid redefination of structures.h, this header is included in the main so structures.h also gets included
using namespace std;

//All reserves and delimiters
vector<string> reserves={"int","float","boolean","string","while","until","if","else","true","false","+","-","*","/","%",":=","==",">","<",">=","<=","!=","&&","||","!","?",":","{","}","(",")","[","]",";",",","="};
vector<char> delimiters={'{','}','(',')','[',']',';',','};
//Function definitions
int isdelim(char c,vector<char> &delim);
void getToken(struct Token *x,string &s, int start,vector<char> &delim);
int typeToken(string &t,vector<string> &reserves);
