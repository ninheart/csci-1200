#ifndef UTILITIES_H
#define UTILITIES_H

#include <iostream>
#include <cmath>
#include <cassert>
#include <list>
#include "unrolled.h"

/*UnrolledLL class implementation*/


template <class T>
void UnrolledLL<T>::push_back(const T& v){
	//check if there's a node
	if(!tail_){
		//we create a new Node
		Node<T>* newp = new Node<T>(v);
		//fill array
		newp->elements[newp->numElement] = v;
		newp->numElement++;
		head_=tail_=newp;
		//newp->prev = NULL;
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
		//check 
		if(head_->getNumElements()>=NUM_ELEMENTS_PER_NODE){
			Node<T>* newp = new Node<T>(v);
			newp->elements[newp->getNumElements()] = v;
			newp->numElement++;
			newp->next = head_;
			head_->prev = newp;
			head_ = newp;
		}else{
			//std::cout<<head_->numElement<<'\n';
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
		
		//itr.ptr->numElement--;
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
			//std::cout<<"testing"<<'\n';
			itr.ptr->prev->next = itr.ptr->next;
			itr.ptr->next->prev = itr.ptr->prev;
		}
		delete itr.ptr;
		return nextNode;
		//we're moving the last element in the list, so move to next node
	}
	
	else if(off >= itr.ptr->getNumElements()){
		return nextNode;
	}else{
		return nextEle;
	}	
}

/*List iterator implementation*/
//insert within the node and insert a new node
template<class T>
typename UnrolledLL<T>::iterator UnrolledLL<T>::insert(iterator itr, const T& v){
	//check if we're going to overflow the node
	bool withinNode =false;
	int off = itr.offset;
	//std::cout<<itr.ptr->prev->getNumElements()<<std::endl;
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
		//
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
	assert(size_ > 0);
	//decrease size of the list
	--size_;
	//access the offset index
	int off = itr.offset;
	//see if we need to remove the node 
	if(itr.ptr->numElement <= 1){
		//we need to erase this node. 
		//std::cout<<"testing"<<'\n';
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
}


#endif