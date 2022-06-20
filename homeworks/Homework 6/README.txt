HOMEWORK 6: STAR BATTLE


NAME:  < Yifu Liu >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< None / Stackoverflow >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of zones (z)? 
The average number of squares in a zone (t) 
The number of stars per zone(s)? 
etc.

My recursion go through each region. First I fill the region by trying different coordinates and once the rgion has been filled, the function move to the next region by increase region parameter. 

The time complexity of going through the region and its coordinate will be O(Zxt);

The valid function checks if we can place the star. The time complexity is O(t);

If the star is more than one, the time complexity will multiply by the star number since we have to put S in the zone. The time complexity is O(ZxtxS);

When it comes to check unique solution, I compare the board with other boards stored in the solution vector. The time complexity is O(s x number of solutions). I compare stars' coordinate to see if the solution is unique. 


DESCRIPTION OF YOUR ADDTIONAL PUZZLES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).

Interesting test cases are larger ones because it takes time to compile. 

SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES:
# of solutions & approximate wall clock running time for different
puzzles / stars per zone for a single solution or all solutions. Be
specific about which puzzle/parameters you were timing.

For custome 1 the time is around 0.00375s
For custome 2 the time is around 0.006s;
The time may increase or decrease based on number of stars


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


