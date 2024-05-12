#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;



#include "calculator.h"



int main (int argc, char** argv)
{
    string accepted;
    calcParser p;
    p.setABCDE();
    string input;
    try {
        while (1) {
            cout << "> ";
            getline(cin, input);
            if (input.find("quit") != string::npos) exit(1);
            accepted = (p.parse(input)) ? "True" : "False";
            cout << "is syntax accepted: " << accepted << endl;
            cout << "solution:           " << p.getResult() << endl;

        }
    }
    catch(string str) {
        cout << "Exception " << str << " occured\n";
    }
    
   


    return 0;
}