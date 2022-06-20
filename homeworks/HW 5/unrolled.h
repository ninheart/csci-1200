#ifndef UNROLLED_H
#define UNROLLED_H

#include <iostream>
#include <cmath>
#include <cassert>
#include <list>
//#include "utilities.h"

const int NUM_ELEMENTS_PER_NODE = 6;

//initialize node class
template <class T>
class Node{
public:
	Node(){
		prev=next=NULL;
		numElement = 0;
	};
    Node(const T& v){
		//numElement = v;
		prev=next=NULL;
	}
	
	//accessors
	int getNumElements(){return numElement;}
	//access offset index in elemnts
	const T& offsetIndex(uint offset) const{
		return elements[offset];
	}
	T& offsetIndex(uint offset){
		return elements[offset];
	}
	//erase within a node
	T eraseInNode(int index);
	
	void print(std::ostream& ostr) const;
	//changing number count in the node
	
	//represnetation
	Node<T>* prev;
	Node<T>* next; 
	int numElement = 0;
	//initialize array size of 6
	T elements[NUM_ELEMENTS_PER_NODE];
};

template<class T> class UnrolledLL;

template<class T> 
class list_iterator{
public:
	
	list_iterator(Node<T>* p=NULL) : ptr(p),offset(0){}
	list_iterator(): ptr(nullptr) {}
	list_iterator(Node<T>* p, uint offset) : ptr(p), offset(offset) {}
	list_iterator(const list_iterator<T>& old) : ptr(old.ptr), offset(old.offset) {}
	list_iterator<T>& operator=(const list_iterator<T>& other){
		ptr = other.ptr;
		offset = other.offset;
		return *this;
	}

	//dereference operator
	T& operator*(){
		//output the array in each node
		return ptr->offsetIndex(offset);
	}

	list_iterator<T>& operator++(){
		//we iterate within the node to retrieve 
		if(ptr){
			offset++;
			//we move to the next node 
			if(offset > ptr->numElement-1){
				ptr = ptr->next;
				offset=0;
			}
		}else{
			offset = 0;
		}
		
		return *this;
	}

	list_iterator<T> operator++(int){
		list_iterator<T> temp(*this);
		//if the pointer is va
		if(ptr){
			offset++;
			if(offset > ptr->numElement-1){
				ptr = ptr->next;
				offset=0;
			}
		}else{
			offset = 0;
		}
		return temp;
	}

	list_iterator<T>& operator--(){
		//check if there's no more elements in the node's array
		if(offset == 0){
			//we go back to the previous node
			//first check if previous node is valid
			//we set offset to the previous node's num elements
			ptr = ptr->prev;
			offset = ptr->getNumElements()-1;
	
		}else{
			//we iterate within the node 
			offset--;
		}
		return *this;
	}

	list_iterator<T> operator--(int){
		list_iterator<T> temp(*this);
		if(offset ==0){
			ptr = ptr->prev;
			offset = ptr->getNumElements()-1;
		}else{
			offset--;
		}
		return temp;
	}

	friend class UnrolledLL<T>;
	//compare operators
	bool operator==(const list_iterator<T>& r) const{
		return ptr==r.ptr && offset==r.offset;
	}

	bool operator!=(const list_iterator<T>& r) const{
		return ptr!=r.ptr || offset != r.offset;
	}

private:
	Node<T> *ptr = NULL;//pointer to node
	uint offset = 0;//offset index
};


template <class T>
class UnrolledLL{
public:
	UnrolledLL(): head_(NULL), tail_(NULL), size_(0){}
	UnrolledLL(const UnrolledLL& other){copy_list(other);}
	UnrolledLL& operator=(const UnrolledLL<T>& other);
	~UnrolledLL(){this->destroy_list();}
	typedef list_iterator<T> iterator;

	//accessors and modifiers
	int size() const{return size_;}
	bool empty() const{return head_ == NULL;}
	void clear(){destroy_list();}

	//read/write access to contents
	const T& front() const { return head_->offsetIndex(0);  }
    T& front() { return head_->offsetIndex(0); }
    const T& back() const { return tail_->offsetIndex(tail_->getNumElements()-1); }
    T& back() { return tail_->offsetIndex(tail_->getNumElements()-1); }

	// modify the  list structure
	void push_front(const T&v);
	void pop_front();
    void push_back(const T& v);
    void pop_back();

	//two type of erase, one handling pop front and pop back
	iterator erase(iterator itr,std::string command);
	iterator erase(iterator itr);
	iterator insert(iterator itr, const T& v);
	iterator begin(){
		return head_ != NULL? iterator(head_) : end();
	}
	iterator end(){
		return iterator(nullptr);
	}
	//outputing 
	void print(std::ostream& ostr) const;
	
private:
	//helper function
	void copy_list(const UnrolledLL& other);
	void destroy_list();
	void memory_clear(Node<T>* node);

