#include <iostream>
#include <chrono>
#include <bits/stdc++.h>



void quickSortTest(int n);

using namespace std;
using namespace std::chrono;


/**
 * Method for switching two integers.
 *
 * @param firstNumber is to be switched with its other argument.
 * @param secondNumber is to be switched with its other argument.
 */
void switchPlace(int *firstNumber, int *secondNumber) {
    int temporaryHolder = *secondNumber;
    *secondNumber = *firstNumber;
    *firstNumber = temporaryHolder;
}


/**
 * Median sorts takes the number in the first index, the number in the last index
 * and the number in the middle of the table and finds the median. The table is the sorted afterwards.
 *
 * @param table is the collection of number that we extract the numbers from.
 * @param leftEnd is the number from the first index in the table.
 * @param rightEnd is the number from the last index in the table.
 * @return the number from the middle of th table.
 */
int medianSort(int *table, int leftEnd, int rightEnd) {

    int middlePos = (leftEnd + rightEnd) / 2;

    if (table[leftEnd] > table[middlePos]) {
        switchPlace(&table[leftEnd], &table[middlePos]);
    }

    if (table[middlePos] > table[rightEnd]) {

        switchPlace(&table[middlePos], &table[rightEnd]);

        if (table[leftEnd] > table[middlePos]) {
            switchPlace(&table[leftEnd], &table[middlePos]);
        }

    }

    return middlePos;
}

/**
 * Divided arrays into appropriate sub-arrays.
 *
 * @param table the table to be further divided
 * @param leftEnd of the table.
 * @param rightEnd of the table
 * @return returns an integer, which represents the index in where the array should be divided.
 */
int split(int *table, int leftEnd, int rightEnd) {
    int iv;
    int ih;
    int divideNumber = medianSort(table, leftEnd, rightEnd);
    int dv = table[divideNumber];
    switchPlace(&table[divideNumber], &table[rightEnd - 1]);

    for (iv = leftEnd, ih = rightEnd - 1;;) {
        while (table[++iv] < dv);
        while (table[--ih] > dv);
        if (iv >= ih) break;
        switchPlace(&table[iv], &table[ih]);
    }

    switchPlace(&table[iv], &table[rightEnd-1]);

    return iv;
}

/**
 * Sorting algorithm for lots of data.
 * @param table represents the table in  which we are going to sort
 * @param leftEnd of the table.
 * @param rightEnd right en
 */
void quickSort(int *table, int leftEnd, int rightEnd) {
    if (rightEnd - leftEnd > 2) {
        int dividingPosition = split(table, leftEnd, rightEnd);
        quickSort(table, leftEnd, dividingPosition - 1);
        quickSort(table, dividingPosition + 1, rightEnd);
    } else medianSort(table, leftEnd, rightEnd);
}


/**
 * A s
 * @param
 * @return
 */
int * createArray(int n) {

    srand((int)time(0));

    int *table = new int [n];
    for (int i = 0; i < n; ++i) {
        table[i] = rand() % 30;
    }

    return table;
}

int * createArrayWithHugeSpread(int n) {

    srand((int)time(0));

    int *table = new int [n];
    for (int i = 0; i < n; ++i) {
        table[i] = rand() % 500;
    }

    return table;
}


int * createArrayOfDuplicates(int n) {

    srand((int)time(0));

    int *table = new int [n];
    for (int i = 0; i < n; ++i) {
        if (i % 2 == 0) {
            table[i] = rand() % 30;
        } else {
            table[i] = 42;
        }
    }

    return table;
}


/**
 * Checks if the given table is sorted such as 1..2..3..4
 *
 * @param table the table to be checked.
 * @param tableLength the amount of elements in the table.
 * @return true or false statement.
 */
bool checkSorted(int *table, int tableLength) {

    for (int i = 1; i < tableLength - 1; i++) {
        if (table[i] < table[i-1]) {
            return false;
        }
    }

    return true;

}


/**
 * Calculates a sum of a given table.
 *
 * @param table in the table to be checked.
 * @param tableLength the amount of elements in the table.
 * @return the integer which is the sum.
 */
int sumCalculate(int *table, int tableLength) {

    int sum = 0;

    for (int i = 0; i < tableLength; i++) {
        sum += table[i];
    }


    return sum;
}


