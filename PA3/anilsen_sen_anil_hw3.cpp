#include "BST.h"
#include "AVL.h"

#include <sstream>
#include <fstream>
#include <chrono>

using namespace std;

string allUpperCaseMain(string str) {

	string result = "";
	for (int i = 0;i < str.length();i++) {
		result += toupper(str[i]);
	}
	return result;
}




int main() {


	string fileName;
	
	cout << "Please enter the contact file name: ";
	cin >> fileName;


	ifstream file;

	file.open(fileName);

	while (file.fail()) {
		cout << "File could not be found" << endl;
		cout << "Please enter the correct file name: " << endl;
		cin >> fileName;
		file.open(fileName);
	}

	BST<string> myBST;
	AVL<string> myAVL;



	string line;

	//Reading into BST
	cout << "\nLoading the phonebook into a BST." << endl;
	auto startBST = std::chrono::high_resolution_clock::now();
	while (getline(file, line)) {
		istringstream ss(line);

		string firstName, lastName, phoneNumber, city;
		ss >> firstName >> lastName >> phoneNumber >> city;
		
		


		string firstNameUpper = allUpperCaseMain(firstName);
		string lastNameUpper = allUpperCaseMain(lastName);

		myBST.AddContact(firstNameUpper, lastNameUpper, phoneNumber, city);
		
	}
	auto finishBST = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsedBST = finishBST - startBST;


	cout << "Phonebook creation in BST took " << elapsedBST.count() << " milliseconds. . ." << endl;


	int heightLeftBST = height(myBST.getRoot()->left) + 1;
	int heightRightBST = height(myBST.getRoot()->right) + 1;

	if (abs(heightLeftBST-heightRightBST)>1) {
		cout << "Tree is not balanced" << endl;
	}
	else {
		cout << "Tree is balanced" << endl;
	}

	cout << "The heights of BST are for left: " << heightLeftBST
		<< " and right: " << heightRightBST<< endl;


	file.clear();
	file.seekg(0);
	


	//Reading into AVL
	cout << "Loading the phonebook into a AVL." << endl;
	auto startAVL = std::chrono::high_resolution_clock::now();
	while (getline(file, line)) {
		istringstream ss(line);

		string firstName, lastName, phoneNumber, city;
		ss >> firstName >> lastName >> phoneNumber >> city;


		string firstNameUpper = allUpperCaseMain(firstName);
		string lastNameUpper = allUpperCaseMain(lastName);
		
		myAVL.AddContact(firstNameUpper, lastNameUpper, phoneNumber, city);

	}
	auto finishAVL = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsedAVL = finishAVL - startAVL;


	cout << "Phonebook creation in AVL took " << elapsedAVL.count() << " milliseconds. . ." << endl;



	
	int heightLeftAVL = height(myAVL.getRoot()->left) + 1;
	int heightRightAVL = height(myAVL.getRoot()->right) + 1;


	if (abs(heightLeftAVL - heightRightAVL)>1) {
		cout << "Tree is not balanced" << endl;
	}
	else {
		cout << "Tree is balanced" << endl;
	}


	cout << "The heights of BST are for left: " << heightLeftAVL
		<< " and right: " << heightRightAVL  << endl;

	
	

	int action = 0;
	while(action!=6){
		cout << "\nChoose which action to perform from 1 to 6:\n"
			"1 - Search a phonebook contact\n"
			"2 - Adding a phonebook contact\n"
			"3 - Deleting a phonebook contact\n"
			"4 - Print the phonebook to a file(inorder)\n"
			"    Print the phonebook to a file(preorder)\n"
			"5 - Draw the phonebook as a Tree to a file\n"
			"6 - Press 6 to exit\n";
		cin >> action;

		if (action == 1) {
			string searchStr;
			cout << "Search for a contact: ";
			cin.ignore();
			getline(cin,searchStr);

			string searchStrUpper = allUpperCaseMain(searchStr);
		
			cout << "\nSearching an item in the phonebook (BST) . . .\n" << endl;
	
			cout << "Phonebook: Searching for : (" << searchStr << ")" << endl;
			cout << "====================================" << endl;
			auto searchStartBST = std::chrono::high_resolution_clock::now();
			myBST.SearchAContact(searchStrUpper);
			auto searchFinishBST = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedSearchBST = searchFinishBST - searchStartBST;
		
			

			cout << "\nSearching an item in the phonebook (AVL) . . .\n" << endl;
			cout << "Phonebook: Section: (" << searchStr << ")" << endl;
			cout << "====================================" << endl;
			auto searchStartAVL = std::chrono::high_resolution_clock::now();
			myAVL.SearchAContact(searchStrUpper);
			auto searchFinishAVL = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedSearchAVL = searchFinishAVL - searchStartAVL;

			
			cout << "\nThe search in BST took "<<elapsedSearchBST.count()<<" milliseconds. . ." << endl;
			cout << "The search in AVL took "<< elapsedSearchAVL.count()<<" milliseconds. . ." << endl;
		}
		else if (action == 2) {
			cout << "\nEnter the information of the contact to be added:" << endl;
			cout << "Name: ";
			string fullName;
			cin.ignore();
			getline(cin, fullName);

			istringstream ss(fullName);
			string firstName, lastName;
			ss >> firstName >> lastName;
		
			string firstNameUpper = allUpperCaseMain(firstName);
			string lastNameUpper = allUpperCaseMain(lastName);


			
			cout << "\nTel: ";
			string phoneNumber;
			cin >> phoneNumber;
			cout << "\nCity: ";
			string city;
			cin >> city;

			cout << "\nAdding an item to the phonebook BST . . ." << endl;
			cout << "====================================" << endl;;


			bool isAddedBST = false;
			bool isAddedAVL = false;





			auto addStartBST = std::chrono::high_resolution_clock::now();
			if (myBST.AddContact(firstNameUpper,lastNameUpper,phoneNumber,city)) {
				cout << "Contact has been added successfully to the BST" << endl;
				isAddedBST = true;
			}
			else {
				cout << "Contact already exists in BST" << endl;
			}
			auto addFinishBST = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedAddBST = addFinishBST - addStartBST;




			cout << "\nAdding an item to the phonebook AVL. . ." << endl;
			cout << "====================================" << endl;;

			auto addStartAVL = std::chrono::high_resolution_clock::now();
			if (myAVL.AddContact(firstNameUpper, lastNameUpper, phoneNumber, city)) {
				cout << "Contact has been added successfully to the AVL" << endl;
				isAddedAVL = true;
			}
			else {
				cout << "Contact already exists in AVL" << endl;
			}
			auto addFinishAVL = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedAddAVL = addFinishAVL - addStartAVL;



			if (isAddedBST){
				cout << "\nAdding a contact to the Binary Tree took " << elapsedAddBST.count() << " milliseconds. . ." << endl;
			}if (isAddedAVL) {
				cout << "Adding a contact to the AVL Tree took " << elapsedAddAVL.count() << " milliseconds. . .\n" << endl;
			}
		}
		else if (action == 3) {

			cout << "\nDeleting an item from the phonebook . . ." << endl;
			cout << "Enter the fullname of the contact to be deleted: ";
			string searchStr;
			cin.ignore();
			getline(cin, searchStr);
			
			string searchStrUpper = allUpperCaseMain(searchStr);

			bool isSuccessful = false;
			auto deleteStartBST = std::chrono::high_resolution_clock::now();
			if (myBST.DeleteContact(searchStrUpper)) {
				cout << "\nDeleted succcessfully. . .\n" << endl;
				isSuccessful = true;
			}
			else {
				cout << "Not found" << endl;
			}
			auto deleteFinishBST = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedDeleteBST = deleteFinishBST - deleteStartBST;

			

			auto deleteStartAVL = std::chrono::high_resolution_clock::now();
			myAVL.DeleteContact(searchStrUpper);
			auto deleteFinishAVL = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedDeleteAVL = deleteFinishAVL - deleteStartAVL;

			if (isSuccessful) {
				cout << "Deletion from the Binary Tree took " << elapsedDeleteBST.count() << " milliseconds. . ." << endl;
				cout << "Deletion from the AVL Tree took " << elapsedDeleteAVL.count() << " milliseconds. . ." << endl;
			}
			


		}
		else if (action == 4) {
			auto print1StartBST = std::chrono::high_resolution_clock::now();
			myBST.InOrderPrintToFile();
			auto print1FinishBST = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedPrint1BST = print1FinishBST - print1StartBST;
			
			auto print1StartAVL = std::chrono::high_resolution_clock::now();
			myAVL.InOrderPrintToFile();
			auto print1FinishAVL = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedPrint1AVL = print1FinishAVL - print1StartAVL;


			cout << "Printing in order to file from the Binary Tree took " << elapsedPrint1BST.count() << " milliseconds. . ." << endl;
			cout << "Printing in order to file from the AVL Tree took " << elapsedPrint1AVL.count() << " milliseconds. . ." << endl;

			auto print2StartBST = std::chrono::high_resolution_clock::now();
			myBST.PreOrderPrintToFile();
			auto print2FinishBST = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedPrint2BST = print2FinishBST - print2StartBST;
			

			auto print2StartAVL = std::chrono::high_resolution_clock::now();
			myAVL.PreOrderPrintToFile();
			auto print2FinishAVL = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedPrint2AVL = print2FinishAVL - print2StartAVL;



			cout << "Printing pre order to file from the Binary Tree took " << elapsedPrint2BST.count() << " milliseconds. . ." << endl;
			cout << "Printing pre order to file from the AVL Tree took " << elapsedPrint2AVL.count() << " milliseconds. . ." << endl;

		}
		else if (action == 5) {


			auto drawStartBST = std::chrono::high_resolution_clock::now();
			myBST.DrawTreeToFile();
			auto drawFinishBST = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedDrawBST = drawFinishBST - drawStartBST;

			auto drawStartAVL = std::chrono::high_resolution_clock::now();
			myAVL.DrawTreeToFile();
			auto drawFinishAVL = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::milli> elapsedDrawAVL = drawFinishAVL - drawStartAVL;

			cout << "Drawing tree to file from the Binary Tree took " << elapsedDrawBST.count() << " milliseconds. . ." << endl;
			cout << "Drawing tree to file from the AVL Tree took " << elapsedDrawAVL.count() << " milliseconds. . ." << endl;

		}



		cout << endl;
		

	}

	return 0;
}