#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

void merge(int arr[], int low, int mid, int high)
{
    int temp[1000];
    int left = low;
    int right = mid + 1;
    int k = 0;
    while (left <= mid && right <= high)
    {
        if (arr[left] <= arr[right])
        {
            temp[k++] = arr[left++];
            // cout<<temp[k];
        }
        else
        {
            temp[k++] = arr[right++];
            // cout<<temp[k];
        }
    }
    while (left <= mid)
    {
        temp[k++] = arr[left++];
        // cout<<temp[k];
    }
    while (right <= high)
    {
        temp[k++] = arr[right++];
        // cout<<temp[k];
    }

    for (int i = low; i <= high; i++)
    {
        arr[i] = temp[i - low];
    }
}

void mergeSort(int arr[], int low, int high)
{
    if (low >= high)
    {
        return;
    }
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

void parallelMergeSort(int arr[], int low, int high)
{
    int mid;
    if (low >= high)
    {
        return;
    }
    mid = (low + high) / 2;
    #pragma omp parallel sections
    {
        #pragma omp section 
        {
            parallelMergeSort(arr, low, mid);
        }
        #pragma omp section 
        {
            parallelMergeSort(arr, mid + 1, high);
        }
    }
    merge(arr, low, mid, high);
}

int main()
{
    int *arr, n;
    cout << "Enter the number of elements \n";
    cin >> n;
    arr = new int[n];
    cout << "Enter the elements \n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    cout << "\n Before Sorting \n";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    auto start = chrono::high_resolution_clock::now();
    mergeSort(arr, 0, n - 1);
    auto stop = chrono::high_resolution_clock::now();
    cout << "\n\n Array after sorting \n";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "  ";
    }
    auto seq_time = chrono::duration_cast<microseconds>(stop - start);
    cout<<"\n Time required for sequential algorithm "<<seq_time.count();


    // Parallel merge sort
    auto start_time = chrono::high_resolution_clock::now();
    // auto s = omp_get_wtime();
    #pragma omp parallel 
    {
        #pragma omp single 
        {
            parallelMergeSort(arr, 0, n-1);
        }
    }
    auto stop_time = chrono::high_resolution_clock::now();
    // auto ss = omp_get_wtime();
    cout << "\n\n Array after sorting \n";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << "  ";
    }
    auto par_time = chrono::duration_cast<microseconds>(stop_time-start_time);
    cout<<" \n Time required to execute parallel algorithm "<<par_time.count();
    return 0;
}