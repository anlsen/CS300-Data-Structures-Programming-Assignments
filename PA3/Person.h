
#pragma once

#include <iostream>

using namespace std;

class Person {

private:

	string firstName;
	string lastName;
	string phoneNumber;
	string city;
public:
	Person(string firstName, string lastName, string phoneNumber, string city) {
		this->firstName = firstName;
		this->lastName = lastName;
		this->phoneNumber = phoneNumber;
		this->city = city;
	}
	//COPY CONSTRUCTOR
	Person(const Person& rhs) {
		this->firstName = rhs.firstName;
		this->lastName = rhs.lastName;
		this->phoneNumber = rhs.phoneNumber;
		this->city = rhs.city;
	}

	string getFullName() const {
		return firstName + " " + lastName;
	}


	Person& operator=(const Person& rhs) {
		if (this != &rhs) {
			this->firstName = rhs.firstName;
			this->lastName = rhs.lastName;
			this->city = rhs.city;
			this->phoneNumber = rhs.phoneNumber;

		}
		return *this;
	}

	bool operator<(const Person& rhs) {
		return this->getFullName() < rhs.getFullName();
	}
	bool operator>(const Person& rhs) {
		return this->getFullName() > rhs.getFullName();
	}
	bool operator==(const Person& rhs) {
		return this->getFullName() == rhs.getFullName();
	}
	bool operator<(const string& fullName) {
		return this->getFullName() < fullName;
	}
	bool operator>(const string& fullName) {
		return this->getFullName() > fullName;
	}
	bool operator==(const string& fullName) {
		return this->getFullName() == fullName;
	}
};