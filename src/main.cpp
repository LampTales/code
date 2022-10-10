#include <iostream>
#include <vector>
#include "stuffs.hpp"

using namespace std;

Num getNum(int& pos, string const str, vector<Ver> veris) {
    bool reverse = false;
    if (str[pos] == '-') {
        reverse = true;
        pos++;
    } else if (str[pos] == '+') {
        pos++;
    } else if (str[pos] == '*' || str[pos] == '/') {
        Num err = {"N", true};
        return err;
    }

    for (int v = 0; v < (int)veris.size(); v++) {
        if (str[pos] == veris[v].name) {
            pos++;
            Num x = veris[v].value;
            if (reverse) {
                x.sign = !x.sign;
            }
            return x;
        }
    }

    int i = 0;
    bool hasdot = false;
    int espot = -2;
    bool hasEsign = false;
    for (i = pos; i < (int)str.length(); i++) {
        // cout << str[i] << endl;
        if (str[i] >= '0' && str[i] <= '9') {
            // cout << str[i] << endl;
            continue;
        } else if (str[i] == '.' && i != pos && !hasdot) {
            hasdot = true;
        } else if ((str[i] == 'e' || str[i] == 'E') && espot == -2 && i != pos) {
            espot = i;
        } else if ((str[i] == '+' || str[i] == '-') && espot == i - 1 && !hasEsign) {
            hasEsign = true;
        } else {
            break;
        }
    }
    Num num = createNumWall(str.substr(pos, i - pos));
    pos = i;
    // cout << num << endl;
    if (reverse) {
        num.sign = !num.sign;
    }

    return num;
}

