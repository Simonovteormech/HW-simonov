#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;
int main() {
    string s;
    ifstream at ("F:\\Studies\\C++\\int.txt");
    at.is_open();
    getline (at, s);
    int x_1 = stoi(s);
    string z = to_string(x_1);
    s.erase(s.find(z), 2);
    int x_2 = stoi(s);
    at.close();

    float arg_r = 0;
    float arg_l = 0;
    int r_1 = 0;
    int r_2 = 0;
    int l_1 = 0;
    int l_2 = 0;
     string str;
     ifstream in ("F:\\Studies\\C++\\int.txt");
     if(in.is_open()){
        while (getline (in,str)){
            int a_1 = stoi(str);
            string b = to_string(a_1);
            str.erase(str.find(b), b.length());
            int a_2 = stoi(str);
            float ugol = acos((x_1 * a_1 + x_2 * a_2) / (sqrt(pow(x_1, 2) + pow(x_2, 2)) * sqrt(pow(a_1, 2) + pow(a_2, 2))));
            if ((x_2 != 0 && a_1 >= x_1 * a_2 / x_2) || (x_2 == 0 && x_1 >= 0 && a_2 <= 0) || (x_2 == 0 && x_1 < 0 && a_2 >= 0)) {
                if (ugol > arg_r) {
                    arg_r = ugol;
                    r_1 = a_1;
                    r_2 = a_2;
                }
            }
            else {
                if (ugol > arg_l) {
                    arg_l = ugol;
                    l_1 = a_1;
                    l_2 = a_2;
                }
            }
        }
    }
    cout << "right: " << arg_r << ", " << r_1 << ", " << r_2 << endl;
    cout << "left: " << arg_l << ", " << l_1 << ", " << l_2 << endl;

    return 0;
}