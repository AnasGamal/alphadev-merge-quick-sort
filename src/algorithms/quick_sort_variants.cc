#include "quick_sort_variants.h"
#include "sorting_networks.h"
#include <vector>
#include <algorithm>
#include <random>

namespace pivot_strategies {
    int getLast(int* arr, int low, int high) {
        return high;
    }
    
    int getRandom(int* arr, int low, int high) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(low, high);
        return dis(gen);
    }
    
    int getMedianOfThree(int* arr, int low, int high) {
        int mid = low + (high - low) / 2;
        if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
        if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);
        if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
        return mid;
    }
}

namespace partition_schemes {
    int hoarePartition(int* arr, int low, int high, int pivotIndex) {
        int pivot = arr[pivotIndex];
        int i = low - 1;
        int j = high + 1;
        
        while (true) {
            do {
                i++;
            } while (arr[i] < pivot);
            
            do {
                j--;
            } while (arr[j] > pivot);
            
            if (i >= j) return j;
            std::swap(arr[i], arr[j]);
        }
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
            if (size == 3) Sort3AlphaDev(arr);
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
class QuickSortVariant {
private:
    static void quickSortRecursive(int* arr, int low, int high) {
        int size = high - low + 1;
        
        if (Config::shouldUseNetwork(size)) {
            Config::applySortingNetwork(arr + low, size);
            return;
        }
        
        if (low < high) {
            int pivotIndex = pivot_strategies::getMedianOfThree(arr, low, high);
            int pi = partition_schemes::hoarePartition(arr, low, high, pivotIndex);
            
            quickSortRecursive(arr, low, pi);
            quickSortRecursive(arr, pi + 1, high);
        }
    }

public:
    static void sort(int* arr, int size) {
        quickSortRecursive(arr, 0, size - 1);
    }
};

using QuickSortClassic = QuickSortVariant<configs::ClassicConfig>;
using QuickSort3To8 = QuickSortVariant<configs::Current3To8Config>;
using QuickSort3 = QuickSortVariant<configs::Network3Config>;
using QuickSort3To4 = QuickSortVariant<configs::Networks3To4Config>;
using QuickSort3To5 = QuickSortVariant<configs::Networks3To5Config>;
using QuickSortEven = QuickSortVariant<configs::NetworksEvenConfig>;
using QuickSortOdd = QuickSortVariant<configs::NetworksOddConfig>;
using QuickSortPowerOf2 = QuickSortVariant<configs::NetworksPowerOf2Config>;
using QuickSortVarSort3 = QuickSortVariant<configs::VarSort3Config>;
using QuickSortVarSort4 = QuickSortVariant<configs::VarSort4Config>;
using QuickSortVarSort5 = QuickSortVariant<configs::VarSort5Config>;

void quickSortClassic(int* arr, int size) {
    QuickSortClassic::sort(arr, size);
}

void quickSort3To8(int* arr, int size) {
    QuickSort3To8::sort(arr, size);
}

void quickSort3(int* arr, int size) {
    QuickSort3::sort(arr, size);
}

void quickSort3To4(int* arr, int size) {
    QuickSort3To4::sort(arr, size);
}

void quickSort3To5(int* arr, int size) {
    QuickSort3To5::sort(arr, size);
}

void quickSortEven(int* arr, int size) {
    QuickSortEven::sort(arr, size);
}

void quickSortOdd(int* arr, int size) {
    QuickSortOdd::sort(arr, size);
}

void quickSortPowerOf2(int* arr, int size) {
    QuickSortPowerOf2::sort(arr, size);
}

void quickSortVarSort3(int* arr, int size) {
    QuickSortVarSort3::sort(arr, size);
}

void quickSortVarSort4(int* arr, int size) {
    QuickSortVarSort4::sort(arr, size);
}

void quickSortVarSort5(int* arr, int size) {
    QuickSortVarSort5::sort(arr, size);
}