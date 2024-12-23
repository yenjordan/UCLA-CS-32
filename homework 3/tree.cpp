// #include <iostream>
// #include <string>
// #include <cassert>

// using namespace std;

int numberOfTimesHas(const string a1[], int n1, const string a2[], int n2) {
    if (n2 <= 0) // Base case: if n2 is zero or negative, return 1
        return 1;
    if (n1 <= 0) // Base case: if n1 is zero or negative, return 0
        return 0;

    if (a1[0] == a2[0]) {
        // If the first elements match, recur for the rest of the arrays
        return numberOfTimesHas(a1 + 1, n1 - 1, a2 + 1, n2 - 1) + 
               numberOfTimesHas(a1 + 1, n1 - 1, a2, n2);
    } else {
        // Otherwise, move to the next element in a1
        return numberOfTimesHas(a1 + 1, n1 - 1, a2, n2);
    }
}

void exchange(string& x, string& y) {
    string t = x;
    x = y;
    y = t;
}

void separate(string a[], int n, string separator, int& firstNotLess, int& firstGreater) {
    if (n < 0)
        n = 0;

    firstNotLess = 0;
    firstGreater = n;
    int firstUnknown = 0;
    while (firstUnknown < firstGreater) {
        if (a[firstUnknown] > separator) {
            firstGreater--;
            exchange(a[firstUnknown], a[firstGreater]);
        } else {
            if (a[firstUnknown] < separator) {
                exchange(a[firstNotLess], a[firstUnknown]);
                firstNotLess++;
            }
            firstUnknown++;
        }
    }
}

void order(string a[], int n) {
    if (n <= 1) // Base case: if n is 1 or less, do nothing
        return;

    // Use separate function to partition the array
    int firstNotLess, firstGreater;
    separate(a, n, a[0], firstNotLess, firstGreater);

    // Recur for the two partitions
    order(a, firstNotLess);
    order(a + firstGreater, n - firstGreater);
}



// int main() {

//     string berg[] = { "john", "amy", "ketanji", "sonia", "amy", "ketanji", "elena" };
//     string test1[] = { "john", "sonia", "ketanji" };
//     string test2[] = { "john", "ketanji", "elena" };
//     string test3[] = { "sonia", "john", "ketanji" };
//     string test4[] = { "amy", "ketanji", "elena" };

//     assert(numberOfTimesHas(berg, 7, test1, 3) == 1);
//     assert(numberOfTimesHas(berg, 7, test2, 3) == 2);
//     assert(numberOfTimesHas(berg, 7, test3, 3) == 0);
//     assert(numberOfTimesHas(berg, 7, test4, 3) == 3);

//     string a[] = { "c", "e", "a", "b", "g", "f" };
//     string b[] = { "d", "b", "c", "b", "d", "a", "b", "c", "d", "a", "e", "b" };
//     assert(numberOfTimesHas(a, 3, b, 3) == 0);
//     assert(numberOfTimesHas(b, 12, a, 3) == 0);
//     order(a, 6);
//     assert(a[0] == "a" && a[1] == "b" && a[2] == "c" && a[3] == "e" && a[4] == "f" && a[5] == "g");

//     order(b, 12);
//     assert(b[0] == "a" && b[1] == "a" && b[2] == "b" && b[3] == "b" && b[4] == "b" && b[5] == "b" && b[6] == "c" && b[7] == "c" && b[8] == "d" && b[9] == "d" && b[10] == "d" && b[11] == "e");

//     string c[] = { "1", "3", "3", "1", "1", "3", "3", "1", "3", "3", "1" };
//     string d[] = { "1", "3", "3" };
//     string e[1] = {};

//     assert(numberOfTimesHas(b, 12, a, 3) == 16);
//     assert(numberOfTimesHas(c, 3, d, 3) == 1);
//     assert(numberOfTimesHas(c, 2, d, 3) == 0);
//     assert(numberOfTimesHas(c, 3, d, 2) == 2);
//     assert(numberOfTimesHas(d, 3, c, 2) == 2);
//     assert(numberOfTimesHas(d, 3, c, 0) == 1);
//     assert(numberOfTimesHas(c, 7, c, 1) == 3); //aliasing !!!
//     assert(numberOfTimesHas(c, 7, e, 0) == 1);
//     assert(numberOfTimesHas(c, 11, d, 1) == 5);
//     assert(numberOfTimesHas(c, 7, d, 3) == 8);
//     assert(numberOfTimesHas(c, 11, d, 3) == 28);

//     cerr << "passed all tests, maybe..." << endl;

//     /*
//     per the spec, in the numberOfTimesHas function, you cannot check strings more than (n1+1) choose n2 times.
//     This means that if n2 = n1+1, then you can only check once, and if n2 > n1+1, you cannot check at all
//     If n1 = n2, you can only check strings n1+1 times. Apply these tests and put a cerr statement in the appropriate
//     places in your code (after a comparison of two strings). If you exceed the number of comparisons on the right of
//     each of the following test cases, then you haven't passed all test cases yet. comment out the test cases on top
//     so you don't get swarmed with those messages.
//     */

//     string spec1[] = { "the", "final", "boss", "!!" };
//     string spec2[] = { "the", "final", "boss", };

//     //comment out to check each individual test case
//     assert(numberOfTimesHas(spec2, 3, spec1, 3) == 1); //must not make more than 4 comparisons
//     cerr << "test 1 passed!" << endl;
//     assert(numberOfTimesHas(spec2, 3, spec1, 4) == 0); //must not make more than 1 comparison
//     cerr << "test 2 passed!" << endl;
//     assert(numberOfTimesHas(spec1, 2, spec2, 4) == 0); //must not make any comparisons
//     cerr << "test 3 passed!" << endl;

//     string spec3[] = { "1", "1", "1", "1", "1" };
//     string spec4[] = { "1", "1", "1", "1", "1" };

//     assert(numberOfTimesHas(spec3, 5, spec4, 0) == 1); //must not make more than 1 comparison
//     cerr << "test 4 passed!" << endl;
//     assert(numberOfTimesHas(spec3, 5, spec4, 1) == 5); //must not make more than 6 comparisons
//     cerr << "test 5 passed!" << endl;
//     assert(numberOfTimesHas(spec3, 5, spec4, 2) == 10); //must not make more than 15 comparisons
//     cerr << "test 6 passed!" << endl;
//     assert(numberOfTimesHas(spec3, 5, spec4, 3) == 10); //must not make more than 20 comparisons
//     cerr << "test 7 passed!" << endl;
//     assert(numberOfTimesHas(spec3, 5, spec4, 4) == 5); //must not make more than 15 comparisons
//     cerr << "test 8 passed!" << endl;
//     assert(numberOfTimesHas(spec3, 5, spec4, 5) == 1); //must not make more than 6 comparisons
//     cerr << "test 9 passed!" << endl;

//     cerr << "passed all tests, yippee!!";

//     return 0;
// }