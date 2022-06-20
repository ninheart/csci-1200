#include <cassert>
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include "Order.h"
#include "Item.h"


typedef std::list<Order> OrderList;
typedef std::list<Item> KitchenList;

//Needed for CanFillOrder()
typedef std::list <KitchenList::const_iterator> OrderFillList;

bool CanFillOrder(const Order &order, const KitchenList &kitchen_completed,
                  OrderFillList &items_to_remove) {
  items_to_remove.clear(); //We will use this to return iterators in kitchen_completed

  //Simple solution is nested for loop, but I can do better with sorting...

  std::list <std::string> order_items = order.getItems();
  order_items.sort(); //O(nlogn)

  std::list<std::string>::const_iterator item_it;
  std::string prev_item = "";
  KitchenList::const_iterator kitchen_it;
  
  for (item_it = order_items.begin(); item_it != order_items.end(); item_it++) {
    bool found = false;

    /*Start back at beginnging of list if we're looking for something else
     *Thanks to sorting the order_items list copy, we know we're done with
       whatever kind of item prev_item was!*/
    if (prev_item != *item_it) {
      kitchen_it = kitchen_completed.begin();
      prev_item = *item_it;
    }

    /*Resume search wherever we left off last time (or beginning if it's a
    new kind of item*/

	//kitchenlist is a list of item object
	//item object getName() returns the name, which is the same as 
    for (; !found && kitchen_it != kitchen_completed.end(); kitchen_it++) {
      if (kitchen_it->getName() == *item_it) {
        items_to_remove.push_back(kitchen_it);
        found = true;
      }
    }

    //If we failed to satisfy an element of the order, no point continuing the search
    if (!found) {
      break;
    }
  }

  //If we couldn't fulfill the order, return an empty list
  if (items_to_remove.size() != order_items.size()) {
    items_to_remove.clear();
    return false;
  }

  return true;
}

//add an order to all orders
void add_order(OrderList& orders, Order& order){
	//if(CanFillOrder(order,))
    orders.push_back(order); //O(1)
    //sort the order
    orders.sort(sortOrders); //O(nlogn)
	  std::cout<<"Received new order #"<<order.getID()<<" due in "<<
    order.getTime()<<" minute(s):"<<'\n';
    //outputing orders
    std::list<std::string> temp = order.getItems(); 
    std::list<std::string>::iterator items_itr = temp.begin();
    for(;items_itr != temp.end(); items_itr++){
        std::cout<<"  "<<*items_itr<<'\n';
    }  
}

//add an order to all orders
void add_item(KitchenList& food_cooking, Item& item){
  //the kitchen is cooking the item. 
  food_cooking.push_back(item);
  std::cout<<"Cooking new "<<item.getName()<<" with "<<item.getTime()<<" minute(s) left."<<'\n';
  //sort with regard to time. 
  food_cooking.sort(compareItem);
}

  //update remaining time on all orders
  //update cooking time
  //if an item can be completed, move to completed
  //check if an order can be fulfilled(all items on the order) if so, remove from orders
  //if cannot be fulfilled, expire it and remove
  //run until next will only resolve one event
