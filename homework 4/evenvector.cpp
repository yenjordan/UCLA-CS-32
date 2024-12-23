#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

// Remove the even integers from v.
void removeEven(vector<int>& v)
{
    v.erase(remove_if(v.begin(), v.end(), [](int n) { return n % 2 == 0; }), v.end());
}

void test()
{
    int a[9] = { 4, 1, 7, 6, 5, 8, 0, 3, 2 };
    vector<int> x(a, a+9);  // construct x from the array
    assert(x.size() == 9 && x.front() == 4 && x.back() == 2);
    removeEven(x);
    assert(x.size() == 4);
    sort(x.begin(), x.end());
    int expect[4] = { 1, 3, 5, 7 };
    for (int k = 0; k < 4; k++)
        assert(x[k] == expect[k]);
}

int main()
{
    test();
    cout << "Passed" << endl;
}
