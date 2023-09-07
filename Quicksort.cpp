#include <iostream>
#include <chrono>
#include <bits/stdc++.h>
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

void findLargestNumber(int table, int tableLength) {

}
int split2(int *table, int leftEnd, int rightEnd) {
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


void quickSort(int *table, int leftEnd, int rightEnd) {
    if (rightEnd - leftEnd > 2) {
        int dividingPosition = split(table, leftEnd, rightEnd);
        quickSort(table, leftEnd, dividingPosition - 1);
        quickSort(table, dividingPosition + 1, rightEnd);
    } else medianSort(table, leftEnd, rightEnd);
}

int * createArray(int n) {
    srand((int)time(0));

    int *table = new int [n];
    for (int i = 0; i < n; ++i) {
        table[i] = rand() % 10;
    }

    return table;
}

bool checkSorted(int *table, int tableLength) {
    for (int i = 1; i < tableLength - 1; i++) {
        if (table[i] < table[i-1]) {
            return false;
        }
    }
    return true;
}

int sumCalculate(int *table, int tableLength) {
    int sum = 0;
    for (int i = 0; i < tableLength; i++) {
        sum += table[i];
    }
    return sum;
}

void countSort(int n, int inputTable[n], int outputTable[n], int k) {

    int ht[k+1];

    for (int i = 0; i <= k; ++i) {
        ht[i] = 0;

    }

    for (int i = 0; i < n; ++i)  {
        ++ht [inputTable[i]];
    }

    for (int i = n - 1; i >= 0; --i) {
        outputTable[--ht[inputTable[i]]] = inputTable[i];
    }
}

void quickSortWithOptimization(int *table, int leftEnd, int rightEnd) {

    int max = *max_element(array, 1, 2);
    int min = table[leftEnd];

    if (rightEnd - leftEnd > 2) {
        int dividingPosition = split2(table, leftEnd, rightEnd);
        quickSortWithOptimization(table, leftEnd, dividingPosition - 1);
        quickSortWithOptimization(table, dividingPosition + 1, rightEnd);
    } else medianSort(table, leftEnd, rightEnd);
}

int main() {

    int n = 100000000;
    int *array = createArray(n);
    int sum = sumCalculate(array, n);

    auto start = high_resolution_clock::now();
    quickSort(array, 0, n-1);
    auto stop = high_resolution_clock::now();

    if (checkSorted(array, n)) {
        cout << "The table is sorted." << endl;
    } else {
        cout << "The table is not sorted." << endl;
    }

    if (sum == sumCalculate(array, n)) {
        cout << "No overwriting has happened." << endl;
    } else {
        cout << "Overwriting has happened." << endl;
    }

    auto duration = duration_cast<seconds>(stop - start);
    cout << duration.count() << "sec" << endl;


    auto start2 = high_resolution_clock::now();
    quickSort(array, 0, n-1);
    auto stop2 = high_resolution_clock::now();

    if (checkSorted(array, n)) {
        cout << "The second table is sorted." << endl;
    } else {
        cout << "The second table is not sorted." << endl;
    }

    if (sum == sumCalculate(array, n)) {
        cout << "No overwriting has happened." << endl;
    } else {
        cout << "Overwriting has happened." << endl;
    }

    auto duration2 = duration_cast<seconds>(stop2 - start2);
    cout << duration2.count() << "sec" << endl;



    delete array;

    return 0;
}








