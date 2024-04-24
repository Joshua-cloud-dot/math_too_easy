#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <forward_list>

using namespace std;






int main(int argc, char** argv)
{
    if (argc != 2) {
         cout << "Usage: " << argv[0] << " <length n>" << endl; 
         return -1;
    }

    const int n = atoi(argv[1]);
    cout << n << endl; 
    forward_list<char>  CYK_table[n][n]; 
    

    for (int i = 0; i < n; i++) {
        char a = (i + 1000) % 128;
        CYK_table[0][0].push_front(a);
    }
    
    auto it =  CYK_table[0][0].begin();
    for (; it != CYK_table[0][0].end() ; it++) {
        cout << *it;


    }




    return 0;
}