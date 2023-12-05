#pragma once



template <typename Comparable>
struct Node {

	//in our case data will be fullName which will be a subject in comparisons while traversing through tree
	Comparable data;

	//in order to keep the rest of the information, they are also stored as template
	Comparable firstName;
	Comparable lastName;
	Comparable phoneNumber;
	Comparable city;

	Node* right;
	Node* left;

	Node(Comparable firstName, Comparable lastName, Comparable phoneNumber, Comparable city) :
		firstName(firstName), lastName(lastName), phoneNumber(phoneNumber), city(city)
		, right(nullptr), left(nullptr) {


		data = firstName + " " + lastName;
	}


};
