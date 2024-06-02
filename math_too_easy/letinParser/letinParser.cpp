#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cmath>



using namespace std;

#include "letinParser.h"

bool Parser::parse(string word) {
    input = word + '#';
    inputIndex = 0;
    bool inLang = Start() && match('#');
    return inLang;
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




void letinParser::ignoreWhitespace() {
    while (next() == ' '){ match(' '); }
}

bool letinParser::Start() {
    result = 0;
    ignoreWhitespace();
    if (next() == 'l') { 
        return match('l') 
            && match('e') 
            && match('t') 
            && match(' ') 
            && VARS() 
            && match('i') 
            && match('n') 
            && match(' ')
            && EQ();
    } 
    else {
        return EQ();
    }
}

bool letinParser::VARS() {
    // declare variables
    ignoreWhitespace();
    char c = next();
    string identifier;


    if (isalpha(c)) {  
        match(c);
        identifier += c;  
        c = next();
        while (isalnum(c)) {
        match(c);
        identifier += c;
        c = next();
        }
        // end of identifier

        // match '='
        ignoreWhitespace();
        if (!match('=')) {cout << "error no =\n"; return false;}
        ignoreWhitespace();
        
        // value
        double value = Zahl();

        (*vars)[identifier] = value;   // Speichere Variable in hash
        

        ignoreWhitespace();

        if (next() == ',') {
            match(',');
            return VARS();
        }
        else return true;
    }
    else {
        cout << "error with " << next() << endl;
        return false;
    }
}



bool letinParser::EQ() {
    result = E();
    return true;
}


double letinParser::E() { // plus minus
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

double letinParser::T() { // mal, durch
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

double letinParser::F() {
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

double letinParser::R() {
    double res;

    if (next() == '(') {
        match('(');
        res = E();
        match(')');
    }
    else res = Zahl(); 

    return res;
}


double letinParser::Zahl() {
    char symbol = next();
    int res = 0, sgn = 1;


    // Vorzeichenbehandlung
    if (next() == '-') {
        match('-');
        sgn = -1;
        symbol = next();
    }

    // Variablen
    if (isalpha(symbol)) {
        match(symbol);
        string identifier;
        identifier += symbol;
        while (isalnum(next())) {
            identifier += next();
            match(next());
        }
        if (vars->count(identifier) == 0) {
            cout << "Variable " << identifier << " not defined" << endl;
            throw(string("invalid Value"));
        }
        else {
            res = (*vars)[identifier];
            return res;
        }
        return res;
    }

    else if (isdigit(symbol)) {
        match(symbol);
        res += (symbol - '0') * sgn;
        symbol = next();
        while (isdigit(symbol)) {
            match(symbol);
            res = 10 * res + (symbol - '0') * sgn;
            symbol = next();
        }
        return res;
    } 
    else throw(string("invalid Value"));
}