#include "BST.h"
#include "Hash.h"

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
	Hash<string> myHash;



	string line;

	//Reading into BST

	
	while (getline(file, line)) {
		istringstream ss(line);

		string firstName, lastName, phoneNumber, city;
		ss >> firstName >> lastName >> phoneNumber >> city;




		string firstNameUpper = allUpperCaseMain(firstName);
		string lastNameUpper = allUpperCaseMain(lastName);

		myBST.AddContact(firstNameUpper, lastNameUpper, phoneNumber, city);

	}
	


	


	


	file.clear();
	file.seekg(0);



	//Reading into Hash
	
	while (getline(file, line)) {
		istringstream ss(line);

		string firstName, lastName, phoneNumber, city;
		ss >> firstName >> lastName >> phoneNumber >> city;


		string firstNameUpper = allUpperCaseMain(firstName);
		string lastNameUpper = allUpperCaseMain(lastName);

		string fullName = firstNameUpper + " " + lastNameUpper;

		myHash.insertHash(fullName, phoneNumber, city);

	}



	

	cout << "\n\nAfter preprocessing, the unique word count is " << myHash.getItemCount() <<
		".Current load ratio is " << myHash.getLoadFactor() << endl << endl;
	

	
	





	int action = 0;
	while (action != 4) {
		cout << "\nChoose which action to perform from 1 to 4:\n"
			"1 - Search a phonebook contact\n"
			"2 - Adding a phonebook contact\n"
			"3 - Deleting a phonebook contact\n"
			"4 - Press 4 to exit\n";
		cin >> action;

		if (action == 1) {
			string searchStr;
			cout << "Search for a contact: ";
			cin.ignore();
			getline(cin, searchStr);

			string searchStrUpper = allUpperCaseMain(searchStr);

			cout << "\nSearching an item in the phonebook (BST) . . .\n" << endl;

			cout << "Phonebook: Searching for : (" << searchStr << ")" << endl;
			cout << "====================================" << endl;
			
			if (!myBST.SearchAContact(searchStrUpper)) {
				cout << "Name not found!" << endl;
			}
			

			

			int k = 500;
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < k; i++)
			{
				myBST.SearchAContactWithoutPrint(searchStrUpper);
			}
			auto BSTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
				(std::chrono::high_resolution_clock::now() - start);
			
			auto BSTResult = BSTTime.count() / k;
			cout << "\nBST Search Time: " << BSTResult << "\n";


			cout << "\nSearching an item in the phonebook (HashTable) . . .\n" << endl;
			cout << "Phonebook: Searching for: (" << searchStr << ")" << endl;
			cout << "====================================" << endl;
			
			if (!myHash.searchHash(searchStrUpper)) {
				cout << "Name not found!" << endl;
			}
			
			start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < k; i++)
			{
				myHash.searchHashWithoutPrint(searchStrUpper);
			}
			auto HTTime = std::chrono::duration_cast<std::chrono::nanoseconds>
				(std::chrono::high_resolution_clock::now() - start);
			auto HTResult = HTTime.count() / k;
			cout << "\nHash Table Search Time: " << HTResult << "\n";
			cout << "Speed up: " << double(BSTResult) / HTResult << endl;

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
			bool isAddedHash = false;



			

			auto addStartBST = std::chrono::high_resolution_clock::now();
			if (myBST.AddContact(firstNameUpper, lastNameUpper, phoneNumber, city)) {
				cout << "Contact has been added successfully to the BST" << endl;
				isAddedBST = true;
			}
			else {
				cout << "Contact already exists in BST" << endl;
			}
			auto addFinishBST = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::nano> elapsedAddBST = addFinishBST - addStartBST;


			string fullNameUpper = firstNameUpper + " " + lastNameUpper;

			cout << "\nAdding an item to the phonebook AVL. . ." << endl;
			cout << "====================================" << endl;;

			auto addStartHash = std::chrono::high_resolution_clock::now();
			if (myHash.insertHash(fullNameUpper,phoneNumber,city)) {
				cout << "Contact has been added successfully to the Hash Table" << endl;
				isAddedHash = true;
			}
			else {
				cout << "Contact already exists in Hash Table" << endl;
			}
			auto addFinishHash = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::nano> elapsedAddHash = addFinishHash - addStartHash;



			if (isAddedBST) {
				cout << "\nAdding a contact to the Binary Tree took " << elapsedAddBST.count() << " nanoseconds. . ." << endl;
			}if (isAddedHash) {
				cout << "Adding a contact to the Hash Table took " << elapsedAddHash.count() << " nanoseconds. . .\n" << endl;
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
				cout << "Name not found" << endl;
			}
			auto deleteFinishBST = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::nano> elapsedDeleteBST = deleteFinishBST - deleteStartBST;



			auto deleteStartHash = std::chrono::high_resolution_clock::now();
			myHash.deleteHash(searchStrUpper);
			auto deleteFinishHash = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double, std::nano> elapsedDeleteHash = deleteFinishHash - deleteStartHash;

			if (isSuccessful) {
				cout << "Deletion from the Binary Tree took " << elapsedDeleteBST.count() << " nanoseconds. . ." << endl;
				cout << "Deletion from the Hash Table took " << elapsedDeleteHash.count() << " nanoseconds. . ." << endl;
			}



		}
		
		

		cout << endl;


	}

	
	
	return 0;
}
