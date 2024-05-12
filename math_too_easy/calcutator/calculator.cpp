#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cmath>



using namespace std;

#include "calculator.h"




bool Parser::parse(string word) {
    input = word + '#';
    bool isValid = Start() && match('#');
    inputIndex = 0;
    return isValid;
}

bool Parser::match(char c) {
    if (c == input[inputIndex]) {
            inputIndex++;
            return true; 
    }
    else return false;
}

char Parser::next() const{   
    return input[inputIndex];  
}









void calcParser::ignoreWhitespace() {
    while (next() == ' '){ match(' '); }
}

bool calcParser::Start() {
    result = E();
    return true;
}

double calcParser::E() { // plus minus
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

double calcParser::T() { // mal, durch
    double res;
    res = F();
    ignoreWhitespace();
    while (next() == '*' || next() == '/') {
            if (next() == '*') {
                match('*');
                ignoreWhitespace();
                res *= F();
                ignoreWhitespace();
            }
            else if (next() == '/') {
                match('/');
                ignoreWhitespace();
                res /= F();
                ignoreWhitespace();
            }
        }
    return res;
}

double calcParser::F() {
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

double calcParser::R() {
    double res;

    if (next() == '(') {
        match('(');
        res = E();
        match(')');
    }
    else res = Zahl(); 

    return res;
}


double calcParser::Zahl() {
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
                throw(string("invalid Variable"));
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