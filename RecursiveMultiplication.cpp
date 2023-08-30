#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;



double multiplicationOne(int n, double x) {

    if (n == 1) {
        return x;
    }

    return x + multiplicationOne((n - 1), x);
}

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


int main() {


    int n;
    double x;

    cout << "Type in your n: "; // Type a number and press enter
    cin >> n; // Get user input from the keyboard
    cout << endl;

    cout << "Type in your x: "; // Type a number and press enter
    cin >> x; // Get user input from the keyboard
    cout << endl;

    auto start = high_resolution_clock::now();
    cout << multiplicationOne(4, 4) << endl;
    auto stop = high_resolution_clock::now();

    auto start2 = high_resolution_clock::now();
    cout << multiplicationTwo(4, 4) << endl;
    auto stop2 = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);

    auto duration2 = duration_cast<microseconds>(stop2 - start2);

    cout << duration.count() << endl;

    cout << duration2.count() << endl;

    return 0;

}