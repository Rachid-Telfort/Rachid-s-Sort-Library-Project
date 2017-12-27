#include"Sort.h"

const short int characterLessThan(const void* const firstComparatee, const void* const secondComparatee)
{
    if(*(char*)firstComparatee<*(char*)secondComparatee)
    {
        return -1;
    }

    else if(*(char*)firstComparatee>*(char*)secondComparatee)
    {
        return 1;
    }

    return 0;
}

const short int characterGreaterThan(const void* const firstComparatee, const void* const secondComparatee)
{
    if(*(char*)firstComparatee<*(char*)secondComparatee)
    {
        return 1;
    }

    else if(*(char*)firstComparatee>*(char*)secondComparatee)
    {
        return -1;
    }

    return 0;
}

const short int integerLessThan(const void* const firstComparatee, const void* const secondComparatee)
{
    if(*(int*)firstComparatee<*(int*)secondComparatee)
    {
        return -1;
    }

    else if(*(int*)firstComparatee>*(int*)secondComparatee)
    {
        return 1;
    }

    return 0;
}

const short int integerGreaterThan(const void* const firstComparatee, const void* const secondComparatee)
{
    if(*(int*)firstComparatee<*(int*)secondComparatee)
    {
        return 1;
    }

    else if(*(int*)firstComparatee>*(int*)secondComparatee)
    {
        return -1;
    }

    return 0;
}

const short int stringLessThan(const void* const firstComparatee, const void* const secondComparatee)
{
    return strcmp(*(const char** const)firstComparatee, *(const char** const)secondComparatee);
}

const short int stringGreaterThan(const void* const firstComparatee, const void* const secondComparatee)
{
    return -strcmp(*(const char** const)firstComparatee, *(const char** const)secondComparatee);
}

void insertionSort(const void* const sequence, const size_t sequenceSize, const size_t sequenceElementSize, const short int(*comparator)(const void* const, const void* const))
{
    if(sequence!=NULL&&sequenceSize>1)
    {
        ///This points to the first byte of the sequence.
        unsigned char* sequenceStart=(unsigned char*)sequence;

        ///This points to the first byte of the current key where we are trying to insert it in its appropriate index.
        unsigned char* mainKeyPointer=NULL;

        ///This helps with inserting the key to insert in its appropriate slot.
        unsigned char* otherKeyPointer=NULL;

        ///This helps with the key swap mechanism when doing the backwards linear search to place the key to insert in its appropriate index.
        unsigned char* keySwapPointer=NULL;

        ///This helps with placing the key to insert in its appropriate index.
        unsigned char* keyPlacementPointer=NULL;

        ///This holds the key to insert's data so as to not get lost due to the swap mechanism in the backwards linear search to place the key to insert in its appropriate slot.
        unsigned char* mainKeyBuffer=malloc(sequenceElementSize*sizeof(unsigned char));

        ///This is the case where memory is failed to be allocated.
        if(mainKeyBuffer==NULL)
        {
            printf("Error: Memory could not be allocated to continue insertion sort.\n\n");
            printf("Aborting insertion sort...\n\n");

            sequenceStart=NULL;

            return;
        }

        ///This keeps track of the index of the key that we are inserting in its rightful place.
        unsigned long long int index=0;

        ///This keeps track of the other keys' indexes that are being swapped in the backwards linear search mechanism.
        long long int subIndex=0;

        ///We start at the second element due to the backwards linear search for each element of the sequence to place it in its appropriate index.
        ///The first element has no elements before it so the backwards linear search is not possible as well as the fact that the first element is assumed to be sorted by default.
        ///This is due to the fact that the sub array before the key to be placed is already sorted.
        for(index=1; index<sequenceSize; ++index)
        {
            ///We are preparing the key to be inserted as well as the pointer that will point to the end of the sorted sub array before the index of the key to be inserted.
            mainKeyPointer=sequenceStart+index*sequenceElementSize;
            otherKeyPointer=sequenceStart+(index-1)*sequenceElementSize;
            memcpy(mainKeyBuffer, mainKeyPointer, sequenceElementSize);

            ///Setting the sub index to be the index of the element before the index of the key to be inserted for the swap mechanism of the backwards linear search.
            subIndex=index-1;

            ///We are now doing the swaps to find the appropriate index to insert the key to insert.
            while(subIndex>=0&&comparator(mainKeyBuffer, otherKeyPointer)<0)
            {
                ///We are doing the swapping and comparing.
                keySwapPointer=otherKeyPointer+sequenceElementSize;
                memcpy(keySwapPointer, otherKeyPointer, sequenceElementSize);
                otherKeyPointer-=sequenceElementSize;
                --subIndex;
            }

            ///We place the key to be inserted at its appropriate index.
            keyPlacementPointer=otherKeyPointer+sequenceElementSize;
            memcpy(keyPlacementPointer, mainKeyBuffer, sequenceElementSize);
        }

        ///Cleaning up resources since the sorting is done.
        sequenceStart=NULL;
        mainKeyPointer=NULL;
        otherKeyPointer=NULL;
        keySwapPointer=NULL;
        keyPlacementPointer=NULL;

        free(mainKeyBuffer);
        mainKeyBuffer=NULL;
    }
}

