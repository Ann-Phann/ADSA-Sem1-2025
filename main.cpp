#include <vector>
#include <iostream>
#include <sstream>

int same_len (std::string &num1, std::string &num2) {
    int len1 = num1.size();
    int len2 = num2.size();

    int max_len = std::max(len1, len2);

    while (num1.size() < max_len) num1 = "0" + num1;
    while (num2.size() < max_len) num2 = "0" + num2;

    return max_len;
}

std::string addition(std::string& num1, std::string& num2, int base) {
    int len = same_len(num1, num2);

    std::string result = "";
    int carry = 0;

    // add from right to left
    for (int i = len - 1; i >= 0; i--) {
        int digit_1 = num1[i] - '0'; // convert char to int
        int digit_2 = num2[i] - '0';

        int sum = digit_1 + digit_2 + carry;
        carry = sum / base;
        int digit = sum % base;
        result = (char)(digit + '0') + result;
    }

    // if there still carry
    if (carry > 0) {
        result = (char)(carry + '0') + result; // convert back to char
    }

    return result;

}

std::string kara_multiple(std::string& num1, std::string& num2, int base) {
    return "";
}

int main () {
    std::string num1, num2;
    int base;

    // Read the whole line first
    std::string line;
    std::getline(std::cin, line);

    // Use stringstream to extract the numbers and base
    std::stringstream ss(line);
    ss >> num1 >> num2 >> base; // Extract 2 numbers and the base

    std::string add = addition(num1, num2, base);
    std::cout << add << 0 << 0 << std::endl;

    return 0;
}