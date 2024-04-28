#include <iostream>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <cstdlib>

using namespace std;



// jsfas

// IDEA: to implement rules of grammar, 
// hash table with array long as number of Variables + alphabet = m



int hash_func(const string & symbol, int m){
    int i, sum = 0;
    int n = symbol.length();
    for (i = 0; i < n; i++) {
        sum += symbol[i] * pow(129, i);
    }
    return sum % m;
}






int main(int argc, char** argv)
{
        int i, m = atoi(argv[1]);
        string * table[m];

        // main CYK loop



        string symbol = argv[2];
        i = hash_func(symbol, m);



        cout << i << endl;

    return 0;
}