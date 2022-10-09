#include <iostream>
#include <string>
#include "stuffs.hpp"

using namespace std;

string trim(string str) {  // finish
    int p1 = str.find_first_not_of(" ");
    int p2 = str.find_last_not_of(" ") + 1;
    // cout << str.substr(p1, p2 - p1) << endl;
    // cout << str.substr(p1, p2 - p1).length() << endl;
    return str.substr(p1, p2 - p1);
}

bool veriDef(vector<Ver>& veris, string str) {  // finish
    char name = str[0];

    if (str.length() < 2) {
        return false;
    }

    str = trim(str.substr(1));
    if (str[0] != '=') {
        return false;
    }

    if (!((int)name > 64 && (int)name < 91) && !((int)name > 96 && (int)name < 123)) {
        cout << "this is an illegal variable name!" << endl;
        return true;
    }
    // cout << str.substr(2) << endl;
    string numStr = trim(str.substr(1));
    Ver ver = createVer(name, numStr);

    for (int i = 0; i < (int)veris.size(); i++) {
        if (veris[i].name == ver.name) {
            veris[i] = ver;
            cout << "An existing variable is re-assigned!" << endl;
            return true;
        }
    }

    veris.push_back(ver);
    cout << "A new variable added!" << endl;
    return true;
}

int dotSpot(Num num) {
    for (int i = 0; i < (int)num.num.length(); i++) {
        if (num.num[i] == '.') {
            return i;
        }
    }
    return -1;
}

void align(Num n1, Num n2, Num& a, Num& b) {
    int dot1 = dotSpot(n1);
    int dot2 = dotSpot(n2);
    if (dot1 == -1 && dot2 == -1) {
        if (n1.num.length() >= n2.num.length()) {
            for (int i = 0; i < (int)(n1.num.length() - n2.num.length()); i++) {
                b.num = "0" + b.num;
            }
        } else {
            for (int i = 0; i < (int)(n2.num.length() - n1.num.length()); i++) {
                a.num = "0" + a.num;
            }
        }
    } else {
        // append dot
        if (dot1 == -1) {
            a.num = a.num + ".";
            dot1 = n1.num.length();
        } else if (dot2 == -1) {
            b.num = b.num + ".";
            dot2 = n2.num.length();
        }
        int cnt = (int)(a.num.length() - 1 - dot1) - (int)(b.num.length() - 1 - dot2);
        // fix before dot
        if (dot1 >= dot2) {
            for (int i = 0; i < dot1 - dot2; i++) {
                b.num = "0" + b.num;
            }
        } else {
            for (int i = 0; i < dot2 - dot1; i++) {
                a.num = "0" + a.num;
            }
        }
        // fix after dot
        if (cnt >= 0) {
            for (int i = 0; i < cnt; i++) {
                b.num = b.num + "0";
            }
        } else {
            cnt = -cnt;
            for (int i = 0; i < cnt; i++) {
                a.num = a.num + "0";
            }
        }
    }
}

string subZero(string str) {
    // zero before dot
    for (int i = 0; i < (int)str.length(); i++) {
        if (str[i] != '0') {
            if (str[i] == '.') {
                str = str.substr(i - 1);
                break;
            } else {
                str = str.substr(i);
                break;
            }
        }
    }
    // zero after dot
    int dot = dotSpot(createNum(str));
    if (dot != -1) {
        for (int i = str.length() - 1; i >= dot; i--) {
            if (str[i] != '0') {
                str = (str[i] == '.') ? str.substr(0, i) : str.substr(0, i + 1);
                break;
            }
        }
    }
    return str;
}

bool bigger(string const a, string const b) {
    int length = a.length();
    for (int i = 0; i < length; i++) {
        if (a[i] > b[i]) {
            return true;
        } else if (a[i] < b[i]) {
            return false;
        }
    }
    return true;
}

bool compare(Num n1, Num n2) {
    Num a = n1;
    Num b = n2;
    align(n1, n2, a, b);
    return bigger(a.num, b.num);
}

string getCom(string str) {
    string ans = "";
    bool ex = true;
    for (int i = str.length() - 1; i >= 0; i--) {
        if (str[i] == '.') {
            ans = '.' + ans;
            continue;
        }

        if (ex) {
            if (str[i] == '0') {
                ans = '0' + ans;
            } else {
                ans = (char)(10 - ((int)str[i] - 48) + 48) + ans;
                ex = false;
            }
        } else {
            ans = (char)(9 - ((int)str[i] - 48) + 48) + ans;
        }
    }
    // cout << "C finish " << ans << endl;
    if (ex) {
        return "0";
    } else {
        return ans;
    }
}

