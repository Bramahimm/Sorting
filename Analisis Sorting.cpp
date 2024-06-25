#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

void bubbleSort(vector<int>& angka) {
    int ukuran = angka.size();
    for (int i = 0; i < ukuran-1; ++i) {
        for (int j = 0; j < ukuran-i-1; ++j) {
            if (angka[j] > angka[j+1]) {
                swap(angka[j], angka[j+1]);
            }
        }
    }
}

void insertionSort(vector<int>& angka) {
    int ukuran = angka.size();
    for (int i = 1; i < ukuran; ++i) {
        int key = angka[i];
        int j = i - 1;
        while (j >= 0 && angka[j] > key) {
            angka[j + 1] = angka[j];
            j = j - 1;
        }
        angka[j + 1] = key;
    }
}

void selectionSort(vector<int>& angka) {
    int ukuran = angka.size();
    for (int i = 0; i < ukuran-1; ++i) {
        int minIdx = i;
        for (int j = i+1; j < ukuran; ++j) {
            if (angka[j] < angka[minIdx]) {
                minIdx = j;
            }
        }
        swap(angka[minIdx], angka[i]);
    }
}

void merge(vector<int>& angka, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1), R(n2);
    
    for (int i = 0; i < n1; ++i)
        L[i] = angka[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = angka[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            angka[k] = L[i];
            ++i;
        } else {
            angka[k] = R[j];
            ++j;
        }
        ++k;
    }
    
    while (i < n1) {
        angka[k] = L[i];
        ++i;
        ++k;
    }
    
    while (j < n2) {
        angka[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort2(vector<int>& angka, int left, int right) {
    if (left >= right)
        return;
    
    int mid = left + (right - left) / 2;
    mergeSort2(angka, left, mid);
    mergeSort2(angka, mid + 1, right);
    merge(angka, left, mid, right);
}

void mergeSort(vector<int>& angka) {
    mergeSort2(angka, 0, angka.size() - 1);
}

int partition(vector<int>& angka, int low, int high) {
    int pivot = angka[high];
    int i = (low - 1);
    
    for (int j = low; j < high; ++j) {
        if (angka[j] < pivot) {
            ++i;
            swap(angka[i], angka[j]);
        }
    }
    swap(angka[i + 1], angka[high]);
    return (i + 1);
}

void quickSort2(vector<int>& angka, int low, int high) {
    if (low < high) {
        int pi = partition(angka, low, high);
        quickSort2(angka, low, pi - 1);
        quickSort2(angka, pi + 1, high);
    }
}

void quickSort(vector<int>& angka) {
    quickSort2(angka, 0, angka.size() - 1);
}

void printArray(const vector<int>& angka) {
    for (int i : angka) {
        cout << i << " ";
    }
    cout << endl;
}

vector<int> DataRandom(int ukuran) {
    vector<int> angka(ukuran);
    for (int i = 0; i < ukuran; ++i) {
        angka[i] = rand() % 10000;
    }
    return angka;
}


vector<int> DataUrut(int ukuran) {
    vector<int> angka(ukuran);
    for (int i = 0; i < ukuran; ++i) {
        angka[i] = i;
    }
    return angka;
}


vector<int> ArrayTerbalik(int ukuran) {
    vector<int> angka(ukuran);
    for (int i = 0; i < ukuran; ++i) {
        angka[i] = ukuran - i;
    }
    return angka;
}


void waktu(void (*sortFunction)(vector<int>&), vector<int> angka, const string& sortName, int ukuran) {
    auto start = high_resolution_clock::now();
    sortFunction(angka);    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << sortName << " Sort (N=" << ukuran << "): " << duration.count() << " microseconds" << endl;
}

int main() {
    vector<int> sizes = {10, 100, 500, 1000, 10000};
    
    for (int ukuran : sizes) {
        vector<int> random = DataRandom(ukuran);
        vector<int> urut = DataUrut(ukuran);
        vector<int> terbalik = ArrayTerbalik(ukuran);
        
        cout << "Array Acak:" << endl ;
        waktu(bubbleSort, random, "Bubble", ukuran);
        waktu(insertionSort, random, "Insertion", ukuran);
        waktu(selectionSort, random, "Selection", ukuran);
        waktu(mergeSort, random, "Merge", ukuran);
        waktu(quickSort, random, "Quick", ukuran);
        cout<<"\n";
        
        cout << "Array Urutan:" << endl ;
        waktu(bubbleSort, urut, "Bubble", ukuran);
        waktu(insertionSort, urut, "Insertion", ukuran);
        waktu(selectionSort, urut, "Selection", ukuran);
        waktu(mergeSort, urut, "Merge", ukuran);
        waktu(quickSort, urut, "Quick", ukuran);
        cout<<"\n";
        
        cout << "Array Terbalik:" << endl;
        waktu(bubbleSort, terbalik, "Bubble", ukuran);
        waktu(insertionSort, terbalik, "Insertion", ukuran);
        waktu(selectionSort, terbalik, "Selection", ukuran);
        waktu(mergeSort, terbalik, "Merge", ukuran);
        waktu(quickSort, terbalik, "Quick", ukuran);
    }
    
    return 0;
}
