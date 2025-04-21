#include "RadixSort.h"
#include <iostream>

/// <summary>
/// Count Sort Radix
/// </summary>
/// <param name="arr">array argument with the values</param>
/// <param name="n">number of elements</param>
/// <param name="pos">digit position</param>
void RadixSort::Count_Sort(int arr[], int n, int pos)
{

    //Initializing the Result Storage
    int count[10] = { 0 };

    // we count the frequency of each distinct digit at
    // given place for every element in the original array
    for (int i = 0; i < n; i++) {
        count[(arr[i] / pos) % 10]++;
    }

    // we perform prefix sum and update the count array
    for (int i = 1; i < 10; i++) {
        count[i] = count[i] + count[i - 1];
    }

    // we store our answer in the ans array
    int ans[372974] = { 0 };
    for (int i = n - 1; i >= 0; i--) {
        ans[--count[(arr[i] / pos) % 10]] = arr[i];
    }

    // here we copy the contents of ans array to our
    // original array
    for (int i = 0; i < n; i++) {
        arr[i] = ans[i];
    }
}

// function to implement radix sort
void RadixSort::Radix_Sort(int arr[], int n)
{
    // max_element() is a c++ stl function to find the
    // maximum element from an array
    int k = 372974;

    for (int pos = 1; (k / pos) > 0; pos *= 10) {
        Count_Sort(arr, n, pos);
    }

    cout << "Done" << endl;
}