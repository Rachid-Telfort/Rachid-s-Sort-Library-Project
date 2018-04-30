#include"Sort.h"

int characterAscending(const void* firstComparate, const void* secondComparate)
{
    if(*(const char*)firstComparate<*(const char*)secondComparate)
    {
        return -1;
    }

    else if(*(const char*)firstComparate>*(const char*)secondComparate)
    {
        return 1;
    }

    return 0;
}

int characterDescending(const void* firstComparate, const void* secondComparate)
{
    if(*(const char*)firstComparate<*(const char*)secondComparate)
    {
        return 1;
    }

    else if(*(const char*)firstComparate>*(const char*)secondComparate)
    {
        return -1;
    }

    return 0;
}

int integerAscending(const void* firstComparate, const void* secondComparate)
{
    if(*(const int*)firstComparate<*(const int*)secondComparate)
    {
        return -1;
    }

    else if(*(const int*)firstComparate>*(const int*)secondComparate)
    {
        return 1;
    }

    return 0;
}

int integerDescending(const void* firstComparate, const void* secondComparate)
{
    if(*(const int*)firstComparate<*(const int*)secondComparate)
    {
        return 1;
    }

    else if(*(const int*)firstComparate>*(const int*)secondComparate)
    {
        return -1;
    }

    return 0;
}

int stringAscending(const void* firstComparate, const void* secondComparate)
{
    return strcmp(*(const char**)firstComparate, *(const char**)secondComparate);
}

int stringDescending(const void* firstComparate, const void* secondComparate)
{
    return -strcmp(*(const char**)firstComparate, *(const char**)secondComparate);
}

void insertionSort(void* sequence, size_t sequenceSize, size_t sequenceElementSize, int(*comparator)(const void*, const void*))
{
    if(sequence&&sequenceSize>1)
    {
        ///This points to the first byte of the sequence.
        unsigned char* sequenceStart=sequence;

        ///This points to the first byte of the current key where we are trying to insert it in its appropriate index.
        unsigned char* mainKeyPointer;

        ///This helps with inserting the key to insert in its appropriate slot.
        unsigned char* otherKeyPointer;

        ///This helps with the key swap mechanism when doing the backwards linear search to place the key to insert in its appropriate index.
        unsigned char* keySwapPointer;

        ///This helps with placing the key to insert in its appropriate index.
        unsigned char* keyPlacementPointer;

        ///This holds the key to insert's data so as to not get lost due to the swap mechanism in the backwards linear search to place the key to insert in its appropriate slot.
        unsigned char* mainKeyBuffer=malloc(sequenceElementSize*sizeof(unsigned char));

        ///This is the case where memory is failed to be allocated.
        if(!mainKeyBuffer)
        {
            printf("Error: Memory could not be allocated to continue insertion sort.\n\n");
            printf("Aborting insertion sort...\n\n");

            return;
        }

        ///This keeps track of the index of the key that we are inserting in its rightful place.
        size_t index=1;

        ///This keeps track of the other keys' indexes that are being swapped in the backwards linear search mechanism.
        ptrdiff_t subIndex;

        ///We start at the second element due to the backwards linear search for each element of the sequence to place it in its appropriate index.
        ///The first element has no elements before it so the backwards linear search is not possible as well as the fact that the first element is assumed to be sorted by default.
        ///This is due to the fact that the sub array before the key to be placed is already sorted.
        for(; index<sequenceSize; ++index)
        {
            ///We are preparing the key to be inserted as well as the pointer that will point to the end of the sorted sub array before the index of the key to be inserted.
            mainKeyPointer=sequenceStart+index*sequenceElementSize;
            otherKeyPointer=sequenceStart+(index-1)*sequenceElementSize;
            memcpy(mainKeyBuffer, mainKeyPointer, sequenceElementSize);

            ///We are now doing the swaps to find the appropriate index to insert the key to insert.
            for(subIndex=index-1; subIndex>=0&&comparator(mainKeyBuffer, otherKeyPointer)<0; --subIndex)
            {
                ///We are doing the swapping and comparing.
                keySwapPointer=otherKeyPointer+sequenceElementSize;
                memcpy(keySwapPointer, otherKeyPointer, sequenceElementSize);
                otherKeyPointer-=sequenceElementSize;
            }

            ///We place the key to be inserted at its appropriate index.
            keyPlacementPointer=otherKeyPointer+sequenceElementSize;
            memcpy(keyPlacementPointer, mainKeyBuffer, sequenceElementSize);
        }

        ///Cleaning up resources since the sorting is done.
        free(mainKeyBuffer);
    }
}

