#include <iostream>
#include <vector>
#include "stuffs.hpp"

using namespace std;

Num createNum(string str) {
    Num num;
    if (str[0] == '-') {
        num.sign = false;
        num.num = str.substr(1);
    } else if (str[0] == '+') {
        num.sign = true;
        num.num = str.substr(1);
    } else {
        num.sign = true;
        num.num = str;
    }
    // cout << num << endl;
    return num;
}

Num createNumWall(string str) {
    Num num;
    if (str.length() == 0) {
        num.sign = true;
        // cout << "*" << endl;
        num.num = "N";
        return num;
    }

    if (str[0] == '-') {
        num.sign = false;
        num.num = str.substr(1);
    } else if (str[0] == '+') {
        num.sign = true;
        num.num = fixE(str.substr(1));
    } else {
        num.sign = true;
        num.num = fixE(str);
    }
    // cout << num << endl;
    return num;
}

Num createNum(int num) {
    string str = to_string(num);
    return createNum(str);
}

Ver createVer(char name, string str) {
    Ver ver;
    ver.name = name;
    ver.value = createNum(str);
    return ver;
}

void printNum(Num num) {
    if (!num.sign) {
        cout << "-";
    }
    cout << num.num << endl;
}

ostream& operator<<(ostream& out, Num& num) {
    if (num.num != "0") {
        out << (num.sign ? "" : "-") << num.num;
    } else {
        out << "0";
    }

    return out;
}

Num Num::operator+(Num n2) {
    Num n1 = *this;
    Num a = n1;
    Num b = n2;
    align(n1, n2, a, b);
    // cout << a << "  " << b << endl;
    if (a.sign == b.sign) {
        Num num = createNum(add(a.num, b.num));
        num.sign = a.sign;
        // cout << "+= " << num << endl;
        return num;
    } else {
        if (bigger(a.num, b.num)) {
            // cout << "before 1 getCom" << endl;
            b.num = getCom(b.num);
            Num num = createNum(addP(a.num, b.num));
            num.sign = a.sign;
            return num;
        } else {
            // cout << "before 2 getCom" << endl;
            a.num = getCom(a.num);
            Num num = createNum(addP(b.num, a.num));
            num.sign = b.sign;
            return num;
        }
    }
}
Num Num::operator-(Num n2) {
    Num re2 = n2;
    re2.sign = !re2.sign;
    // cout << "before add" << endl;
    return *this + re2;
}
Num Num::operator*(Num n2) {
    Num num = createNum(mul(this->num, n2.num));
    num.sign = (this->sign == n2.sign);
    // cout << "*= " << num << endl;
    return num;
}
Num Num::operator/(Num n2) {
    Num a = *this;
    Num b = n2;
    a.num = subZero(this->num);
    b.num = subZero(n2.num);
    if (b.num == "0") {
        cout << "you can't divide a num by 0! The answer is given zero!" << endl;
        Num num = {"0", true};
    }
    a.sign = true;
    b.sign = true;
    Num ans = createNum(0);
    for (int i = magni(a.num, b.num); i > -9; i--) {
        // cout << "Now i = " << i << endl;
        Num step = pow(b, i);
        for (int m = 1; m < 10; m++) {
            bool conti = compare(a, step);
            if (conti) {
                a = a - step;
            } else {
                ans = ans + pow(createNum(1), i) * createNum(m - 1);
                // cout << "Now ans = " << ans << endl;
                break;
            }
        }
    }
    ans.num = subZero(ans.num);
    ans.sign = (this->sign == n2.sign);
    return ans;
}

Num sqt(Num num) {
    int digit = getHighest(num.num);
    if (num.sign == false) {
        cout << "function sqt does not support negative number! The answer is given zero!" << endl;
        Num num = {"0", true};
        return num;
    }
    Num ans = createNum(0);
    for (int i = digit; i > -9; i--) {
        // cout << "Now i = " << i << endl;
        Num step = pow(createNum(1), i);
        for (int m = 1; m < 10; m++) {
            bool conti = compare(num, (step + ans) * (step + ans));
            if (conti) {
                ans = ans + step;
            } else {
                break;
            }
        }
    }
    ans.num = subZero(ans.num);
    ans.sign = true;
    return ans;
}