#include <iostream>
#include <vector>
#include <algorithm> // for std::random_shuffle
#include <ctime>     // for std::clock

// Insertion Sort implementation
void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Merge Sort helper function to merge two sorted halves
void merge(std::vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// Merge Sort implementation
void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {
    int max_n = 330; // define maximum n value
    int repetitions = 10000; // number of repetitions for timing
    std::vector<double> insertionSortTimes, mergeSortTimes;

    for (int n = 320; n <= max_n; n += 1) {
        std::vector<int> data(n);
        // Fill 'data' with random numbers
        for (int &val : data) val = rand();

        // Time Insertion Sort
        double totalInsertionTime = 0.0;
        for (int i = 0; i < repetitions; ++i) {
            std::vector<int> data_copy = data; // make a copy of data for fair timing
            std::clock_t start_time = std::clock();
            insertionSort(data_copy); // call insertion sort
            std::clock_t tot_time = std::clock() - start_time;
            totalInsertionTime += (double) tot_time / CLOCKS_PER_SEC;
        }
        insertionSortTimes.push_back(totalInsertionTime / repetitions);

        // Time Merge Sort
        double totalMergeTime = 0.0;
        for (int i = 0; i < repetitions; ++i) {
            std::vector<int> data_copy = data; // make a copy of data for fair timing
            std::clock_t start_time = std::clock();
            mergeSort(data_copy, 0, data_copy.size() - 1); // call merge sort
            std::clock_t tot_time = std::clock() - start_time;
            totalMergeTime += (double) tot_time / CLOCKS_PER_SEC;
        }
        mergeSortTimes.push_back(totalMergeTime / repetitions);

        // Output results for this value of n
        std::cout << "n = " << n 
                  << ", Avg Insertion Sort Time = " << insertionSortTimes.back() << " seconds"
                  << ", Avg Merge Sort Time = " << mergeSortTimes.back() << " seconds\n";
    }

    return 0;
}