void selectionSort(const void* const sequence, const size_t sequenceSize, const size_t sequenceElementSize, const short int(*comparator)(const void* const, const void* const))
{
    if(sequence!=NULL&&sequenceSize>1)
    {
        ///This points to the first byte of the sequence.
        unsigned char* sequenceStart=(unsigned char*)sequence;

        ///This points to the main key that we are selecting against for sorting purposes.
        unsigned char* mainKeyPointer=NULL;

        ///This helps with the key swap mechanism that occurs if or when we find the appropriate key to select against the main key.
        unsigned char* swapKeyPointer=NULL;

        ///This helps with comparing keys when searching for a key to select against the main key.
        unsigned char* otherKeyPointer=NULL;

        ///This holds the current key data for swapping the current key with a key found, if one is found, to be selected against the main key
        ///so as to not lose the main key data.
        unsigned char* mainKeyBuffer=malloc(sequenceElementSize*sizeof(unsigned char));

        ///This is the case where memory is failed to be allocated.
        if(mainKeyBuffer==NULL)
        {
            printf("Error: Memory could not be allocated to continue selection sort.\n\n");
            printf("Aborting selection sort...\n\n");

            sequenceStart=NULL;

            return;
        }

        ///This helps keep track of the index of the main key that is being selected against.
        unsigned long long int index=0;

        ///This helps keep track of the other keys that are being selected against the main key.
        unsigned long long int subIndex=0;

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
        sequenceStart=NULL;
        mainKeyPointer=NULL;
        swapKeyPointer=NULL;
        otherKeyPointer=NULL;

        free(mainKeyBuffer);
        mainKeyBuffer=NULL;
    }
}

void mergeSort(const void* const sequence, const size_t sequenceSize, const size_t sequenceElementSize, const short int(*comparator)(const void* const, const void* const))
{
    if(sequence!=NULL&&sequenceSize>1)
    {
        divide(sequence, sequenceElementSize, 0, sequenceSize, comparator);
    }
}

void divide(const void* const sequence, const size_t sequenceElementSize, const size_t subSequenceStart, const size_t subSequenceEnd, const short int(*comparator)(const void* const, const void* const))
{
    ///We check if the current subsequence is greater than one element.
    ///If it is not, then we do not need to break the subsequence down and sort it
    ///as the sequence is already sorted.
    if(subSequenceStart<subSequenceEnd-1)
    {
        ///Here we breakdown the first half of the subsequence recursively until we reach the base case of the subsequence having one element.
        divide(sequence, sequenceElementSize, subSequenceStart, (subSequenceStart+subSequenceEnd)/2, comparator);

        ///Here we breakdown the second half of the subsequence recursively until we reach the base case of the subsequence having one element.
        divide(sequence, sequenceElementSize, (subSequenceStart+subSequenceEnd)/2, subSequenceEnd, comparator);

        ///Here we combine the two halves of the subsequence by comparing the elements in each half with the result being the sorted subsequence.
        conquerAndCombine(sequence, sequenceElementSize, subSequenceStart, (subSequenceStart+subSequenceEnd)/2, subSequenceEnd, comparator);
    }
}

