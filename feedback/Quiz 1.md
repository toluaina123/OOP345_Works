# Quiz Question(s)

# Quiz 1 — Rule of Five

**Time:** 30 minutes

Assume the following class is fully implemented:

```cpp
class Item {
public:
    Item(const char* name = "");
    void display() const;
};
```

The following class manages a dynamically allocated collection of `Item` objects:

```cpp
class Collection {
    Item* m_items;
    size_t m_count;

public:
    Collection();
    Collection(size_t count);

    // Implement the Rule of Five here
};
```

Assume that the two constructors shown above are already fully implemented and that:

- `m_items` points to a dynamically allocated array of `Item` objects.
- `m_count` contains the number of elements in that array.
- An empty `Collection` has `m_items` set to `nullptr` and `m_count` set to `0`.

## Task

Implement the **Rule of Five** for the `Collection` class:

1. Destructor
2. Copy constructor
3. Copy assignment operator
4. Move constructor
5. Move assignment operator

### Requirements

Your implementation must:

- correctly release dynamically allocated memory;
- perform a **deep copy** for copy operations;
- transfer ownership of the dynamic memory for move operations;
- leave the source object in a safe empty state after a move;
- correctly handle self-assignment where applicable; and
- return the appropriate object from the assignment operators.

Write only the code required to add the Rule of Five to the `Collection` class. You do **not** need to implement `Item`, the existing constructors, or a `main()` function.

# Original Student Answer

## Quiz 1_taina2_attempt_2026-10-02-12-00-17_test.cpp

```cpp
class Item {
public:
    Item(const char* name = "");
    void display() const;
};

Collection :: -Collection 90
{
	delete[] m_items;
}

Collection::Collection (const Collection &other)
{
	m_count = other._count;
	
	if (mc_count > 0)
	{
		m_items = new Item[m_counts];
		
		for (size_t i=0; i < m_count; i++)
		{
			m_items[i] = other.m_items[i];
		}
	}
	else
	{
		m_items= nullptr;
	}
}
return*this;
}

Collections::Collection(Collection && other)
{
	m_itmes = other.m_items;
	m_count = other.m_count;
	
	other.m_items = nullptr;
	other.m_count = 0;
}

Collections& COllection;;operator=(Collection&& other) noexcept
{
	if this != &other)
	{
		delete[] m_items;
		
		m_items = other.m_items;
		m_count = other.m_count;
		
		other.m_items = nullptr;
		other.m_count = 0;
	}
	return * this;
}
```

# Feedback

# Quiz 1

Student: Tolu Aina
Seneca User ID: taina2
Assessment Version: Version 2
Points: **57**/78
Final Mark: **7.31**/10

## Marking

### Destructor

* 1/1 Destructor signature
* 2/2 Releases dynamic memory

### Copy constructor

* 3/3 Copy constructor signature
* 3/3 Initializes copy
* 4/4 Copy allocation
* 4/4 Copies every element

### Copy assignment operator

* 0/4 Copy assignment signature
  - The copy assignment operator is missing.
* 0/2 Self-assignment protection
  - The copy assignment operator is missing.
* 0/2 Releases current memory
  - The copy assignment operator is missing.
* 0/3 Prepares destination
  - The copy assignment operator is missing.
* 0/4 Copy allocation
  - The copy assignment operator is missing.
* 0/4 Copies every element
  - The copy assignment operator is missing.
* 0/2 Returns *this
  - The copy assignment operator is missing.

### Move constructor

* 4/4 Move constructor signature
* 6/6 Transfers ownership
* 6/6 Empties source

### Move assignment operator

* 5/5 Move assignment signature
* 2/2 Self-move protection
* 3/3 Releases current resource
* 6/6 Transfers ownership
* 6/6 Empties source
* 2/2 Returns *this

Points: **57**/78
Final Mark: **7.31**/10

## Feedback

