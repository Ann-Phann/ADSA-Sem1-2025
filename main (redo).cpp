#include <vector>
#include <iostream>

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
}

std::string kara_multiple(std::string& num1, std::string& num2, int base) {

}

int main () {
    std::vector<int> input (3);
    int num; 

    for (int i = 0; i < 3; i++) {
        std::cin >> num;
        input[i] = num;
    }

    std::string num1 = std::to_string(input[0]);
    std::string num2 = std::to_string(input[1]);
    int base = input[2];
    
    std::string add = addition(num1, num2, base);
    std::cout << "add: " << add << std::endl;

    std::string multiple = kara_multiple (num1, num2, base);
    std::cout << "add: " << add << " " << "mul:" << multiple << " " ;

    return 0;
}