void run_until_next(OrderList& orders, KitchenList& food_cooking, KitchenList& food_completed){
  //go over food_completed
  OrderList::iterator orders_itr;
  KitchenList::iterator cooking_itr;
  KitchenList::iterator completed_itr;

  int timeDeduct = 0;
  //first piority
  //remove item from cooking list
  if(food_cooking.size() != 0){
    //keep tracking time elapsed 
    //we take the first item from the cooking list
    //we know that will be our first event, so we take its time
    timeDeduct = food_cooking.front().getTime();
    //we update time elapsed by this event and deduct time from each orders

    for(orders_itr=orders.begin();orders_itr!=orders.end();++orders_itr){
        int c = orders_itr->getTime();
        int n = c-timeDeduct;
        orders_itr->setTime(n);
    }

    std::cout<<"Finished cooking "<<food_cooking.front().getName()<<'\n';
    std::cout<<food_cooking.front().getTime()<<" minute(s) have passed."<<'\n';

    //move the item to completed
    food_completed.push_back(food_cooking.front());
    //remove the item
    food_cooking.pop_front();

    //deduct time from cooking list. 
    for(cooking_itr = food_cooking.begin();cooking_itr!=food_cooking.end();++cooking_itr){
      //decrease all items' time by one minute. 
      int currentTime = 0;
      currentTime = (*cooking_itr).getTime();
      (*cooking_itr).setTime(currentTime-timeDeduct);
    }
  //if we don't have anything cooking list
  }else if(orders.size() != 0){
    //initialize items_to_remove for later CanFillItems

    OrderFillList items_to_remove;
    //iterate through this list and check any order can be filled 

    for(orders_itr=orders.begin();orders_itr!=orders.end();orders_itr++){
        //if this order can be filled
        if(CanFillOrder(*orders_itr,food_completed,items_to_remove)){
            //Thank to the TA that helped figured out iterator-- that caused 
            //memory leak. 
            orders.erase(orders_itr--);
            std::cout<<orders.size()<<'\n';
        //if we cannot fill the order or the order exactly has time of 0, then it's expired 
        }else if(!CanFillOrder(*orders_itr,food_completed,items_to_remove)||orders_itr->getTime() == 0){
            
            std::cout<<"Order # "<<orders_itr->getID()<<" expired."<<'\n';
            //deduct time like we did in the above
            timeDeduct = (*orders_itr).getTime();
            std::cout<<timeDeduct<<" minute(s) have passed."<<'\n';
            //remove from orders
            orders.erase(orders_itr--);
            //update time in orders 
            OrderList::iterator itr = orders.begin();
            for(;itr!=orders.end();++itr){
              itr->setTime(itr->getTime()-timeDeduct);
            }
            //update time in kitchen;
            for(cooking_itr = food_cooking.begin();cooking_itr!=food_cooking.end();++cooking_itr){
              cooking_itr->setTime(cooking_itr->getTime()-timeDeduct);
            }

        }
    }
  }else{
      //nothing in the order list and cooking list. 
      std::cout<<"No events waiting to process."<<"\n";
  }
}

//run for time function runs event multiple times. 
//For me it's different from run until next because it can print out multiple event 
//at the same time. So the implementation is different from that. 

void run_for_time(int run_time,OrderList& orders, KitchenList& food_cooking, KitchenList& food_completed){
  std::cout<<"===Starting run of "<<run_time<<" minute(s)==="<<'\n';
  
  int deduct = 0;
  //total min ran by event
  //it helps if the total events time is less than run_time, we need to make up the left over time
  int total = 0;
  OrderFillList items_to_remove;
  //we could have run_time that is 0, and when it's 0 this function only run once. 
  //use a flag to track run_time value greater than 0 or not
  bool flag = false;
  if(run_time == 0) flag = true;
  //run until time is reached or there's nothing in the cooking list. 
  while(run_time >= 0 && food_cooking.size() >0){
      //if we still able to cook

      if(food_cooking.size() != 0){
        //keep tracking time elapsed 
        //we take the least time item in the cooking list
        deduct = food_cooking.front().getTime();
        //total adds all deduct time and calculates left over time after the while loop
        total+=deduct;
        //temp holder holds multiple events if that happens. 
        KitchenList tempItemHolder;
        tempItemHolder.push_back(food_cooking.front());
        food_completed.push_back(food_cooking.front());
        food_cooking.pop_front();
        
        
        KitchenList::iterator temp = food_cooking.begin();
        //if we can fill multiple events we need to move it to completed
        //And events happened in this time frame. 
        for(;temp != food_cooking.end(); ++temp){
          if((*temp).getTime() == deduct){
            tempItemHolder.push_back(*temp);
            food_completed.push_back(*temp);
            food_cooking.erase(temp--);
          }
        }
        //initialize iterators. 
        OrderList::iterator orders_itr;
        std::list<Order> filledOrders;
        std::list<Order> expiredOrders;

        //check if any orders have been filled.        
        for(orders_itr=orders.begin();orders_itr!=orders.end();++orders_itr){
          //deduct time from each order. 
          int newTime = (*orders_itr).getTime()-deduct;
          (*orders_itr).setTime(newTime);
          //if we can fill this order and the time does not exceed
          if(newTime >= 0 && CanFillOrder(*orders_itr,food_completed,items_to_remove)){
            
            OrderFillList::iterator remove = items_to_remove.begin();
            //remove items from completed list
            for(;remove!=items_to_remove.end();++remove){
              food_completed.erase(*remove);
            }
            //display filled orders later 
            filledOrders.push_back(*orders_itr);
            orders.erase(orders_itr--);
            //if we cannot fill this order and time is tie with running time
          }else if(newTime == 0 && !CanFillOrder(*orders_itr,food_completed,items_to_remove)){
            //std::cout<<"ties"<<'\n';
            expiredOrders.push_back(*orders_itr);
            orders.erase(orders_itr--);
            // case where we have negative time, we expire it immediately. 
          }else if(newTime < 0){
            std::cout<<"Order # "<<orders_itr->getID()<<" expired."<<'\n';
            orders.erase(orders_itr--);
          }
        }

        //thisRoundItr represents events happend in this time frame
        KitchenList::iterator thisRounditr = tempItemHolder.begin();
        for(;thisRounditr != tempItemHolder.end(); ++thisRounditr){
          std::cout<<"Finished cooking "<<(*thisRounditr).getName()<<'\n';
        }
        tempItemHolder.clear();
        //we display orders that are expired. 
        std::list<Order>::iterator expired_iterator = expiredOrders.begin();
        for(;expired_iterator != expiredOrders.end();++expired_iterator){
          std::cout<<"Order # "<<expired_iterator->getID()<<" expired."<<'\n';
        }
        //we sort orders by least time. 
        filledOrders.sort(sortOrders);
        std::list<Order>::iterator filled_itr = filledOrders.begin();
        for(;filled_itr!=filledOrders.end();++filled_itr){
          std::cout<<"Filled order #"<<filled_itr->getID()<<'\n';
          //we make a copy of items in the order and display them.  
          std::list<std::string> copyItems = filled_itr->getItems();
          std::list<std::string>::iterator item_itr=copyItems.begin();
          for(;item_itr!=copyItems.end();++item_itr){
            std::cout<<"Removed a "<<*item_itr<<" from completed items."<<'\n';
          }
        }

        //go through items in the kitchen and update the time
        KitchenList::iterator cooking_itr = food_cooking.begin();
        for(;cooking_itr!=food_cooking.end();++cooking_itr){
          //decrease all items' time by this time frame.
          int currentTime = cooking_itr->getTime();
          cooking_itr->setTime(currentTime-deduct);
        }
      }
      //if run_time is 0, we run this function one time only. 
      if(flag){break;}
      else{continue;}
  }

  //left over minutes that from total run_time, we have to update all orders by that time. 
  //we deduct total events time from run_time. 
  int leftOver = run_time-total;
  OrderList::iterator tmpItr = orders.begin();
  for(;tmpItr != orders.end();++tmpItr){
    int current = tmpItr->getTime();
    int newT = current - leftOver;
    tmpItr->setTime(newT);
  }
  std::cout<<"===Run for specified time is complete==="<<'\n';
}

