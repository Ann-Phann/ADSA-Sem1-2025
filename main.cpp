#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

enum Status {
    NEVER_USED,
    OCCUPIED,
    TOMBSTONE
};

struct Slot {
    std::string key;
    Status status;

    Slot() : key(""), status(NEVER_USED){}
};

// define the table size of 26
const int TABLE_SIZE = 26;

// class for hash table
class HashTable {
private:
    Slot table[TABLE_SIZE];

    // helper function to get hash
    int hashHelp(const std::string& key);
    //helper function to search --> needed for any operation (insert, remove)
    int search(const std::string& key);


public:
    // function to call insert or remove
    void handleInstructions(const std::string& instruction);
    // use & for not creating copy and read-only
    void insert(const std::string& key);
    void remove(const std::string& key);

    // this will return an index of the key and -1 if not found
    void print(); // print final output
};

int HashTable::hashHelp(const std::string& key){
    return key.back() - 'a';
}

void HashTable::handleInstructions(const std::string &instruction){
    char action = instruction[0];

    if(action == 'A') {
        // get the rest of word
        insert(instruction.substr(1));
    }
    else if (action == 'D') {
        remove(instruction.substr(1));
    }
}

int HashTable::search(const std::string &key){
    int hash = hashHelp(key);

    for (int i =0; i < TABLE_SIZE; i++) {
        int index = (hash + i) % TABLE_SIZE;

        // this mean that the key is def not here
        if (table[index].status == NEVER_USED) {
            return -1; // demonstrate that not insert
        }

        if (table[index].status == OCCUPIED && table[index].key == key) {
            return index;
        }
    }
    // find nothing after the loop
    return -1; 
}

void HashTable::insert(const std::string &key){
    int findKey = search(key);

    // if found the key --> exit early
    if (findKey != -1) {
        return;
    }
    // start hash and put in the table
    int hash = hashHelp(key);

    for (int i = 0; i < TABLE_SIZE; i++) {
        int index = (hash + i) % TABLE_SIZE;
        Slot& slot = table[index];

        // if status tombstone and never use --> insert in 
        if (table[index].status == NEVER_USED || table[index].status == TOMBSTONE) {
            slot.key = key;
            slot.status = OCCUPIED;
            return;
        }
        // if the slot is already occupied --> move to the next slot that can put in
        // --> this is just done by i++
    }
}

void HashTable::remove(const std::string &key){
    int index = search(key);
    // found the key
    if (index != -1) {
        table[index].status = TOMBSTONE;
    }
}

void HashTable::print(){
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].status == OCCUPIED) {
            std::cout << table[i].key << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    // call hashtable 
    HashTable* table = new HashTable();

    // getting input
    std::string inputLine;
    std::getline(std::cin, inputLine);

    std::stringstream ss(inputLine);

    std::vector<std::string> instructions;
    std::string word;

    while (ss >> word) {
        instructions.push_back(word);
    }

    for (int i = 0; i < instructions.size(); i++) {
        table->handleInstructions(instructions[i]);
    }
    table->print();
    return 0;
}