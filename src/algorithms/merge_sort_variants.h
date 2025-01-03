#ifndef MERGE_SORT_VARIANTS_H_
#define MERGE_SORT_VARIANTS_H_

void mergeSortClassic(int* arr, int size);

void mergeSort3To8(int* arr, int size);
void mergeSort3(int* arr, int size);
void mergeSort3To4(int* arr, int size);
void mergeSort3To5(int* arr, int size);
void mergeSortEven(int* arr, int size);
void mergeSortOdd(int* arr, int size);
void mergeSortPowerOf2(int* arr, int size);

void mergeSortVarSort3(int* arr, int size);
void mergeSortVarSort4(int* arr, int size);
void mergeSortVarSort5(int* arr, int size);

void merge(int* arr, int left, int mid, int right);

#endif