#include "Stack.h"


template <typename T>
Stack<T>::Stack() :head(nullptr){
}//sets head as null in default constructor

template <typename T>
bool Stack<T>::isEmpty() {//returns true if head is null
	if (this->head == nullptr) {
		return true;
	}
	return false;
}

template <typename T>
int Stack<T>::size() {
	if (this->isEmpty()) {
		return 0;
	}
	else {
		int counter = 0;
		Node<T>* traverser = head;
		while (traverser) {
			counter++;
			traverser = traverser->next;
		}
		return counter;
	}
}


template <typename T>
void Stack<T>::push(T& data) {
	
	if (this->isEmpty()) {//if it is empty, directly add to the head
		head = new Node<T>(data,nullptr);

	}
	else {//if it is not empty, add to the beginning of the stack, updating head
		Node<T>* temp = new Node<T>(data, head);
		head = temp;
	}


}

template <typename T>
void Stack<T>::print() {
	if (!this->isEmpty()) {
		Node<T>* temp = head;
		while (temp) {
			cout << temp->data << " ";
			temp = temp->next;
		}
		cout << endl;
	}
}


template <typename T>
void Stack<T>::pop() {//if not empty, deletes the node 
						//pointed by head, and shifting head to the right
	if (!this->isEmpty()) {
		Node <T>* temp = head;
		head = head->next;
		delete temp;
	}

}

template <typename T>
Node<T>* Stack<T>::top() {//returns pointer to head
	return this->head;
}