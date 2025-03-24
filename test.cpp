#include <iostream>
#include <string>
#include <algorithm>

// Function to pad two strings to the same length
int same_len(std::string& num1, std::string& num2) {
    int len1 = num1.size();
    int len2 = num2.size();
    int max_len = std::max(len1, len2);

    while (num1.size() < max_len) num1 = "0" + num1;
    while (num2.size() < max_len) num2 = "0" + num2;

    return max_len;
}

// Function to add two numbers in a given base
std::string addition(std::string& num1, std::string& num2, int base) {
    // Ensure both numbers have the same length by padding with zeros if necessary
    int max_len = same_len(num1, num2);

    std::string result = "";
    int carry = 0;

    // Add digits from right to left
    for (int i = num1.size() - 1; i >= 0; i--) {
        int digit1 = num1[i] - '0';  // Convert char to int
        int digit2 = num2[i] - '0';  // Convert char to int

        // Add digits and carry
        int sum = digit1 + digit2 + carry;
        carry = sum / base;  // New carry
        int digit = sum % base;  // Current digit (within base)

        result = (char)(digit + '0') + result;  // Convert back to char and prepend to result
    }

    // If there's a carry left, prepend it
    if (carry > 0) {
        result = (char)(carry + '0') + result;
    }

    return result;
}

int main() {
    std::string num1, num2;
    int base;

    // Taking input for the numbers and base
    std::cout << "Enter the first number: ";
    std::cin >> num1;
    std::cout << "Enter the second number: ";
    std::cin >> num2;
    std::cout << "Enter the base: ";
    std::cin >> base;

    // Perform addition
    std::string result = addition(num1, num2, base);

    // Output the result
    std::cout << "Result of addition in base " << base << ": " << result << std::endl;

    return 0;
}