Tolu, your copy constructor and move operations show the required logic. Copy assignment is missing, so its marks could not be awarded. Practise writing all five complete functions and check the function names and syntax before submitting.


# Rubric

```cpp
//# 10

#include <cstddef>
using namespace std;

class Item {
public:
   Item(const char* name = "");
   void display() const;
};

class Collection {
   Item* m_items;
   size_t m_count;

public:
   Collection();              // assumed implemented
   Collection(size_t count);  // assumed implemented

   //+ Destructor
   ~Collection() {
      //- 1 signature - destructor: 1

          //+
      delete[] m_items;
      //- 2 releases dynamic memory - delete[]: 1, m_items: 1
   }

   //+ Copy constructor
   Collection(const Collection& other) {
      //- 3 signature - Collection: 1, const: 1, Collection&: 1

          //+
      m_items = nullptr;
      m_count = other.m_count;
      //- 3 initializes copy - m_items to nullptr: 1, m_count: 1, other.m_count: 1

      //+
      if (m_count > 0) {
         m_items = new Item[m_count];
      }
      //- 4 allocation - condition: 1, m_items: 1, new Item[]: 1, m_count: 1

      //+
      for (size_t i = 0; i < m_count; i++) {
         m_items[i] = other.m_items[i];
      }
      //- 4 deep copy - loop through elements: 2, destination element: 1, source element: 1
   }

   //+ Copy assignment operator
   Collection& operator=(const Collection& other) {
      //- 4 signature - Collection& return type: 1, operator=: 1, const: 1, Collection& parameter: 1

          //+
      if (this != &other) {
         //- 2 self-assignment protection - this: 1, &other comparison: 1

             //+
         delete[] m_items;
         //- 2 releases current memory - delete[]: 1, m_items: 1

         //+
         m_items = nullptr;
         m_count = other.m_count;
         //- 3 prepares destination - nullptr: 1, m_count: 1, other.m_count: 1

         //+
         if (m_count > 0) {
            m_items = new Item[m_count];
         }
         //- 4 allocation - condition: 1, m_items: 1, new Item[]: 1, m_count: 1

         //+
         for (size_t i = 0; i < m_count; i++) {
            m_items[i] = other.m_items[i];
         }
         //- 4 deep copy - loop through elements: 2, destination element: 1, source element: 1
      }

      //+
      return *this;
      //- 2 return - return: 1, *this: 1
   }

   //+ Move constructor
   Collection(Collection&& other) {
      //- 4 signature - Collection: 1, Collection&&: 2, source parameter: 1

          //+
      m_items = other.m_items;
      m_count = other.m_count;
      //- 6 transfers ownership - destination pointer: 1, source pointer: 1, destination count: 1, source count: 1, no allocation: 1, ownership transfer: 1

      //+
      other.m_items = nullptr;
      other.m_count = 0;
      //- 6 empties source - source pointer: 1, nullptr: 1, source count: 1, zero: 1, prevents shared ownership: 1, safe empty state: 1
   }

   //+ Move assignment operator
   Collection& operator=(Collection&& other) {
      //- 5 signature - Collection& return type: 1, operator=: 1, Collection&&: 2, source parameter: 1

          //+
      if (this != &other) {
         //- 2 self-move protection - this: 1, &other comparison: 1

             //+
         delete[] m_items;
         //- 3 releases current resource - delete[]: 1, m_items: 1, release before transfer: 1

         //+
         m_items = other.m_items;
         m_count = other.m_count;
         //- 6 transfers ownership - destination pointer: 1, source pointer: 1, destination count: 1, source count: 1, no allocation: 1, ownership transfer: 1

         //+
         other.m_items = nullptr;
         other.m_count = 0;
         //- 6 empties source - source pointer: 1, nullptr: 1, source count: 1, zero: 1, prevents shared ownership: 1, safe empty state: 1
      }

      //+
      return *this;
      //- 2 return - return: 1, *this: 1
   }
};
```
