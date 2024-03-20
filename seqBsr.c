#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void bubbleSort(int* bucket, int size) {
    int temp;
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (bucket[j] > bucket[j + 1]) {
                temp = bucket[j];
                bucket[j] = bucket[j + 1];
                bucket[j + 1] = temp;
            }
        }
    }
}

int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int findMin(int arr[], int n) {
    int min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int calculateBucketIndex(int value, int min, int max, int bucketCount) {
    double fraction = (double)(value - min) / (max - min + 1);
    return (int)(fraction * (bucketCount - 1));
}

void modifiedBucketSort(int arr[], int n) {
    int max = findMax(arr, n);
    int min = findMin(arr, n);
    int bucketCount = (int)sqrt(n); 
    
    int** buckets = (int**)malloc(bucketCount * sizeof(int*));
    int* size = (int*)calloc(bucketCount, sizeof(int));

    for (int i = 0; i < bucketCount; i++) {
        buckets[i] = (int*)malloc(n * sizeof(int)); 
    }

    for (int i = 0; i < n; i++) {
        int bucketIndex = calculateBucketIndex(arr[i], min, max, bucketCount);
        buckets[bucketIndex][size[bucketIndex]++] = arr[i];
    }

    int index = 0;
    for (int i = 0; i < bucketCount; i++) {
        if (size[i] > 0) {
            bubbleSort(buckets[i], size[i]);
            for (int j = 0; j < size[i]; j++) {
                arr[index++] = buckets[i][j];
            }
        }
        free(buckets[i]);
    }

    free(buckets);
    free(size);
}

int main() {
    clock_t start = clock();

    int n = 1000; 
    int *arr = (int*)malloc(n * sizeof(int));

    srand(time(NULL)); 

    for(int i = 0; i < n; i++) {
        arr[i] = (rand() % 201) - 100;
    }

    modifiedBucketSort(arr, n);

    clock_t end = clock();


    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    free(arr); 

    return 0;
}
