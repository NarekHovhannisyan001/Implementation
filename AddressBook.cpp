#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int start() {
    std::cout << "1. I want to see the table:" << std::endl;
    std::cout << "2. I want add in Address Book" << std::endl;
    std::cout << "3. I want remove in Address Book" << std::endl;
    std::cout << "4. For exit" << std::endl;
    std::cout << "Enter the number:";
    int res;
    std::cin >> res;
    return res;
}

void print() {
    std::ifstream inputFile("AddressBook.txt");
    if (!inputFile) {
        std::cerr << "Error opening the file: AddressBook.txt" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::cout << line << std::endl;
    }
    inputFile.close();
}

void add() {
    std::ofstream outputFile;
    std::string name;
    std::cout << "Enter first name and last name:" << std::endl;
    std::getline(std::cin.ignore(), name);
    if (name.empty()) {
        std::cerr << "Name cannot be empty." << std::endl;
        return;
    }

    std::string phone_number;
    std::cout << "Enter phone number +374(..)(......):" << std::endl;
    std::getline(std::cin, phone_number);

    std::string email;
    std::cout << "Enter your email:" << std::endl;
    std::getline(std::cin, email);

    if (phone_number.empty() || email.empty()) {
        std::cerr << "Phone number and email cannot be empty." << std::endl;
        return;
    }

    outputFile.open("AddressBook.txt", std::ios::app);
    outputFile << "\n" << name << " +374" << phone_number << " " << email;
}

void remove(std::string& line_to_remove) {
    std::ifstream inputFile("AddressBook.txt");
    if (!inputFile) {
        std::cerr << "Error opening the file: AddressBook.txt" << std::endl;
        return;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(inputFile, line)) {
        if (line != line_to_remove) {
            lines.push_back(line);
        }
    }
    inputFile.close();

    std::ofstream outputFile("AddressBook.txt", std::ios::trunc);
    if (!outputFile) {
        std::cerr << "Error opening the file: AddressBook.txt for writing." << std::endl;
        return;
    }

    for (const auto& l : lines) {
        outputFile << l << std::endl;
    }
}

int main() {
    while (true) {
        switch (start()) {
            case 1:
               { 
                print();
                break;
                }
            case 2:
                {
                add();
                break;
                }
            case 3:
            {
                std::string line_to_remove;
                std::cout << "Enter the line you want to remove from the Address Book: " << std::endl;
                std::getline(std::cin.ignore(), line_to_remove);

                if (line_to_remove.empty()) {
                    std::cerr << "Line to remove cannot be empty." << std::endl;
                } else {
                    remove(line_to_remove);
                }
                break;
            }
            case 4: 
            {
             return 0;
            }
            default:
            {
                std::cout << "Invalid input. Please enter a valid number." << std::endl;
                break;
            }
        }
    }
}