void selectionSort(void* sequence, size_t sequenceSize, size_t sequenceElementSize, int(*comparator)(const void*, const void*))
{
    if(sequence&&sequenceSize>1)
    {
        ///This points to the first byte of the sequence.
        unsigned char* sequenceStart=sequence;

        ///This points to the main key that we are selecting against for sorting purposes.
        unsigned char* mainKeyPointer;

        ///This helps with the key swap mechanism that occurs if or when we find the appropriate key to select against the main key.
        unsigned char* swapKeyPointer;

        ///This helps with comparing keys when searching for a key to select against the main key.
        unsigned char* otherKeyPointer;

        ///This holds the current key data for swapping the current key with a key found, if one is found, to be selected against the main key
        ///so as to not lose the main key data.
        unsigned char* mainKeyBuffer=malloc(sequenceElementSize*sizeof(unsigned char));

        ///This is the case where memory is failed to be allocated.
        if(!mainKeyBuffer)
        {
            printf("Error: Memory could not be allocated to continue selection sort.\n\n");
            printf("Aborting selection sort...\n\n");

            return;
        }

        ///This helps keep track of the index of the main key that is being selected against.
        size_t index=0;

        ///This helps keep track of the other keys that are being selected against the main key.
        size_t subIndex;

        ///The reason we end at the second-to-last element and not the last element in the sequence is because due to the selection mechanism, two elements must be selected against
        ///each other in each iteration, i.e. the main element and one of the other elements in the sub array after the main element. That means that the last element in the sequence that will have another key to be selected against it is the second-to-last element
        ///as the last element will have no more elements to select against it. Furthermore by the time we get to the last element all other previous elements would
        ///have been selected against and put in their appropriate slots meaning the last element would have been in its appropriate slot further meaning that the sequence would be
        ///already sorted by the time we get to the last element.
        for(; index<sequenceSize-1; ++index)
        {
            ///Setting the main key pointer to point to the main key to be selected against.
            mainKeyPointer=sequenceStart+index*sequenceElementSize;

            ///Setting up the swap pointer to point to the same key as the main key for
            ///comparison purposes.
            swapKeyPointer=mainKeyPointer;

            ///Setting up the helper pointer to point to the start of the sub array after the main key
            ///in order to find another key to select against the main key.
            otherKeyPointer=sequenceStart+(index+1)*sequenceElementSize;

            ///We are now going to find the appropriate key to select against the main key.
            for(subIndex=index+1; subIndex<sequenceSize; ++subIndex)
            {
                if(comparator(otherKeyPointer, swapKeyPointer)<0)
                {
                    swapKeyPointer=otherKeyPointer;
                }

                otherKeyPointer+=sequenceElementSize;
            }

            ///We perform the swap mechanism if we found a key to select against the main key.
            if(mainKeyPointer!=swapKeyPointer)
            {
                memcpy(mainKeyBuffer, mainKeyPointer, sequenceElementSize);
                memcpy(mainKeyPointer, swapKeyPointer, sequenceElementSize);
                memcpy(swapKeyPointer, mainKeyBuffer, sequenceElementSize);
            }
        }

        ///Cleaning up resources since the sorting is done.
        free(mainKeyBuffer);
    }
}

void bubbleSort(void* sequence, size_t sequenceSize, size_t sequenceElementSize, int(*comparator)(const void*, const void*))
{
    if(sequence&&sequenceSize>1)
    {
        ///This points to the first byte of the sequence.
        unsigned char* sequenceStart=sequence;

        ///This points to the main key that we are checking against, based on the comparator function passed, for sorting purposes.
        unsigned char* mainKeyPointer;

        ///This helps with the key swap mechanism that occurs if or when we find the appropriate key to check against the main key.
        unsigned char* swapKeyPointer;

        ///This holds the current key data for swapping the current key with a key found, if one is found, to be checked against the main key
        ///so as to not lose the main key data.
        unsigned char* mainKeyBuffer=malloc(sequenceElementSize*sizeof(unsigned char));

        ///This is the case where memory is failed to be allocated.
        if(!mainKeyBuffer)
        {
            printf("Error: Memory could not be allocated to continue bubble sort.\n\n");
            printf("Aborting bubble sort...\n\n");

            return;
        }

        ///This helps keep track of the index of the main key that is being checked against.
        size_t index=0;

        ///This helps keep track of the other keys, to potentially swap with the main key, that are being checked against the main key.
        size_t subIndex;

        ///The reason we loop until the second-to-last element is because once we get to the last element
        ///all other elements before it have already been checked against it. That means once we get to
        ///the last element, the sequence is already in sorted order.
        for(; index<sequenceSize-1; ++index)
        {
            ///In this loop, we go backwards in the sequence starting with the last element
            ///and swap elements as appropriate. The reason we stop at the second element is because
            ///the first element has no other elements before it to check against and/or to swap with.
            for(subIndex=sequenceSize-1; subIndex>=index+1; --subIndex)
            {
                ///Setting the main key pointer to point to the main key to be checked against.
                mainKeyPointer=sequenceStart+subIndex*sequenceElementSize;

                ///Setting up the swap pointer to point to the key before the main key for
                ///comparison purposes.
                swapKeyPointer=sequenceStart+(subIndex-1)*sequenceElementSize;

                ///We perform the swap mechanism if a key is found to swap with the main key
                ///based on the comparator function passed.
                if(comparator(mainKeyPointer, swapKeyPointer)<0)
                {
                    memcpy(mainKeyBuffer, mainKeyPointer, sequenceElementSize);
                    memcpy(mainKeyPointer, swapKeyPointer, sequenceElementSize);
                    memcpy(swapKeyPointer, mainKeyBuffer, sequenceElementSize);
                }
            }
        }

        ///Cleaning up resources since the sorting is done.
        free(mainKeyBuffer);
    }
}