	//representation
	Node<T>* head_;
	Node<T>* tail_; 
	int size_;
};

template <class T>
UnrolledLL<T>& UnrolledLL<T>::operator=(const UnrolledLL<T>& other){
	if(&other != this){
		destroy_list();
		copy_list(other);
	}
}

//copy a list to another list
template <class T>
void UnrolledLL<T>::copy_list(const UnrolledLL<T>& other) {
	size_ = other.size_;
	//if it's an empty list
	if(size_ == 0){
		head_=tail_=0;
		return;
	}
	
	Node<T>* temp = other.head_;
	head_ = new Node<T>();
	tail_ = head_;
	head_->numElement = temp->numElement;
	for(int i =0; i < temp->numElement;++i){
		head_->elements[i] = temp->elements[i];
	}

	head_->next = nullptr;
	temp = temp->next;
	while(temp){
		tail_->next = new Node<T>();
		tail_->next->prev = tail_;
		tail_ = tail_->next;
		tail_->numElement = temp->numElement;
		for(int i =0; i < temp->numElement;++i){
			tail_->elements[i] = temp->elements[i];
		}
		tail_->next = nullptr;
		temp = temp->next; 
	}
}

template <class T>
void UnrolledLL<T>::push_back(const T& v){
	//check if there's a node
	if(!tail_){
		//if there's not we create a new Node
		Node<T>* newp = new Node<T>(v);
		//fill array with value
		newp->elements[newp->numElement] = v;
		newp->numElement++;
		head_=tail_=newp;

	}else{
		//check if it has been fully filled
		if(tail_->getNumElements()>=NUM_ELEMENTS_PER_NODE){
			//create a new Node
			Node<T>* newp = new Node<T>(v);
			//fill this node's array
			newp->elements[newp->numElement] = v;
			newp->numElement++;
			//we have to connect this node to our list
			newp->prev = tail_;
			tail_->next = newp;
			tail_ = newp;
		}else{
			//we can fill the tail node
			tail_->elements[tail_->numElement] = v;
			//increase size
			tail_->numElement++;
		}
	}
	size_++;
};


template <class T>
void UnrolledLL<T>::push_front(const T& v){
	if(!head_){
		//create a new node
		Node<T>* newp = new Node<T>(v);
		newp->elements[newp->numElement] = v;
		newp->numElement++;
		head_ = tail_ = newp;
	}else{
		//check if we need to create a new node 
		if(head_->getNumElements()>=NUM_ELEMENTS_PER_NODE){
			Node<T>* newp = new Node<T>(v);
			newp->elements[newp->getNumElements()] = v;
			newp->numElement++;
			newp->next = head_;
			head_->prev = newp;
			head_ = newp;
		}else{
			//we push front in the node. 
			//shift index 
			int i;
			for(i = head_->getNumElements()+1; i>=1; --i){
				head_->elements[i] = head_->elements[i-1];
			}

			head_->elements[0] = v;
			head_->numElement++;
		}
	}
	size_++;
}

template<class T>
void UnrolledLL<T>::pop_front(){
	erase(head_,"pop_front");
}

template<class T>
void UnrolledLL<T>::pop_back(){
	erase(tail_,"pop_back");
}

template <class T>
void UnrolledLL<T>::destroy_list(){
	memory_clear(head_);
	head_ = NULL;
	tail_ = NULL;
	size_=0;
}
template <class T>
void UnrolledLL<T>::memory_clear(Node<T>* node){
	if(node != tail_){
		memory_clear(node->next);
	}
	delete node;
}

//print function that display the list
template <class T>
void UnrolledLL<T>::print(std::ostream& out) const{
	out<<"UnrolledLL, size: "<<size_<<'\n';
	Node<T>* temp = head_;
	while(temp){
		out<<" ";
		temp->print(out);
		out<<'\n';
		temp = temp->next;
	}
}

/*Node class implementation*/
template <class T>
void Node<T>::print(std::ostream& out) const{
	out<<"node:["<<numElement<<"] ";
	for(int i = 0;i<numElement;i++){
		out<<elements[i]<<' ';
	}out<<'\n';
}


//erase element in a node's array
template <class T>
T Node<T>::eraseInNode(int index){
	T erasedNumber = elements[index];
	if(getNumElements()-1-index > 0){
		for(int i = index; i < getNumElements()-1;++i){
			elements[i] = elements[i+1];		
		}
	}
	numElement--;
	return erasedNumber;
}


