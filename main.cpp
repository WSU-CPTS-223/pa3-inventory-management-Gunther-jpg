#include <iostream>

#include "HashMap.h"
#include "Container.h"

//It rests upon the user that the .csv that they wish to read from exists in the same folder as this code and that the
// below string matches the name of the file exactly
std::string const FILENAME = "marketing_sample.csv";

int main() {
    int user_choice = -1;
    std::string user_string = "";
    Container my_container(FILENAME);

    Container_Tests my_test_container;
    my_test_container.do_all_tests();

    my_container.import_data();

    do {

        std::cout << "1. Search by product ID " << std::endl << "2. Search by product category" << std::endl << "3. Exit" << std::endl;

        do {
            std::cin >> user_choice;
        } while(user_choice < 1 || user_choice > 3);

        if(user_choice == 1) {
            std::cout << "Product ID to search for: ";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(std::cin, user_string);

            my_container.find(user_string);

        } else if (user_choice == 2) {
            std::cout << "Product category to search for: ";

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(std::cin, user_string);

            my_container.list_inventory(user_string);
        }

    } while(user_choice != 3);


    return 0;
}
