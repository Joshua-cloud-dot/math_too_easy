#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cmath>
#include <map>

using namespace std;



#include "letinParser.h"



int main (int argc, char** argv)
{



    string accepted;
    letinParser p;
    string input;
    while (1) {
        try {
            cout << "> ";
            getline(cin, input);
            if (input.find("quit") != string::npos) exit(1);
            p.parse(input);
            cout << "input accepted, " << endl;
            cout << "solution:            " << p.getResult() << endl;

        }
        catch(string str) {
        cout << "Exception '" << str << "' occured\n";
        cout << "input unaccepted\n";
        }
    }
    
    
   


    return 0;
}