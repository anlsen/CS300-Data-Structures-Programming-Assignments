#ifndef _HASH_H
#define _HASH_H

#include <iostream>
#include <vector>

using namespace std;

template <typename Comparable>
struct HashEntry {
	string situation;//THIS WILL BE ONE OF THE "ACTIVE", "DELETED" AND "EMPTY" strings 

	Comparable fullName;

	Comparable phoneNumber;
	Comparable city;

	HashEntry(Comparable fullName, Comparable phoneNumber, 
		Comparable city,string situation = "EMPTY")
		: situation(situation),fullName(fullName),phoneNumber(phoneNumber),city(city){}
	HashEntry() {
		situation = "EMPTY";
	}

};



template <typename Comparable>
class Hash {

private:
	//in rehashing, to pick the next prime for the new size, below functions are necessary
	bool isPrime(int n);
	int nextPrime(int n);


	long long doHash(Comparable str, int sizeOfArray);
	void reHash();

	//in the test case this ratio is used
	const double LOAD_FACTOR_LIMIT = 0.9;

	int itemCount;
	int sizeOfArray;
	double loadFactor;
	vector<HashEntry<Comparable>> hashArray;
	
public:
	
	Hash();

	int getItemCount() {
		return itemCount;
	}
	double getLoadFactor() {
		return loadFactor;
	}

	bool searchHash(Comparable fullName);
	void searchHashWithoutPrint(Comparable fullName);





	bool insertHash(Comparable fullName, Comparable phoneNumber,Comparable city);
	bool deleteHash(Comparable fullName);
};










#include "Hash.cpp"








#endif _HASH_H