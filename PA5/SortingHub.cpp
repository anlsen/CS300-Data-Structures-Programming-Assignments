#include "SortingHub.h"


template <typename Comparable>
void SortingHub<Comparable>::InsertionSort(vector<ComparableNode<Comparable>>& vec,int start,int end) {

   

    if (end == start) {
        return;
    }
    else {

        for (int i = 1;i <= end;i++) {
            ComparableNode<Comparable> contact= vec[i];
            int j = i - 1;

            while (j >= 0 && vec[j].fullName > contact.fullName) {
                vec[j + 1] = vec[j];
                j--;
            }
            vec[j + 1] = contact;


            



        }
    }
}
template <typename Comparable>
void SortingHub<Comparable>::swapTwo(ComparableNode<Comparable>& val1, ComparableNode<Comparable>& val2) {
    ComparableNode<Comparable> temp = val1;
    val1 = val2;
    val2 = temp;
}

template <typename Comparable>
int SortingHub<Comparable>::partitionQuickSort(vector<ComparableNode<Comparable>>& vec, int start, int end) {
    

    int mid = (start + end) / 2;
    
    //MEDIAN 3  method
    if (vec[start].fullName > vec[mid].fullName) {
        swapTwo(vec[start], vec[mid]);
        if (vec[mid].fullName > vec[end].fullName) {
            swapTwo(vec[mid], vec[end]);
        }


    }
    else {
        if (vec[mid].fullName > vec[end].fullName) {
            swapTwo(vec[end], vec[mid]);
        }
    }
    if (vec[start].fullName > vec[mid].fullName) {
        swapTwo(vec[start], vec[mid]);
    }



    
    //put middle to end-1th position

    swapTwo(vec[mid], vec[end - 1]);

    //now we need to start i from start
    //and we need to go until end - 1, since pivot is in (end-1)th position
    /*IGNORING FIRST AND LAST ELEMENT BY USING THIS SENSE*/


    //LOMUTO PARTITION
    int i = start;
    int j = start + 1;

    for (j;j < end - 1;j++) {

        if (vec[j].fullName < vec[end - 1].fullName) {


            i++;
            swapTwo(vec[i], vec[j]);


        }

    }

    i++;
    swapTwo(vec[i], vec[j]);

    return i;

    
    /* HOARE PARTITION
    int i = start;
    int j = end - 2;

    while (true) {
        while (vec[i].fullName < vec[end - 1].fullName) {
            i++;
        }
        while (vec[j].fullName > vec[end - 1].fullName) {
            j--;
        }
        if (i >= j) {
            break;
        }
        swapTwo(vec[i], vec[j]);
        i++;
        j--;
    }

    swapTwo(vec[i], vec[end - 1]);
    return i;
    
    */
    

}


template<typename Comparable>
void SortingHub<Comparable>::QuickSort(vector<ComparableNode<Comparable>>& vec,int start,int end){

    if (start >= end) {
        return;
    }
    if (end - start + 1 < 10) {
        this->InsertionSort(vec, start, end);
        return;
    }
    int pivot = partitionQuickSort(vec, start, end);

    if (pivot - start < end - pivot) {
        QuickSort(vec, start, pivot - 1);
    }
    else {
        QuickSort(vec, pivot + 1, end);
    }
    /*
    QuickSort(vec, start, pivot - 1);
    QuickSort(vec, pivot + 1, end);
    */
}

template<typename Comparable>
void SortingHub<Comparable>::merge(vector<ComparableNode<Comparable>>& vec, int start, int end) {
    int mid = (start + end) / 2;


    //LEFT ARRAY IS -> [START,MID]
    //RIGHT ARRAY IS -> [MID+1,END]
    
    //these are conceptual arrays, they dont exist in an external memory
    //we simply think of seperating an array into two from the mid point in an imaginary way

    //first index of left array
    int leftCtr = start;
    //first index of right array
    int rightCtr = mid + 1;

    for (;leftCtr <= mid;leftCtr++) {
        if (vec[leftCtr].fullName <= vec[rightCtr].fullName) {

        }
        else {
            swapTwo(vec[leftCtr], vec[rightCtr]);
            //rearrange right array

            //putting newly inserted array in an appropriate order in the right array
            int rightCtrCopy = rightCtr;

            ComparableNode<Comparable> contact = vec[rightCtrCopy];

            while (rightCtrCopy + 1 <= end) {
                if (contact.fullName > vec[rightCtrCopy + 1].fullName) {
                    vec[rightCtrCopy] = vec[rightCtrCopy + 1];
                    rightCtrCopy++;
                }
                else {
                    break;
                }

            }
            vec[rightCtrCopy] = contact;

        }
    }
}




template<typename Comparable>
void SortingHub<Comparable>::MergeSort(vector<ComparableNode<Comparable>>& vec, int start, int end) {

    if (start >= end) {
        return;
    }
    int mid = (start + end) / 2;


    MergeSort(vec, start, mid);
    MergeSort(vec, mid + 1, end);
    this->merge(vec, start, end);


}

template <typename Comparable>
void SortingHub<Comparable>::percolateDownMaxHeap(vector<ComparableNode<Comparable>>& vec, int size, int hole) {

    ComparableNode<Comparable> holeContact = vec[hole];

    int holeLeft = 2 * hole + 1;
    int holeRight = 2 * hole + 2;

    while (holeLeft < size) {


        if (vec[holeLeft].fullName > holeContact.fullName) {
            if (holeRight<size && vec[holeRight].fullName>vec[holeLeft].fullName) {
                vec[hole] = vec[holeRight];
                hole = holeRight;
            }
            else {
                vec[hole] = vec[holeLeft];
                hole = holeLeft;
            }

        }
        else {
            if (holeRight<size && vec[holeRight].fullName>holeContact.fullName) {
                vec[hole] = vec[holeRight];
                hole = holeRight;
            }
            else {
                break;
            }


        }
        holeLeft = 2 * hole + 1;
        holeRight = 2 * hole + 2;

    }
    vec[hole] = holeContact;


}

template <typename Comparable>
void SortingHub<Comparable>::heapify(vector<ComparableNode<Comparable>>& vec) {
    int startIndex = (vec.size() - 2) / 2;

    for (int i = startIndex;i >= 0;i--) {
        percolateDownMaxHeap(vec, vec.size(), i);
    }
   
}


template<typename Comparable>
void SortingHub<Comparable>::HeapSort(vector<ComparableNode<Comparable>>& vec){

    /*HEAPIFY*/
    heapify(vec);



  
    //SWAPPING THE MAX WITH THE LAST ELEMENT OF THE ARRAY
    //AND PERCOLATING THAT DOWN
    for (int i = 0;i < vec.size() - 1;i++) {

        //SWAP PROCESSS
        swapTwo(vec[0], vec[vec.size() - 1 - i]);
        
        /*
        ComparableNode<Comparable> temp = vec[0];
        vec[0] = vec[vec.size() - 1 - i];
        vec[vec.size() - 1 - i] = temp;
        */


        //TREATING PERCOLATING PROCESS AS IF WE DELETE,THUS PASSING 1 SIZE LESS
        percolateDownMaxHeap(vec, vec.size() - i - 1, 0);



    }

}

