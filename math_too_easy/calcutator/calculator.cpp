#include <iostream>
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
        return Start() && match('#');
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
        else res = Zahl(next()); 

        return res;
    }






    int Zahl(char symbol) {
        if (!match(symbol)) {
            cout << "couldn't match\n";
            exit(EXIT_FAILURE);
        }
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
                cout << "not in Language\n";
                exit(EXIT_FAILURE);
        }
    }
};






int main (int argc, char** argv)
{
    a = b = c = 2;
    d = e = 3;
    calcParser p;
    cout << "In L = " << p.parse(argv[1]) << endl;
    cout << "solution: " << p.result << endl;


    return 0;
}