/**
 * A count sort method which sorts numbers in chronological order.
 *
 * @param tableLength the amount of elements in the array.
 * @param array in the array to be checked.
 * @param max_value the maximum value that exists in the given array.
 */
void countSort(int tableLength, int *array, int max_value, int leftEnd, int rightEnd) {
    int count[max_value + 1];

    for (int i = 0; i <= max_value; ++i) {
        count[i] = 0;
    }
    for (int i = leftEnd; i <= rightEnd; ++i) {
        ++count[array[i]];
    }

    int index = leftEnd;
    for (int i = 0; i <= max_value; ++i) {
        while(count[i] > 0) {
            array[index] = i;
            index++;
            count[i]--;
        }
    }


}

void quickSortWithOptimization(int *array, int leftEnd, int rightEnd) {

    int arraySize = rightEnd - leftEnd;

    if (array[rightEnd + 1] - array[leftEnd - 1] < rightEnd - leftEnd) {
        countSort(arraySize, array, array[rightEnd + 1], leftEnd, rightEnd);
    }

    else if (rightEnd - leftEnd > 2) {

        int dividingPosition = split(array, leftEnd, rightEnd);
        quickSortWithOptimization(array, leftEnd, dividingPosition - 1);
        quickSortWithOptimization(array, dividingPosition + 1, rightEnd);

    } else {
        medianSort(array, leftEnd, rightEnd);
    }

}


int findMaxIndexInArray(int arraySize, int *array) {
    int max = 0;
    int index = 0;

    for (int i = 0; i < arraySize; ++i) {
        if (array[i] > max) {
            max = array[i];
            index = i;
        }
        
    }
    return index;
}

int findMinIndexInArray(int arraySize, int *array) {

    int min = INT_MAX;
    int index = 0;

    for (int i = 0; i < arraySize; ++i) {
        if (array[i] < min) {
            min = array[i];
            index = i;
        }

    }
    return index;
}

void confirmArray(int n, int *array, int sum) {

    if (checkSorted(array, n)) {
        cout << "INFO: " << "The table is sorted." << endl;
    } else {
        cout << "INFO: " << "The table is not sorted." << endl;
    }

    if (sum == sumCalculate(array, n)) {
        cout << "INFO: " << "No overwriting has happened." << endl;
    } else {
        cout << "INFO: " << "Overwriting has happened." << endl;
    }

    cout << endl;
}

void optimizedQuickSort(int n) {
    int *array = createArray(n);
    int sum = sumCalculate(array, n);
    switchPlace(&array[n-1], &array[findMaxIndexInArray(n,array)]);
    switchPlace(&array[0], &array[findMinIndexInArray(n, array)]);
    auto start = high_resolution_clock::now();
    quickSortWithOptimization(array, 1, n-2);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time : " <<  duration.count() << "ms" << endl;
    confirmArray(n, array, sum);
    delete array;
}


void optimizedQuickSortWithDuplicates(int n) {
    int *array = createArrayOfDuplicates(n);
    int sum = sumCalculate(array, n);
    switchPlace(&array[n-1], &array[findMaxIndexInArray(n,array)]);
    switchPlace(&array[0], &array[findMinIndexInArray(n, array)]);
    auto start = high_resolution_clock::now();
    quickSortWithOptimization(array, 1, n-2);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time : " <<  duration.count() << "ms" << endl;
    confirmArray(n, array, sum);
    delete array;
}


