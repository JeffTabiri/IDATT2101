#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

/**
 * First multiplication method without the use of "*"
 *
 * @param n is first factor, integer
 * @param x is the second factor, can be an integer or a double
 * @return n * x
 */
double multiplicationOne(int n, double x) {

    if (n == 1) {
        return x;
    }

    return x + multiplicationOne((n - 1), x);
}

/**
 * Second multiplication method without the use of "*"
 *
 * @param n is first factor, integer
 * @param x is the second factor, can be an integer or a double
 * @return n*x
 */
double multiplicationTwo(int n, double x) {

    if (n == 1) {
        return x;
    }

    else if (n & 1) {
        return x +  multiplicationTwo((n-1)/2, (x+x));
    }

    else {
        return multiplicationTwo(n/2, (x+x));
    }
}

void multipleLoop(int n, double x, int numberOfIterations) {

    double firstResult = 0;

    double loopLimit = numberOfIterations;

    //Loop Measure 1.
    auto start = high_resolution_clock::now();
    for (int i = 0; i < loopLimit; ++i) {
        firstResult = multiplicationOne(n,x);
    }
    auto stop = high_resolution_clock::now();

    double secondResult = 0;

    //Loop Measure 2.
    auto start2 = high_resolution_clock::now();
    for (int i = 0; i < loopLimit; ++i) {
        secondResult = multiplicationTwo(n,x);
    }
    auto stop2 = high_resolution_clock::now();


    //Calculate time used.
    auto duration = duration_cast<microseconds>(stop - start);
    auto duration2 = duration_cast<microseconds>(stop2 - start2);

    cout << "Method 1 Result: " << firstResult << endl;
    cout << "Method 1 Time: " << duration.count()/loopLimit << "ms" << endl;

    cout << "\n";

    cout << "Method 2 Result: " << secondResult << endl;
    cout << "Method 2 Time: " << duration2.count()/loopLimit << "ms" << endl;
}


int main() {

    int n;
    double x;
    int iterations;

    cout << "Type in your n: "; // Type a number and press enter
    cin >> n; // Get user input from the keyboard
    cout << endl;

    cout << "Type in your x: "; // Type a number and press enter
    cin >> x; // Get user input from the keyboard
    cout << endl;

    cout << "The algorithm will run multiple iterations to measure the time. How many iterations should it run?"; // Type a number and press enter
    cin >> iterations; // Get user input from the keyboard
    cout << endl;

    cout << "The computation is " << n << " * " << x << endl;
    cout << "The amount of iterations is: " << iterations << endl;
    cout << "The amount of n is: " << n << endl;
    cout << "\n";

    multipleLoop(n,x, iterations);
}