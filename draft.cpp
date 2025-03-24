#include <iostream>
#include <vector>
#include <math.h>

int same_len (std::string &num1, std::string &num2) {
    int len1 = num1.size();
    int len2 = num2.size();

    int max_len = std::max(len1, len2);

    while (num1.size() < max_len) num1 = "0" + num1;
    while (num2.size() < max_len) num2 = "0" + num2;

    return max_len;
}

// int addition (int I1, int I2, int base) {
//     int carry = 0;
//     int num1 = I1;
//     int num2 = I2;

//     int result = 0; 

//     while (num1 > 0 || num2 > 0 || carry > 0) {
//         int last_digit_1 = num1 % 10;
//         int last_digit_2 = num2 % 10;

//         int sum = last_digit_1 + last_digit_2 + carry;
//         carry = sum / base;
//         std::cout << "carry: " << carry << std::endl;
//         int digit = sum % base;

//         result = result * 10 + digit ;

//         num1 /= 10;
//         num2 /= 10;

//         std::cout << "this is running" << std::endl;
//     }

//     // reverse the result 
//     int rev_num = 0;
//     while (result > 0) {
//         rev_num = rev_num * 10 + result % 10;
//         result = result / 10;
//     }
//     return rev_num;
// }



// long long addition(long I1, long I2, int base) {
//     int carry = 0;
//     long num1 = I1;
//     long num2 = I2;
//     long result = 0;
//     int place = 1;  // Keeps track of place value (1, 10, 100, etc.)

//     while (num1 > 0 || num2 > 0 || carry > 0) {
//         int last_digit_1 = num1 % 10;
//         int last_digit_2 = num2 % 10;

//         int sum = last_digit_1 + last_digit_2 + carry;
//         carry = sum / base;  // Calculate new carry
//         int digit = sum % base;  // Store the correct digit in the given base

//         result += digit * place;  // Build the final result
//         place *= 10;  // Move to the next place value

//         num1 /= 10;
//         num2 /= 10;
//     }

//     return result;
// }

