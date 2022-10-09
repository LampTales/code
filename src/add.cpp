#include <iostream>
#include <string>
#include "stuffs.hpp"

using namespace std;

string add(string const a, string const b) {
    int length = a.length();
    int carry = 0;
    string ans = "";
    for (int i = length - 1; i >= 0; i--) {
        if (a[i] == '.') {
            ans = '.' + ans;
            continue;
        }
        int sum = ((int)a[i] - 48) + ((int)b[i] - 48) + carry;
        if (sum >= 10) {
            carry = 1;
            sum -= 10;
        } else {
            carry = 0;
        }
        ans = (char)(sum + 48) + ans;
    }
    if (carry == 1) {
        ans = '1' + ans;
    }
    ans = subZero(ans);
    return ans;
}

string addP(string const a, string const b) {
    if (b == "0") {
        return subZero(a);
    }

    int length = a.length();
    int carry = 0;
    string ans = "";
    for (int i = length - 1; i >= 0; i--) {
        if (a[i] == '.') {
            ans = '.' + ans;
            continue;
        }
        int sum = ((int)a[i] - 48) + ((int)b[i] - 48) + carry;
        if (sum >= 10) {
            carry = 1;
            sum -= 10;
        } else {
            carry = 0;
        }
        ans = (char)(sum + 48) + ans;
    }
    ans = subZero(ans);
    return ans;
}