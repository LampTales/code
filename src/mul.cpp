#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "stuffs.hpp"

using namespace std;

string fixHeadZero(string num) {
    int length = num.length();
    int nonzero = 0;
    for (int i = 0; i < length; i++) {
        if (num[i] != '0') {
            nonzero = i;
            break;
        }
    }

    return num.substr(nonzero);
}

string mul(string const a, string const b) {
    string stra = a;
    string strb = b;
    int move = 0;
    if (dotSpot(createNum(stra)) != -1) {
        move += cntFM(stra);
        stra = fixF(stra);
    }
    if (dotSpot(createNum(strb)) != -1) {
        move += cntFM(strb);
        strb = fixF(strb);
    }
    stra = fixHeadZero(stra);
    strb = fixHeadZero(strb);
    // cout << stra << endl << strb << endl;
    // cout << "finish ini" << endl;

    const int alen = stra.length();
    const int blen = strb.length();
    const int mlen = alen + blen;
    int ans[mlen] = {0};
    for (int i = 0; i < alen; i++) {
        for (int j = 0; j < blen; j++) {
            ans[mlen - 1 - i - j] += (((int)stra[alen - 1 - i]) - 48) * (((int)strb[blen - 1 - j]) - 48);
        }
    }
    // cout << "finish raw mul" << endl;

    int temp = 0;
    for (int i = 1; i < mlen; i++) {
        temp = ans[mlen - i];
        ans[mlen - i] = temp % 10;
        ans[mlen - i - 1] += temp / 10;
    }
    // cout << "finish fixing carry" << endl;

    const int realen = (ans[0] == 0 ? mlen : mlen + 1);
    char ansc[realen] = {'\0'};
    // cout << "finish determining length" << endl;

    for (int i = 0; i <= realen - 2; i++) {
        ansc[realen - 2 - i] = (char)(ans[mlen - 1 - i] + 48);
    }
    string answer = ansc;
    // cout << "finish filling char array" << endl;

    answer = moving(answer, move);
    // cout << "finish moving" << endl;
    answer = subZero(answer);
    return answer;
}