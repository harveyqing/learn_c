/* Merge sort
 *
 * Implementation of merge sort.
 *
 * Algorithm details.
 * MergeSort(arr[], l, r)
 * If r > l
 *   1. Find the middle point to divide the array into two havels:
 *      middle m = (l + r) / 2
 *   2. Call MergeSort(arr, l, m)
 *   3. Call MergeSort(arr, m+1, r)
 *   4. Merge the two havels sorted in step 2 and 3:
 *      call merge(arr, l, m, r)
 *
 * Time Complexity: O(nlgn)
 * Auxiliary Space: O(n)
 * Algorithmic Paradigm: Divide and Conquer
 * Sorting in Place: No in a typical implementation
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

void merge(int arr[], int l, int m, int r)
{
    int i, j, k = l;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[j + m + 1];

    i = 0;
    j = 0;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];

        if (R[j] < L[i])
            arr[k++] = R[j++];
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r)
{
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

void test()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    mergeSort(arr, 0, n - 1);

    printf("Sorted array: \n");
    printArray(arr, n);
}

int main()
{
    printf("Merge sort test...\n");
    test();

    getchar();
    return 0;
}