void conquerAndCombine(const void* const sequence, const size_t sequenceElementSize, const size_t subSequenceStart, const size_t subSequenceMiddle, const size_t subSequenceEnd, const short int(*comparator)(const void* const, const void* const))
{
    ///This points to the first byte of the sequence.
    unsigned char* sequenceStart=(unsigned char*)sequence;

    ///This keeps track of the amount of elements that will be in the helper sequence
    ///that will contain all the elements from the first half of the unsorted subsequence.
    size_t leftSubSequenceSize=subSequenceMiddle-subSequenceStart;

    ///This keeps track of the amount of elements that will be in the helper sequence
    ///that will contain all the elements from the second half of the unsorted subsequence.
    size_t rightSubSequenceSize=subSequenceEnd-subSequenceMiddle;

    ///This holds the elements for the first half of the unsorted subsequence.
    unsigned char* leftSubSequence=malloc(leftSubSequenceSize*sequenceElementSize*sizeof(unsigned char));

    ///This is the case where memory is failed to be allocated for the first helper sequence.
    if(leftSubSequence==NULL)
    {
        printf("Error: Memory could not be allocated in the first helper sequence to continue merge sort.\n\n");
        printf("Aborting merge sort...\n\n");

        sequenceStart=NULL;

        return;
    }

    ///This holds the elements for the second half of the unsorted subsequence.
    unsigned char* rightSubSequence=malloc(rightSubSequenceSize*sequenceElementSize*sizeof(unsigned char));

    ///This is the case where memory is failed to be allocated for the second helper sequence.
    if(rightSubSequence==NULL)
    {
        printf("Error: Memory could not be allocated in the second helper sequence to continue merge sort.\n\n");
        printf("Aborting merge sort...\n\n");

        sequenceStart=NULL;

        free(leftSubSequence);
        leftSubSequence=NULL;

        return;
    }

    ///This helps with copying the data from the subsequence into the helper sequences
    ///as well as sorting the subsequence.
    unsigned char* sequencePointer=NULL;

    ///This helps with copying data from the subsequence into the first helper sequence
    ///as well as to keep track of the current element in the first helper sequence
    ///when sorting the subsequence.
    unsigned char* leftSubSequencePointer=NULL;

    ///This helps with copying data from the subsequence into the second helper sequence
    ///as well as to keep track of the current element in the second helper sequence
    ///when sorting the subsequence.
    unsigned char* rightSubSequencePointer=NULL;

    ///This helps with keeping track of the current element in the first helper sequence.
    unsigned long long int leftIndex=0;

    ///This helps with keeping track of the current element in the second helper sequence.
    unsigned long long int rightIndex=0;

    ///This helps keep track of the current element in the subsequence.
    unsigned long long int subSequenceIndex=0;

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
    sequenceStart=NULL;

    free(leftSubSequence);
    leftSubSequence=NULL;

    free(rightSubSequence);
    rightSubSequence=NULL;

    sequencePointer=NULL;
    leftSubSequencePointer=NULL;
    rightSubSequencePointer=NULL;
}

