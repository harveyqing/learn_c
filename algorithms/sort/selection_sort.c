/* Selection sort
 *
 * Implementation of selection sort.
 *
 * Time Complexity: O(n*n)
 * Auxiliary Space: O(n)
 */

#include <stdio.h>

#define XOR_SWAP(a, b) do {a ^= b; b ^= a; a ^= b;} while (0)

void printArray(int arr[], int size)
{
    for (int i=0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++) {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element with the first element
        XOR_SWAP(arr[min_idx], arr[i]);
    }
}

void test()
{
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original order of the array is: ");
    printArray(arr, n);

    selectionSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);
}

int main()
{
    test();

    getchar();
    return 0;
}
