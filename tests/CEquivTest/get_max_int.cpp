
#include <iostream>
using namespace std;

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

int main() {
    int arr[] = {1, 45, 3, 85, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    return 0;
}
