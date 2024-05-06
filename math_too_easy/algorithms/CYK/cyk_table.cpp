#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <string>
#include <forward_list>

using namespace std;



typedef forward_list<char>  char_list;

// need class cyk_table

class cyk_table {

    string input;
    public:


    char_list**  CYK_table;


    cyk_table(string word) : input(word) {
        int n = word.length();
        CYK_table =  new char_list*[n];
    }

};



int main(int argc, char** argv)
{
    if (argc != 2) {
         cout << "Usage: " << argv[0] << " <some array>" << endl; 
         return -1;
    }

    cyk_table table(argv[1]);
     
    table.CYK_table[0]->push_front('c');

    // for (int i = 0; i < string(argv[1]).length(); i++) {
    //     char a = 'c';
    //     table.CYK_table[0][0].push_front(a);
    //     cout << argv[1][i] << endl;
    // }
    
    auto it =  table.CYK_table[0]->begin();
    for (; it != table.CYK_table[0]->end() ; it++) {
        cout << *it;
    }




    return 0;
}