template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr){
	assert(size_ > 0);
	//decrease size of the list
	size_--;
	//access the offset index
	int off = itr.offset;
	iterator nextNode(itr.ptr->next,0);
	iterator nextEle(itr.ptr,off);
	itr.ptr->eraseInNode(off);
	//see if we need to remove the node 
	if(itr.ptr->numElement < 1){
	//we need to erase this node. 
		//we will move to next node 
		//if this the only node in the list
		
		if(itr.ptr == head_ && itr.ptr == tail_){
			head_=tail_=NULL;
		//if this node is the head 
		}else if(itr.ptr == head_){
			head_=head_->next;
			head_->prev=nullptr;
			
		}else if(itr.ptr == tail_){
			tail_ = tail_->prev;
			tail_->next = nullptr;
		}else{
			itr.ptr->prev->next = itr.ptr->next;
			itr.ptr->next->prev = itr.ptr->prev;
		}
		delete itr.ptr;
		return nextNode;
		//we're moving the last element in the list, so move to next node
	}	
	else if(off >= itr.ptr->getNumElements()){
		return nextNode;
	}
	return nextEle;
		
}

/*List iterator implementation*/
//insert within the node and insert a new node
template<class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v){
	//check if we're going to overflow the node
	bool withinNode =false;
	int off = itr.offset;
	//accessing next element or next node
	iterator nxt(itr.ptr,itr.offset+1);
	iterator nxtNode(itr.ptr->next,0);

	if(itr.ptr->getNumElements() >= NUM_ELEMENTS_PER_NODE){
		//we're going create a new node and chop the previous node
		Node<T> *newp = new Node<T>();
		//first copy from offset to end of this node to the new node 
		int holder = itr.ptr->getNumElements();
		int count = 0;
		for(int i = off; i < holder;++i){
			count++;
			//perform copying
			newp->elements[newp->getNumElements()] = itr.ptr->elements[i];
			newp->numElement++;
		}
		//change the size of the array
		for(int i = 0; i < count-1; ++i){
			itr.ptr->numElement--;
		}
		//setting new element 
		itr.ptr->elements[off] = v;
		//connect new node 
		newp->next = itr.ptr->next;
		itr.ptr->next = newp;
		newp->prev = itr.ptr;
		newp->next->prev = newp;
	}else{
		//perform insert within the node 
		withinNode = true;
		//perform index shifting like push front
		int i;
		for(i = itr.ptr->getNumElements()+1; i>off; --i){
			itr.ptr->elements[i] = itr.ptr->elements[i-1];
		}
		//set value
		itr.ptr->elements[off] = v;
		itr.offset++;
		itr.ptr->numElement++;
	}

	size_++;
	if(withinNode){return nxt;}
	return nxtNode;
}

template <class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::erase(iterator itr,std::string command){
	if(size_ < 1){
		std::cerr<<"cannot perform erase operation"<<'\n';
	}
	assert(size_ > 0);
	//decrease size of the list
	--size_;
	//access the offset index
	int off = itr.offset;
	//see if we need to remove the node 
	iterator nxt(itr.ptr,itr.offset+1);
	if(itr.ptr->numElement <= 1){
		//we need to erase this node. 
		itr.ptr->numElement--;
		//we will move to next node 
		iterator result(itr.ptr->next,0);
		//if this the only node in the list
		if(itr.ptr == head_ && itr.ptr == tail_){
			head_=tail_=NULL;
		//if this node is the head 
		}else if(itr.ptr == head_){
			head_ = head_->next;
			head_->next->prev = nullptr;
			
		}else if(itr.ptr == tail_){
			tail_ = tail_->prev;
			tail_->next = nullptr;
		}else{
			itr.ptr->prev->next = itr.ptr->next;
			itr.ptr->next->prev = itr.ptr->prev;
		}
		delete itr.ptr;
		return result;
	}else{
		//we erase within the node 
		//check if we have elements after offset,
		//if there are we need to move the index 
		if(command == "pop_front"){
			off = 0;
			for(int i = off; i<itr.ptr->getNumElements()-1;++i){
				itr.ptr->elements[i] = itr.ptr->elements[i+1];		
			}
		}else if(command == "pop_back"){
			off = itr.ptr->getNumElements()-1;
			for(int i = off; i<itr.ptr->getNumElements()-1;++i){
				itr.ptr->elements[i] = itr.ptr->elements[i+1];		
			}
		}else{
			if(off-itr.ptr->getNumElements()-1>0){
				for(int i = off; i<itr.ptr->getNumElements()-1;++i){
					itr.ptr->elements[i] = itr.ptr->elements[i+1];		
				}
			}
		}
		itr.ptr->numElement--;
	}
	return nxt;
}


#endif