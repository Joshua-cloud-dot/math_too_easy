#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <forward_list>

using namespace std;





// IDEA: to implement rules of grammar, 
// hash table with array long as number of Variables + alphabet = m





// finished dynamic Table, now need to fill according to rules of grammar and given Word

const char word[] = "aaabbb";


int main(int argc, char** argv)
{

    const int n = sizeof(word) / sizeof(char);
    forward_list<char>  CYK_table[n][n]; // erstelle leere CYK-Tabelle


        // main CYK loop
        int i,j,h,k;
        char c;

        // build loop for table for h = 0 to n - 1
        for (h = 0; h < n; h++) {
            for (i = 0 ; i < n - h ; i++){
                j = h + i;
                if (i == j) {
                    CYK_table[i][j].push_front(word[i]);
                    
                }
                else {
                    for (k = i; k < j; k++) {
                        // each loop results in a new test if there is a rule to form two Symbols, coming from table
                        c = k + '0';
                        CYK_table[i][j].push_front(c);
                    }
                }
            }
        }


        // Table look
        for (h = 0; h < n; h++) {
            for (i = 0 ; i < n - h ; i++){
                j = h + i;
                auto it = CYK_table[i][j].begin();
                auto end = CYK_table[i][j].end();
                cout << "T[" << i << j << "] " << endl << "\t";
                if (i != j) {
                    for (; it != end ; it++) {
                    c = *it;
                    char c1 = c + 1;
                    cout << i << c << " and " << c1 << j << "\t";
                    }
                }
                else {
                    for (; it != end ; it++) {
                    cout << *it;
                    }
                }
                cout << endl;
            }
        }
            cout << endl;
    return 0;
}