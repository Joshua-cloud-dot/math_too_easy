#include <iostream>
#include <cstring>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <cctype>
#include <cmath>

using namespace std;

#include "letinParser.h"

// general parsing
void Parser::parse(string word) {
    input = word + '#';
    inputIndex = 0;
    Start();
    match('#');
}

// match next char else throw exception
void Parser::match(char c) {
    if (c == input[inputIndex]) {
        inputIndex++; 
    }
    else 
        throw((string)"could not match " + c + " with " + input[inputIndex]);
}

char Parser::next() const{   
    return input[inputIndex];  
}




void letinParser::ignoreWhitespace() {
    while (next() == ' '){ match(' '); }
}

void letinParser::Start() {
    result = 0;
    ignoreWhitespace();
    if (next() == 'l') { 
        match('l'); 
        match('e'); 
        match('t'); 
        match(' '); 
        VARS(); 
        match('i'); 
        match('n');
        match(' ');
        result = E();
    } 
    else {
        result = E();
    }
}

void letinParser::VARS() {
    // for declaring variables
    ignoreWhitespace();
    string identifier;

    // beginnt nur mit Buchstaben
    if (isalpha(next())) {
        identifier += next();  
        match(next());
        // enthält beliebig viele alnum Zeichen nach erstem 
        while (isalnum(next())) {
        identifier += next();
        match(next());
        }
        // end of identifier

        // match '='
        ignoreWhitespace();
        match('=');
        ignoreWhitespace();
        
        // value
        double value = Zahl();
        ignoreWhitespace();
        // Speichere Variable in hash
        (*vars)[identifier] = value;   

        if (next() == ',') {
            match(',');
            VARS();
        }
    }
    else {
        throw((string)"Error in VARS with " + next() + " : varname only starts with letter");
    }
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

    // Variablenhandling
    if (isalpha(symbol)) {
        match(symbol);
        string identifier;
        identifier += symbol;
        while (isalnum(next())) {
            identifier += next();
            match(next());
        }
        if (vars->count(identifier) == 0) { // existiert varname überhaupt in Hashtable
            throw(string("Unknown identifier: " + identifier));
        }
        else {
            res = (*vars)[identifier];
            return res;
        }
        return res;
    }

    else if (isdigit(symbol)) {
        match(symbol);
        res += (symbol - '0');
        symbol = next();
        while (isdigit(symbol)) {
            match(symbol);
            res = 10 * res + (symbol - '0');
            symbol = next();
        }
        return res * sgn;
    } 
    else throw((string)"invalid number: " + symbol);
}