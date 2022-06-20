/*
Write your Rope implementation in this file. 
You do not have to keep any of the code that is already in this file.
Functions that are required that you have not implemented have an assert 0
meaning they will always crash. This should help you make sure you implement
everything.
*/

#include <cassert>
#include "Rope.h"

//Should advance to the next Node using in-order traversal
//It can point at any Node, not just leaves

//in order: left->node->right
rope_iterator& rope_iterator::operator++(){
	//the print function uses operator++
	//we starting at bottom left leaf
	if(ptr_->right){
		//go right 
		ptr_ = ptr_->right;
		//if we can go left, in order
		while(ptr_->left) {
			ptr_ = ptr_->left;
		}
	}else{
		//this means we at a leaf
		//we check if there's a valid parent and we go up if
		//we at a right leaf
		//at a left node: left->parent->right
		//at a right node: go to parent until the parent is not a right node
		while(ptr_->parent && ptr_->parent->right == ptr_ ) {
			ptr_ = ptr_->parent;
		}
		ptr_ = ptr_->parent;
	}

	return *this;
	//assert(0 && "rope_iterator operator++ not implemented!");
}

//Point to the first Node for in-order traversal
rope_iterator Rope::begin() const{
	//borrowed from ds_set
	if(!root) return rope_iterator(NULL);
	Node* p = root;
	//begin at the most left leaf
	while(p->left) {p = p->left;}
	return rope_iterator(p);
	//assert(0 && "rope_iterator begin() not implemented!");
}

//default constructor
Rope::Rope(){
	this->root = NULL;
	this->size_ = 0;
	//assert(0 && "Rope default constructor not implemented!");
}

//Should make the root = p and adjust any member variables
//This should not make a copy of the rope with root at p,
//it should just "steal" the Node*
Rope::Rope(Node* p){
	this->root = p;
	this->size_ = p->weight;
	//since only the right side has greater weight we only need to add 
	//right nodes if there's any
	while(p->right){
		p = p->right;
		this->size_ += p->weight;
	}
	//add all the weight
	//assert(0 && "Rope constructor from Node not implemented!");
}
//borrowed from ds_set
void Rope::destroy_tree(Node*& p){
	if(p != NULL){
		if(p->left){
			destroy_tree(p->left);
		}
		if(p->right){
			destroy_tree(p->right);
		}
		delete p;
	}
};

//destructor
Rope::~Rope(){
	destroy_tree(root);
	this->root = NULL;
}
//borrowed from ds_set
Node* Rope::copy_tree(Node* old,Node* p){
	if(!old) return NULL;
	Node* newNode = new Node;
	newNode->value = old->value;
	newNode->weight = old->weight;
	newNode->left = copy_tree(old->left,newNode);
	newNode->right = copy_tree(old->right,newNode);
	newNode->parent = p;
	return newNode;
}

Rope::Rope(const Rope& r){
	size_ = r.size_;
	root = this->copy_tree(r.root,NULL);
	//assert(0 && "Rope copy constructor not implemented!");
}

Rope& Rope::operator= (const Rope& r){
	if(&r != this){
		//if this is not duplicate
		//destory the tree first
		destroy_tree(root);
		//copy the tree 
		this->root = copy_tree(r.root,NULL);
		//update the size
		this->size_ = r.size_;
	}
	return *this;
	//assert(0 && "Rope assignment not implemented!");
}
//similar to index function but returns the leaf node.
//use it in split. 
Node* Rope::findLeaf(int& i){
	Node* ptr = root;
	while(!is_leaf(ptr)){
		//if the weight is greater than the index
		if(ptr->left || ptr->right){
			if(ptr->weight > i){
				ptr = ptr->left;
			}else if (ptr->weight <= i){
				i -= ptr->weight;
				ptr = ptr->right;
			}
		}
	}
	return ptr;
}

//MUST BE ITERATIVE
//Get a single character at index i
bool Rope::index(int i, char& c) const{
	//decide go left or right
	Node* ptr = root;
	//as long as we haven't reach the leaf yet. 
	while(!is_leaf(ptr)){
		//if the weight is greater than the index
		if(ptr->left || ptr->right){
			if(ptr->weight > i){
				ptr = ptr->left;
			}else if (ptr->weight <= i){
				i -= ptr->weight;
				ptr = ptr->right;
			}
		}
	}
	// we assign c to the character
	c = ptr->value[i];
	return true;
}

