// #include <iostream>
// #include <string>
// #include <cassert>
// using namespace std;

// bool somePredicate(string s)
//         {
//             return s.empty();
//         }

bool allFalse(const string a[], int n)
{
    if (n <= 0)
        return true;
    else
        return !somePredicate(a[n - 1]) && allFalse(a, n - 1);
}

int countFalse(const string a[], int n)
{
    if (n <= 0)
        return 0;
    else
        return countFalse(a, n - 1) + (somePredicate(a[n - 1]) ? 0 : 1);
}

int firstFalse(const string a[], int n)
{
    if (n <= 0)
        return -1;

    int pos = firstFalse(a + 1, n - 1);

    if (pos == -1)
        return somePredicate(a[0]) ? -1 : 0;

    return somePredicate(a[0]) ? 1 + pos : 0;
}


int indexOfMax(const string a[], int n)
{
    if (n < 1)
        return -1;
    if (n == 1)
        return 0;

    int max1 = indexOfMax(a, n / 2);
    int max2 = indexOfMax(a + n / 2, n - (n / 2)) + n / 2;

    if (max1 == -1)
        return max2;
    else if (max2 == -1)
        return max1;
    else if (a[max1] >= a[max2])
        return max1;
    else
        return max2;
}


bool has(const string a1[], int n1, const string a2[], int n2)
{
    if (n2 <= 0)
        return true;
    else if (n1 <= 0)
        return false;
    else if (a1[0] == a2[0])
        return has(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    else
        return has(a1 + 1, n1 - 1, a2, n2);
}

// int main()
// {
//   string a[6] = { "john", "amy", "ketanji", "sonia", "amy", "ketanji" };
//   string a2[3] = { "amy", "sonia", "elena" };
//   string a3[3] = { "amy", "ketanji", "ketanji" };
//   string a4[3] = { "amy", "elena", "sonia" };
//   string a5[3] = { "john", "sonia", "sonia" };

//   string b[3] = { "amy", "sonia", "elena" };
//   string b2[4] = { "amy", "sonia", "elena", ""};
//   string c[4] = { "", "", "", "" };
//   string d[6] = { "", "", "", "", "john", "amy", };


//   assert(allFalse(a, 6) == true);
//   assert(allFalse(b, 3) == true);
//   assert(allFalse(c, 4) == false);

//   assert(countFalse(a, 6) == 6);
//   assert(countFalse(b, 3) == 3);
//   assert(countFalse(c, 4) == 0);

//   assert(firstFalse(a, 6) == 0);
//   assert(firstFalse(b, 3) == 0);
//   assert(firstFalse(c, 4) == -1);
//   assert(firstFalse(d, 6) == 4);

//   assert(indexOfMax(a, 6) == 3);
//   assert(indexOfMax(a, 2) == 0);
//   assert(indexOfMax(b, 0) == -1);
//   assert(indexOfMax(b, 3) == 1);
//   assert(indexOfMax(c, 4) == 0);
//   assert(indexOfMax(d, 6) == 4);
//   assert(indexOfMax(d, 4) == 0);

//   assert(has(a, 7, a2, 3) == false);
//   assert(has(a, 7, a3, 3) == true);
//   assert(has(a, 3, a3, 3) == false);
//   assert(has(a, 7, a4, 3) == false);
//   assert(has(a, 7, a5, 3) == false);
//   assert(has(a, 1, a2, -2) == true);

//   cerr << "all tests PASSED" << endl;
// }