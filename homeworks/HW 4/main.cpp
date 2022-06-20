// ==================================================================
// Important Note: You are encouraged to read through this provided
//   code carefully and follow this structure.  You may modify the
//   file as needed to complete your implementation.
// ==================================================================

#include <cassert>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include "Order.h"
#include "Item.h"
#include "utilities.h"

typedef std::list<Order> OrderList;
typedef std::list<Item> KitchenList;

//Needed for CanFillOrder()
typedef std::list <KitchenList::const_iterator> OrderFillList;

//Helper function
//Returns true if order can be fulfilled, and false otherwise. If true, then
//items_to_remove has iterators to kitchen_completed for all items that are used 
//in the order.
//bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  //OrderFillList &items_to_remove);


int main() {

  OrderList orders;
  KitchenList food_cooking; //current
  KitchenList food_completed; //completed
  std::string token;

  while (std::cin >> token) {
    if (token == "add_order") {
		
      int id, promised_time, n_items;
	    std::string next_item;
      std::list <std::string> order_items;
	    std::cin >> id >> promised_time >> n_items;
      
	    assert(n_items > 0);

        for (int i = 0; i < n_items; i++){
            std::cin >> next_item;
            order_items.push_back(next_item);
        }
	    //initialize an order
	    Order order(id,promised_time,order_items);
	  	add_order(orders,order);
    } else if (token == "add_item") {

      int cook_time = -1;
      std::string name;
      std::cin >> cook_time >> name;
      assert(cook_time >= 0);

      Item item(cook_time,name);
      add_item(food_cooking,item);


    } else if (token == "print_orders_by_time") {
      print_orders_by_time(orders);

    } else if (token == "print_orders_by_id") {
      print_orders_by_id(orders);

    } else if (token == "print_kitchen_is_cooking") {
      print_kitchen_is_cooking(food_cooking);

    } else if (token == "print_kitchen_has_completed"){
      print_completed(food_completed);

    } else if (token == "run_for_time") {
      int run_time = 0;
      std::cin >> run_time;
      assert(run_time >= 0);

      run_for_time(run_time,orders,food_cooking,food_completed);

    } else if (token == "run_until_next") {
      std::cout << "Running until next event." << std::endl;
      run_until_next(orders,food_cooking,food_completed);
    }
  }
}

//if the items in the order is matching kitchen completed


