HOMEWORK 4: Pizza Event SimulaTOr (PESto)


NAME:  < Yifu Liu >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Graduate TA / https://www.cplusplus.com/, stackoverflow, geeksforgeeks >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.


ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 7 >


ORDER NOTATION:
For each function, using the variables:

  c = number of items still being cooked
  d = number of items completely cooked, but not yet added to an order
  m = number of different item names available
  o = number of orders that have not been filled and are not expired
  p = min number of items per order
  q = max number of items per order

Include a short description of your order notation analysis.

add_order:
//first I sort the order then I iterate through the order. 
//Sort has O(ologo) and iterate has O(o);
O(o*log(o)+o)
add_item:
Since push_back is O(1), everything I did is to sort the item list. 
O(mlogm)
print_orders_by_time:
sort by time then iterate through order list. 
O(o+ologo)

print_orders_by_id:
sort by id then iterate through orders
O(o+ologo)
print_kitchen_is_cooking:
//iterate through the kitchen should take linear time. 
O(c)

print_kitchen_has_completed:
//still linaer time 
O(d)

run_until_next:

this function has three conditions:
check if there's anything is cooking. 
  first iterate through orders to update time O(o) 
  then iterate through cooking list and update time O(c)
  the time complexity is O(o+c);

check if we can fill any orders
  iterate through orders and update time. O(o)

check if we cannot fill any order or the time has expired. 
  O(o+c).

run_for_time:
  go over cooking list and take the front event; 
  first iterate through orders to check any can be filled O(o);
  CanFill has O(ologo + q + d)
  so we have to run this multiple times 
  we have to iterate through order item list as well
  O(c+o*(logo+q+d)+m)


MISC. COMMENTS TO GRADER:  
Optional, please be concise!






