HOMEWORK 5: UNROLLED LINKED LISTS


NAME:  < Yifu Liu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Myself / cppreference.com, stackoverflow.com, dslist.h handout>

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 6 >



TESTING & DEBUGGING STRATEGY:
Please be concise!  

I don't know if this assignment requires  to dynamically allocate array on heap,
nonetheless, my array on the stack does the job. 


ORDER NOTATION & EVALUATION:
What is the order notation of each of the member functions in your
class? Discuss any differences between the UnrolledLL, dslist, and STL
list classes. Evaluate the memory usage of your initial implementation
in the worst case. Give a specific example sequence of operations
where the data structure is inefficient. What is the average number of
elements per node in this case? 

The order notation of dslist, stl list, and UnrolledLL are similar.
Dslist and stl list have order notation of O(1) since they don't need to consider
copying elements into array inside the node. 

The worst case is each node carries half filled array of elements, which is 3 or less
per node. The most ineffcient operation is keep inserting to a filled node. This will likely
makes the new node half filled and we need to perform copy operation. 



Let integer m be the number of nodes
Let integer n be number of elements in each node  

<---- Node class implementation ---->
print:
O(n): we need to iterate each element in the array
offsetIndex:
O(1): constant time retrieving index 

<---- list iterator implementation ---->
operator*: 
O(1)
operator++: 
O(1)
operator++(int):
O(1)
operator--() && operator--(int): 
O(1)

<---- UnrolledLL implementation ---->
push_back():
O(1)
push_front():
O(1)
erase: 
O(n): we need to find and loop over the array in the node to shift the index 
insert: 
O(n): If we overflow the node we need to create a new node and copy n elements in to the new node;
pop_front():
O(n) if we have a specific index
O(1) without index
pop_back():
O(1);
copy_list: 
O(n*m): copy each node's array
destroy list: 
O(m): since our array is not located on the heap, we only need to delete the node. 

EXTRA CREDIT:
Improved memory usage implementation.  Discussion as outlined in .pdf.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!


