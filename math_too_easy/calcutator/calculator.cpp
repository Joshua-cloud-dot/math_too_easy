#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;


int a, b, c, d, e;





class Parser {
    int inputIndex;
    string input;
public:
    Parser() : inputIndex(0){}

    bool parse(string word) {
        input = word + '#';
        bool isValid = Start() && match('#');
        inputIndex = 0;
        return isValid;
    }
    virtual bool Start()=0;

    bool match(char c) {
        if (c == input[inputIndex]) {
             inputIndex++;
             return true; 
        }
        else return false;
    }

    char next() const{   
        return input[inputIndex];  
    }
};








class calcParser : public Parser {
    void ignoreWhitespace() {
        while (next() == ' '){ match(' '); }
    }


public:
    double result;

    bool Start() {
        result = E();
        return true;
    }

    double E() { // plus minus
        double res;
        res = T(); 
        ignoreWhitespace();
        while (next() == '+' ||next() == '-') {
            if (next() == '+') {
                match('+');
                ignoreWhitespace();
                res += T();
                ignoreWhitespace();
            }
            else if (next() == '-') {
                match('-');
                ignoreWhitespace();
                res -= T();
                ignoreWhitespace();
            }
        }
        return res;
    }

    double T() { // mal, durch
        double res;
        res = F();
        ignoreWhitespace();
        while (next() == '*' ||next() == '/') {
                if (next() == '*') {
                    match('*');
                    ignoreWhitespace();
                    res *= T();
                    ignoreWhitespace();
                }
                else if (next() == '/') {
                    match('/');
                    ignoreWhitespace();
                    res /= T();
                    ignoreWhitespace();
                }
            }
        return res;
    }

    double F() {
        double res;
        res = R();     // matches number

        ignoreWhitespace();

        while (next() == '^') {
            match('^');
            ignoreWhitespace();
            res = pow(res, F());
            ignoreWhitespace();
        }
        return res;
    }

    double R() {
        double res;

        if (next() == '(') {
            match('(');
            res = E();
            match(')');
        }
        else res = Zahl(); 

        return res;
    }


    int Zahl() {
        char symbol = next();
        int res = 0;

        if (isalpha(symbol)) {
            match(symbol);
            switch (symbol) {
                case 'a':
                    return a;    
                case 'b':
                    return b;
                case 'c':
                    return c;
                case 'd':
                    return d;
                case 'e':
                    return e;
                default:
                    cout << symbol << " is not accepted\n";
                    exit(EXIT_FAILURE);
            }
        }
        else if (isdigit(symbol)) {
            match(symbol);
            res += symbol - '0';
            symbol = next();
            while (isdigit(symbol)) {
                match(symbol);
                res = 10 * res + (symbol - '0');
                symbol = next();
            }
            return res;
        }

        else throw(string("invalid Value"));
        
    }
};




int main (int argc, char** argv)
{
    a = b = c = 2;
    d = e = 3;
    string accepted;
    calcParser p;

    string input;
    try {
        while (1) {
            cout << "> ";
            getline(cin, input);
            if (input.find("quit") != string::npos) exit(1);
            accepted = (p.parse(input)) ? "True" : "False";
            cout << "is syntax accepted: " << accepted << endl;
            cout << "solution:           " << p.result << endl;

        }
    }
    catch(string str) {
        cout << "Exception " << str << " occured\n";
    }
    
   


    return 0;
}