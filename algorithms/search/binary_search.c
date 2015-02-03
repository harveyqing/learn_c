/* Binary search
 *
 * Implementation of binary search on a `sorted` arry.
 *
 * Binary Search Overview:
 * -----------------------
 * Recursively partitions the array until the key is found.
 *
 * Time Complexity: O(lg n)
 *
 * Psuedo Code: http://en.wikipedia.org/wiki/Binary_search
 *
 * Steps:
 * 1. Compare x with the middle element.
 * 2. If x matches with middle element, we return the mid index.
 * 3. Else if x is greater than the mid element, than x can only lie in right
 *    half subarray after the mid element. So we recur for right half.
 * 4. Else (x is smaller) recur for the left half.
 */

#include <stdio.h>
#include <stdlib.h>

int recurBinarySearch(int array[], int l, int r, int x)
{
    if (r < l) return -1;  // not found. base case

    int mid = l + (r - 1) / 2;
    if (array[mid] == x) return mid;
    if (array[mid] > x) return recurBinarySearch(array, l, mid - 1, x);
    return recurBinarySearch(array, mid + 1, r, x);
}

int binarySearch(int array[], int l, int r, int x)
{
    while (l <= r) {
        int mid = l + (r - 1) / 2;
        if (array[mid] == x) return mid;
        if (array[mid] > x) r = mid - 1;
        else l = mid + 1;
    }

    return -1;
}

void test1()
{
    int array[] = {2, 3, 4, 10, 40};
    int n = sizeof(array) / sizeof(array[0]);
    int x = 10;
    int result = recurBinarySearch(array, 0, n - 1, x);
    (result == -1)? printf("Element is not present in array.\n")
                  : printf("Element is present at index %d.\n", result);
}

void test2()
{
    int array[] = {2, 3, 4, 10, 40};
    int n = sizeof(array) / sizeof(array[0]);
    int x = 10;
    int result = binarySearch(array, 0, n - 1, x);
    (result == -1)? printf("Element is not present in array.\n")
                  : printf("Element is present at index %d.\n", result);
}

int main()
{
    printf("Test recursive version of binary search...\n");
    test1();

    printf("Test non-recursive version of binary search...\n");
    test2();

    getchar();
    return 0;
}
