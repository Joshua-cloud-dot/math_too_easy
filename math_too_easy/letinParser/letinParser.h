#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <map>

using namespace std;

class Parser {
    int    inputIndex;
    string input;
public:
    Parser() : inputIndex(0){}

    // starts a parsing of string word, returns true if w in L
    void parse(string word); 

    // must override function for Startsymbol
    virtual void Start()=0;

    // returns true if c equals the char at inputIndex of input then index++
    void match(char c);

    // returns current inputIndex
    char next() const;
};



// objects of this class parses and calculates simple "let <variable definitions> in <equation>"  expressions
class letinParser : public Parser {
    void ignoreWhitespace();

    double result;  // stores result of successful parse
    map<string, double> * vars; // hashmap stores expression variables

public:
    letinParser() : result(0), vars(new map<string, double>) {}
    ~letinParser() {delete vars;}
    double getResult() {return result;}

    void Start();
    void VARS();

    double E();
    double T();
    double F();
    double R();

    double Zahl();

};

#endif