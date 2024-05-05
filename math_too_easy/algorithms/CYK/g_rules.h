#ifndef __G_RULES_H__
#define __G_RULES_H__

#include <string>
#include <unordered_map>
#include <forward_list>
using namespace std;

// using a list of small strings for rSide od grammar rules
typedef forward_list<string> str_list;

// list of chars for set of Variables fo grammar
typedef forward_list<char>  char_list;

// tuple of rule pairs, where char is lSide and str_list is rSide
typedef pair<char, str_list> rule_pair;


class grammar {
    unordered_map<char, str_list> hashed_rules; // main hash table for relationships
    char start_symbol;          

public:
    // must instantiate with a startsymbol rule
    grammar(rule_pair new_pair);

    // pairs must have form char, string with len<=2
    bool insertNewRule(rule_pair new_pair);

    // displays all Variables and their corresponding rSides
    void display();

    // tests if a rule pair exists
    bool ruleExists (char Var, string prod);

    // return list of all Vars, that derive prod
     char_list productionOriginVars (string prod);
};

// this returns a new rule pair with user shell input questionairre
rule_pair createNewRulePair ();
#endif