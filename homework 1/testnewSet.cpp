        #include "newSet.h"
        #include <string>
        #include <iostream>
        #include <cassert>
        using namespace std;

        void test()
        {
            Set ss;
            assert(ss.insert("pita"));
            assert(ss.insert("roti"));
            assert(ss.size() == 2);
            assert(ss.contains("roti"));
            ItemType x = "laobing";
            assert(ss.get(0, x)  &&  x == "roti");
            assert(ss.get(1, x)  &&  x == "pita");
        }

        int main()
        {
            test();
            cout << "Passed all tests" << endl;
        }