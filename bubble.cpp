#include<iostream>
#include<omp.h>
#include<chrono>
#include<bits/stdc++.h>

using namespace std::chrono;
using namespace std;

void sequential_bubble_sort(int *arr, int n) {
    for (int i=0; i<n; i++) {
        int swapped = 0;
        for(int j=0; j<n-1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = 1;
            }
        }
        if(!swapped) {
            break;
        }
    }
}

void parallel_bubble_sort(int *arr, int n) {
    for(int i=0; i<n; i++) {
        int swapped = 0;
        int first = i % 2;
        #pragma omp parallel for shared(first, arr)
        for(int j=first; j<n-1; j++) {
            if(arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
                swapped = 1;
            }
        }

        if(!swapped) {
            break;
        }
    }
}

int main() {
    int *arr, n;
    cout<<"Enter the number of elements ";
    cin>>n;
    arr = new int[n];
    for(int i=0; i<n; i++) {
        cin>>arr[i];
    }

    // sequential bubble sort
    auto start = chrono::high_resolution_clock::now();
    sequential_bubble_sort(arr, n);
    auto stop = chrono::high_resolution_clock::now();
    auto seq_time = duration_cast<microseconds>(stop - start);
    cout<<"Sorted array is \n";
    for(int i=0; i<n; i++) {
        cout<<arr[i]<<" ";
    }
    cout<<endl;
    cout<<"Time required to execute sequential algorithm is "<<seq_time.count()<<"microseconds"<<endl;

    // Parallel Bubble sort
    auto start_time = chrono::high_resolution_clock::now();
    parallel_bubble_sort(arr, n);
    auto stop_time = chrono::high_resolution_clock::now();
    auto par_time = duration_cast<microseconds>(stop_time - start_time);
    cout<<"Time required to execute parallel algorith is "<<par_time.count()<<"microseconds"<<endl;
    return 0;
}