void heapSort(void* sequence, size_t sequenceSize, size_t sequenceElementSize, int(*comparator)(const void*, const void*))
{
    if(sequence&&sequenceSize>1)
    {
        ///This points to the first byte of the sequence.
        unsigned char* sequenceStart=sequence;

        ///This points to the main key in the array heap that we are checking against its parent element for sorting purposes.
        unsigned char* mainKeyPointer;

        ///This helps with the key swap mechanism that occurs if or when the parent element violates the heap property in relation to the main key.
        unsigned char* swapKeyPointer;

        ///This holds the main key data for swapping the main key's parent element with the main key, if the heap property is violated based on the comparator,
        ///so as to not lose the main key data.
        unsigned char* mainKeyBuffer=malloc(sequenceElementSize*sizeof(unsigned char));

        ///This is the case where memory is failed to be allocated.
        if(!mainKeyBuffer)
        {
            printf("Error: Memory could not be allocated to continue heap sort.\n\n");
            printf("Aborting heap sort...\n\n");

            return;
        }

        ///This helps keep track of the index of the main key that is being checked against its parent element.
        size_t index=sequenceSize-1;

        ///This helps with keeping track of the elements remaining in the array heap during the sorting mechanism.
        size_t subIndex;

        ///This for loop first creates the array heap based on the comparator passed.
        ///We go backwards starting at the last element of the array, similar to a binary heap, and check if its parent
        ///violates the heap property. If that is the case, then we swap the current element and its parent. Since this is a
        ///zero-index based array heap, at every element these properties hold true: given an element at index i,
        ///its parent element can be found at index (i-1)/2, its left child element can be found at index 2i+1, and its
        ///right child element can be found at index 2i+2.
        for(; index>0; --index)
        {
            ///We set the main key pointer to the current element we are checking against its parent.
            mainKeyPointer=sequenceStart+index*sequenceElementSize;

            ///We set the swap key pointer to the current element's parent element.
            swapKeyPointer=sequenceStart+(index-1)/2*sequenceElementSize;

            ///We perform the swap mechanism if the main key's parent element violates the heap property
            ///based on the comparator.
            if(comparator(mainKeyPointer, swapKeyPointer)>0)
            {
                memcpy(mainKeyBuffer, mainKeyPointer, sequenceElementSize);
                memcpy(mainKeyPointer, swapKeyPointer, sequenceElementSize);
                memcpy(swapKeyPointer, mainKeyBuffer, sequenceElementSize);
            }
        }

        ///We set up the index to point to the last element of the heap array to get ready for the actual sorting
        ///and potential future swaps.
        index=sequenceSize-1;

        for(; index>0; --index)
        {
            ///We set up the main key pointer to point to the first element of the elements remaining in the heap.
            ///This element will be the next element, backwards, of the final sorted array.
            mainKeyPointer=sequenceStart;

            ///We set up the swap key pointer to point to the last element of the elements remaining in the heap. We will swap
            ///this element with the element pointed to by the main key pointer for the sorting to work appropriately.
            swapKeyPointer=sequenceStart+index*sequenceElementSize;

            ///These three line is where we perform the aforementioned swap mechanism.
            memcpy(mainKeyBuffer, mainKeyPointer, sequenceElementSize);
            memcpy(mainKeyPointer, swapKeyPointer, sequenceElementSize);
            memcpy(swapKeyPointer, mainKeyBuffer, sequenceElementSize);

            ///We set up the subIndex size_t variable to the index of the last element of the array heap.
            ///This will help with reorganizing the remaining elements in the array heap to
            ///restore the heap property, based on the comparator, for the next iteration of the sorting mechanism.
            subIndex=index-1;

            ///This for loop rearranges the remaining elements in the array heap in order to restore the heap property
            ///to get ready for the next iteration of the sorting mechanism. This is similar to the loop that made the initial
            ///array heap before the sorting mechanism took place.
            for(; subIndex>0; --subIndex)
            {
                mainKeyPointer=sequenceStart+subIndex*sequenceElementSize;
                swapKeyPointer=sequenceStart+(subIndex-1)/2*sequenceElementSize;

                if(comparator(mainKeyPointer, swapKeyPointer)>0)
                {
                    memcpy(mainKeyBuffer, mainKeyPointer, sequenceElementSize);
                    memcpy(mainKeyPointer, swapKeyPointer, sequenceElementSize);
                    memcpy(swapKeyPointer, mainKeyBuffer, sequenceElementSize);
                }
            }
        }

        ///Cleaning up resources since the sorting is done.
        free(mainKeyBuffer);
    }
}

void quickSort(void* sequence, size_t sequenceSize, size_t sequenceElementSize, int(*comparator)(const void*, const void*))
{
    if(sequence&&sequenceSize>1)
    {
        quickSortConquerCombine(sequence, sequenceElementSize, 0, sequenceSize, comparator);
    }
}

