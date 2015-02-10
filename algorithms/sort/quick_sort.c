/* Quick sort
 *
 * Implementation of quick sort
 * 
 * Analysis of QuickSort:
 * Time taken by QuickSort in general can be written as following.
 * T(n) = T(k) + T(n - k - 1) + \theta(n)
 * The first two terms are for two recursive calls, the last term is for the 
 * partition process. k is the number of elements which are small than pivot.
 *
 * The time taken by QuickSort depends upon the input array and partition
 * strategy. Following are three cases.
 *
 * Worst Case: The worst case occurs when the partition process always picks
 * greatest or smallest element as pivot.
 * T(n) = T(0) + T(n-1) + \theta(n)
 * which is equivalent to
 * T(n) = T(n-1) + \theta(n)
 * The solution of above recurrence is \theta(n ** 2)
 *
 * Best Case: The best case occurs when the partition process always picks the
 * middle element as pivot. Following is recurrence for best case.
 * T(n) = 2T(n/2) + \theta(n)
 * The solution of above recurrence is \theta(nlgn).
 *
 */

#include <stdio.h>

#define XOR_SWAP(a, b) do {a ^= b; b ^= a; a ^= b;} while (0)

/* This function takes last element as pivot, places the pivot element at it 
 * correct position in sorted array, and place all smaller (smaller than pivot)
 * to left of pivot and all greater elements to right of pivot.
 */
int partition(int arr[], int l, int h)
{
    int x = arr[h];           // pivot
    int i = (l - 1);          // Index of smaller element

    for (int j = l; j < h; j++) {
         // If current element is smaller than or equal to pivot
        if (arr[j] <= x) {
            i++;              // increment index of smaller element
            XOR_SWAP(arr[i], arr[j]);  // Swap current element with index
        }
    }

    XOR_SWAP(arr[i + 1], arr[h]);
    return  (i + 1);
}

void quickSort(int arr[], int l, int h)
{
    if (l < h) {
        int p = partition(arr, l, h);  // Partitioning index
        quickSort(arr, l, p - 1);
        quickSort(arr, p + 1, h);
    }
}

void printArray(int arr[], int size)
{
    for (int i=0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

void test()
{
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: \n");
    printArray(arr, n);
    printf("\n");

    quickSort(arr, 0, n - 1);

    printf("Sorted array: \n");
    printArray(arr, n);
}

int main()
{
    test();

    getchar();
    return 0;
}

