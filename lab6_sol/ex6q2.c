#include "ex6q2.h"

// Please don't change anything in this main function!
int main(void) {
    if (!test_bubble(bubble_sort))
        fprintf(stderr, "Bubble sorting failed\n");
    if (!test_gnome(gnome_sort))
        fprintf(stderr, "Gnome sorting failed\n");
    if (!test_insertion(insertion_sort))
        fprintf(stderr, "Insertion sorting failed\n");
    if (!test_custom(custom_sort)) {
        fprintf(stderr, "Custom sorting failed\n");
	}
	return 0;
}

void bubble_sort(int n, int arr[n]) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


// Not very well known, but very easy!
// Check out the description on here https://en.wikipedia.org/wiki/Gnome_sort
void gnome_sort(int n, int arr[n]) {
    int index = 0;
    while (index < n) {
        if (index == 0) {
            index++;
        }
        if (arr[index] >= arr[index - 1]) {
            index++;
        } else {
            int temp = arr[index];
            arr[index] = arr[index - 1];
            arr[index - 1] = temp;
            index--;
        }
    }
}

void insertion_sort(int n, int arr[n]) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}


// The sort you found! (See lab description for details)
void custom_sort(int n, int arr[n]) {
    int gap, i, j, temp;
    for (gap = n / 2; gap > 0; gap /= 2) {
        for (i = gap; i < n; i++) {
            temp = arr[i];
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}