size_t quickSortDivide(void* sequence, size_t sequenceElementSize, size_t subSequenceStart, size_t subSequenceEnd, int(*comparator)(const void*, const void*))
{
    ///This points to the first byte of the sequence.
    unsigned char* sequenceStart=sequence;

    ///This will point to the key that will be used as the pivot in the partitioning mechanism.
    ///We set the main key pointer to point to the last element in the array.
    ///This element will be used as the pivot for the rest of this function.
    unsigned char* mainKeyPointer=sequenceStart+(subSequenceEnd-1)*sequenceElementSize;

    ///This will help with the key swap mechanism that occurs if or when we find the appropriate key to partition in regards to the pivot based on the comparator.
    unsigned char* swapKeyPointer;

    ///This will also help with the key swap mechanism that occurs if or when we find the appropriate key to partition in regards to the pivot based on the comparator.
    unsigned char* otherKeyPointer;

    ///This will hold the swap key data for swapping the key pointed to by the swap key pointer key with a key found, if one is found, to be selected against the swap key
    ///so as to not lose the swap key data.
    unsigned char* mainKeyBuffer=malloc(sequenceElementSize*sizeof(unsigned char));

    ///This is the case where memory is failed to be allocated.
    if(!mainKeyBuffer)
    {
        printf("Error: Memory could not be allocated to continue quick sort.\n\n");
        printf("Aborting quick sort...\n\n");

        ///We return zero here because it is the smallest number of the size_t integral data type.
        ///We cannot return a negative number due to the size_t integral data type being unsigned.
        return 0;
    }

    ///We set up the index size_t variable to reference the last element of the array, i.e. the pivot element
    ///that we will partition the other elements of the subsequence against.
    ptrdiff_t index=subSequenceStart-1;

    ///We set up the subIndex size_t variable to reference the start of the subsequence
    ///in order to partition all the elements before the pivot appropriately.
    size_t subIndex=subSequenceStart;

    ///This for loop will go through all the elements before the pivot and compare them against
    ///the pivot in order to partition the other elements appropriately in the subsequence.
    for(; subIndex<subSequenceEnd-1; ++subIndex)
    {
        ///We set up the swap key pointer to point to the current indexed element
        ///in the subsequence before the pivot.
        swapKeyPointer=sequenceStart+subIndex*sequenceElementSize;

        ///Here we check if the pivot element goes against the current element.
        ///If it does, then we swap the current element with the element that is referenced by the
        ///index size_t variable so all elements that go before and after the pivot are at their appropriate
        ///places when the loop is done.
        if(comparator(mainKeyPointer, swapKeyPointer)>=0)
        {
            ///We increase the index size_t variable to keep it within bounds of the
            ///subsequence and to help with the swapping mechanism.
            ++index;

            ///We set the other key pointer to point to the element referenced by the index
            ///size_t variable so as to be able to employ the swapping mechanism.
            otherKeyPointer=sequenceStart+index*sequenceElementSize;

            ///Here we employ the swapping mechanism.
            memcpy(mainKeyBuffer, otherKeyPointer, sequenceElementSize);
            memcpy(otherKeyPointer, swapKeyPointer, sequenceElementSize);
            memcpy(swapKeyPointer, mainKeyBuffer, sequenceElementSize);
        }
    }

    ///Here we assign the swap key pointer to point to the element after the element
    ///referenced by the index size_t variable. The reason we point to the element after the element referenced after
    ///the index size_t variable is because we want to keep the pivot element within bounds of the subsequence which can happen
    ///if a swap never occurred in the above for loop.
    swapKeyPointer=sequenceStart+(index+1)*sequenceElementSize;

    ///Here we swap the pivot element and the element pointed to by the swap key pointer so we can place the pivot
    ///in its appropriate spot in the now-partitioned subsequence.
    memcpy(mainKeyBuffer, mainKeyPointer, sequenceElementSize);
    memcpy(mainKeyPointer, swapKeyPointer, sequenceElementSize);
    memcpy(swapKeyPointer, mainKeyBuffer, sequenceElementSize);

    ///Cleaning up resources since the partitioning is done.
    free(mainKeyBuffer);

    ///We return the appropriate size_t index of the element that is the pivot.
    return index+1;
}

void quickSortConquerCombine(void* sequence, size_t sequenceElementSize, size_t subSequenceStart, size_t subSequenceEnd, int(*comparator)(const void*, const void*))
{
    ///We check if the current subsequence is greater than one element.
    ///If it is not, then we do not need to break the subsequence down and sort it
    ///as the sequence is already sorted.
    if(subSequenceEnd>0&&subSequenceStart<subSequenceEnd-1)
    {
        ///We first get the pivot which is the index that the conquer and combine step will use as a reference
        ///when breaking the initial array into smaller sequences for further partitioning. Getting the pivot is the
        ///divide step of the divide, conquer, and combine paradigm in regards to quick sort.
        size_t pivot=quickSortDivide(sequence, sequenceElementSize, subSequenceStart, subSequenceEnd, comparator);

        ///Based on the pivot, we further break the array down into all elements less than or equal to the pivot until
        ///we have one-element sub arrays and recurse back up, probably making additional partitions in the process, finishing with the initial array being sorted.
        quickSortConquerCombine(sequence, sequenceElementSize, subSequenceStart, pivot, comparator);

        ///Based on the pivot, we further break the array down into all elements greater than the pivot until
        ///we have one-element sub arrays and recurse back up, probably making additional partitions in the process, finishing with the initial array being sorted.
        quickSortConquerCombine(sequence, sequenceElementSize, pivot, subSequenceEnd, comparator);
    }
}

