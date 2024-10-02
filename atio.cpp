#include <iostream>

// Function to compute the GCD of two integers using recursion
int gcd(int a, int b) {
  // Base case: if b is 0, return a
  if (b == 0) {
    return a;
  } else {
    // Recursive call
    return gcd(b, a % b);
  }
}

int main() {
  int a, b;

  // Input two positive integers
  std::cout << "Enter two positive integers: ";
  std::cin >> a >> b;

  // Calculate GCD
  int result = gcd(a, b);

  // Output the result
  std::cout << "The GCD of " << a << " and " << b << " is " << result << std::endl;

  return 0;
}