HOMEWORK 3: CONNECT FOUR


NAME:  < Yifu Liu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< None / geeksforgeeks stackoverflow >

Remember: Your implementation for this assignment must be done on your
own, as described in the "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 7 >



ORDER NOTATION:
For each of the functions below, write the order notation O().
Write each answer in terms of m = the number of rows and n = the
number of columns.  You should assume that calling new [] or delete []
on an array will take time proportional to the number of elements in
the array.

insert (excluding checking for connected four)
My insert has three different cases,
within the bound, out of column bound and out of row bound
if it's within the bound the time complexity is O(m); which creates a new array that has a size of row 
and copy the old array then add token in it.

If it's out of column bound the time complexity is O(n+m+m*n).
First it creates a new m_data array, so it will copy the old array which is O(n) time complexity
Then it copys old row array, which is O(m);
Finally it adds the new array, which is the same as the previous, O(m*n);


insert (including checking for connected four)
THe time complexity is O(2*m*n), it first check if there's a connected four in the column, which will iterate through the row number. Then it checks if there's a connected four in the row, which will iterate through the column number. 

numTokensInColum
it takes the column number and iterate through the row, 
therefore the function depends on the size of the row
O(m)

numTokensInRow
it takes the row number and iterate through it, 
therefore the function depends on the size of the column.
O(n)

numColumns
the function returns a member variable which the time is constant
O(1)

numRows
the function returns a member variable which the time is constant
O(1)
print
the function iterate through the row then the column, therefore the time
is m*n
O(m*n)

clear


TESTING & DEBUGGING STRATEGY: 
Discuss your strategy for testing & debugging your program.  
What tools did you use (gdb/lldb/Visual Studio debugger,
Valgrind/Dr. Memory, std::cout & print, etc.)?  How did you test the
"corner cases" of your Matrix class design & implementation?

Most of the time I use std::cout and commnet to debug. It is efficient and tells me which 
section of the code creates a problem. 

MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