void mergeSort(void* sequence, size_t sequenceSize, size_t sequenceElementSize, int(*comparator)(const void*, const void*))
{
    if(sequence&&sequenceSize>1)
    {
        mergeSortDivide(sequence, sequenceElementSize, 0, sequenceSize, comparator);
    }
}

void mergeSortDivide(void* sequence, size_t sequenceElementSize, size_t subSequenceStart, size_t subSequenceEnd, int(*comparator)(const void*, const void*))
{
    ///We check if the current subsequence is greater than one element.
    ///If it is not, then we do not need to break the subsequence down and sort it
    ///as the sequence is already sorted.
    if(subSequenceEnd>0&&subSequenceStart<subSequenceEnd-1)
    {
        ///Here we breakdown the first half of the subsequence recursively until we reach the base case of the subsequence having one element.
        mergeSortDivide(sequence, sequenceElementSize, subSequenceStart, (subSequenceStart+subSequenceEnd)/2, comparator);

        ///Here we breakdown the second half of the subsequence recursively until we reach the base case of the subsequence having one element.
        mergeSortDivide(sequence, sequenceElementSize, (subSequenceStart+subSequenceEnd)/2, subSequenceEnd, comparator);

        ///Here we combine the two halves of the subsequence by comparing the elements in each half with the result being the sorted subsequence.
        mergeSortConquerCombine(sequence, sequenceElementSize, subSequenceStart, (subSequenceStart+subSequenceEnd)/2, subSequenceEnd, comparator);
    }
}

