# DFA-NFA
 Count Strings Problem: Hacker Rank


Given a regular expression and an integer, , count how many strings of length are recognized by it.

Sources Used for reference:
https://www.cs.york.ac.uk/fp/lsa/lectures/REToC.pdf
https://en.wikipedia.org/wiki/Nondeterministic_finite_automaton
https://en.wikipedia.org/wiki/Powerset_construction
And a bit of insipiration from:
https://github.com/kennyledet/Algorithm-Implementations/blob/master/Thompsons_Construction_Algorithm/C%2B%2B/AlexMathew/RE_to_NFA.cpp

Steps:
1) Parsing ---> converting Infix regex to Postfix

2) Postfix Expression---> NFA (Thompson Algorithm)

3) NFA --> DFA (Subset Construction Algorithm)

4)DFA-->Adjacency MAtrix
