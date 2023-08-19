#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
using namespace std;

const int noOfCores = 4; //found by 'nproc' command on terminal
int arr[100]; //user's array

//store the multiple values that are needed in mergeSort function
struct args
{
	int array[100];
	int begin;
	int end;
	int mid;
};
struct args thread_args; //initialized in main
struct args *vals = (struct args*) &thread_args; //assign values of thread_args to this struct which will be used in mergeSort function

// C++ program for Merge Sort
//https://www.geeksforgeeks.org/merge-sort/

// Merges two subarrays of array[].
// First subarray is arr[begin..mid]
// Second subarray is arr[mid+1..end]
void merge(int array[], int const left, int const mid,
           int const right)
{
    auto const subArrayOne = mid - left + 1;
    auto const subArrayTwo = right - mid;
 
    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];
 
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    auto indexOfSubArrayOne
        = 0, // Initial index of first sub-array
        indexOfSubArrayTwo
        = 0; // Initial index of second sub-array
    int indexOfMergedArray
        = left; // Initial index of merged array
 
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    
    //copy the sorted array part back into the user's array
    copy(array, array+indexOfMergedArray, arr);
    
    delete[] leftArray;
    delete[] rightArray;
}

// begin is for left index and end is
// right index of the sub-array
// of arr to be sorted */
/*void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return; // Returns recursively
 
    auto mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}*/

void* mergeSort(void* arg)
{	
	int b, e;

    if (vals->begin >= vals->end)
        return NULL; // Returns recursively
        
    auto mid = vals->begin + (vals->end - vals->begin) / 2;
    vals->mid = mid;
    
 	//mergeSort(array, begin, mid);
 	b = vals->begin; e = vals->end;
 	vals->end = mid;
	mergeSort(NULL);
	
	//mergeSort(array, mid + 1, end);
	vals->begin = mid+1;
	vals->end = e;
	mergeSort(NULL);

    merge(vals->array, b, mid, e);
}

int main()
{
	//print number of cores (nproc on terminal)
	cout << "Number of cores = " << noOfCores << endl;
	//print mac address, found by 'ifconfig -a' command on terminal
	cout << "Mac address = 74:e6:e2:14:5d:62" << endl;
	
	int arrSize;
	
	//take size of array from user
	cout << "Enter number of elements in your array: ";
	cin >> arrSize;
	
	//take array elements from user
	for(int i = 0; i < arrSize; i++)
	{
		cout << "Enter element " << i << " of Array: ";
		cin >> arr[i];
	}
	
	cout << "Your array: ";
	for(int i = 0; i < arrSize; i++)
		cout << arr[i] << ' ';
	
	//declare 4 threads (= no of processors)
	pthread_t threads[noOfCores];
	
	//initialize thread arguments with arguments to be passed to mergeSort function
	for(int i = 0; i < arrSize; i++)
		thread_args.array[i] = arr[i];
	thread_args.begin = 0;
	thread_args.end = arrSize - 1;
	//mergeSort(arr, 0, arr_size - 1);
	
	//create 4 threads and wait for them
	for(int i = 0; i < noOfCores; i++)
	{
		pthread_create(&threads[i], NULL, mergeSort, NULL);
		pthread_join(threads[i], NULL);
	}
	
	//output sorted array
	cout << endl << "Sorted array: ";
	for(int i = 0; i < arrSize; i++)
		cout << arr[i] << ' ';
}

