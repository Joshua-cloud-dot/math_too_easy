#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <cstdlib>


using namespace std;

#include "g_rules.h"
        
// must instantiate with a startsymbol rule
grammar::grammar(rule_pair new_pair) : start_symbol(new_pair.first) { 
    new_pair.second.sort();    // always work with sorted rSides for merging
    new_pair.second.unique();  // always work with no duplicate rules
    hashed_rules.insert(new_pair);
}

// pairs must have form char, string with len<=2
bool grammar::insertNewRule(rule_pair new_pair) {  
    char Var = new_pair.first; // lSide Variable
    new_pair.second.sort();    // always work with sorted rSide for merging
    new_pair.second.unique();
    str_list rSide = new_pair.second; 

    // test if variable already in hash, then merge rSides
    if (hashed_rules.count(Var)) {
        auto it = hashed_rules.find(Var);
        it->second.merge(rSide);
        it->second.unique();
        return true;
    } 
    // else insert new pair
    else
        return hashed_rules.insert(new_pair).second; // .second returns whether insert works out
}

// displays all Variables and their corresponding rSides
void grammar::display() {
    cout << "Startsymbol: " << start_symbol << endl;
    auto it = hashed_rules.begin();
    int list_len, k;

    for (unsigned i = 0; i < hashed_rules.size(); ++i, ++it){
        cout << it->first << " --> ";
        auto list_end = it->second.end();
        auto list_it = it->second.begin();

        for (list_len = 0; list_it != list_end; ++list_it, ++list_len); // get list len into n

        for (list_it = it->second.begin(), k = 0; k < list_len - 1; ++list_it, ++k) { // display production rules with '|'
            cout << *list_it << " | ";
        }
        cout << *list_it << endl;
    }
}

// tests if a rule pair exists
bool grammar::ruleExists (char Var, string prod) {
    if (prod.length() > 2) return false; // if prod is too long nope

    // if Var is a key in Hash go further
    if(hashed_rules.count(Var)) {

        // iterate through forward list to match prod with a list element
        auto it = hashed_rules.find(Var);
        auto list_end = it->second.end();
        auto list_it = it->second.begin();
        int list_len, k;
        for (list_len = 0; list_it != list_end; ++list_it, ++list_len); // get list len into n

        for (list_it = it->second.begin(), k = 0; k < list_len - 1; ++list_it, ++k) { 
            if (*list_it == prod) return true;
        }
    }
    return false;
}

// return list of all Vars, that derive prod
char_list grammar::searchLSidesFor (string prod) {
    char_list Vars;
    if (prod.length() > 2) return Vars;


    auto hash_it = hashed_rules.begin();
    int list_len, k;
    // iterate through all keys and their string list rSides, then push to list all that derive prod
    for (unsigned i = 0; i < hashed_rules.size(); ++i, ++hash_it){

        auto list_end = hash_it->second.end();
        auto list_it = hash_it->second.begin();
        int list_len, k;
        for (list_len = 0; list_it != list_end; ++list_it, ++list_len); // get list len into n
        for (list_it = hash_it->second.begin(), k = 0; k < list_len; ++list_it, ++k) { // check if list elements are equal to prod
            if (*list_it == prod) Vars.push_front(hash_it->first);
        }
    }
    Vars.sort(); // sort for merging purposes
    return Vars;
}



// this returns a new rule pair with user shell input questionairre
rule_pair createNewRulePair (string rule) {

        if (!(rule[1] == '-' && rule[2] == '>')) {
                cout << rule << " is not a valid rule format" << endl;
                cout << "\"<lSide_variable>-> <production> [<| production>]\"";
                return rule_pair();
        }

        str_list rSide;
        string production = "";
        char Var;

        Var = rule[0];
        for (int i = 3; i < rule.length(); i++) {

            if (rule[i] == ' ') continue;
            else if (rule[i] == '|') {
                rSide.push_front(production); 
                production = "";
            }
            else production += rule[i];

            if (production.length() > 2) {
                cout << "Production with more than two chars" << endl;
                return rule_pair();
            }
        }
        rSide.push_front(production); 
        rule_pair grule(Var, rSide);
        return grule;
}






// int main(int argc, char** argv)
// {
//     cout << "input the starting rules for grammar: " << endl;
//     rule_pair newPair = createNewRulePair();
//     grammar test(newPair);

    
//     test.insertNewRule(createNewRulePair());






//     test.display();



//     char_list sol = test.productionOriginVars("AB");
//     for (auto it = sol.begin(); it != sol.end(); ++it) {
//         cout << *it << endl;
//     }

//     cout << test.ruleExists('E', "AD") << endl;

//     return 0;
// }