void binaryInsertionSort(const void* const sequence, const size_t sequenceSize, const size_t sequenceElementSize, const short int(*comparator)(const void* const, const void* const))
{
    if(sequence!=NULL&&sequenceSize>1)
    {
        ///This points to the first byte of the sequence.
        unsigned char* sequenceStart=(unsigned char*)sequence;

        ///This points to the first byte of the current key where
        ///we are trying to insert it in its appropriate index.
        unsigned char* mainKeyPointer=NULL;

        ///This helps with inserting the key to insert
        ///in its appropriate slot.
        unsigned char* otherKeyPointer=NULL;

        ///This helps with the key swap mechanism when doing the backwards linear search
        ///to place the key to insert in its appropriate index.
        unsigned char* keySwapPointer=NULL;

        ///This helps with placing the key to insert
        ///in its appropriate index.
        unsigned char* keyPlacementPointer=NULL;

        ///This holds the key to insert's data so as to not get lost
        ///due to the swap mechanism in the backwards linear search to
        ///place the key to insert in its appropriate slot.
        unsigned char* mainKeyBuffer=malloc(sequenceElementSize*sizeof(unsigned char));

        ///This is the case where memory is failed to be allocated.
        if(mainKeyBuffer==NULL)
        {
            printf("Error: Memory could not be allocated to continue binary insertion sort.\n\n");
            printf("Aborting binary insertion sort...\n\n");

            sequenceStart=NULL;

            return;
        }

        ///This keeps track of the index of the key that
        ///we are inserting in its rightful place.
        unsigned long long int index=0;

        ///This keeps track of the other keys' indexes
        ///that are being swapped in the backwards linear search mechanism.
        long long int subIndex=0;

        ///This keeps track of the first key's index in the
        ///subsequence to be binary searched.
        long long int startIndex=0;

        ///This keeps track of the index of the key
        ///that is being compared against in the binary search mechanism.
        long long int middleIndex=0;

        ///This keeps track of the last key's index in the
        ///subsequence to be binary searched.
        long long int endIndex=0;

        ///We start at the second element due to the backwards linear search
        ///for each element of the sequence to place it in its appropriate index
        ///after the appropriate index is found using binary search.
        ///The first element has no elements before it so the backwards linear search
        ///is not possible as well as the fact that the first element is assumed to be sorted by default.
        ///This is due to the fact that the sub array before the key to be placed is already sorted.
        for(index=1; index<sequenceSize; ++index)
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

            ///Setting the sub index to be the index of the element
            ///before the index of the key
            ///to be inserted for the swap mechanism
            ///of the backwards linear search.
            subIndex=index-1;

            ///We are now doing the swaps to get to the appropriate
            ///index, previously found in the binary search mechanism,
            ///to insert the key to insert.
            while(subIndex>=middleIndex)
            {
                ///We are doing the swapping.
                keySwapPointer=otherKeyPointer+sequenceElementSize;
                memcpy(keySwapPointer, otherKeyPointer, sequenceElementSize);
                otherKeyPointer-=sequenceElementSize;
                --subIndex;
            }

            ///We place the key to be inserted at its appropriate index.
            keyPlacementPointer=otherKeyPointer+sequenceElementSize;
            memcpy(keyPlacementPointer, mainKeyBuffer, sequenceElementSize);
        }

        ///Cleaning up resources since the sorting is done.
        sequenceStart=NULL;
        mainKeyPointer=NULL;
        otherKeyPointer=NULL;
        keySwapPointer=NULL;
        keyPlacementPointer=NULL;

        free(mainKeyBuffer);
        mainKeyBuffer=NULL;
    }
}

void sortTest(const void* const sequence, const size_t sequenceSize, const size_t sequenceElementSize, const short int(*comparator)(const void* const, const void* const), void(*sortFunction)(const void* const, const size_t, const size_t, const short int(*)(const void* const, const void* const)))
{
    ///This function serves as a unit test to see if the provided sort function works correctly based on the provided arguments.

    printf("Testing provided sort function...\n\n");

    ///These if statements list potential errors that can occur that could stop continuation of the test.
    if(sequence==NULL)
    {
        printf("Error: Cannot continue with the provided sort test due to null sequence.\n\nExiting sort test...\n\n");

        return;
    }

    else if(sequenceSize==0)
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

    sortFunction(sequence, sequenceSize, sequenceElementSize, comparator);

    ///Setting up pointers to test if the provided sort function worked correctly by using the comparator provided.
    unsigned char* firstComparatee=(unsigned char*)sequence;
    unsigned char* secondComparatee=firstComparatee+sequenceElementSize;

    ///This is used to help with iterating over the sequence.
    unsigned long long int index=0;
    for(index=1; index<sequenceSize; ++index)
    {
        if(comparator(firstComparatee, secondComparatee)>0)
        {
            printf("Provided sort failed!\n\nExiting sort test...\n\n");

            ///Cleaning up resources after failure.
            firstComparatee=NULL;
            secondComparatee=NULL;

            return;
        }

        ///We are moving to the other elements in the sequence for comparison.
        firstComparatee+=sequenceElementSize;
        secondComparatee+=sequenceElementSize;
    }

    printf("Provided sort succeeded!\n\nExiting sort test...\n\n");

    ///Cleaning up resources after success.
    firstComparatee=NULL;
    secondComparatee=NULL;
}