void mergeSortConquerCombine(void* sequence, size_t sequenceElementSize, size_t subSequenceStart, size_t subSequenceMiddle, size_t subSequenceEnd, int(*comparator)(const void*, const void*))
{
    ///This points to the first byte of the sequence.
    unsigned char* sequenceStart=sequence;

    ///This keeps track of the amount of elements that will be in the helper sequence
    ///that will contain all the elements from the first half of the unsorted subsequence.
    size_t leftSubSequenceSize=subSequenceMiddle-subSequenceStart;

    ///This keeps track of the amount of elements that will be in the helper sequence
    ///that will contain all the elements from the second half of the unsorted subsequence.
    size_t rightSubSequenceSize=subSequenceEnd-subSequenceMiddle;

    ///This holds the elements for the first half of the unsorted subsequence.
    unsigned char* leftSubSequence=malloc(leftSubSequenceSize*sequenceElementSize*sizeof(unsigned char));

    ///This is the case where memory is failed to be allocated for the first helper sequence.
    if(!leftSubSequence)
    {
        printf("Error: Memory could not be allocated in the first helper sequence to continue merge sort.\n\n");
        printf("Aborting merge sort...\n\n");

        return;
    }

    ///This holds the elements for the second half of the unsorted subsequence.
    unsigned char* rightSubSequence=malloc(rightSubSequenceSize*sequenceElementSize*sizeof(unsigned char));

    ///This is the case where memory is failed to be allocated for the second helper sequence.
    if(!rightSubSequence)
    {
        printf("Error: Memory could not be allocated in the second helper sequence to continue merge sort.\n\n");
        printf("Aborting merge sort...\n\n");

        free(leftSubSequence);

        return;
    }

    ///This helps with copying the data from the subsequence into the helper sequences
    ///as well as sorting the subsequence.
    unsigned char* sequencePointer;

    ///This helps with copying data from the subsequence into the first helper sequence
    ///as well as to keep track of the current element in the first helper sequence
    ///when sorting the subsequence.
    unsigned char* leftSubSequencePointer;

    ///This helps with copying data from the subsequence into the second helper sequence
    ///as well as to keep track of the current element in the second helper sequence
    ///when sorting the subsequence.
    unsigned char* rightSubSequencePointer;

    ///This helps with keeping track of the current element in the first helper sequence.
    size_t leftIndex=0;

    ///This helps with keeping track of the current element in the second helper sequence.
    size_t rightIndex=0;

    ///This helps keep track of the current element in the subsequence.
    size_t subSequenceIndex=0;

    ///We set up the sequencePointer to point to the first byte of the subsequence.
    sequencePointer=sequenceStart+subSequenceStart*sequenceElementSize;

    ///We set up the leftSubSequencePointer to point
    ///to the first byte of the first helper sequence.
    leftSubSequencePointer=leftSubSequence;

    ///Now we copy the first half of the subsequence into the first helper sequence.
    for(; leftIndex<leftSubSequenceSize; ++leftIndex)
    {
        memcpy(leftSubSequencePointer, sequencePointer, sequenceElementSize);
        sequencePointer+=sequenceElementSize;
        leftSubSequencePointer+=sequenceElementSize;
    }

    ///We set up the sequencePointer to point to the first byte of the middle element of the subsequence.
    sequencePointer=sequenceStart+subSequenceMiddle*sequenceElementSize;

    ///We set up the rightSubSequencePointer to point
    ///to the first byte of the second helper sequence.
    rightSubSequencePointer=rightSubSequence;

    ///Now we copy the second half of the subsequence into the second helper sequence.
    for(; rightIndex<rightSubSequenceSize; ++rightIndex)
    {
        memcpy(rightSubSequencePointer, sequencePointer, sequenceElementSize);
        sequencePointer+=sequenceElementSize;
        rightSubSequencePointer+=sequenceElementSize;
    }

    ///We set up the helper variables that will help us sort the subsequence.
    leftIndex=0;
    rightIndex=0;
    subSequenceIndex=subSequenceStart;

    ///We set up the sequencePointer to point to the first byte of the subsequence
    ///in preparation for sorting.
    sequencePointer=sequenceStart+subSequenceIndex*sequenceElementSize;

    ///We set up the leftSubSequencePointer to point
    ///to the first byte of the first helper sequence
    ///in preparation for sorting.
    leftSubSequencePointer=leftSubSequence;

    ///We set up the rightSubSequencePointer to point
    ///to the first byte of the second helper sequence
    ///in preparation for sorting.
    rightSubSequencePointer=rightSubSequence;

    ///Now we compare the elements in the helper sequences to sort the subsequence.
    for(; subSequenceIndex<subSequenceEnd; ++subSequenceIndex)
    {
        ///This is the case where all the elements of the first helper sequence
        ///have already been added to the sorted subsequence
        ///before all the elements of the second helper sequence have been added
        ///to the subsequence as the subsequence becomes sorted.
        if(leftIndex==leftSubSequenceSize)
        {
            memcpy(sequencePointer, rightSubSequencePointer, sequenceElementSize);
            rightSubSequencePointer+=sequenceElementSize;
            ++rightIndex;
        }

        ///This is the case where all the elements of the second helper sequence
        ///have already been added to the sorted subsequence
        ///before all the elements of the first helper sequence have been added
        ///to the subsequence as the subsequence becomes sorted.
        else if(rightIndex==rightSubSequenceSize)
        {
            memcpy(sequencePointer, leftSubSequencePointer, sequenceElementSize);
            leftSubSequencePointer+=sequenceElementSize;
            ++leftIndex;
        }

        ///This is the case where the current element in the first helper sequence
        ///is the element before the current element in the second helper sequence
        ///based on the comparator passed to mergeSort. Thus, the current element in the
        ///first helper sequence is chosen to be added to the subsequence as the subsequence becomes sorted.
        else if(comparator(leftSubSequencePointer, rightSubSequencePointer)<0)
        {
            memcpy(sequencePointer, leftSubSequencePointer, sequenceElementSize);
            leftSubSequencePointer+=sequenceElementSize;
            ++leftIndex;
        }

        ///This is the case where the current element in the second helper sequence
        ///is the element before the current element in the first helper sequence
        ///based on the comparator passed to mergeSort. Thus, the current element in the
        ///second helper sequence is chosen to be added to the subsequence as the subsequence becomes sorted.
        else
        {
            memcpy(sequencePointer, rightSubSequencePointer, sequenceElementSize);
            rightSubSequencePointer+=sequenceElementSize;
            ++rightIndex;
        }

        sequencePointer+=sequenceElementSize;
    }

    ///Cleaning up resources since the sorting is done.
    free(leftSubSequence);
    free(rightSubSequence);
}

