/* Bubble sort
 *
 * Implementation of bubble sort.
 *
 * Time Complexity: O(n*n)
 * Auxiliary Space: O(1)
 * Boundary Cases: Bubble sort takes minimum time (Order of n) when elements
 *                 are already sorted.
 * Sorting in Place: Yes
 * Stable: Yes
 */

#include <stdio.h>

#define XOR_SWAP(a, b) do {a ^= b; b ^= a; a ^= b;} while (0)

void printArray(int arr[], int size)
{
    for (int i=0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

void bubbleSort(int arr[], int n)
{
    for (int i=0; i < n; i++)
        for (int j=0; j < n - 1 - i; j++) // last i elements are already in place
            if (arr[j] > arr[j+1])
                XOR_SWAP(arr[j], arr[j+1]);
}

// an optimized version of bubble sort
void optBubbleSort(int arr[], int n)
{
    int swapped;

    for (int i = 0; i < n; i++) {
        swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j+1]) {
                XOR_SWAP(arr[j], arr[j+1]);
                swapped = 1;
            }
        }

        // if no two elements were swapped by inner loop, then break
        if (!swapped)
            break;
    }
}

void test1()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    bubbleSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);
}

void test2()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    optBubbleSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);
}


int main()
{
    printf("Regular bubble sort test...\n");
    test1();

    printf("Optimized bubble sort test...\n");
    test2();

    getchar();
    return 0;
}

