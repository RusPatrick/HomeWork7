#include <iostream>
#include <string>
#include "List.h"

using namespace std;

int main() {
    try {
        List<int> iList1{5, 6, 3, 3};
        cout << iList1 << endl;

        List<int> iList2{8, 3, 2, 5, 1, 7, 4};
        cout << iList2 << endl;

        iList1.sort(ascending_cmp);
        cout << iList1 << endl;
        iList2.sort(ascending_cmp);
        cout << iList2 << endl;

        List<int> iList3 = iList1 + iList2;
        cout << iList3 << endl;

        iList3.sort(ascending_cmp);
        cout << iList3 << endl;

        List<string> sList1{"rrr", "qqq", "bbb", "ttt", "bbb", "kkk"};
        cout << sList1 << endl;

        List<string> sList2{"nnn", "yyy", "lll", "yyy", "ttt", "nnn"};
        cout << sList2 << endl;

        sList1.sort(ascending_cmp);
        cout << sList1 << endl;
        sList2.sort(ascending_cmp);
        cout << sList2 << endl;

        List<string> sList3 = sList1 + sList2;
        cout << sList3 << endl;

        sList3.sort(ascending_cmp);
        cout << sList3 << endl;
    }
    
    catch (const std::bad_alloc& bA) {
        std::cerr << "Error occured during the main() function\n";
        std::cerr << bA.what() << std::endl;
        //throw;
        return EXIT_FAILURE;
    }
    catch(...) {
        throw;
        //return EXIT_FAILURE;
    }
}
