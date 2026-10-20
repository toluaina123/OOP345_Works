# Quiz Question(s)

# Generic Locker Management

**Duration:** 25 minutes  
**Total Marks:** 10

A facility uses lockers to hold different types of belongings. Each locker has a fixed maximum capacity and is assigned to a supervisor.

Assume the following classes are fully implemented:

```cpp
class Belonging {
   string m_description;
   float m_weight;
public:
   Belonging();
   Belonging(const string& description, float weight);
   float weight() const;
};

class Supervisor {
   string m_name;
public:
   Supervisor(const string& name);
   const string& name() const;
};
```

## Your Task

Implement a class template named `Locker` that meets the following requirements:

1. The template must accept a type parameter `T` representing the type of belongings stored, and an integer template parameter `SIZE` representing the maximum number of belongings.
2. Each locker must contain its own fixed-size array of `SIZE` belongings of type `T`. The belongings belong to the locker and have the same lifetime as the locker.
3. The locker must keep track of the number of belongings currently stored, initially zero.
4. Each locker is assigned to an existing `Supervisor` object. The supervisor must not be copied or owned by the locker, and must remain accessible throughout the locker's lifetime.
5. The constructor must receive a `Supervisor` object and establish the required relationship.
6. Implement `bool insert(const T& belonging)` to add a belonging to the end of the stored belongings if space is available. Return `true` if the belonging is added and `false` if the locker is full.
7. Implement `const T& operator[](int index) const` to return the belonging at the specified index. Assume the index is always valid.
8. Implement `int count() const` to return the number of belongings currently stored.
9. Implement `const Supervisor& supervisor() const` to return the supervisor assigned to the locker.

## Instructions

- Write the complete definition of the `Locker` class template.
- All member functions must be implemented inside the class.
- Do not write a `main()` function.
- Do not include any header files.
- Assume all required headers and namespace declarations are already provided.
- You may assume that `T` is default-constructible and copy-assignable, and that `SIZE` is greater than zero.

# Original Student Answer

## Quiz 2_taina2_attempt_2026-10-16-12-03-38_test.cpp

```cpp
class Belonging {
   string m_description;
   float m_weight;
public:
   Belonging();
   Belonging(const string& description, float weight);
   float weight() const;
};
 
class Supervisor {
   string m_name;
public:
   Supervisor(const string& name);
   const string& name() const;
};

/* My Version*/

template <typename T, int Size>
class Locker {
private:
T m_belongings{SIZE];
int  m_count;
const Supervisors& m_supervisor;

public
Locker(const Supervisors& supervisor)
: m_count(0), m_supervisor(supervisor) {
}
bool insert(const T& belonging) {
	if (m_const >= SIZE) {
		return false;
	}
	
	m_belonging[m_count] = belonging;
	++m_count;
	return true;
}

const T& operator[](int index) const (
return m_belonging [index];
}
int count() const{
	return m_count;
}

const Supervisor& supervisor() const{
	return m_supervisor;
	}
};
```

# Feedback

# Quiz 2

Student: Tolu Aina
Seneca User ID: taina2
Assessment Version: Version 2
Points: **30**/30
Final Mark: **10.00**/10

## Marking

### Class Template
* 6/6 Template declaration

### Composition
* 4/4 Owned storage
* 2/2 Item counter

### Aggregation
* 6/6 Supervisor relationship

### Constructor
* 3/3 Constructor

### Insert Function
* 2/2 Signature
* 4/4 Insert logic

### Accessors
* 1/1 Subscript operator
* 1/1 Count accessor
* 1/1 Supervisor accessor

Points: **30**/30
Final Mark: **10.00**/10

## Feedback

Tolu, your solution shows the required template, owned array, supervisor reference, and zero counter. The insertion logic and accessors are correct in intent. Check names and punctuation carefully: keep SIZE, m_count, m_belongings, and Supervisor consistent, and use matching brackets and braces. The small writing errors do not hide the C++ knowledge shown here.

# Rubric

```cpp

//# 10

//+ Class Template
template <typename T, int SIZE>
//- 6 Template declaration - template keyword: 1, typename: 1, T: 1, int: 1, SIZE: 1, correct template parameter syntax: 1

class Locker {
   //+ Composition
   T m_belongings[SIZE];
   //- 4 Owned storage - array member: 1, element type T: 1, array size SIZE: 1, direct storage as a member (not externally owned): 1

   //+
   int m_count{};
   //- 2 Item counter - integer member: 1, initialized to zero: 1

   //+ Aggregation
   const Supervisor& m_supervisor;
   //- 6 Supervisor relationship - Supervisor type: 1, member declaration: 1, reference instead of owned object or pointer: 3, const qualification: 1

public:
   //+ Constructor
   Locker(const Supervisor& supervisor)
      : m_supervisor(supervisor) {}
   //- 3 Constructor - correct constructor signature: 1, accepting Supervisor by const reference: 1, initializing m_supervisor with the supplied supervisor: 1

   //+ Insert Function
   bool insert(const T& belonging) {
      //- 2 Signature - bool return type: 1, const T& parameter: 1

         //+
      bool success = false;
      if (m_count < SIZE) {
         m_belongings[m_count++] = belonging;
         success = true;
      }
      return success;
      //- 4 Insert logic - capacity check: 1, storing at the next available position: 1, incrementing count after insertion: 1, correct success/failure return: 1
   }

   //+ Accessors
   const T& operator[](int index) const {
      return m_belongings[index];
   }
   //- 1 Subscript operator - correct const-qualified accessor returning the indexed belonging by const reference: 1

   //+
   int count() const {
      return m_count;
   }
   //- 1 Count accessor - returns the stored belonging count without modifying the object: 1

   //+
   const Supervisor& supervisor() const {
      return m_supervisor;
   }
   //- 1 Supervisor accessor - returns the associated supervisor by const reference without copying it: 1
};

```
