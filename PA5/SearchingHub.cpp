#include "SearchingHub.h"
#include <iostream>




template<typename Comparable>
bool SearchingHub<Comparable>::doesInclude(Comparable source,string queryStr)
{
	//getting the string version of these two,
	string sourceStrUpper =string(source);


	for (int i = 0;i < queryStr.length();i++) {
		if (sourceStrUpper[i] != queryStr[i]) {
			return false;
		}
	}
	return true;
}

template <typename Comparable>
bool SearchingHub<Comparable>::SequentialSearch(vector<ComparableNode<Comparable>>& vec,string query) {

	bool isFound = false;

	int startingPoint = 0;

	for (int i = 0;i < vec.size();i++) {
		if (doesInclude(vec[i].fullName, query)) {
			cout << vec[i].fullName << " " << vec[i].phoneNumber << " " << vec[i].city << endl;
			
			isFound = true;
			startingPoint = i+1;

		}
	}
	
	//since we might get partial string
	//from the startingPoint we check further contacts,
	//since it is sorted alphabetically, we directly get the other matching pairs if we get partials
	while (startingPoint < vec.size() - 1 && doesInclude(vec[startingPoint].fullName, query)) {
		cout << vec[startingPoint].fullName << " " << vec[startingPoint].phoneNumber << " " << vec[startingPoint].city << endl;
		startingPoint++;
	}
	return isFound;
}

template<typename Comparable>
bool SearchingHub<Comparable>::SequentialSearchWithoutPrint(vector<ComparableNode<Comparable>>& vec, string query){

	bool isFound = false;

	int startingPoint = 0;

	for (int i = 0;i < vec.size();i++) {
		if (doesInclude(vec[i].fullName, query)) {

			isFound = true;
			startingPoint = i + 1;

		}
	}

	//since we might get partial string
	//from the startingPoint we check further contacts,
	//since it is sorted alphabetically, we directly get the other matching pairs if we get partials
	while (startingPoint < vec.size() - 1 && doesInclude(vec[startingPoint].fullName, query)) {
		startingPoint++;
	}
	return isFound;

}

template<typename Comparable>
bool SearchingHub<Comparable>::BinarySearch(vector<ComparableNode<Comparable>>& vec,string query){
	int start = 0;
	int end = vec.size() - 1;


	bool isFound = false;

	int startingPoint = 0;
	

	while (start <= end) {
		int mid = (start + end) / 2;
		if (doesInclude(vec[mid].fullName, query)) {

			isFound = true;
			startingPoint = mid;
			break;
		}
		else if (vec[mid].fullName > query) {
			end = mid - 1;
		}
		else {
			start = mid + 1;
		}
		
	}
	//since we might get partial string
	
	//when we get partial str, possible case is     not not MATCHING  FOUND  MATCHING MATCHING not not not ...
	//therefore, we need to go to first matching contact and start printing forward
	
	//going backwards to get the first instance
	while (startingPoint >= 0 && doesInclude(vec[startingPoint].fullName, query)) {
		startingPoint--;
	}
	startingPoint++;
	//now starting point points to first matching instance

	while (startingPoint < vec.size() - 1 && doesInclude(vec[startingPoint].fullName, query)) {
		cout << vec[startingPoint].fullName << " " << vec[startingPoint].phoneNumber << " " << vec[startingPoint].city << endl;
		startingPoint++;
	}
	
	
	return isFound;
}

template<typename Comparable>
bool SearchingHub<Comparable>::BinarySearchWithoutPrint(vector<ComparableNode<Comparable>>& vec, string query){

	int start = 0;
	int end = vec.size() - 1;


	bool isFound = false;

	int startingPoint = 0;


	while (start <= end) {
		int mid = (start + end) / 2;
		if (doesInclude(vec[mid].fullName, query)) {

			isFound = true;
			startingPoint = mid;
			break;
		}
		else if (vec[mid].fullName > query) {
			end = mid - 1;
		}
		else {
			start = mid + 1;
		}

	}
	//since we might get partial string

	//when we get partial str, possible case is     not not MATCHING  FOUND  MATCHING MATCHING not not not ...
	//therefore, we need to go to first matching contact and start printing forward

	//going backwards to get the first instance
	while (startingPoint >= 0 && doesInclude(vec[startingPoint].fullName, query)) {
		startingPoint--;
	}
	startingPoint++;
	//now starting point points to first matching instance

	while (startingPoint < vec.size() - 1 && doesInclude(vec[startingPoint].fullName, query)) {
		startingPoint++;
	}


	return isFound;
}
