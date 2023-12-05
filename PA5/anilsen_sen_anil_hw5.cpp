#include <iostream>
#include <fstream>
#include <sstream>
#include <chrono>
#include "SortingHub.h"
#include "SearchingHub.h"

using namespace std;




int main()
{
	cout << "Please enter the contact file name:" << endl;
	string fileName;
	cin >> fileName;

	ifstream file;
	file.open(fileName);
	while (file.fail()) {
		cout << "Please enter the contact file name:" << endl;
		cin >> fileName;
		file.open(fileName);
	}
	cout << "Please enter the word to be queried:" << endl;
	string queryContact;
	cin >> queryContact;
	string queryContactUpper = allUpperCase(queryContact);


	vector<ComparableNode<string>> insertionSortVec;
	vector<ComparableNode<string>> quickSortVec;
	vector<ComparableNode<string>> mergeSortVec;
	vector<ComparableNode<string>> heapSortVec;

	string line;
	while (getline(file, line)) {
		string firstName, lastName,phoneNumber,city;
		istringstream ss(line);

		ss >> firstName >> lastName >> phoneNumber >> city;

		string fullName = firstName + " " + lastName;

		


		ComparableNode<string> contact(allUpperCase(fullName), phoneNumber, allUpperCase(city));

		insertionSortVec.push_back(contact);
		quickSortVec.push_back(contact);
		mergeSortVec.push_back(contact);
		heapSortVec.push_back(contact);

	}
	
	SortingHub<string> sortingHub;

	//since their size will be equal, one of the vectors size can be used
	const int VEC_SIZE = insertionSortVec.size();

	vector<ComparableNode<string>> unsortedVec = insertionSortVec;



	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0;i < 100;i++) {
		sortingHub.QuickSort(unsortedVec,0,VEC_SIZE-1);
		unsortedVec = insertionSortVec;
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::nano> quickSortTime = end-start;

	/*---------------------------------------------------*/
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0;i < 100;i++) {
		sortingHub.InsertionSort(unsortedVec, 0, VEC_SIZE - 1);
		unsortedVec = insertionSortVec;
	}

	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::nano> insertionSortTime = end - start;
	/*---------------------------------------------------*/
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0;i < 100;i++) {
		sortingHub.MergeSort(unsortedVec, 0, VEC_SIZE - 1);
		unsortedVec = insertionSortVec;
	}

	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::nano> mergeSortTime = end - start;
	/*---------------------------------------------------*/
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0;i < 100;i++) {
		sortingHub.HeapSort(unsortedVec);
		unsortedVec = insertionSortVec;
	}

	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::nano> heapSortTime = end - start;
	/*---------------------------------------------------*/
	cout << "Sorting the vector copies" << endl;
	cout << "======================================" << endl;
	cout << "Quick Sort Time: " << quickSortTime.count()/100 <<" Nanoseconds" << endl;
	cout << "Insertion Sort Time: " << insertionSortTime.count()/100 << " Nanoseconds" << endl;
	cout << "Merge Sort Time: " << mergeSortTime.count()/100 << " Nanoseconds" << endl;
	cout << "Heap Sort Time: " << heapSortTime.count()/100 << " Nanoseconds" << endl;
	


	
	
	sortingHub.InsertionSort(insertionSortVec,0, VEC_SIZE-1);
	sortingHub.QuickSort(quickSortVec, 0, VEC_SIZE-1);
	sortingHub.MergeSort(mergeSortVec, 0, VEC_SIZE-1);
	sortingHub.HeapSort(heapSortVec);
	
	

	cout << "Searching for " << queryContact << endl;
	cout << "======================================" << endl;



	cout << "\nSearch results for Binary Search:\n" << endl;
	SearchingHub<string> searchingHub;
	if (searchingHub.BinarySearch(insertionSortVec, queryContactUpper)) {

	}
	else {
		cout << queryContactUpper << " does NOT exist in the dataset" << endl;
	}


	start = std::chrono::high_resolution_clock::now();
	for (int i = 0;i < 100;i++) {
		searchingHub.BinarySearchWithoutPrint(insertionSortVec, queryContactUpper);
	}

	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::nano> binarySearchTime = end - start;
	cout << "Binary Search Time: " << binarySearchTime.count()/100 << " Nanoseconds" << endl;


	
	cout << "\nSearch results for Sequential Search:\n" << endl;
	if (searchingHub.SequentialSearch(insertionSortVec, queryContactUpper)) {

	}
	else {
		cout << queryContactUpper << " does NOT exist in the dataset" << endl;
	}
	start = std::chrono::high_resolution_clock::now();
	for (int i = 0;i < 100;i++) {
		searchingHub.SequentialSearchWithoutPrint(insertionSortVec, queryContactUpper);
	}

	end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::nano> sequentialSearchTime = end - start;
	cout << "Sequential Search Time: " << sequentialSearchTime.count()/100 << " Nanoseconds" << endl;


	cout << "\nSpeedUp between Search Algorithms" << endl;
	cout << "======================================" << endl;
	if (sequentialSearchTime.count() > binarySearchTime.count()) {
		cout << "(Sequential Search/ Binary Search) SpeedUp = " << sequentialSearchTime.count() / binarySearchTime.count() << endl;
	}
	else {
		cout << "(Binary Search/ Sequential Search) SpeedUp = " << binarySearchTime.count() / sequentialSearchTime.count() << endl;
	}
	
	cout << "\nSpeedUps between Sorting Algorithms" << endl;
	cout << "======================================" << endl;

	if (insertionSortTime.count() > quickSortTime.count()) {
		cout << "(Insertion Sort/ Quick Sort) SpeedUp = " << insertionSortTime.count() / quickSortTime.count() << endl;
	}
	else {
		cout << "(Quick Sort/ Insertion Sort) SpeedUp = " << quickSortTime.count() / insertionSortTime.count() << endl;
	}

	if (mergeSortTime.count() > quickSortTime.count()) {
		cout << "(Merge Sort/ Quick Sort) SpeedUp = " << mergeSortTime.count() / quickSortTime.count() << endl;
	}
	else {
		cout << "(Quick Sort/ Merge Sort) SpeedUp = " << quickSortTime.count() / mergeSortTime.count() << endl;
	}

	if (heapSortTime.count() > quickSortTime.count()) {
		cout << "(Heap Sort/ Quick Sort) SpeedUp = " << heapSortTime.count() / quickSortTime.count() << endl;
	}
	else {
		cout << "(Quick Sort/ Heap Sort) SpeedUp = " << quickSortTime.count() / heapSortTime.count() << endl;
	}

}
