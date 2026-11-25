# Quiz Question(s)

# OOP345 Quiz 3.4

### Before You Start

If Notepad++ is not open, [click here to go to MyApps](https://myapps.senecapolytechnic.ca/), open **Notepad++**, and save a file named **quiz3.cpp** on your **Desktop**.

**DO NOT copy and paste your answer into the quiz answer box.**

Write all three answers in **quiz3.cpp**. Begin each answer with its question number as a C++ comment, such as `// Question 1`.

When you are finished, save your file and attach it to your Blackboard answer using either method:

- Drag `quiz3.cpp` from your Desktop into the answer area.
- Click the attachment icon and select `quiz3.cpp`.

**Attach only one file.**

**Total: 10 marks · Suggested time: 50 minutes**

A hiking club keeps a guide to local trails. Each trail has a name and a length in whole kilometres. Assume the following code is provided for all three questions. Write only the requested implementations. A `main()` function is not required.

```cpp
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

struct Trail {
    string name;
    int kilometres;
};
```

The **reference** section at the end of the quiz contains the signatures of the STL algorithms used in the questions.

### Question 1 – Check for a short hike (3 marks)

Begin your answer with `// Question 1`.

Implement a **function object** named `IsShortHike`. Its constructor receives an integer and stores it as the maximum length of a short hike. Assume the maximum is positive.

When called with a `Trail` by constant reference, the function object must return `true` if the trail is **at least one kilometre long and no longer than the stored maximum**. Otherwise, it must return `false`. The call must work with a constant `IsShortHike` object.

Then implement the following function using `any_of` and your `IsShortHike` object. Return `true` if at least one trail qualifies as a short hike. Return `false` if no trail qualifies, including when the vector is empty.

```cpp
bool hasShortHike(const vector<Trail>& trails, int maxKm);
```

For example, if the trail lengths are `0, 12, 8`, a maximum of `8` gives `true` because the last trail qualifies. A maximum of `7` gives `false`.

### Question 2 – Record trails and handle errors (3 marks)

Begin your answer with `// Question 2`.

Implement both functions below.

```cpp
void recordTrail(vector<Trail>& guide, const Trail& trail);

void recordSurvey(vector<Trail>& guide, const vector<Trail>& survey,
                  ostream& errors);
```

**`recordTrail`**

- If the trail length is positive, add the trail to the end of `guide`.
- If the length is zero or negative, throw a `runtime_error` with the message `"Invalid trail length"`. The guide must remain unchanged for that trail.

**`recordSurvey`**

- Call `recordTrail` for each trail in `survey`, in order. Assume `guide` and `survey` are separate vectors.
- If `recordTrail` throws a `runtime_error`, catch it by constant reference. Write the trail name, a colon and a space, and the exception’s message to `errors`, followed by a newline.
- Continue processing the remaining trails after each error.

For example, suppose the guide is empty and the survey contains `{"Cedar", 6}`, `{"Marsh", -1}`, and `{"Ridge", 9}`, in that order. After the call, the guide contains `Cedar` followed by `Ridge`, and the error stream contains this line:

```text
Marsh: Invalid trail length
```

### Question 3 – Build a list of long hikes (4 marks)

Begin your answer with `// Question 3`.

Implement the following function. Assume `minKm` is positive and every trail in `trails` has a positive length.

```cpp
vector<Trail> selectLongHikes(const vector<Trail>& trails, int minKm);
```

1. Create a new `vector<Trail>` for the selected hikes.
2. Use `for_each` with a **lambda expression** to add every trail that is **at least `minKm` kilometres long**. Keep every qualifying trail, including trails of the same length.
3. Use `sort` with a **lambda expression** to arrange the selected trails by length, **longest first**. When two trails have the same length, sort them by name in **ascending order** using the usual `string` comparison.
4. Return the selected trails. If no trails qualify, return an empty vector. Preserve the original order of the input vector `trails`.

For example, suppose `minKm` is `8` and `trails` contains:

```cpp
{ {"Willow", 10}, {"Creek", 5}, {"Pine", 8}, {"Aspen", 10} }
```

The returned vector contains:

```cpp
{ {"Aspen", 10}, {"Willow", 10}, {"Pine", 8} }
```

### reference

The following algorithms are declared in `<algorithm>`. Each operates on the range `[first, last)`, which includes `first` and excludes `last`.

**`std::any_of` — Check whether at least one element satisfies a condition**

```cpp
template<class InputIt, class UnaryPredicate>
bool any_of(InputIt first, InputIt last, UnaryPredicate pred);
```

Returns `true` if `pred(element)` is true for at least one element. Returns `false` if no element satisfies the condition or if the range is empty.

**`std::for_each` — Perform an action on each element**

```cpp
template<class InputIt, class UnaryFunction>
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction action);
```

Calls `action(element)` once for each element, in order. Returns the function object after processing the range.

**`std::sort` — Arrange elements using a comparison rule**

```cpp
template<class RandomIt, class Compare>
void sort(RandomIt first, RandomIt last, Compare comp);
```

Rearranges the elements in the supplied range. `comp(a, b)` returns `true` when `a` should come before `b`. It must return `false` when the two elements are equivalent under the comparison rule.

# Original Student Answer

### Quiz 3_taina2_attempt_2026-11-20-13-37-14_quiz3.cpp

```cpp
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector> 

using namespace std;

struct Trail {
  string name;
  int kilometres;
};

// question 1

class IsShortHike {
  int maxKm;

public
IsShortHike(int maximum) : MaxKm(maximum) {}

bool operator () (const Trail& trail) const {
  return trail.kilometres >= 1 &&
         trail.kilometres <=maxKm;
  }
};

bool hasShortHike (const vector<Trail>& trails, int maxKm) {
  return any_of(trails.begin() , trails.end(),
                  IsShortHike(maxKm));
}

//question 2

void recordTrail﻿(vector<Trail>& guide, const Trail& trail) {
  if(trail.kilometres <= 0) {
  throw runtime_error("Invalid trail length");
}

  guide.push_back(trail);
}

void recordSurvey(vector<Trail>& guide,
                const vector<Trail>& survey,
                ostream& errors) {

    for (const Trail& trail : survey) {
          try {
            recordTrail (guide, trail);
        }
    catch (const runtime_error& e) {
    errors << trail.name << ": " << e.waht() << '\n';
      }
    }
}

// question 3

vector<Trail> selectLongHikes (const vector<Trail>& trails,
                            int minKm) {
  vector<Trail> selected;

  for_each(trails.begin(), trails.end(),
        [&selected, minKm] (const Trail& trail) {
             if (trail.kilometres >=minKm) {
              selected.push_back(trail);
              }
          });

sort (selected.begin(), selected.end (),
    [](const Trail& a, const Trail& b) {
    if (a.kilometres != b.kilometres) {
      return a.kilometres > b.kilometres;
    }

    return a.name < b.name;
  });

  return selected;
}﻿﻿
﻿﻿
```

# Feedback

# Quiz 3

Student: Tolu Aina
Seneca User ID: taina2
Assessment Version: Version 4
Points: **50**/50
Final Mark: **10.00**/10

## Marking

### Question 1 — Function object and collection algorithm
* 3/3 Constructor and state - stores a maximum for each object: 1, public constructor accepts an integer: 1, initializes the stored maximum from the argument: 1
* 4/4 Call operator - defines a public operator(): 1, returns bool: 1, accepts a Trail by const reference: 1, callable on a const IsShortHike object: 1
* 4/4 Short-hike rule - checks that the length is positive: 1, compares the length against the stored upper limit: 1, includes a length equal to the limit: 1, requires both conditions to hold: 1
* 4/4 Collection check - uses any_of: 1, supplies the full trails range: 1, passes an IsShortHike object configured with maxKm: 1, returns the algorithm's Boolean result: 1

### Question 2 — Validation and exception handling
* 4/4 Validation - recognizes zero and negative lengths: 1, throws an exception for an invalid trail: 1, uses runtime_error: 1, supplies the exact message "Invalid trail length": 1
* 3/3 Guide update - appends at the end of the caller's guide: 1, appends the supplied trail: 1, leaves the guide unchanged for an invalid trail: 1
* 2/2 Survey traversal - iterates over the full survey: 1, visits trails in their original order: 1
* 2/2 Protected call - calls recordTrail with the destination guide and current trail: 1, protects each call individually so processing continues after an error: 1
* 1/1 Exception handler - catches runtime_error by const reference: 1
* 3/3 Error reporting - writes to the supplied errors stream: 1, writes the current trail name followed by a colon and a space: 1, writes the exception message from what() followed by a newline: 1

### Question 3 — Selection and sorting
* 2/2 Destination - creates a separate vector of Trail objects: 1, starts the selection empty: 1
* 2/2 Traversal - uses for_each: 1, supplies the full range of the input trails vector: 1
* 4/4 Selection lambda - passes a lambda as the action: 1, accepts the current trail: 1, captures minKm so the threshold is available: 1, captures the destination so additions affect the selected vector: 1
* 2/2 Length threshold - accepts lengths above the minimum and excludes those below it: 1, also accepts a length equal to the minimum: 1
* 2/2 Selected trails - appends the complete qualifying trail: 1, retains every qualifying occurrence including trails of equal length: 1
* 3/3 Sorting setup - uses sort: 1, supplies the full range of the selected vector: 1, supplies a comparison lambda that accepts two trails: 1
* 3/3 Tie handling - uses names to break ties in length: 1, orders tied trails by name in ascending order: 1, returns false when both lengths and names are equal: 1
* 1/1 Primary ordering - places the longer trail first when lengths differ: 1
* 1/1 Result - returns the completed selection, including an empty vector when no trails qualify: 1

Points: **50**/50
Final Mark: **10.00**/10

## Feedback

Tolu, your answers show strong understanding of function objects, exception handling, lambda captures, and vector algorithms. Your selection includes the boundary, and your sorting handles equal lengths correctly. Keep practising careful typing and checking names when you write C++ under time limits.


# Rubric

```cpp
//# 10

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// Provided in the question
struct Trail {
   string name;
   int kilometres;
};

// Question 1

//+ IsShortHike function object
class IsShortHike {
   int m_maxKm;
public:
   IsShortHike(int maxKm) : m_maxKm(maxKm) {}
   //- 3 Constructor and state - stores a maximum for each object: 1, public constructor accepts an integer: 1, initializes the stored maximum from the argument: 1

   //+
   bool operator()(const Trail& trail) const {
      //- 4 Call operator - defines a public operator(): 1, returns bool: 1, accepts a Trail by const reference: 1, callable on a const IsShortHike object: 1

      //+
      return trail.kilometres >= 1 && trail.kilometres <= m_maxKm;
      //- 4 Short-hike rule - checks that the length is positive: 1, compares the length against the stored upper limit: 1, includes a length equal to the limit: 1, requires both conditions to hold: 1
   }
};

//+ Check for a short hike
bool hasShortHike(const vector<Trail>& trails, int maxKm) {
   return any_of(trails.begin(), trails.end(), IsShortHike(maxKm));
   //- 4 Collection check - uses any_of: 1, supplies the full trails range: 1, passes an IsShortHike object configured with maxKm: 1, returns the algorithm's Boolean result: 1
}

// Question 2

//+ Record one trail
void recordTrail(vector<Trail>& guide, const Trail& trail) {
   if (trail.kilometres <= 0) {
      throw runtime_error("Invalid trail length");
   }
   //- 4 Validation - recognizes zero and negative lengths: 1, throws an exception for an invalid trail: 1, uses runtime_error: 1, supplies the exact message "Invalid trail length": 1

   //+
   guide.push_back(trail);
   //- 3 Guide update - appends at the end of the caller's guide: 1, appends the supplied trail: 1, leaves the guide unchanged for an invalid trail: 1
}

//+ Record a survey
void recordSurvey(vector<Trail>& guide, const vector<Trail>& survey,
                  ostream& errors) {
   for (const Trail& trail : survey) {
      //- 2 Survey traversal - iterates over the full survey: 1, visits trails in their original order: 1

      //+
      try {
         recordTrail(guide, trail);
      }
      //- 2 Protected call - calls recordTrail with the destination guide and current trail: 1, protects each call individually so processing continues after an error: 1

      //+
      catch (const runtime_error& err) {
         //- 1 Exception handler - catches runtime_error by const reference: 1

         //+
         errors << trail.name << ": " << err.what() << '\n';
         //- 3 Error reporting - writes to the supplied errors stream: 1, writes the current trail name followed by a colon and a space: 1, writes the exception message from what() followed by a newline: 1
      }
   }
}

// Question 3

//+ Select long hikes
vector<Trail> selectLongHikes(const vector<Trail>& trails, int minKm) {
   vector<Trail> selected;
   //- 2 Destination - creates a separate vector of Trail objects: 1, starts the selection empty: 1

   //+
   for_each(trails.begin(), trails.end(),
       //- 2 Traversal - uses for_each: 1, supplies the full range of the input trails vector: 1

       //+
       [minKm, &selected](const Trail& trail) {
         //- 4 Selection lambda - passes a lambda as the action: 1, accepts the current trail: 1, captures minKm so the threshold is available: 1, captures the destination so additions affect the selected vector: 1

         //+
         if (trail.kilometres >= minKm) {
            //- 2 Length threshold - accepts lengths above the minimum and excludes those below it: 1, also accepts a length equal to the minimum: 1

            //+
            selected.push_back(trail);
            //- 2 Selected trails - appends the complete qualifying trail: 1, retains every qualifying occurrence including trails of equal length: 1
         }
       });

   //+ Sort the selected hikes
   sort(selected.begin(), selected.end(),
       [](const Trail& left, const Trail& right) {
         //- 3 Sorting setup - uses sort: 1, supplies the full range of the selected vector: 1, supplies a comparison lambda that accepts two trails: 1

         //+
         if (left.kilometres == right.kilometres) {
            return left.name < right.name;
         }
         //- 3 Tie handling - uses names to break ties in length: 1, orders tied trails by name in ascending order: 1, returns false when both lengths and names are equal: 1

         //+
         return left.kilometres > right.kilometres;
         //- 1 Primary ordering - places the longer trail first when lengths differ: 1
       });

   //+
   return selected;
   //- 1 Result - returns the completed selection, including an empty vector when no trails qualify: 1
}
```
