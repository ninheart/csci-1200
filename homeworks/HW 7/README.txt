HOMEWORK 7: WORD FREQUENCY MAPS


NAME:  < Yifu Liu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Myself  / geeksforgeeks, submitty handouts >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 6 hours >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

n = total number of words in the sample text file
m = number of unique words in the file
w = width of the sequencing window
p = average number of words observed to follow a particular word
x = the number of words that should be generated

How much memory will the map data structure require, in terms of n, m,
w, p, x (order notation for memory use)?

The memory is O(w*m*p) because map data structure doesn't care about total words in the input file.

What is the order notation for performance (running time) of each of
the commands?

For Loading is O(nlogm), it finds the word, if it cannot, insert a pair. If it finds one check
its previos word and increase count.  The worst case is to insert a new word to the map. 

For printing, we first find the word in the map, which is O(logn). Next we locate the inner map word and print out each word,
which is O(p). The total time complexity is O(p+logn)

For generating, we find the word in outter map, then go through the inner map to find the next or next next word. Then we jump to the next next word. 
Therefore the time complexity is O(logm+logn+p).

EXTRA CREDIT
Parsing & using punctuation data, implementation supports *any*
window size, new test cases (describe & summarize performance, but
don't include large datasets with submission).



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


