#include "AVL.h"


//Returns the height of the inputted Node
template <typename Comparable>
int height(Node<Comparable>*& root) {

	if (root == nullptr) {
		return -1;
	}
	else {
		return max(height(root->right), height(root->left)) + 1;
	}
}



//AVL Right Rotation
template <typename Comparable>
Node<Comparable>* rightRotate(Node<Comparable>* &problematic) {
	Node<Comparable> * leftChild = problematic->left;

	problematic->left = leftChild->right;
	leftChild->right = problematic;


	
	return leftChild;
}

//AVL Left Rotation
template <typename Comparable>
Node<Comparable>* leftRotate(Node<Comparable>*& problematic) {

	Node<Comparable>* rightChild = problematic->right;

	problematic->right = rightChild->left;
	rightChild->left = problematic;



	return rightChild;

}


//Returns the difference between inputted Node's left and right subtrees' hight
template <typename Comparable>
int Balance(Node<Comparable>* &root) {
	if (root == nullptr) {
		return 0;
	}

	return height(root->left) - height(root->right);
}


//Adds new node to the AVL, and balancing the subtrees according to AVL requirements
template <typename Comparable>
Node<Comparable>* addHelperAVL(Node<Comparable>* root, Comparable& firstName, Comparable& lastName,
	Comparable& phoneNumber, Comparable& city,bool& isSuccessful,Comparable& fullName) {

	if (root == nullptr) {

		//Adding new Node
		Node<Comparable> * temp = new Node<Comparable>(firstName,lastName,phoneNumber,city);
		//Addition process is now successful
		isSuccessful = true;
		return temp;
	}
	else if (root->data > (fullName)) {
		root->left = addHelperAVL(root->left, firstName, lastName, phoneNumber, city,isSuccessful,fullName);

	}
	else if (root->data < (fullName)) {
		root->right = addHelperAVL(root->right, firstName, lastName, phoneNumber, city,isSuccessful,fullName);

	}
	else {
		
	}

	
	//From this point on, tree members will be checked if they violate the AVL Tree Rules
	
	if (Balance(root) >= 2) {

		//Left subtree's height is greater, so it can be inferred that 
		//addition is made on the left child
		
	

		//Check whether it is added to left subtree of the left child or
		//right subtree of the left child
		if (fullName > root->left->data) {
			//Right subtree of the left child

			//Doing Left Right Rotation
			root->left = leftRotate(root->left);
			return rightRotate(root);
		}
		else {
			//Left subtree of the left child

			return rightRotate(root);
		}


	}
	else if (Balance(root) <= -2) {
		//Right subtree's height is greater, so it can be inferred that 
		//addition is made on the right child





		//Check whether it is added to left subtree of the right child or
		//right subtree of the right child
		if (fullName > root->right->data) {
			//Right subtree of the right child
			return leftRotate(root);
		}
		else {
			//Left subtree of the right child

			//Doing Right Left Rotation
			root->right = rightRotate(root->right);
			return leftRotate(root);

		}

	}
	return root;

}


//Adding a new contact using helper method
template <typename Comparable>
bool AVL<Comparable>::AddContact(Comparable& firstName, Comparable& lastName, Comparable& phoneNumber, Comparable& city) {
	bool check = false;
	string fullName = firstName + " " + lastName;
	


	root = addHelperAVL(this->root, firstName, lastName,
		phoneNumber, city,check,fullName);
	//To return whether it is successful or not
	return check;
}


//Return the minimum Comparable data from the given root
template <typename Comparable>
Comparable FindMin(Node<Comparable>* root) {

	//Going to the leftmost Node and returning it
	while (root->left != nullptr) {
		root = root->left;

	}
	return root->data;
}



template <typename Comparable>
Node<Comparable>* deleteHelperAVL(Node<Comparable>* root, string fullName,bool& isSuccessful) {

	if (root == nullptr) {
		//That means the inputted fullName cannot be found, hence returning false
		isSuccessful = false;

	}
	else if (root->data > fullName) {
		root->left = deleteHelperAVL(root->left, fullName,isSuccessful);

	}
	else if (root->data < fullName) {
		root->right = deleteHelperAVL(root->right, fullName,isSuccessful);

	}
	else {
		
		//At this point root is now the root that is desired to be deleted


		//If it is a leaf node, it can be simply deleted
		if (root->left == nullptr && root->right == nullptr) {
			delete root;
			root = nullptr;

		}

		//If it has only one child then we connect the node's parent with its child, and delete the Node itself
		
		
		else if (root->left == nullptr) {
			Node<Comparable>* temp = root;
			root = root->right;
			delete temp;


		}
		else if (root->right == nullptr) {
			Node<Comparable>* temp = root;
			root = root->left;
			delete temp;

		}
		//If it has both right and left child, we get the minimum element of the right subtree for current Node
		//and delete the original Node from which we take the minimum value through recursive call

		else {
			Node<Comparable>* rightChild = root->right;
			root->data= FindMin(rightChild);
			root->right = deleteHelperAVL(rightChild, root->data,isSuccessful);


		}
		
	}

	//From this point onwards,
	//we traverse back to the root node in the same way we came

	if (root == nullptr) {
		return root;
	}
	else {
		

		
		int balance = Balance(root);

		//Left child has greater height and it due to its left subtree
		if (balance >= 2 && Balance(root->left) >= 0) {
			root = rightRotate(root);


		}
		//Left child has greater height and it due to its right subtree
		else if (balance >= 2 && Balance(root->left) < 0) {
			root->left = leftRotate(root->left);
			root = rightRotate(root);

		}
		//Right child has greater height and it due to its left subtree
		else if (balance <= -2 && Balance(root->right) > 0) {
			root->right = rightRotate(root->right);
			root = leftRotate(root);
		}
		//Right child has greater height and it due to its right subtree
		else if (balance <= -2 && Balance(root->right) >= 0) {
			root = leftRotate(root);
		}

		return root;


	}









}


