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
