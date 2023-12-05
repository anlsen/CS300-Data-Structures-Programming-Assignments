#ifndef _STACK_H
#define _STACK_H
 
#include <iostream>

using namespace std;

template <typename T>
struct Node {
	//Reference type because we need to deal with exactly the same cells in both
	//stack and mazeVector
	T & data;
	Node<T>* next;

	Node(T & _data, Node<T>* _next):data(_data),next(_next) {
		
	}


};


template <typename T>
class Stack {

private:
	
	Node<T>* head;


public:

	Stack();//default constructor
	
	void push(T&);//pushes onto stack

	void pop();//pop the element on top

	Node<T>* top();//returns the pointer pointing to the top element of the stack

	bool isEmpty();//check if the stack is empty

	int size();//returns the total elements in stack

	void print();//prints out the stack

	/*print and size functions are not used in the main program but
	they are the general functions that could be used in stack implementation*/
};

#include "Stack.cpp"
#endif