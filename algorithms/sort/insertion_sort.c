/* Insertion sort
 *
 * Implementation of insertion sort.
 *
 * Time Complexity: O(n*n)
 * Auxiliary Space: O(1)
 * Boundary Cases: Insertion sort takes maxinum time to sort if elements are
 *                 sorted in reverse order. And it takes minimum time
 *                 (Order of n) when elements are already sorted.
 * Algorithm Paradigm: Incremental Approach
 * Sorting In Place: Yes
 * Stable: Yes
 */

#include <stdio.h>

void printArray(int arr[], int size)
{
    for (int i=0; i < size; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

void insertionSort(int arr[], int n)
{
    int key;

    for (int i = 1; i < n; i++) {
        key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
         * greater than key, to one position ahead
         * of there current position.
         */
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }

        arr[j+1] = key;
    }
}

void test()
{
    int arr[] = {12, 11, 13, 5, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    insertionSort(arr, n);

    printf("Sorted array: \n");
    printArray(arr, n);
}

int main()
{
    printf("Insertion sort test...");
    test();

    getchar();
    return 0;
}

