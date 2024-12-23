#include <list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>
using namespace std;

// Remove the even integers from li.
void removeEven(list<int>& li)
{
    for (auto it = li.begin(); it != li.end();)
    {
        if (*it % 2 == 0)
        {
            it = li.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void test()
{
    int a[9] = { 4, 1, 7, 6, 5, 8, 0, 3, 2 };
    list<int> x(a, a+9);  // construct x from the array
    assert(x.size() == 9 && x.front() == 4 && x.back() == 2);
    removeEven(x);
    assert(x.size() == 4);
    vector<int> v(x.begin(), x.end());  // construct v from x
    sort(v.begin(), v.end());
    int expect[4] = { 1, 3, 5, 7 };
    for (int k = 0; k < 4; k++)
        assert(v[k] == expect[k]);
}

int main()
{
    test();
    cout << "Passed" << endl;
}