int getHighest(string str) {
    int length = str.length();
    int dot = dotSpot(createNum(str));
    if (dot == -1) {
        for (int i = 0; i < length; i++) {
            if (str[i] != '0') {
                // cout << str << " has highest digit: " << (length - i - 1) << endl;
                return length - i - 1;
            }
        }
    } else {
        for (int i = 0; i < length; i++) {
            if (str[i] != '0' && str[i] != '.') {
                // cout << str << " has highest digit: " << ((i < dot) ? dot - i - 1 : dot - i) << endl;
                return (i < dot) ? dot - i - 1 : dot - i;
            }
        }
    }
    // cout << str << " has highest digit: " << 0 << endl;
    return 0;
}

int magni(string a, string b) {
    int ha = getHighest(a);
    int hb = getHighest(b);
    return ha - hb;
}

Num pow(Num num, int i) {
    string ans;
    if (i >= 0) {
        ans = "1";
        for (int m = 0; m < i; m++) {
            ans = ans + "0";
        }
    } else {
        ans = "0.";
        for (int m = -1; m > i; m--) {
            ans = ans + '0';
        }
        ans = ans + '1';
    }
    return num * createNum(ans);
}

int cntFM(string num) {
    int length = num.length();
    int spot = 0;
    for (int i = 0; i < length; i++) {
        if (num[i] == '.') {
            spot = i;
            break;
        }
    }
    return -(length - spot - 1);
}

string fixF(string num) {
    const int length = num.length();
    int spot = 0;
    for (int i = 0; i < length; i++) {
        if (num[i] == '.') {
            spot = i;
            break;
        }
    }

    char fixed[length] = {'\0'};
    for (int i = 0; i < length - 1; i++) {
        if (i < spot) {
            fixed[i] = num[i];
        } else {
            fixed[i] = num[i + 1];
        }
    }
    string fixs = fixed;
    return fixs;
}

string moving(string ori, int move) {
    string moved;
    if (move == 0) {
        moved = ori;
    } else if (move > 0) {
        moved = ori.append(move, '0');
    } else {
        move = -move;
        int length = (int)ori.length();
        if (move < length) {
            moved = ori.insert(ori.length() - move, 1, '.');
        } else {
            moved = "0.";
            moved = moved.append(move - ori.length(), '0');
            moved += ori;
        }
        for (int i = moved.length() - 1; i >= 0; i--) {
            if (moved[i] != '0') {
                moved = moved.substr(0, i + 1);
                break;
            }
        }
        if (moved[moved.length() - 1] == '.') {
            moved = moved.substr(0, moved.length() - 1);
        }
    }
    return moved;
}

string fixE(string str) {
    int spot = -1;
    for (int i = 0; i < (int)str.length(); i++) {
        if (str[i] == 'e' || str[i] == 'E') {
            spot = i;
        }
    }
    if (spot == -1) {
        return str;
    }
    string oriNum = str.substr(0, spot);
    int move = stoi(str.substr(spot + 1));
    int dot = dotSpot(createNum(oriNum));
    if (move >= 0) {
        if (dot == -1) {
            for (int i = 0; i < move; i++) {
                oriNum = oriNum + "0";
            }
        } else if (oriNum.length() - 1 - dot <= move) {
            move -= oriNum.length() - 1 - dot;
            oriNum = oriNum.erase(dot, 1);
            for (int i = 0; i < move; i++) {
                oriNum = oriNum + "0";
            }
        } else {
            oriNum = oriNum.erase(dot, 1);
            oriNum = oriNum.insert(dot + move, 1, '.');
        }
    } else {
        if (dot != -1) {
            move -= oriNum.length() - 1 - dot;
            oriNum = oriNum.erase(dot, 1);
        }
        move = -move;
        if (move < oriNum.length()) {
            oriNum = oriNum.insert(oriNum.length() - move, 1, '.');
        } else {
            move -= oriNum.length();
            for (int i = 0; i < move; i++) {
                oriNum = "0" + oriNum;
            }
            oriNum = "0." + oriNum;
        }
    }
    oriNum = subZero(oriNum);
    // cout << oriNum << endl;
    return oriNum;
}
