HOMEWORK 8: ROPES


NAME:  < Yifu Liu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Ben / Stackoverflow, submitty handouts, ds_set >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >

BALANCED/WORST CASE RUNNIG TIME ANALYSIS:
n = characters in the string of the current Rope (*this)
m = characters in the string of the Rope passed in (for functions that take
    a second rope)
v = longest "value" of a leaf
p = longest path from root to a leaf
Using these variables, state and explain the big-O running time of each 
of the following operations two ways: 1) with a balanced Rope, 2) with an 
extremely unbalanced Rope. Explain what you considered an extremely 
unbalanced rope for the string "Hello my name is Simon".

Copy Constructor:
The time complexity of copy constructor would be O(nlogn).
We go to each nodes in the old tree and link left and right to the new tree.
Which requires O(logn) time per node. 

Construct from Node*:
O(1): Since we are just connceting the root to the Node. 

Index:
O(p): The worst case is to go all the way right or all the way left to reach the leaf node. 
So we assume that it has the longest path.

Report:
O(v): The worst case will be going through the entire string. Therefore it has O(v) time complexity
iterator operator++:
O(1): Because each time we are going to the next node, which is one step regardless of the direction. 

Split:
O(v+p): first we find the leaf that we need to split. It will be O(p) becasue we could be splitting the last index. Then I go up to find if we can split right tree. Disconnecting and linking nodes will take O(1) time. Finally, we assign rhs rope to the rope we concated(different concat, without copying). The operator = has a time
complexity of O(m+n) because it first destroy the passed in tree, then copy the current tree. The overall time complexity will be O(m+p+n).

Concat:
O(m): We will be copying the right subtree, and the worst case is copy n-1 of the tree.  

TESTING & DEBUGGING STRATEGY: 
Briefly describe the tests in your StudentTests() function.
How did you test the "corner cases" of your implementation?

For most times, I use memory debugger on Submitty. 
In the student tests, I test different splits and invalid splits. 
Then I test concat which after splitting two strings. 
Finally, I test copy and assignment operators. 


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)

