#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

///SAMPLE COMPARATOR FUNCTIONS
const short int characterLessThan(const void* const, const void* const);
const short int characterGreaterThan(const void* const, const void* const);
const short int integerLessThan(const void* const, const void* const);
const short int integerGreaterThan(const void* const, const void* const);
const short int stringLessThan(const void* const, const void* const);
const short int stringGreaterThan(const void* const, const void* const);

///SORT FUNCTIONS
void insertionSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void selectionSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));

///The reason for the divide and conquerAndCombine methods is because merge sort closely follows the divide and conquer paradigm.
void mergeSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void divide(const void* const, const size_t, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void conquerAndCombine(const void* const, const size_t, const size_t, const size_t, const size_t, const short int(*)(const void* const, const void* const));

///This is the same as insertion sort except binary search is used to search for the location to put the current indexed key as opposed to a backwards linear search.
///However, due to the swaps when moving other keys to place the current indexed key in the appropriate location, the running time is still O(n^2).
void binaryInsertionSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));

///NOT IMPLEMENTED YET
void insertionMergeSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void subInsertionMergeSort(const void* const, const size_t, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void insertionMergeSortMerge(const void* const, const size_t, const size_t, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void binaryInsertionMergeSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void bubbleSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void heapSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void quickSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void countingSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void radixSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void bucketSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));
void treeSort(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const));

///TEST FUNCTION FOR UNIT TESTING
void sortTest(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const), void(*)(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const)));

#endif///SORT_H_INCLUDED
