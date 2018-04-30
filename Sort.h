#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include<stddef.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

///CONTINUE AT CHAPTER 9 IN CLRS.

///SAMPLE COMPARATOR FUNCTIONS
int characterAscending(const void*, const void*);
int characterDescending(const void*, const void*);
int integerAscending(const void*, const void*);
int integerDescending(const void*, const void*);
int stringAscending(const void*, const void*);
int stringDescending(const void*, const void*);

///SORT FUNCTIONS
void insertionSort(void*, size_t, size_t, int(*)(const void*, const void*));
void selectionSort(void*, size_t, size_t, int(*)(const void*, const void*));
void bubbleSort(void*, size_t, size_t, int(*)(const void*, const void*));
void heapSort(void*, size_t, size_t, int(*)(const void*, const void*));

///The reason for the mergeSortDivide and mergeSortConquerCombine methods is because merge sort closely follows the divide and conquer paradigm.
void mergeSort(void*, size_t, size_t, int(*)(const void*, const void*));
void mergeSortDivide(void*, size_t, size_t, size_t, int(*)(const void*, const void*));
void mergeSortConquerCombine(void*, size_t, size_t, size_t, size_t, int(*)(const void*, const void*));

///This is the same as insertion sort but recursion is used instead of iteration to sort the elements in the provided sequence.
///The running time is O(n^2) as in normal insertion sort because you recurse n-1 times and then you swap at most n times to
///find the appropriate index to insert a key, thus (n-1)*n at worst case is O(n^2).
void recursiveInsertionSort(void*, size_t, size_t, int(*)(const void*, const void*));

///This is the same as insertion sort except binary search is used to search for the location to put the current indexed key as opposed to a backwards linear search.
///However, due to the swaps when moving other keys to place the current indexed key in the appropriate location, the running time is still O(n^2).
void binaryInsertionSort(void*, size_t, size_t, int(*)(const void*, const void*));

///This is my implementation of quick sort. The C standard library provides its
///own version of quick sort known as qsort() with the exact same parameters as my version.
///Thus, one can use mine or the C standard library's version if they wish. Note: Both
///mine and the C standard library's versions of quick sort could be used in the sortTest()
///function I implemented to test for correctness.
///The reason for the quickSortDivide and quickSortConquerCombine methods is because quick sort, like merge sort, closely follows the divide and conquer paradigm.
///However, unlike merge sort, it sorts in place, meaning little to no outside temporary element storage is used.
void quickSort(void*, size_t, size_t, int(*)(const void*, const void*));
size_t quickSortDivide(void*, size_t, size_t, size_t, int(*)(const void*, const void*));
void quickSortConquerCombine(void*, size_t, size_t, size_t, int(*)(const void*, const void*));

///NOT IMPLEMENTED YET
void randomizedQuickSort(void*, size_t, size_t, int(*)(const void*, const void*));
void tailRecursiveQuickSort(void*, size_t, size_t, int(*)(const void*, const void*));
void fuzzySort(void*, size_t, size_t, size_t, int(*)(const void*, const void*));
void countingSort(void*, size_t, size_t, int(*)(const void*, const void*));
void radixSort(void*, size_t, size_t, int(*)(const void*, const void*));
void bucketSort(void*, size_t, size_t, int(*)(const void*, const void*));
void compareExchangeInsertionSort(void*, size_t, size_t, int(*)(const void*, const void*));
void columnSort(void**, size_t, size_t, size_t, int(*)(const void*, const void*));

///TEST FUNCTION FOR UNIT TESTING
void sortTest(void*, size_t, size_t, int(*)(const void*, const void*), void(*)(void*, size_t, size_t, int(*)(const void*, const void*)));

#endif///SORT_H_INCLUDED
