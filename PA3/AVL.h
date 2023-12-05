#ifndef _AVL_H
#define _AVL_H

#include <iostream>
#include "Node.h"

using namespace std;



template<typename Comparable>
class AVL {

private:

	Node<Comparable>* root;


public:

	AVL() {
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

#include "AVL.cpp"

#endif
