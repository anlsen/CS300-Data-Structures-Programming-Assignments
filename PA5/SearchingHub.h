#pragma once
#include "ComparableNode.h"
#include <vector>
#include <iostream>
using namespace std;

string allUpperCase(string str) {

	string result = "";
	for (int i = 0;i < str.length();i++) {
		result += toupper(str[i]);
	}
	return result;
}

template <typename Comparable>
class SearchingHub {
public:

	bool doesInclude(Comparable source, string query);;

	bool SequentialSearch(vector<ComparableNode<Comparable>>& vec,string query);

	bool SequentialSearchWithoutPrint(vector<ComparableNode<Comparable>>& vec, string query);

	bool BinarySearch(vector<ComparableNode<Comparable>>& vec,string query);

	bool BinarySearchWithoutPrint(vector<ComparableNode<Comparable>>& vec, string query);

};

#include "SearchingHub.cpp"