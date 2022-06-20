HOMEWORK 9: IMDB SEARCH


NAME:  < Yifu Liu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< None / stackoverflow >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 40 hours >


HASH FUNCTION DESCRIPTION
The hash function hashes the key that is made by combination of a movie's information. 
Essentially, I concat the strings from the movie and use the hash function provided in ds_set 
to create the hash value. 

My query implementation is similar to a movie object. It has all the information about a movie. 
By using the provided permutation function, I'm able to generate 64 different queries of one movie. 

Insert: When I want to insert a key value pair, I first check if the index is empty. If it's empty insert it. If it's not then check see if the movie object belongs to that bucket, by checking the hash value. The last case is it doesn't match, I'll perform linear probing to find the next available bucket that has the same hash value. 

Resize: I create a new m_table and perform insertion from the old table. The insertion will rehash the value just like insert above. 

Find: find is straightforward. it's like the insert and all we have to do is to find the matching hash value.



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