//Deleting a contact through helper function
template<typename Comparable>
bool AVL<Comparable>::DeleteContact(Comparable fullName) {
	bool check = true;
	root = deleteHelperAVL(this->root, string(fullName),check);

	return check;
}





//checks whether fullName contains the given partial string
bool doesIncludeAVL(string partialStr, string fullName) {

	

	for (int i = 0;i < partialStr.length();i++) {
		if (partialStr[i] != fullName[i]) {
			return false;
		}
	}
	return true;
}

//prints out matching contact containing string

template <typename Comparable>
void searchAVL(Node<Comparable>* root, string str) {

	
	if (root != nullptr) {

		
		if (doesIncludeAVL(str, string(root->data))) {

			
			cout << root->data << " " << root->phoneNumber << " " << root->city << endl;
			

			//if we find a matching pair then the rest of matching contacts
			//will be in the subtrees of the first found contact
			searchAVL(root->left, str);


			searchAVL(root->right, str);
		}
		
		else {
			//Usual search method until we find a contact containing partial string
			if (str < root->data) {
				searchAVL(root->left, str);
			}
			else {
				searchAVL(root->right, str);
			}
		}




	}
	

}


//Takes different actions for string to be partial and full.
template <typename Comparable>
void AVL<Comparable>::SearchAContact(string str) {

	
	searchAVL(root,str);


}

//Implements preOrder print recursively
template <typename Comparable>
void preOrderPrintHelperAVL(Node<Comparable>* root, ofstream& file) {
	if (root != nullptr) {

		file << root->data << " " << root->phoneNumber << " " << root->city << endl;
		preOrderPrintHelperAVL(root->left, file);
		preOrderPrintHelperAVL(root->right, file);
	}
}
//Implements inOrder print recursively
template <typename Comparable>
void InOrderPrintHelperAVL(Node<Comparable>* root, ofstream& file) {
	if (root != nullptr) {
		InOrderPrintHelperAVL(root->left, file);
		file << root->data << " " << root->phoneNumber << " " << root->city << endl;
		InOrderPrintHelperAVL(root->right, file);
	}
}
//using recursive function, print out preOrder to txt file
template <typename Comparable>
void AVL<Comparable>::PreOrderPrintToFile() {

	ofstream preOrderFile;
	preOrderFile.open("phonebookPreOrderAVL.txt");

	preOrderPrintHelperAVL(root, preOrderFile);



}
////using recursive function, print out inOrder to txt file

template <typename Comparable>
void AVL<Comparable>::InOrderPrintToFile() {

	ofstream inOrderFile;
	inOrderFile.open("phonebookInOrderAVL.txt");

	InOrderPrintHelperAVL(root, inOrderFile);


}

//Draws tree structure for AVL

template <typename Comparable>
void drawHelperAVL(Node<Comparable>* root, ofstream& file, int level, bool isLeft,string printStr) {
	if (root != nullptr) {
		level++;

		


		file << printStr;


		//if the Node is root
		if (level == 0) {
			file << "|__";

		//if it is left subtree
		}else if (isLeft) {
			file << "--";
		}

		//if it is right subtree
		else{
			file << "__";
		}




		file << root->data << endl;


		
		
		if (isLeft || level==0) {
			printStr += "  |";
		}
		else {
			//if we are on the right subtree that means the next element that is going to be displayed
			//will not have | symbol

			//getting rid of | symbol
			printStr = printStr.substr(0,printStr.length()-1);
			//appending double whitespace instead and adding | symbol for further nodes
			printStr += "  |";
		}
		
		drawHelperAVL(root->left, file, level, true,printStr);
		
		
		
		drawHelperAVL(root->right, file, level, false,printStr);
	}




}


template <typename Comparable>
void AVL<Comparable>::DrawTreeToFile() {
	ofstream drawFile;
	drawFile.open("phonebookTreeAVL.txt");

	//For the first Node to be referred as node, we pass the level as -1,
	//which is later going to be incremented to 0
	drawHelperAVL(root, drawFile, -1, false,"");
}