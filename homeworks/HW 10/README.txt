HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  < insert name >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< insert collaborators / resources >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 8>



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.

------------------------------------------------------------------------------
|          |          | remove   |          | closest  | first f  | longest  |
|          | sort     | dups     | mode     | pair     | sorted   | substr   | 
------------------------------------------------------------------------------
|          | O(nlogn) | O(n^2)   | O(n)     | O(nlogn) |O(nlogn+f)|O(l^2*n^2)|
| vector   |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          | O(nlogn) | O(n^2)   | O(nlogn) | O(nlogn) |O(nlogn+f)|O(l^2*n^2)|
| list     |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          | O(n)     | O(n)     | O(n)     |   O(n)   | O(f)     |O(l^2*n^2)|
| bst      |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          | O(n)     |    X     |   O(n)   | O(n)     |  O(f)    | X        |
| pq       |          |          |          |          |          |          |
------------------------------------------------------------------------------
|          | X        |   O(n)   |   O(n)   | O(n^2)   |    O(1)  |O(l^2*n^2)|
| hash     |          |          |          |          |          |          |
------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

< insert your performance measurements and coefficient estimates >
sort:
vector: 0.37s, k = 6.02*10^-8
list: 0.75s, k = 6.030*10^-8
bst: 0.64s, k = 5.76*10^-7
pq: 0.70s, k = 6.212*10^-7
hash: 1.64s

remove duplicates:
vector: 5.984s, k = 8.39*10^-9
list: 8.703s, k = 2.201*10^-9
bst: 0.609s, k = 1.301*10^-6
pq: infeasible
hash: 0.68s, k = 2.019*10^-5

mode:
vector: 0.0156s, k = 6.24*10^-7
list: 0.03125s, k = 8.556*10^-8
bst: 0.3125s, k = 8.556*10^-8
pq: 0.0157s, k = 6.28*10^-7
hash: 0.0156s, k = 6.24*10^-7

closest pair:
vector: 0.0156s, k = 4.948*10^-8
list: 0.0156s, k = 4.948*10^-8
bst: 0.0156s, k = 7.134*10^-7
pq: 0.0156s, k = 7.134*10^-7
hash: 5.359, k = 1.121*10^-8


first sorted: 
vector: 0.0132, k = 4.278*10^-8
list: 0.03233s, k = 8.555*10^-8
bst: 0.03566s, k = 1.042*10^-3
pq: 0.0930s, k = 0.00052
hash: 0.0469s.

longest substring:
vector: 73.70s, k = 4.411*10^-9
list: 92.875s, k = 5.210*10^-9
bst: 84.372s, k = 4.398*10^-9
pq: infeasible
hash: 90.7031s, k = 2.89*9^-10



DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  

I know this homework won't count but I will still give my thoughts on it.
First, most of the results match my prediction. Many data structures share similar implementaion, such as longest substring, sort, remove duplicates, for vector list, and for bst and hashmap. As a result, their running time and complexity are similar. Some operation, for example sort, on hashmap just doesn't make sense therefore it's infeasible. 
If I want a sorted map, I'll just use regular map. 

Some result are some what different from my prediction. But when I think it again, it is because I did other operations such as looping over or extra boundary checks. 

I learned that different data structures have different advantages on specific operations. For example, if I want to access my array, I would use a hashtable, and sort I will use a min heap(priority queue).


MISC. COMMENTS TO GRADER:  
Optional, please be concise!
