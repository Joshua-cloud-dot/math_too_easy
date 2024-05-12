#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>





class Parser {
    int inputIndex;
    string input;
public:
    Parser() : inputIndex(0){}

    bool parse(string word); 
    virtual bool Start()=0;
    bool match(char c);
    char next() const;
};



class calcParser : public Parser {
    void ignoreWhitespace();
    double result;
    double a, b, c, d, e;
public:
    calcParser() {setABCDE(); result = 0;}

    double getResult() {return result;};

    bool Start();
    double E();
    double T();
    double F();
    double R();

    double Zahl();
    void setABCDE(double A=0, double B=0, double C=0, double D=0,  double E=0) 
    {a = A;
     b = B;
     c = C;
     d = D;
     e = E;}
};

#endif