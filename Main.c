#include"Sort.h"

int main(int argc, char* argv[])
{
    char a[]="qwertyuioplkjhgfdsazcxvnbm";
    int b[]={0, 1, 2, 6, 7, 3, 0, 0, 78, 99, 100};
    char* c[]={"Rachid Telfort", "Jammil Telfort", "Isaac Monterose", "Marie Telfort", "Samus Aran", "Geralt of Rivia"};

    printf("Entering insertion sort tests...\n\n");
    sortTest(a, sizeof(a)/sizeof(a[0])-1, sizeof(a[0]), characterLessThan, insertionSort);
    sortTest(a, sizeof(a)/sizeof(a[0])-1, sizeof(a[0]), characterGreaterThan, insertionSort);
    sortTest(b, sizeof(b)/sizeof(b[0]), sizeof(b[0]), integerLessThan, insertionSort);
    sortTest(b, sizeof(b)/sizeof(b[0]), sizeof(b[0]), integerGreaterThan, insertionSort);
    sortTest(c, sizeof(c)/sizeof(c[0]), sizeof(c[0]), stringLessThan, insertionSort);
    sortTest(c, sizeof(c)/sizeof(c[0]), sizeof(c[0]), stringGreaterThan, insertionSort);
    printf("Exiting insertion sort tests...\n\n\n\n");

    char d[]="AsdfghjklOP!23";
    int e[]={0, 5, 4, 2, 1, 4, 7, 567};
    char* f[]={"C++", "Java", "Python", "Swift", "Go", "C"};

    printf("Entering selection sort tests...\n\n");
    sortTest(d, sizeof(d)/sizeof(d[0])-1, sizeof(d[0]), characterLessThan, selectionSort);
    sortTest(d, sizeof(d)/sizeof(d[0])-1, sizeof(d[0]), characterGreaterThan, selectionSort);
    sortTest(e, sizeof(e)/sizeof(e[0]), sizeof(e[0]), integerLessThan, selectionSort);
    sortTest(e, sizeof(e)/sizeof(e[0]), sizeof(e[0]), integerGreaterThan, selectionSort);
    sortTest(f, sizeof(f)/sizeof(f[0]), sizeof(f[0]), stringLessThan, selectionSort);
    sortTest(f, sizeof(f)/sizeof(f[0]), sizeof(f[0]), stringGreaterThan, selectionSort);
    printf("Exiting selection sort tests...\n\n\n\n");

    char g[]="ABCDEFGHIJKLPOwesrtyuodfgdgdggfgd";
    int h[]={0, 9, 8 ,67, 68, 66, 34, 32, 1, 1, 0, 0, 0, -9, -80, -90};
    char* i[]={"Television", "Rocky Balboa", "QWERTY", "Megaman ZX", "Johnny Bravo", "Computer Science"};

    printf("Entering merge sort tests...\n\n");
    sortTest(g, sizeof(g)/sizeof(g[0])-1, sizeof(g[0]), characterLessThan, mergeSort);
    sortTest(g, sizeof(g)/sizeof(g[0])-1, sizeof(g[0]), characterGreaterThan, mergeSort);
    sortTest(h, sizeof(h)/sizeof(h[0]), sizeof(h[0]), integerLessThan, mergeSort);
    sortTest(h, sizeof(h)/sizeof(h[0]), sizeof(h[0]), integerGreaterThan, mergeSort);
    sortTest(i, sizeof(i)/sizeof(i[0]), sizeof(i[0]), stringLessThan, mergeSort);
    sortTest(i, sizeof(i)/sizeof(i[0]), sizeof(i[0]), stringGreaterThan, mergeSort);
    printf("Exiting merge sort tests...\n\n\n\n");

    char j[]="wdawfgxfdgfchfgchgcjvhjfgsedawetgrdgyrdgtrdghbbbbbadawdawrewreretdyruyjulkoxdfgsedfsdfvfg4545646475682352352567468572352352z";
    int k[]={0, 2, 1, 567, -900, 90, 56, 23, -23, 47, 46, 46, 47, 50, 69, 68, 67, 66, 65, 44, 999, 888, 000, 6666};
    char* l[]={"I love my life!", "Jammil", "Yvenie", "Ben 10", "Johnny Test"};

    printf("Entering binary insertion sort tests...\n\n");
    sortTest(j, sizeof(j)/sizeof(j[0])-1, sizeof(j[0]), characterLessThan, binaryInsertionSort);
    sortTest(j, sizeof(j)/sizeof(j[0])-1, sizeof(j[0]), characterGreaterThan, binaryInsertionSort);
    sortTest(k, sizeof(k)/sizeof(k[0]), sizeof(k[0]), integerLessThan, binaryInsertionSort);
    sortTest(k, sizeof(k)/sizeof(k[0]), sizeof(k[0]), integerGreaterThan, binaryInsertionSort);
    sortTest(l, sizeof(l)/sizeof(l[0]), sizeof(l[0]), stringLessThan, binaryInsertionSort);
    sortTest(l, sizeof(l)/sizeof(l[0]), sizeof(l[0]), stringGreaterThan, binaryInsertionSort);
    printf("Exiting binary insertion sort tests...\n");

    return 0;
}
