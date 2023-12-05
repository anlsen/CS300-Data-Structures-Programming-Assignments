#pragma once


template <typename Comparable>
struct ComparableNode {
	Comparable fullName;
	Comparable phoneNumber;
	Comparable city;

	ComparableNode(Comparable fullName, Comparable phoneNumber, Comparable city) :
		fullName(fullName), phoneNumber(phoneNumber), city(city) {

	}
};