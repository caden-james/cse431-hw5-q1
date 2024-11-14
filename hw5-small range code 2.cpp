#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>     

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

void mergeSort(std::vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
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
}

int main() {
    int max_n = 350; 
    int repetitions = 10000; 
    std::vector<double> insertionSortTimes, mergeSortTimes;
    for (int n = 300; n <= max_n; n += 10) {
        std::vector<int> data(n);
        for (int &val : data) val = rand();
        double totalInsertionTime = 0.0;
        for (int i = 0; i < repetitions; ++i) {
            std::vector<int> data_copy = data; 
            std::clock_t start_time = std::clock();
            insertionSort(data_copy); 
            std::clock_t tot_time = std::clock() - start_time;
            totalInsertionTime += (double) tot_time / CLOCKS_PER_SEC;
        }
        double insertionSortTime = totalInsertionTime / repetitions;
        double totalMergeTime = 0.0;
        for (int i = 0; i < repetitions; ++i) {
            std::vector<int> data_copy = data; 
            std::clock_t start_time = std::clock();
            mergeSort(data_copy, 0, data_copy.size() - 1); 
            std::clock_t tot_time = std::clock() - start_time;
            totalMergeTime += (double) tot_time / CLOCKS_PER_SEC;
        }
        double mergeSortTime = totalMergeTime / repetitions;
        std::cout << "n = " << n 
                  << ", Avg Insertion Sort Time = " << insertionSortTime << " seconds"
                  << ", Avg Merge Sort Time = " << mergeSortTime << " seconds\n";
    }
}
