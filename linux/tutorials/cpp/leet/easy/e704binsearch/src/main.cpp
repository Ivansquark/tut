#include "print.h"

using namespace Print;
int search(int* arr, int size, int val) {
    int l = 0;
    int r = size - 1;
    int med = 0;
    while (l <= r) {
        med = (l + r) / 2;
        //med = l + (r - l) / 2;
        if (val < arr[med]) {
            r = med - 1;
        } else if (val > arr[med]) {
            l = med + 1;
        } else {
            return med;
        }
    }
    return -1;
}

int rec_search(int* arr, int low, int high, int x) {
    if (high >= low) {
        int mid = low + (high - low) / 2;

        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;

        // If element is smaller than mid, then
        // it can only be present in left subarray
        if (arr[mid] > x)
            return rec_search(arr, low, mid - 1, x);

        // Else the element can only be present
        // in right subarray
        return rec_search(arr, mid + 1, high, x);
    }

    // We reach here when element is not
    // present in array
    return -1;
}

int main() {
    int arr[] = {0, 3, 6, 8, 9};

    print(search(arr, 0, 0));
    print(rec_search(arr, 0, sizeof(arr) / sizeof(int), 8));
    print(search(arr, sizeof(arr) / sizeof(int), -1));
    print(search(arr, sizeof(arr) / sizeof(int), 3));
    print(search(arr, sizeof(arr) / sizeof(int), 6));
    print(search(arr, sizeof(arr) / sizeof(int), 8));
    print(search(arr, sizeof(arr) / sizeof(int), 9));
    print(search(arr, sizeof(arr) / sizeof(int), 10));
    return 0;
}
