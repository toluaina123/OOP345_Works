# OOP345NAA — Assignment 2 feedback

Tolu Aina (taina2)


I reviewed your Assignment 2 submission. I could not find a citation containing an ownership or borrowing statement in the present Archer, Barbarian, CharacterTpl, Guild, Rogue and Team modules. This makes the raw and final assignment grade zero. I searched both companion files wherever present; a citation in either companion would have covered the module.

Raw score: **0/10**. Original Blackboard multiplier: **1.00**. Final Blackboard grade: **0/10**.

The automatic-zero rule takes precedence; the following code guidance is unscored.

## Evidence and improvement guidance


archer: absent ownership/borrowing citation. assignments/assignment 2/archer.h:1–78 (entire file searched).

barbarian: absent ownership/borrowing citation. assignments/assignment 2/barbarian.h:1–95 (entire file searched).

characterTpl: absent ownership/borrowing citation. assignments/assignment 2/characterTpl.h:1–65 (entire file searched).

guild: absent ownership/borrowing citation. assignments/assignment 2/guild.h:1–50 (entire file searched); assignments/assignment 2/guild.cpp:1–213 (entire file searched).

rogue: absent ownership/borrowing citation. assignments/assignment 2/rogue.h:1–93 (entire file searched).

team: absent ownership/borrowing citation. assignments/assignment 2/team.h:1–49 (entire file searched); assignments/assignment 2/team.cpp:1–172 (entire file searched).

Your code — `assignments/assignment 2/archer.h`, lines 1–7:

```cpp
/*
Name: Toluwani Aina
Seneca email: taina2@myseneca.ca
Student ID: 100832237
Date: November 3, 2026

*/
```

Better documentation — if it is truthful for the module, add a citation such as:

```cpp
// I wrote all the code in this module myself, except for code provided by my professor.
```

If you used external code, identify its source and the named functions or clearly marked blocks instead. I do not require a particular template or extra identity/revision metadata for this ownership rule.

## Strengths — unscored formative feedback

I found a useful example of clear, focused implementation steps at `assignments/assignment 2/team.cpp`, lines 106–109:

```cpp
        for (size_t i = 0; i < m_size; ++i) {
            if (m_members[i]->getName() == character->getName()) {
                return;
            }
```
