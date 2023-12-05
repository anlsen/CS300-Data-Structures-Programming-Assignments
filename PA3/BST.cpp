#include "BST.h"

#include <sstream>
#include <fstream>



//Adds new node to tree structure
template<typename Comparable>
Node<Comparable>* addHelper(Node<Comparable>* root, Comparable& firstName, Comparable& lastName,
	Comparable& phoneNumber, Comparable& city,bool& isSuccessful,Comparable& fullName) {
	if (root == nullptr) {
		//We are adding a node, updating boolean variable
		isSuccessful = true;
		return new Node<Comparable>(firstName, lastName, phoneNumber, city);
		
	}
	else {
		if (root->data > (fullName)) {
			root->left=addHelper(root->left, firstName, lastName, phoneNumber, city,isSuccessful,fullName);
		}
		else if (root->data < (fullName)) {
			root->right=addHelper(root->right, firstName, lastName, phoneNumber, city,isSuccessful,fullName);
		}
		else {
			//that means we have already had the data before
			//so keeping our boolean variable "isSuccessful" as false
		}
		return root;
	}
	
}
//returns the root's tree's leftmost element
template<typename Comparable>
Node<Comparable>* findMin(Node<Comparable>* root) {
	while (root->left != nullptr) {
		root = root->left;
	}
	return root;

}

template<typename Comparable>
Node<Comparable>* deleteHelper(Node<Comparable>* root, string fullName,bool& isSuccessful) {
	
	if (root == nullptr) {
		//there is no such fullName
		//updating boolean as false
		isSuccessful = false;
		return root;
	}
	else if (root->data < fullName) {
		root->right = deleteHelper(root->right, fullName,isSuccessful);
		return root;
	}
	else if (root->data > fullName) {
		root->left = deleteHelper(root->left, fullName,isSuccessful);
		return root;
	}
	else {
		//At this point root is pointing to the node that is supposed to be deleted
		

		//Leaf node could be simply deleted
		if (root->right == nullptr && root->left == nullptr) {
			delete root;
			return nullptr;

		}
		//Copying the minimum element in the right subtree of the current node
		//then deleting the node that we have just copied through recursive call
		else if (root->right != nullptr && root->left != nullptr) {
			Node<Comparable>* temp = findMin(root->right);
			root->data = temp->data;
			root->firstName = temp->firstName;
			root->lastName = temp->lastName;
			root->city = temp->city;
			root->phoneNumber = temp->phoneNumber;


			root->right = deleteHelper(root->right,root->data,isSuccessful);
			return root;
		}

		//Deleting the current node and connecting the upper node with
		//current node's left/right child
		else if (root->right == nullptr && root->left != nullptr) {
			Node<Comparable>* temp = root;
			root = root->left;
			delete temp;
			return root;

		}
		else  {
			Node<Comparable>* temp = root;
			root = root->right;
			delete temp;
			return root;

		}

	}

}
//adds new contact, if it is not successful, returns false
template<typename Comparable>
bool BST<Comparable>::AddContact(Comparable& firstName, Comparable& lastName,
	Comparable& phoneNumber, Comparable& city) {
	bool check = false;

	string fullName = firstName + " " + lastName;

	root = addHelper(this->root, firstName,lastName,
		 phoneNumber,  city, check,fullName);

	return check;
}
//deletes the inputted contact, if it is not successful, returns false

template<typename Comparable>
bool BST<Comparable>::DeleteContact(Comparable fullName) {
	bool check = true;
	root = deleteHelper(this->root,string(fullName),check);

	return check;
}


//Returns true, if partial string is in a fullName
bool doesIncludeBST(string partialStr, string fullName) {
	for (int i = 0;i < partialStr.length();i++) {
		if (partialStr[i] != fullName[i]) {
			return false;
		}
	}
	return true;
}


//prints out matching contact containing string

template <typename Comparable>
void searchBST(Node<Comparable>* root, string str) {


	if (root != nullptr) {


		if (doesIncludeBST(str, string(root->data))) {


			cout << root->data << " " << root->phoneNumber << " " << root->city << endl;


			//if we find a matching pair then the rest of matching contacts
			//will be in the subtrees of the first found contact
			searchBST(root->left, str);


			searchBST(root->right, str);
		}

		else {
			//Usual search method until we find a contact containing partial string
			if (str < root->data) {
				searchBST(root->left, str);
			}
			else {
				searchBST(root->right, str);
			}
		}




	}


}





template <typename Comparable>
void BST<Comparable>::SearchAContact(string str) {

	searchBST(root,str);

	
}

//Prints out the preorder to the file
template <typename Comparable>
void preOrderPrintHelperBST(Node<Comparable>* root,ofstream& file) {
	if (root != nullptr) {

		file << root->data << " " << root->phoneNumber << " " << root->city << endl;
		preOrderPrintHelperBST(root->left, file);
		preOrderPrintHelperBST(root->right, file);
	}
}
//Prints out the inorder to the file
template <typename Comparable>
void InOrderPrintHelperBST(Node<Comparable>* root, ofstream& file) {
	if (root != nullptr) {
		InOrderPrintHelperBST(root->left, file);
		file << root->data << " " << root->phoneNumber << " " << root->city << endl;
		InOrderPrintHelperBST(root->right, file);
	}
}




template <typename Comparable>
void BST<Comparable>::PreOrderPrintToFile() {

	ofstream preOrderFile;
	preOrderFile.open("phonebookPreOrderBST.txt");

	preOrderPrintHelperBST(root, preOrderFile);



}
template <typename Comparable>
void BST<Comparable>::InOrderPrintToFile() {

	ofstream inOrderFile;
	inOrderFile.open("phonebookInOrderBST.txt");

	InOrderPrintHelperBST(root, inOrderFile);


}

//Prints out the tree structure to the file

template <typename Comparable>
void drawHelperBST(Node<Comparable>* root, ofstream& file, int level, bool isLeft, string printStr) {
	if (root != nullptr) {
		level++;




		file << printStr;
		//if the Node is root
		if (level == 0) {
			file << "|__";
		}
		//if it is left subtree

		else if (isLeft) {
			file << "--";
		}
		//if it is right subtree

		else {
			file << "__";
		}




		file << root->data << endl;




		if (isLeft || level == 0) {
			printStr += "  |";
		}
		else {

			//if we are on the right subtree that means the next element that is going to be displayed
			//will not have | symbol

			//getting rid of | symbol
			printStr = printStr.substr(0, printStr.length() - 1);
			//appending double whitespace instead and adding | symbol for further nodes
			printStr += "  |";
		}

		drawHelperBST(root->left, file, level, true, printStr);



		drawHelperBST(root->right, file, level, false, printStr);
	}




}


template <typename Comparable>
void BST<Comparable>::DrawTreeToFile() {
	ofstream drawFile;
	drawFile.open("phonebookTreeBST.txt");

	drawHelperBST(root, drawFile, -1, false,"");
}