#include <vector>
#include <iostream>
#include <sstream>

int same_len (std::string &num1, std::string &num2) {
    int len1 = num1.size();
    int len2 = num2.size();

    int max_len = std::max(len1, len2);

    // test: correct add in 0
    while (num1.size() < max_len) {
        num1 = "0" + num1;
    }

    while (num2.size() < max_len){
        num2 = "0" + num2;
    } 

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
        //std::cout << "result: " << result << std::endl;
    }

    // if there still carry
    if (carry > 0) {
        result = (char)(carry + '0') + result; // convert back to char
    }

    return result;
}

// std::string kara_multiple(std::string& num1, std::string& num2, int base) {
//     return "";
// }

// Function to perform subtraction of two strings representing numbers in any base
std::string subtraction(std::string& num1, std::string& num2, int base) {
    // int len1 = num1.size();
    // int len2 = num2.size();

    // int len = std::max(len1,len2);

    // while (len1 < len) num1 = "0" + num1;
    // while (len2 < len) num2 = "0" + num2;    

    int len = same_len(num1, num2);

    std::string result = "";
    int borrow = 0;

    for (int i = len - 1; i >= 0; i--) {
        int digit_1 = num1[i] - '0';
        int digit_2 = num2[i] - '0';

        int diff = digit_1 - digit_2 - borrow;
        if (diff < 0) {
            diff += base;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result = (char)(diff + '0') + result;
    }

    return result;
}

// Convert integer to string representation in the given base
std::string int_to_string(int num, int base) {
    std::string result = "";
    while (num > 0) {
        result = (char)(num % base + '0') + result;
        num /= base;
    }
    return result.empty() ? "0" : result;
}

// Karatsuba multiplication of two numbers represented as strings in any base
std::string karatsuba(std::string num1, std::string num2, int base) {
    // Base case: if numbers are small enough, do regular multiplication
    if (num1.size() == 1 && num2.size() == 1) {
        int product = (num1[0] - '0') * (num2[0] - '0');
        return int_to_string(product, base);
    }

    int len = same_len(num1, num2);
    int half_len = len / 2;

    std::string a1 = num1.substr(0, num1.size() - half_len);
    std::string a0 = num1.substr(num1.size() - half_len);
    std::string b1 = num2.substr(0, num2.size() - half_len);
    std::string b0 = num2.substr(num2.size() - half_len);

    // Recursively calculate three products
    std::string p0 = karatsuba(a0, b0, base);
    std::string p2 = karatsuba(a1, b1, base);
    std::string p1 = karatsuba(addition(a1, a0, base), addition(b1, b0, base), base);

    // z1 - z2 - z0
    std::string temp = subtraction(p1, p2, base);
    temp = subtraction(temp, p0, base);

    // Multiply the result by appropriate powers of the base
    for (int i = 0; i < 2 * half_len; i++) {
        p2 += '0';
    }

    for (int i = 0; i < half_len; i++) {
        temp += '0';
    }

    // Add z2, temp, and z0
    std::string result = addition(p2, temp, base);
    result = addition(result, p0, base);

    // remove leading 0s if have
    while (result.size() > 1 && result[0] == '0') {
        result = result.substr(1);
    }

    
    return result;
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
    std::cout << add << " " << karatsuba(num1, num2, base) << " " <<  0 << std::endl;

    return 0;
}