void recursiveInsertionSort(void* sequence, size_t sequenceSize, size_t sequenceElementSize, int(*comparator)(const void*, const void*))
{
    if(sequence&&sequenceSize>1)
    {
        ///Here we recurse until we get down to one-element sub arrays. Then we recurse up employing the
        ///backwards linear search and swap mechanisms of merge sort on the sub arrays until the initial
        ///array is sorted.
        recursiveInsertionSort(sequence, sequenceSize-1, sequenceElementSize, comparator);

        ///This points to the first byte of the sequence.
        unsigned char* sequenceStart=sequence;

        ///This holds the key to insert's data so as to not get lost due to the swap mechanism in the backwards linear search to place the key to insert in its appropriate slot.
        unsigned char* mainKeyBuffer=malloc(sequenceElementSize*sizeof(unsigned char));

        ///This is the case where memory is failed to be allocated.
        if(!mainKeyBuffer)
        {
            printf("Error: Memory could not be allocated to continue recursive insertion sort.\n\n");
            printf("Aborting recursive insertion sort...\n\n");

            return;
        }

        ///We assign the index size_t variable to reference the last element of the subsequence.
        ///This is necessary as we plan to do a backwards linear search of the subsequence in order to put the element chosen
        /// to be inserted at its appropriate spot in the subsequence.
        size_t index=sequenceSize-1;

        ///We assign the subIndex size_t variable to reference the element before the element referenced by the
        ///index size_t variable as we will start the backwards linear search at the subIndex size_t variable.
        ptrdiff_t subIndex=index-1;

        ///We set up the main key pointer to point to the element referenced by the index size_t variable.
        ///This will be our element chosen to be inserted.
        unsigned char* mainKeyPointer=sequenceStart+index*sequenceElementSize;

        ///We set up the other key pointer to point to the element referenced by the subIndex size_t variable.
        ///This will help us in the backwards linear search to place the key to be inserted in its appropriate spot.
        unsigned char* otherKeyPointer=sequenceStart+subIndex*sequenceElementSize;

        ///This will help with the swapping mechanism that will be done in the backwards linear search
        ///to place the key to be inserted in its appropriate index.
        unsigned char* keySwapPointer;

        ///This will help with placing the key to insert in its appropriate spot after the backwards linear search is done.
        unsigned char* keyPlacementPointer;

        ///We are preparing the key to be inserted by putting it in a buffer in case the original key to be inserted is overwritten.
        memcpy(mainKeyBuffer, mainKeyPointer, sequenceElementSize);

        ///We are now doing the swaps to find the appropriate index to insert the key to insert.
        for(; subIndex>=0&&comparator(mainKeyBuffer, otherKeyPointer)<0; --subIndex)
        {
            ///We are doing the swapping and comparing.
            keySwapPointer=otherKeyPointer+sequenceElementSize;
            memcpy(keySwapPointer, otherKeyPointer, sequenceElementSize);
            otherKeyPointer-=sequenceElementSize;
        }

        ///We place the key to be inserted at its appropriate index.
        keyPlacementPointer=otherKeyPointer+sequenceElementSize;
        memcpy(keyPlacementPointer, mainKeyBuffer, sequenceElementSize);

        ///Cleaning up resources since the sorting is done.
        free(mainKeyBuffer);
    }
}

