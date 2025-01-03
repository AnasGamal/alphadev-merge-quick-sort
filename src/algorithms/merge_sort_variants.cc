#include "merge_sort_variants.h"
#include "sorting_networks.h"
#include <vector>
#include <algorithm>
#include <cstring>

void merge(int* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<int> L(n1), R(n2);
    
    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

namespace configs {
    struct ClassicConfig {
        static bool shouldUseNetwork(int size) {
            return size <= 1;
        }
        
        static void applySortingNetwork(int* arr, int size) {}
    };

    struct Current3To8Config {
        static bool shouldUseNetwork(int size) {
            return size <= 8 && size != 2;
        }
        
        static void applySortingNetwork(int* arr, int size) {
            switch(size) {
                case 1: return;
                case 3: Sort3AlphaDev(arr); return;
                case 4: Sort4AlphaDev(arr); return;
                case 5: Sort5AlphaDev(arr); return;
                case 6: Sort6AlphaDev(arr); return;
                case 7: Sort7AlphaDev(arr); return;
                case 8: Sort8AlphaDev(arr); return;
            }
        }
    };

    struct Network3Config {
        static bool shouldUseNetwork(int size) {
            return size == 3;
        }
        
        static void applySortingNetwork(int* arr, int size) {
            switch(size) {
                case 1: return;
                case 3: Sort3AlphaDev(arr); return;
            }
        }
    };

    struct Networks3To4Config {
        static bool shouldUseNetwork(int size) {
            return size <= 4 && size != 2;
        }
        
        static void applySortingNetwork(int* arr, int size) {
            switch(size) {
                case 1: return;
                case 3: Sort3AlphaDev(arr); return;
                case 4: Sort4AlphaDev(arr); return;
            }
        }
    };

    struct Networks3To5Config {
        static bool shouldUseNetwork(int size) {
            return size <= 5 && size != 2;
        }
        
        static void applySortingNetwork(int* arr, int size) {
            switch(size) {
                case 1: return;
                case 3: Sort3AlphaDev(arr); return;
                case 4: Sort4AlphaDev(arr); return;
                case 5: Sort5AlphaDev(arr); return;
            }
        }
    };

    struct NetworksEvenConfig {
        static bool shouldUseNetwork(int size) {
            return size == 4 || size == 6 || size == 8;
        }
        
        static void applySortingNetwork(int* arr, int size) {
            switch(size) {
                case 4: Sort4AlphaDev(arr); return;
                case 6: Sort6AlphaDev(arr); return;
                case 8: Sort8AlphaDev(arr); return;
            }
        }
    };

    struct NetworksOddConfig {
        static bool shouldUseNetwork(int size) {
            return size < 8 && size % 2 != 0;
        }
        
        static void applySortingNetwork(int* arr, int size) {
            switch(size) {
                case 3: Sort3AlphaDev(arr); return;
                case 5: Sort5AlphaDev(arr); return;
                case 7: Sort7AlphaDev(arr); return;
            }
        }
    };

    struct NetworksPowerOf2Config {
        static bool shouldUseNetwork(int size) {
            return size == 4 || size == 8;
        }
        
        static void applySortingNetwork(int* arr, int size) {
            switch(size) {
                case 4: Sort4AlphaDev(arr); return;
                case 8: Sort8AlphaDev(arr); return;
            }
        }
    };

    struct VarSort3Config {
        static bool shouldUseNetwork(int size) {
            return size <= 3;
        }
        
        static void applySortingNetwork(int* arr, int size) {
            std::vector<int> newArr(size + 1);
            newArr[0] = size;
            std::copy(arr, arr + size, newArr.begin() + 1);
            VarSort3AlphaDev(newArr.data());
            std::copy(newArr.begin() + 1, newArr.end(), arr);
        }
    };

    struct VarSort4Config {
        static bool shouldUseNetwork(int size) {
            return size <= 4;
        }
        
        static void applySortingNetwork(int* arr, int size) {
            std::vector<int> newArr(size + 1);
            newArr[0] = size;
            std::copy(arr, arr + size, newArr.begin() + 1);
            VarSort4AlphaDev(newArr.data());
            std::copy(newArr.begin() + 1, newArr.end(), arr);
        }
    };

    struct VarSort5Config {
        static bool shouldUseNetwork(int size) {
            return size <= 5;
        }
        
        static void applySortingNetwork(int* arr, int size) {
            std::vector<int> newArr(size + 1);
            newArr[0] = size;
            std::copy(arr, arr + size, newArr.begin() + 1);
            VarSort5AlphaDev(newArr.data());
            std::copy(newArr.begin() + 1, newArr.end(), arr);
        }
    };
}

template<typename Config>
class MergeSortVariant {
private:
    static void mergeSortRecursive(int* arr, int left, int right) {
        int size = right - left + 1;
        
        if (Config::shouldUseNetwork(size)) {
            Config::applySortingNetwork(arr + left, size);
            return;
        }
        
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortRecursive(arr, left, mid);
            mergeSortRecursive(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

public:
    static void sort(int* arr, int size) {
        mergeSortRecursive(arr, 0, size - 1);
    }
};

using MergeSortClassic = MergeSortVariant<configs::ClassicConfig>;
using MergeSort3To8 = MergeSortVariant<configs::Current3To8Config>;
using MergeSort3 = MergeSortVariant<configs::Network3Config>;
using MergeSort3To4 = MergeSortVariant<configs::Networks3To4Config>;
using MergeSort3To5 = MergeSortVariant<configs::Networks3To5Config>;
using MergeSortEven = MergeSortVariant<configs::NetworksEvenConfig>;
using MergeSortOdd = MergeSortVariant<configs::NetworksOddConfig>;
using MergeSortPowerOf2 = MergeSortVariant<configs::NetworksPowerOf2Config>;
using MergeSortVarSort3 = MergeSortVariant<configs::VarSort3Config>;
using MergeSortVarSort4 = MergeSortVariant<configs::VarSort4Config>;
using MergeSortVarSort5 = MergeSortVariant<configs::VarSort5Config>;

void mergeSortClassic(int* arr, int size) {
    MergeSortClassic::sort(arr, size);
}

void mergeSort3To8(int* arr, int size) {
    MergeSort3To8::sort(arr, size);
}

void mergeSort3(int* arr, int size) {
    MergeSort3::sort(arr, size);
}

void mergeSort3To4(int* arr, int size) {
    MergeSort3To4::sort(arr, size);
}

void mergeSort3To5(int* arr, int size) {
    MergeSort3To5::sort(arr, size);
}

void mergeSortEven(int* arr, int size) {
    MergeSortEven::sort(arr, size);
}

void mergeSortOdd(int* arr, int size) {
    MergeSortOdd::sort(arr, size);
}

void mergeSortPowerOf2(int* arr, int size) {
    MergeSortPowerOf2::sort(arr, size);
}

void mergeSortVarSort3(int* arr, int size) {
    MergeSortVarSort3::sort(arr, size);
}

void mergeSortVarSort4(int* arr, int size) {
    MergeSortVarSort4::sort(arr, size);
}

void mergeSortVarSort5(int* arr, int size) {
    MergeSortVarSort5::sort(arr, size);
}