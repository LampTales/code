#pragma once
#include <iostream>
#include <vector>

using namespace std;

string add(string const a, string const b);
string addP(string const a, string const b);
string mul(string const a, string const b);

struct Num {  // finish
    string num;
    bool sign;

    friend ostream& operator<<(ostream& out, Num& num);
    Num operator+(Num n2);
    Num operator-(Num n2);
    Num operator*(Num n2);
    Num operator/(Num n2);
};
Num createNum(string str);
Num createNumWall(string str);
Num createNum(int num);
void printNum(Num num);  // finish

struct Ver {  // finish
    char name;
    Num value;
};
Ver createVer(char name, string value);  // finish

string trim(string str);  // finish

bool veriDef(vector<Ver>& veris, string str);  // finish

int dotSpot(Num num); // finish

void align(Num n1, Num n2, Num& a, Num& b); // finish

string subZero(string str);

bool bigger(string const a, string const b); // finish

bool compare(Num n1, Num n2);

string getCom(string str); // finish

int getHighest(string str);

int magni(string a, string b);

Num pow(Num num, int i);

int cntFM(string num);
string fixF(string num);

string moving(string ori, int move);

string fixE(string str);

Num sqt(Num num);