void quickSortWithHugeSpread(int n) {
    int *array = createArrayWithHugeSpread(n);
    int sum = sumCalculate(array, n);
    auto start = high_resolution_clock::now();
    quickSort(array, 0, n-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time : " <<  duration.count() << "ms" << endl;
    confirmArray(n, array, sum);

    delete array;
}

void optimizedQuickSortWithHugeSpread(int n) {
    int *array = createArrayWithHugeSpread(n);
    int sum = sumCalculate(array, n);
    switchPlace(&array[n-1], &array[findMaxIndexInArray(n,array)]);
    switchPlace(&array[0], &array[findMinIndexInArray(n, array)]);
    auto start = high_resolution_clock::now();
    quickSortWithOptimization(array, 1, n-2);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time : " <<  duration.count() << "ms" << endl;
    confirmArray(n, array, sum);
    delete array;
}

void quickSortTestWithDuplicates(int n) {
    int *array = createArrayOfDuplicates(n);
    int sum = sumCalculate(array, n);
    auto start = high_resolution_clock::now();
    quickSort(array, 0, n-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time : " <<  duration.count() << "ms" << endl;
    confirmArray(n, array, sum);
    delete array;
}

void quickSortOfASortedArray(int n) {
    int *array = createArray(n);

    int sum = sumCalculate(array, n);
    quickSort(array, 0, n-1);

    auto start = high_resolution_clock::now();
    quickSort(array, 0, n-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time : " <<  duration.count() << "ms" << endl;
    confirmArray(n, array, sum);

    delete array;
}


void optimizedQuickSortOfASortedArray(int n) {
    int *array = createArray(n);

    int sum = sumCalculate(array, n);

    switchPlace(&array[n-1], &array[findMaxIndexInArray(n,array)]);
    switchPlace(&array[0], &array[findMinIndexInArray(n, array)]);
    auto start = high_resolution_clock::now();
    quickSortWithOptimization(array, 1, n-2);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time : " <<  duration.count() << "ms" << endl;
    confirmArray(n, array, sum);

    cout << "SORTING SECOND TIME." << endl;
    start = high_resolution_clock::now();
    quickSortWithOptimization(array, 1, n-2);
    stop = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(stop - start);
    cout << "Time : " <<  duration.count() << "ms" << endl;
    confirmArray(n, array, sum);

    delete array;
}




int main() {

    //Specifies array size.
    int n = 20000000;

    cout << "QUICKSORT WITH COUNTSORT PHASE" << endl;
    cout << n << " ELEMENTS." << endl;
    cout << "==============================" << endl;
    cout << endl;

    for (int i = 0; i < 5; ++i) {
        optimizedQuickSort(n);
    }

    cout << "QUICKSORT WITH COUNTSORT PHASE" << endl;
    cout << n << " ELEMENTS." << endl;
    cout << "ARRAY WITH IMMENSE DUPLICATES." << endl;
    cout << "===============================" << endl;
    cout << endl;

    for (int i = 0; i < 5; ++i) {
        optimizedQuickSortWithDuplicates(n);
    }

    cout << "QUICKSORT WITH COUNTSORT PHASE" << endl;
    cout << n << " ELEMENTS." << endl;
    cout << "SORT A SORTED ARRAY." << endl;
    cout << "===============================" << endl;
    cout << endl;
    optimizedQuickSortOfASortedArray(n);

    cout << "QUICKSORT WITH COUNTSORT PHASE" << endl;
    cout << n << " ELEMENTS." << endl;
    cout << "1 - 499 IN SPREAD." << endl;
    cout << "===============================" << endl;
    cout << endl;

    for (int i = 0; i < 3; ++i) {
        optimizedQuickSortWithHugeSpread(n);
    }


    cout << "QUICKSORT PHASE" << endl;
    cout << n << " ELEMENTS." << endl;
    cout << "===============================" << endl;
    cout << endl;

    for (int i = 0; i < 5; ++i) {
        quickSortTest(n);
    }

    cout << "QUICKSORT PHASE" << endl;
    cout << n << " ELEMENTS." << endl;
    cout << "ARRAY WITH IMMENSE DUPLICATES." << endl;
    cout << "===============================" << endl;
    cout << endl;

    for (int i = 0; i < 5; ++i) {
        quickSortTestWithDuplicates(n);
    }

    cout << "QUICKSORT WITH PHASE" << endl;
    cout << n << " ELEMENTS." << endl;
    cout << "SORT A SORTED ARRAY." << endl;
    cout << "===============================" << endl;
    cout << endl;
    for (int i = 0; i < 5; ++i) {
        quickSortOfASortedArray(n);
    }

    cout << "QUICKSORT WITH PHASE" << endl;
    cout << n << " ELEMENTS." << endl;
    cout << "1 - 499 IN SPREAD." << endl;
    cout << "===============================" << endl;
    cout << endl;

    for (int i = 0; i < 3; ++i) {
        quickSortWithHugeSpread(n);
    }

    return 0;
}

void quickSortTest(int n) {
    int *array = createArray(n);

    int sum = sumCalculate(array, n);

    auto start = high_resolution_clock::now();
    quickSort(array, 0, n-1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time : " <<  duration.count() << "ms" << endl;
    confirmArray(n, array, sum);

    delete array;
}














