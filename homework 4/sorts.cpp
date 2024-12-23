#include <iostream>
#include <algorithm>
#include <numeric>  // for std::accumulate
#include <utility>
#include <vector>
#include <string>
#include <random>
#include <cmath>
#include <cassert>

using namespace std;

//========================================================================
//  Set this to false to skip the insertion sort tests; you'd do this if
//  you're sorting so many items that insertion_sort would take more time
//  than you're willing to wait.

const bool TEST_INSERTION_SORT = true;

//========================================================================

//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#include <chrono>

class Timer
{
  public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {   
        std::chrono::duration<double, std::milli> diff =
                          std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
  private:
    std::chrono::high_resolution_clock::time_point m_time;
};

//========================================================================

// These are used for random number generation

std::random_device aRandomDevice;
std::default_random_engine generator(aRandomDevice());

// Here's a class that is not cheap to copy because the objects contain a
// large array.

// We'll simplify writing our timing tests by declaring everything public
// in this class.  (We wouldn't make data public in a class intended for
// wider use.)

using IdType = int;

struct Student
{
    IdType id;
    double gpa;
    static const int NGRADES = 200;
    double grades[NGRADES];
    Student(IdType i) : id(i)
    {
        std::uniform_int_distribution<> distro(0, 4);

          // create random grades (from 0 to 4)
        for (size_t k = 0; k < NGRADES; k++)
            grades[k] = distro(generator);
          // (accumulate computes 0.0 + grades[0] + grades[1] + ...)
        gpa = accumulate(grades, grades + NGRADES, 0.0) / NGRADES;
    }
};

inline
bool compareStudent(const Student& lhs, const Student& rhs)
{
      // The Student with the higher GPA should come first.  If they have
      // the same GPA, then the Student with the smaller id number should
      // come first.  Return true iff lhs should come first.  Notice that
      // this means that a false return means EITHER that rhs should come
      // first, or there's a tie, so we don't care which comes first,

    if (lhs.gpa > rhs.gpa)
        return true;
    if (lhs.gpa < rhs.gpa)
        return false;
    return lhs.id < rhs.id;
}

inline
bool compareStudentPtr(const Student* lhs, const Student* rhs)
{
    return compareStudent(*lhs, *rhs);
}

void insertion_sort(vector<Student>& s, bool comp(const Student&, const Student&))
{
    for (size_t i = 1; i < s.size(); ++i)
    {
        Student key = s[i];
        size_t j = i;
        while (j > 0 && comp(key, s[j - 1]))
        {
            s[j] = s[j - 1];
            --j;
        }
        s[j] = key;
    }
}

  // Report the results of a timing test

void report(string caption, double t, const vector<Student>& s)
{
    if (t >= 1)
        t = round(100*t) / 100;
    cout << t << " milliseconds; " << caption
             << "; first few students are\n\t";
    size_t n = s.size();
    if (n > 4)
        n = 4;
    for (size_t k = 0; k < n; k++)
        cout << " (" << s[k].id << ", " << s[k].gpa << ")";
    cout << endl;
}

  // Verify that all ids from 0 to number of students-1 are in vector
bool allPresent(const vector<Student>& students)
{
	vector<int> present(students.size(), 0);
	for (const auto& s : students)
		present[s.id] = 1;
	return find(present.begin(), present.end(), 0) == present.end();
}

void sortUsingPtrs(vector<Student>& students, bool comp(const Student*, const Student*));

int main()
{
    size_t nstudents;
    cout << "Enter number of students to sort: ";
    cin >> nstudents;
    if ( !cin  ||  nstudents <= 0)
    {
        cout << "You must enter a positive number.  Goodbye." << endl;
        return 1;
    }

      // Create a random ordering of id numbers 0 through nstudents-1
    vector<IdType> ids;
    for (size_t j = 0; j < nstudents; j++)
        ids.push_back(IdType(j));
    shuffle(ids.begin(), ids.end(), generator);  // from <algorithm>

      // Create a bunch of Students
    vector<Student> unorderedStudents;
    for (size_t k = 0; k < ids.size(); k++)
        unorderedStudents.push_back(Student(ids[k]));

      // Create a timer

    Timer timer;

      // Sort the Students using the STL sort algorithm.  It uses a variant
      // of quicksort called introsort.

    vector<Student> students(unorderedStudents);
    timer.start();
    sort(students.begin(), students.end(), compareStudent);
    report("STL sort", timer.elapsed(), students);
    assert(is_sorted(students.begin(), students.end(), compareStudent));  // from <algorithm>

      // Sort the already sorted array using the STL sort.  This should be
      // fast.

    timer.start();
    sort(students.begin(), students.end(), compareStudent);
    report("STL sort if already sorted", timer.elapsed(), students);
    assert(is_sorted(students.begin(), students.end(), compareStudent));

    if (TEST_INSERTION_SORT)
    {
          // Sort the original unsorted array using insertion sort.  This
          // should be really slow.  If you have to wait more than a minute,
          // try rerunning the program with a smaller number of Students.

        students = unorderedStudents;
        timer.start();
        insertion_sort(students, compareStudent);
        double elapsed = timer.elapsed();
        if (is_sorted(students.begin(), students.end(), compareStudent)  &&  allPresent(students))
        {
            report("insertion sort if not already sorted", elapsed, students);

              // Sort the already sorted array using insertion sort.  This
              // should be fast.

            timer.start();
            insertion_sort(students, compareStudent);
            report("insertion sort if already sorted", timer.elapsed(), students);
            assert(is_sorted(students.begin(), students.end(), compareStudent)  &&  allPresent(students));
        }
        else
            cout << "[Skipping tests of insertion_sort, since it's not correctly implemented.]" << endl;
    }

      // Since Students are expensive to copy, and since the STL's sort copies
      // Students O(N log N) times, let's sort POINTERS to the Students, then
      // make one final pass to rearrange the Students according to the
      // reordered pointers.  We'll write some code; you write the rest
      // below in sortUsingPtrs.

      // Set students to the original unsorted sequence
    students = unorderedStudents;

      // Start the timing
    timer.start();

      // Sort using pointers
    sortUsingPtrs(students, compareStudentPtr);

      // Report the timing and verify that the sort worked
    report("STL sort of pointers", timer.elapsed(), students);

      // Until you correctly implement sortUsingPointers, this assertion will fail.
    assert(is_sorted(students.begin(), students.end(), compareStudent)  &&  allPresent(students));
}

void sortUsingPtrs(vector<Student>& students, bool comp(const Student*, const Student*))
{
      // Since Students are expensive to copy, and since the STL's sort copies
      // Students O(N log N) times, let's sort POINTERS to the Students, then
      // make one final pass to rearrange the Students according to the
      // reordered pointers.  We'll write some code; you write the rest.

      // Create an auxiliary copy of students to facilitate the later reordering.
    vector<Student> auxStudents(students.begin(), students.end());

      // Create a vector of Student pointers, and set each pointer to point to the corresponding Student in auxStudents.
    vector<Student*> studentPtrs;
    for (size_t i = 0; i < auxStudents.size(); ++i)
    {
        studentPtrs.push_back(&auxStudents[i]);
    }

      // Sort the vector of pointers using the STL sort algorithm with the comp parameter as the ordering relationship.
    sort(studentPtrs.begin(), studentPtrs.end(), comp);

      // Using the now-sorted vector of pointers, replace each Student in students with the Students from auxStudents in the correct order.
    for (size_t i = 0; i < studentPtrs.size(); ++i)
    {
        students[i] = *studentPtrs[i];
    }

      // auxStudents will be destroyed upon return from the function
}
