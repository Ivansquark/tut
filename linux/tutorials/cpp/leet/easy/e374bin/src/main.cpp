#include "print.h"

using namespace Print;

/** 
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

int guessNumber(int n){
	
}


int main() {
    int arr[] = {-1, 3, 6, 8, 9};

    print(guessNumber(6));
    return 0;
}




int search(int* arr, int size, int val) {
    int l = 0;
    int r = size;
    int med = 0;
    while (l < r) {
        med = (l + r) / 2;
        if (val < arr[med]) {
            r = r - 1;
        } else if (val > arr[med]) {
            l = l + 1;
        } else {
            return med;
        }
    }
    return -1;
}