void binaryInsertionSort(void* sequence, size_t sequenceSize, size_t sequenceElementSize, int(*comparator)(const void*, const void*))
{
    if(sequence&&sequenceSize>1)
    {
        ///This points to the first byte of the sequence.
        unsigned char* sequenceStart=sequence;

        ///This points to the first byte of the current key where
        ///we are trying to insert it in its appropriate index.
        unsigned char* mainKeyPointer;

        ///This helps with inserting the key to insert
        ///in its appropriate slot.
        unsigned char* otherKeyPointer;

        ///This helps with the key swap mechanism when doing the backwards binary search
        ///to place the key to insert in its appropriate index.
        unsigned char* keySwapPointer;

        ///This helps with placing the key to insert
        ///in its appropriate index.
        unsigned char* keyPlacementPointer;

        ///This holds the key to insert's data so as to not get lost
        ///due to the swap mechanism in the backwards linear search to
        ///place the key to insert in its appropriate slot.
        unsigned char* mainKeyBuffer=malloc(sequenceElementSize*sizeof(unsigned char));

        ///This is the case where memory is failed to be allocated.
        if(!mainKeyBuffer)
        {
            printf("Error: Memory could not be allocated to continue binary insertion sort.\n\n");
            printf("Aborting binary insertion sort...\n\n");

            return;
        }

        ///This keeps track of the index of the key that
        ///we are inserting in its rightful place.
        size_t index=1;

        ///This keeps track of the other keys' indexes
        ///that are being swapped in the backwards linear search mechanism.
        ptrdiff_t subIndex;

        ///This keeps track of the first key's index in the
        ///subsequence to be binary searched.
        ptrdiff_t startIndex;

        ///This keeps track of the index of the key
        ///that is being compared against in the binary search mechanism.
        ptrdiff_t middleIndex;

        ///This keeps track of the last key's index in the
        ///subsequence to be binary searched.
        ptrdiff_t endIndex;

        ///We start at the second element due to the backwards linear search
        ///for each element of the sequence to place it in its appropriate index
        ///after the appropriate index is found using binary search.
        ///The first element has no elements before it so the backwards linear search
        ///is not possible as well as the fact that the first element is assumed to be sorted by default.
        ///This is due to the fact that the sub array before the key to be placed is already sorted.
        for(; index<sequenceSize; ++index)
        {
            ///We are preparing the key that will be inserted in its rightful place
            ///in the sequence.
            mainKeyPointer=sequenceStart+index*sequenceElementSize;
            memcpy(mainKeyBuffer, mainKeyPointer, sequenceElementSize);

            ///We are preparing the indexes that will be used in the binary search mechanism.
            startIndex=0;
            endIndex=index-1;
            middleIndex=(startIndex+endIndex)/2;

            ///We are preparing the pointer that will be used to help in
            ///the binary search mechanism as well as point to
            ///the end of the sorted subsequence before the index of the
            ///key to be inserted.
            otherKeyPointer=sequenceStart+middleIndex*sequenceElementSize;

            ///We are now employing the binary search mechanism.
            while(startIndex<=endIndex)
            {
                ///This is the case where we have to go down in the
                ///subsequence to search for the correct position
                ///thus eliminating the subsequence [middleIndex, endIndex].
                if(comparator(mainKeyBuffer, otherKeyPointer)<0)
                {
                    ///We are now recalculating indexes appropriately.
                    endIndex=middleIndex-1;
                    middleIndex=(startIndex+endIndex)/2;
                }

                ///This is the case where we have to go up in the
                ///subsequence to search for the correct position
                ///thus eliminating the subsequence [startIndex, middleIndex].
                else if(comparator(mainKeyBuffer, otherKeyPointer)>0)
                {
                    ///We are now recalculating indexes appropriately.
                    startIndex=middleIndex+1;
                    middleIndex=(startIndex+endIndex)/2;
                }

                ///This is the case where the key being compared against
                ///in the binary search mechanism is equal to the
                ///key we wish to insert in its appropriate position.
                ///In this case the key we wish to insert comes after the key being
                ///compared against in the binary search mechanism
                ///thus finishing the search for the appropriate position.
                else
                {
                    ///We are now recalculating indexes appropriately.
                    ++middleIndex;

                    break;
                }

                ///We are now reassigning pointers appropriately
                ///to prepare for the next iteration of the binary search mechanism.
                otherKeyPointer=sequenceStart+middleIndex*sequenceElementSize;

                ///This is the case where we cannot move in the subsequence
                ///to search for the correct position. Thus, we have to
                ///directly compare the key we are trying to insert
                ///and the key that is being compared against
                ///in the binary search mechanism
                ///and choose the correct position appropriately.
                ///After this case, we end the binary search mechanism.
                if(startIndex>=endIndex)
                {
                    ///We are now reassigning pointers appropriately
                    ///to prepare for this specific case.
                    otherKeyPointer=sequenceStart+startIndex*sequenceElementSize;

                    ///This is the case where the key we are trying to insert comes
                    ///before the key being compared against in the binary search
                    ///mechanism.
                    if(comparator(mainKeyBuffer, otherKeyPointer)<0)
                    {
                        ///We are now recalculating indexes appropriately.
                        middleIndex=startIndex;
                    }

                    ///This is the case where the key we are trying to insert comes
                    ///after the key being compared against in the binary search
                    ///mechanism.
                    else
                    {
                        ///We are now recalculating indexes appropriately.
                        middleIndex=startIndex+1;
                    }

                    break;
                }
            }

            ///We are now setting up the pointer that
            ///will help with inserting the key to insert
            ///in its appropriate slot.
            otherKeyPointer=sequenceStart+(index-1)*sequenceElementSize;

            ///We are now doing the swaps to get to the appropriate
            ///index, previously found in the binary search mechanism,
            ///to insert the key to insert.
            for(subIndex=index-1; subIndex>=middleIndex; --subIndex)
            {
                ///We are doing the swapping.
                keySwapPointer=otherKeyPointer+sequenceElementSize;
                memcpy(keySwapPointer, otherKeyPointer, sequenceElementSize);
                otherKeyPointer-=sequenceElementSize;
            }

            ///We place the key to be inserted at its appropriate index.
            keyPlacementPointer=otherKeyPointer+sequenceElementSize;
            memcpy(keyPlacementPointer, mainKeyBuffer, sequenceElementSize);
        }

        ///Cleaning up resources since the sorting is done.
        free(mainKeyBuffer);
    }
}

void sortTest(void* sequence, size_t sequenceSize, size_t sequenceElementSize, int(*comparator)(const void*, const void*), void(*sorter)(void*, size_t, size_t, int(*)(const void*, const void*)))
{
    ///This function serves as a unit test to see if the provided sort function works correctly based on the provided arguments.

    printf("Testing provided sort function...\n\n");

    ///These if statements list potential errors that can occur that could stop continuation of the test.
    if(!sequence)
    {
        printf("Error: Cannot continue with the provided sort test due to null sequence.\n\nExiting sort test...\n\n");

        return;
    }

    else if(!sequenceSize)
    {
        printf("Error: Cannot continue with the provided sort test due to zero-element sequence.\n\nExiting sort test...\n\n");

        return;
    }

    else if(sequenceSize==1)
    {
        printf("Note: Cannot continue with the provided sort test due to one-element sequence as sequence is already sorted.\n\nExiting sort test...\n\n");

        return;
    }

    printf("Entering provided sort test...\n\n");

    sorter(sequence, sequenceSize, sequenceElementSize, comparator);

    ///Setting up pointers to test if the provided sort function worked correctly by using the comparator provided.
    unsigned char* firstComparate=sequence;
    unsigned char* secondComparate=firstComparate+sequenceElementSize;

    ///This is used to help with iterating over the sequence.
    size_t index=1;
    for(; index<sequenceSize; ++index)
    {
        if(comparator(firstComparate, secondComparate)>0)
        {
            printf("Provided sort failed!\n\nExiting sort test...\n\n");

            return;
        }

        ///We are moving to the other elements in the sequence for comparison.
        firstComparate+=sequenceElementSize;
        secondComparate+=sequenceElementSize;
    }

    printf("Provided sort succeeded!\n\nExiting sort test...\n\n");
}
