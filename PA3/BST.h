#ifndef _BST_H
#define _BST_H

#include <iostream>
#include "Node.h"

using namespace std;



template<typename Comparable>
class BST {

private:

	Node<Comparable>* root;


public:
	
	BST() {
		root = nullptr;
	}

	Node<Comparable>* getRoot() {
		return root;
	}

	bool AddContact(Comparable& firstName, Comparable& lastName, Comparable& phoneNumber, Comparable& city);

	bool DeleteContact(Comparable fullName);

	
	void SearchAContact(string str);



	void InOrderPrintToFile();

	void PreOrderPrintToFile();

	void DrawTreeToFile();





};

#include "BST.cpp"

#endif
