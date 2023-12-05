#ifndef _SHUB_H
#define _SHUB_H

#include <vector>
#include <iostream>
#include "ComparableNode.h"
using namespace std;


template <typename Comparable>
class SortingHub {

private:

	/* FOR QUICK SORT*/
	void swapTwo(ComparableNode<Comparable> &x, ComparableNode<Comparable> &y);

	int partitionQuickSort(vector<ComparableNode<Comparable>>& vec, int start, int end);


	/* FOR MERGE SORT*/
	void merge(vector<ComparableNode<Comparable>>& vec, int start, int end);

	/*FOR HEAP SORT*/
	void percolateDownMaxHeap(vector<ComparableNode<Comparable>>& vec, int size, int hole);
	void heapify(vector<ComparableNode<Comparable>>& vec);



public:
	

	void InsertionSort(vector<ComparableNode<Comparable>> & vec,int start,int end);


	void QuickSort(vector<ComparableNode<Comparable>>& vec,int start,int end);


	void MergeSort(vector<ComparableNode<Comparable>>& vec,int start,int end);


	void HeapSort(vector<ComparableNode<Comparable>>& vec);
	



};

#include "SortingHub.cpp"

#endif

