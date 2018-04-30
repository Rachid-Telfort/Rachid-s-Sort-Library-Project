#include"Sort.h"

int main(void)
{
    ///These are sample arrays that will show how to use the sort test.
    ///These sample arrays will also test for the correctness of the sorting algorithms.
    char A[]={'q', 'w', 'e', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f'};
    int B[]={1, 3, 5, 7, 9, 11, 13, 15, 17, 100, 98, 96, 94, 92, 90};
    const char* C[]={"Java", "C++", "Python", "PHP", "Go", "C"};
    char D[]={'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', 'z'};
    int E[]={1, 1, 1, 1, 1, 1, 2, 4, 4, 4, 4, 4, 5, 5, 6, 80, 80, 81};
    const char* F[]={"Kratos", "Aloy", "Atreus", "Geralt of Rivia", "Siri", "Jak and Daxter", "John Snow"};
    char G[]={'1', '2', '@', '#', '$', '4', '5', '6', '7', '*', '8'};
    int H[]={2, 4, 6, 8, 10, 12, -2, -4, -6, -8, -10, 12, 14, 16, 18, 20, -100};
    const char* I[]={"Attack on Titan", "Dragon Ball Z", "Teen Titans", "God of War", "Horizon Zero Dawn", "Shape Dodger", "Space Figher Awesome!"};

    ///These will show some sample sort tests.
    sortTest(A, sizeof(A)/sizeof(char), sizeof(char), characterAscending, insertionSort);
    sortTest(B, sizeof(B)/sizeof(int), sizeof(int), integerAscending, selectionSort);
    sortTest(C, sizeof(C)/sizeof(const char*), sizeof(const char*), stringAscending, bubbleSort);
    sortTest(D, sizeof(D)/sizeof(char), sizeof(char), characterDescending, heapSort);
    sortTest(E, sizeof(E)/sizeof(int), sizeof(int), integerDescending, mergeSort);
    sortTest(F, sizeof(F)/sizeof(const char*), sizeof(const char*), stringDescending, recursiveInsertionSort);
    sortTest(G, sizeof(G)/sizeof(char), sizeof(char), characterAscending, binaryInsertionSort);
    sortTest(H, sizeof(H)/sizeof(int), sizeof(int), integerAscending, quickSort);

    ///This shows that the sortTest() function also works with the built-in C qsort() function.
    sortTest(I, sizeof(I)/sizeof(const char*), sizeof(const char*), stringAscending, qsort);

    return 0;
}