void print_orders_by_id(OrderList& orders){
  orders.sort(sortById);
  std::cout<<"Printing "<<orders.size()<<" order(s) by ID:"<<'\n';
  OrderList::iterator itr = orders.begin();
  for(;itr != orders.end(); ++itr){
    std::cout<<"  #"<<itr->getID()<<" ("<<itr->getTime()<<" minute(s) left):"<<'\n';
    std::list<std::string> items = itr->getItems();
    std::list<std::string>::iterator item_it = items.begin();
    for(;item_it!=items.end(); ++item_it){
      std::cout<<"    "<<*item_it<<'\n';
    }
  } 
}

void print_orders_by_time(OrderList& orders){
  orders.sort(sortByTime);
  std::cout<<"Printing "<<orders.size()<<" order(s) by promised time remaining:"<<'\n';
  
  OrderList::iterator itr = orders.begin();
  for(;itr != orders.end(); ++itr){
    std::cout<<"  #"<<itr->getID()<<" ("<<itr->getTime()<<" minute(s) left):"<<'\n';
    
    std::list<std::string> items = itr->getItems();
    std::list<std::string>::iterator item_it = items.begin();
    for(;item_it!=items.end(); ++item_it){
      std::cout<<"    "<<*item_it<<'\n';
    }
  }  
  
}

void print_kitchen_is_cooking(KitchenList& food_cooking){
  std::cout<<"Printing "<<food_cooking.size()<<" items being cooked:"<<'\n';
  KitchenList::iterator cooking_itr = food_cooking.begin();
  for(;cooking_itr!= food_cooking.end(); ++cooking_itr){
    std::cout<<"  "<<cooking_itr->getName()<<" ("<<cooking_itr->getTime()<<" minute(s) left)"<<'\n';
  }
}

void print_completed(KitchenList& food_completed){
  std::cout<<"Printing "<<food_completed.size()<<" completely cooked items:"<<'\n';
  KitchenList::iterator cooking_itr = food_completed.begin();
  for(;cooking_itr!= food_completed.end(); ++cooking_itr){
    std::cout<<"  "<<cooking_itr->getName()<<'\n';
  }
}