//Add the other rope (r)'s string to the end of my string
void Rope::concat(const Rope& r){
	//creating a new root
	Node* newRoot = new Node;
	//make a copy of the right rope
	Rope newRope(r);
	//update weight
	newRoot->weight = this->size_;
	//connnect left
	newRoot->left = root;
	root->parent = newRoot;
	newRoot->right = newRope.root;
	newRope.root->parent = newRoot;
	//poting the copied tree's root to a null to avoid memory leaks.
	newRope.root = nullptr;
	//setting the root.
	root = newRoot;
	this->size_+=newRope.size_;
}
//concat but don't copy right sub tree
void Rope::concatNoCopy(Rope& r){
	Node* newRoot = new Node;
	newRoot->weight = this->size_;
	newRoot->left = root;
	root->parent = newRoot;
	newRoot->right = r.root;
	r.root->parent = newRoot;
	r.root = NULL;
	root = newRoot;
	this->size_+=r.size_;
}

//Get a substring from index i to index j.
//Includes both the characters at index i and at index j.
//String can be one character if i and j match
//Returns true if a string was returned, and false otherwise
//Function should be written with efficient running time.
bool Rope::report(int i, int j, std::string& s) const{
	//bound checking
	if(i > j || i<0 || j <0 || i > size_-1 || j > size_-1) return false;
	s.clear();
	//we add up the characters 
	for(int temp = i; temp <= j; temp++){
		char c;
		index(temp,c);
		s+=c;
	}
	return true;
}
//The first i characters should stay in the current rope, while a new
//Rope (rhs) should contain the remaining size_-i characters.
//A valid split should always result in two ropes of non-zero length.
//If the split would not be valid, this rope should not be changed,
//and the rhs rope should be an empty rope.
//The return value should be this rope (the "left") part of the string
//This function should move the nodes to the rhs instead of making new copies.
Rope& Rope::split(int i, Rope& rhs){
	//find the leaf we're splitting
	//invalid splits
	if(i <= 0 || i > size()){
		std::cout<<"Invalid split index"<<'\n';
		return *this;
	}
	char c;
	index(i,c);
	//update root's weight
	this->size_ -= i;
	//go to the leaf 
	Node* leaf = findLeaf(i);
	//if in the middle
	if(i > 0){
		//create two new leafs
		Node* l = new Node;
		Node* r = new Node;
		//split the string 
		l->value = leaf->value.substr(0,i);
		l->weight = i;
		r->value = leaf->value.substr(i,leaf->value.length());
		r->weight = leaf->value.length()-i;
		leaf->left = l; 
		leaf->right = r;
		l->parent = r->parent = leaf;
		//update weight of each node
		leaf = leaf->right;
	}
	//now the strucutre is adjusted.
	//go up and find the right subtree
	//a vector of ropes tracking our cuts
	std::vector<Rope> ropes;
	//cut the node first
	Node* tmp = leaf->parent;
	leaf->parent->right = nullptr;
	leaf->parent = nullptr;
	ropes.push_back(leaf);
	//update the leaf's parent node's weight. 
	tmp->weight = tmp->left->weight;
	//while we are on the right side we go all the way up.
	while(tmp->parent->right == tmp){
		tmp = tmp->parent; 
		tmp->weight = tmp->left->weight;
	}
	
	//going up from the left
	while(tmp->parent && tmp->parent->left == tmp){
		//update weight
		tmp = tmp->parent;
		Node* updater = tmp;
		int sum =0;
		updater = updater->left;
		sum+=updater->weight;
		//if we have a right subtree
		while(updater->right){
			updater=updater->right;
			sum+=updater->weight;
		}
		tmp->weight = sum;
		//if there exists a right subtree, disconnect it and push it into ropes vector.
		if(tmp->right){
			Node* rightSub = tmp->right;
			tmp->right = nullptr;
			rightSub->parent = nullptr;
			ropes.push_back(rightSub);
		}
	}
	//forming the new tree;
	//if we made one cut 
	if(ropes.size() == 1){	
		Node* newRoot = new Node;
		newRoot->weight = ropes[0].size();
		newRoot->left = ropes[0].root;
		ropes[0].root->parent = newRoot;
		ropes[0].root = newRoot;
		rhs = ropes[0];
	}else{
		//we have two or more cuts;
		Rope longRope(ropes[0]);
		for(uint i = 1; i<ropes.size(); i++){
			//concat the final rope with ropes we cutted. 
			longRope.concatNoCopy(ropes[i]);
		}
		rhs = longRope; //assign rhs rope
	}
	//adjust weight of the root
	//adjust size
	int s = 0;
	//loop over the tree 
	for(rope_iterator itr = begin(); itr!=end(); itr++){
		if(is_leaf(itr.ptr_)) s+= itr.ptr_->weight;
	}
	this->size_ = s;
	this->root->weight = this->size_;

	
	return *this;

}
