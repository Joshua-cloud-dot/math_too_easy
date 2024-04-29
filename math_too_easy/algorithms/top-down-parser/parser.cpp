#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>

using namespace std;

class Parser {
    int index;
    string input;
public:
    Parser() : index(0){}
    bool parse(string word) {
        input = word + '#';
        return S() && match('#');
    }

    bool match(char c) {
        if (c == input[index]) {
             index++;
             return true; 
        }
        else return false;
    }
    char next() const{   
        return input[index];  
    }
    virtual bool S()=0;

};

class abxba_parser : public Parser {
public:
    bool S() {
        if (next() == 'a') {
            return match('a') && S() && match('a');
        }
        else if (next() == 'b') {
            return match('b') && S() && match('b');
        }
        else if (next() == 'x') {
            return match('x');
        }
        else return false;
    }
};

int main (int argc, char** argv)
{
    abxba_parser p;
    cout << p.parse(argv[1]) << endl;

    return 0;
}