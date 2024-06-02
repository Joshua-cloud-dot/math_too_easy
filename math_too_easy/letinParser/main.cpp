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
    try {
        while (1) {
            cout << "> ";
            getline(cin, input);
            if (input.find("quit") != string::npos) exit(1);
            accepted = (p.parse(input)) ? "True" : "False";
            cout << "is input element L = " << accepted << endl;
            cout << "solution:            " << p.getResult() << endl;

        }
    }
    catch(string str) {
        cout << "Exception " << str << " occured\n";
    }
    
   


    return 0;
}