std::string addition(std::string& num1, std::string& num2, int base) {
    // Ensure both numbers have the same length by padding with zeros if necessary
    int max_len = std::max(num1.size(), num2.size());
    while (num1.size() < max_len) num1 = "0" + num1;
    while (num2.size() < max_len) num2 = "0" + num2;

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

// int kara_multiple (int I1, int I2, int base) {

//     // convert to string to calculate length
//     std::string num1 = std::to_string(I1);
//     std::string num2 = std::to_string(I2);

//     int len1 = num1.size();
//     int len2 = num2.size();

//     // only direct multiply if either number only has 1 digit
//     if (len1 == 1 || len2 == 1) {
//         return I1 * I2;
//     }

//     // karatsuba algorithm
//     // make sure both number have the same size
//     int make_same_len = same_len(num1, num2);

//     // split the number
//     int half_length = std::max(len1,len2) /2;

//     std::string high1 = num1.substr(0, half_length);
//     std::string low1 = num1.substr(half_length);


//     std::string high2 = num2.substr(0, half_length);
//     std::string low2 = num2.substr(half_length);

//     // // solve 3 subprob
//     // int p0 = kara_multiple(std::stoi(low1), std::stoi(low2), base);
//     // int p2 = kara_multiple(std::stoi(high1), std::stoi(high2), base);
    
//     // int add_1 = std::stoi(low1) + std::stoi(high1);
//     // int add_2 = std::stoi(low2) + std::stoi(high2);

//     // int p1 = kara_multiple(add_1, add_2, base);

//     // return p2* pow(base, 2);

//     int low1_int = std::stoi(low1);
//     int high1_int = (high1.empty()) ? 0 : std::stoi(high1);
//     int low2_int = std::stoi(low2);
//     int high2_int = (high2.empty()) ? 0 : std::stoi(high2);

//     // Solve 3 subproblems
//     int p0 = kara_multiple(low1_int, low2_int, base);
//     int p2 = kara_multiple(high1_int, high2_int, base);

//     int add_1 = low1_int + high1_int;
//     int add_2 = low2_int + high2_int;
//     int p1 = kara_multiple(add_1, add_2, base) - p0 - p2;

//     return p2 * pow(base, 2 * (len1 - half_length + len2 - half_length)) +
//            p1 * pow(base, std::max(len1 - half_length, len2 - half_length)) + 
//            p0;
// }

// // Karatsuba multiplication
// long long kara_multiple(int I1, int I2, int base) {
//     std::string num1 = std::to_string(I1);
//     std::string num2 = std::to_string(I2);

//     // Base case: Direct multiplication when either number has only 1 digit
//     if (base == 10 && (num1.size() == 1 || num2.size() == 1)) {
//         return static_cast<long long>(I1) * I2;
//     }

//     else if (base != 10 && (num1.size() == 1 && num1.size() == 1)) {

//     }
//     // Ensure both numbers have the same length
//     int len = same_len(num1, num2);

//     // Compute half-length (for odd-length, round up)
//     int half_len = (len + 1) / 2;

//     // Split the numbers
//     int high1 = std::stoi(num1.substr(0, len - half_len)); // a1
//     int low1 = std::stoi(num1.substr(len - half_len));     // a0
//     int high2 = std::stoi(num2.substr(0, len - half_len)); // b1
//     int low2 = std::stoi(num2.substr(len - half_len));     // b0

//     // Compute subproducts according to the Karatsuba algorithm
//     long long p0 = kara_multiple(low1, low2, base);                      // a0 * b0
//     long long p2 = kara_multiple(high1, high2, base);                    // a1 * b1
//     long long p1 = kara_multiple(addition(low1, high1, base), addition(low2,high2,base), base);      // (a0 + a1) * (b0 + b1)

//     // Compute result using the formula
//     return (p2 * pow(base, 2 * half_len)) + ((p1 - p2 - p0) * pow(base, half_len)) + p0;
// }



// Base Case: Direct multiplication if either number has only 1 digit
bool is_single_digit(int num, int base) {
    return num < base; // Any number less than the base is a single digit in that base
}

// Karatsuba Multiplication
// long long kara_multiple(int I1, int I2, int base) {
//     // Base case: If either number is a single digit, multiply directly
//     if (is_single_digit(I1, base) || is_single_digit(I2, base)) {
//         return static_cast<long long>(I1) * I2;
//     }

//     // Convert to string to get the digits
//     std::string num1 = std::to_string(I1);
//     std::string num2 = std::to_string(I2);

//     // Ensure both numbers have the same length
//     int len = same_len(num1, num2);

//     // Compute half-length (for odd-length, round up)
//     int half_len = (len + 1) / 2;

//     // Split the numbers
//     int high1 = std::stoi(num1.substr(0, len - half_len)); // a1
//     int low1 = std::stoi(num1.substr(len - half_len));     // a0
//     int high2 = std::stoi(num2.substr(0, len - half_len)); // b1
//     int low2 = std::stoi(num2.substr(len - half_len));     // b0

//     // Compute subproducts according to the Karatsuba algorithm
//     long long p0 = kara_multiple(low1, low2, base);                      // a0 * b0
//     long long p2 = kara_multiple(high1, high2, base);                    // a1 * b1
//     long long p1 = kara_multiple(addition(low1, high1, base), addition(low2, high2, base), base);  // (a0 + a1) * (b0 + b1)

//     // Compute result using the Karatsuba formula
//     return (p2 * pow(base, 2 * half_len)) + ((p1 - p2 - p0) * pow(base, half_len)) + p0;
// }
int main () {
    std::vector<int> input (3);
    int num; 

    for (int i = 0; i < 3; i++) {
        std::cin >> num;
        input[i] = num;
    }
    
    std::string add = addition(static_cast<long> (input[0]), static_cast<long> (input[1]), input[2]);
    std::cout << "add: " << add << std::endl;

    // long long multiple = kara_multiple (input[0], input[1], input[2]);
    // // int ratio = floor(input[0] / input[1]);
    // std::cout << "add: " << add << " " << "mul:" << multiple << " " ;

    return 0;
}