Num calculate(vector<Ver> veris, string const str) {
    vector<Num> nums;
    vector<char> oprs;
    int pos = 0;
    bool needNum = true;
    while (pos < (int)str.length()) {
        if (str[pos] == ' ') {
            pos++;
            continue;
        }
        if (needNum) {  // find a num
            if (str[pos] == '(') {
                oprs.push_back('(');
                pos++;
            } else if (pos <= str.length() - 5 && str.substr(pos, 5) == "sqrt(") {
                oprs.push_back('s');
                pos += 5;
            } else {
                // cout << "*" << endl;
                Num num = getNum(pos, str, veris);
                if (num.num[0] == 'N') {
                    return num;
                }
                nums.push_back(num);  // do something!!!
                needNum = false;
            }
        } else {  // deal with operators
            char op = str[pos];
            if (op == '*' or op == '/') {
                while (oprs.size() != 0) {
                    char preP = oprs.back();
                    if (preP == '*') {
                        Num n2 = nums.back();
                        nums.pop_back();
                        Num n1 = nums.back();
                        nums.pop_back();
                        Num ans = n1 * n2;
                        nums.push_back(ans);
                        oprs.pop_back();
                    } else if (preP == '/') {
                        Num n2 = nums.back();
                        nums.pop_back();
                        Num n1 = nums.back();
                        nums.pop_back();
                        Num ans = n1 / n2;
                        nums.push_back(ans);
                        oprs.pop_back();
                    } else {
                        break;
                    }
                }
                oprs.push_back(op);
                pos++;
                needNum = true;
            } else if (op == '+' or op == '-') {
                while (oprs.size() != 0) {
                    char preP = oprs.back();
                    if (preP == '*') {
                        Num n2 = nums.back();
                        nums.pop_back();
                        Num n1 = nums.back();
                        nums.pop_back();
                        Num ans = n1 * n2;
                        nums.push_back(ans);
                        oprs.pop_back();
                    } else if (preP == '/') {
                        Num n2 = nums.back();
                        nums.pop_back();
                        Num n1 = nums.back();
                        nums.pop_back();
                        Num ans = n1 / n2;
                        nums.push_back(ans);
                        oprs.pop_back();
                    } else if (preP == '+') {
                        Num n2 = nums.back();
                        nums.pop_back();
                        Num n1 = nums.back();
                        nums.pop_back();
                        Num ans = n1 + n2;
                        nums.push_back(ans);
                        oprs.pop_back();
                    } else if (preP == '-') {
                        Num n2 = nums.back();
                        nums.pop_back();
                        Num n1 = nums.back();
                        nums.pop_back();
                        Num ans = n1 - n2;
                        nums.push_back(ans);
                        oprs.pop_back();
                    } else {
                        break;
                    }
                }
                oprs.push_back(op);
                pos++;
                needNum = true;
            } else if (op == ')') {
                if (oprs.size() == 0) {
                    Num err = {"N", true};
                    return err;
                }
                while (true) {
                    char preP = oprs.back();

                    if (preP == '*') {
                        Num n2 = nums.back();
                        nums.pop_back();
                        Num n1 = nums.back();
                        nums.pop_back();
                        Num ans = n1 * n2;
                        nums.push_back(ans);
                        oprs.pop_back();
                    } else if (preP == '/') {
                        Num n2 = nums.back();
                        nums.pop_back();
                        Num n1 = nums.back();
                        nums.pop_back();
                        Num ans = n1 / n2;
                        nums.push_back(ans);
                        oprs.pop_back();
                    } else if (preP == '+') {
                        Num n2 = nums.back();
                        nums.pop_back();
                        Num n1 = nums.back();
                        nums.pop_back();
                        Num ans = n1 + n2;
                        nums.push_back(ans);
                        oprs.pop_back();
                    } else if (preP == '-') {
                        Num n2 = nums.back();
                        nums.pop_back();
                        Num n1 = nums.back();
                        nums.pop_back();
                        Num ans = n1 - n2;
                        nums.push_back(ans);
                        oprs.pop_back();
                    } else if (preP == 's') {
                        Num n1 = nums.back();
                        nums.pop_back();
                        Num ans = sqt(n1);
                        nums.push_back(ans);
                        oprs.pop_back();
                        break;
                    } else {
                        oprs.pop_back();
                        break;
                    }
                    if (oprs.size() == 0) {
                        Num err = {"N", true};
                        return err;
                    }
                }
                pos++;
            } else {
                Num err = {"N", true};
                return err;
            }
        }
    }
    // empty stack
    while (oprs.size() != 0) {
        char preP = oprs.back();
        if (preP == '*') {
            Num n2 = nums.back();
            nums.pop_back();
            Num n1 = nums.back();
            nums.pop_back();
            Num ans = n1 * n2;
            nums.push_back(ans);
            oprs.pop_back();
        } else if (preP == '/') {
            Num n2 = nums.back();
            nums.pop_back();
            Num n1 = nums.back();
            nums.pop_back();
            Num ans = n1 / n2;
            nums.push_back(ans);
            oprs.pop_back();
        } else if (preP == '+') {
            Num n2 = nums.back();
            nums.pop_back();
            Num n1 = nums.back();
            nums.pop_back();
            Num ans = n1 + n2;
            nums.push_back(ans);
            oprs.pop_back();
        } else if (preP == '-') {
            Num n2 = nums.back();
            nums.pop_back();
            Num n1 = nums.back();
            nums.pop_back();
            Num ans = n1 - n2;
            nums.push_back(ans);
            oprs.pop_back();
        } else {
            Num err = {"N", true};
            return err;
        }
    }
    return nums.back();
}

int main() {
    vector<Ver> veris;
    cout << "Welcome!\n"
         << "enter a formula to compute;\n"
         << "enter a variable and its value in format \"x = ?\" to add a variable;\n"
         << "enter \"end\" to end the calculator."
         << endl;
    while (true) {
        string str;
        getline(cin, str);
        if (str == "end") {
            break;
        } else if (veriDef(veris, str)) {
            continue;
        } else {
            Num num = calculate(veris, str);
            if (num.num[0] != 'N') {
                cout << "The answer is: " << num << endl;
            } else {
                cout << "The formula is illegal! Please check your input!" << endl;
            }
        }
    }
    cout << "Calculator stop!" << endl;

    // string str;
    // getline(cin, str);
    // veriDef(veris, str);
    // // Ver ver;
    // // ver.name = 'a';
    // // ver.value = {"12345", false};
    // // veris.push_back(ver);
    // cout << veris.size() << endl;
    // Ver ver = veris.back();
    // cout << ver.name << '=' << ver.value.num << endl;

    // Num n1;
    // Num n2;
    // cout << (n1 + n2).sign << (n1 + n2).num << endl;
    // string s = "123456";
    // s.substr(3);
    // cout << s << endl;

    // Num a = createNum("-5.22");
    // Num b = createNum("-5622.196851");
    // a = a + b;
    // Num a = createNum(3);
    // cout << a << endl;
    return 0;
}