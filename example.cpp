#include <iostream>

// Function 1
int add(int a, int b) {
    int result = a + b;
    return result;
}

// Function 2
int subtract(int x, int y) {
    int result = x - y;
    return result;
}

// Function 3
int multiply(int m, int n) {
    int result = m * n;
    return result;
}

// Function 4
void printHello() {
    // Original IR just returns void
    return;
}

// Function 5
double divide(double a, double b) {
    double result = a / b;
    return result;
}

// Function 7
int factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        int sub = n - 1;
        int rec = factorial(sub);
        int result = n * rec;
        return result;
    }
}

// Function 6
int main() {
    int sum = add(10, 20);
    int diff = subtract(50, 30);
    int prod = multiply(5, 6);
    printHello();
    return 0;
}
