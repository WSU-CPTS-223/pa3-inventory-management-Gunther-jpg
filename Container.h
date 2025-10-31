//
// Created by Hunter Whitlock on 10/24/25.
//

#ifndef PA3_CONTAINER_H
#define PA3_CONTAINER_H

#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
#include <cassert>
#include <vector>

#include "List.h"
#include "HashMap.h"
#include "Item.hpp"

class Container {
    friend class Container_Tests;
private:
    //declare/initialize important values
    std::string const nil_string {"\n"};
    std::string const default_string {"EMPTY"};
    Tuple<std::string, Item> default_string_item_tuple {Tuple<std::string, Item>(default_string,Item())};
    Tuple<std::string, List<std::string> > default_string_string_list_tuple {Tuple<std::string, List<std::string> >()};

    HashMap<std::string, Item> inventory {HashMap<std::string, Item>(1000,default_string_item_tuple,nil_string)};
    List<Tuple<std::string, List<std::string>> > categories; //first is a category, second is a list of product ids that fit the category

    std::vector<std::string> all_product_ids {}; //for debugging/testing purposes

    std::string filename;
    std::string common_trailing_characters = " ,.\\\"\t\n"; //deemptyify_string removes all characters contained here from ends of a string

    //returns a copy of a string with common trailing characters, listed in common trailing characters, removed from the
    // beginning and end of a string
    std::string deemptyify_string(std::string &str) {
        std::string output = nil_string;
        if (str != "" && str != "\"\"") {
            output = str;

            //removes common_trailing_characters and non-ascii characters from front of str
            while(common_trailing_characters.find(output.front(),0) != std::string::npos && isascii(output.front())) {
                output.erase(output.begin());
            }

            //removes common_trailing_characters and non-ascii characters from back of str
            while(common_trailing_characters.find(output.back(),0) != std::string::npos && isascii(output.front())) {
                output.erase(output.end() - 1);
            }
        }

        return output;
    }

    //returns a copy of the input string, but all ascii characters are made lowercase
    std::string lowercaseify(std::string str) {

        for(auto it = str.begin(); it != str.end(); it++) {
            if(isascii(*it)) {
                *it = std::tolower(*it);
            }
        }

        return str;
    }

    //returns the next position in a string that matches "," and not ", "
    int skip_false_comma_delimeters(std::string &str, int current_position) {
        if(str.find(",",current_position) == str.find(", ",current_position)) {

            while(str.find(",",current_position) == str.find(", ",current_position)) {
                current_position = str.find(", ", current_position) + 2;
            }
            current_position = str.find(",", current_position);

        } else {
            current_position = str.find(",", current_position);
        }

        return current_position;
    }

public:

    Container(std::string filename) : filename(filename) {}

    //Imports data from the given file name
    //it is up to the user to ensure that the .csv that they wish to read from is provided and that the file name used
    //in the code below in the line reading file.open(..) matches the file's name
    void import_data() {
        int count = 0, line_pos[] = {0, 0};
        std::string line = "", S = "", rest_of_line = "";
        std::ifstream file;
        Tuple<std::string, List<std::string>> new_category_tuple;

        //attempts to open file
        file.open("./" + filename, std::ios_base::in);
        try {
            if(!file.good()) {
                file.open("../" + filename, std::ios_base::in);
                if(!file.good()) {
                    throw 0;
                }
            }
        } catch(...) {
            std::cout << "Either .csv does not exist or the filename stored is not correct" << std::endl;
        }

        getline(file, line, '\n'); // removes first line

        while (getline(file, line, '\n')) {
            Item item; count++; line_pos[0] = 0; line_pos[1] = 0; //simple setup for the loop

            //code below here is the same for storing every element, except where described
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]); //updates line_pos[1] so that it points to the next comma separated value
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]); //sets S to the characters in line between line_pos[0] & line_pos[1]
            item.product_id = deemptyify_string(S); //stores the value
            line_pos[0] = line_pos[1] + 1; //updates line_pos[0] to point just beyond line_pos[1]

            all_product_ids.push_back(item.product_id); //keeping track of all product ids for debugging purposes

            //product name
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.product_name = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //brand name
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.brand_name = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //asin
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.asin = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //product categories
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            //if S is not empty, add every |-seperated value to the set product category
            if(!S.empty() && S != "" && S != "\"\"") {
                std::stringstream product_categories(S);
                while(getline(product_categories, S, '|')) {
                    if(!deemptyify_string(S).empty()) {
                        item.product_category.insert(deemptyify_string(S));
                    }
                }
            }
            line_pos[0] = line_pos[1] + 1;

            //epc cpde
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.epc_code = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //list price
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.list_price = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //selling price
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.selling_price = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //quantity
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.quantity = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //model number
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.model_number = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //about
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.about = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //specification
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.specification = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //technical details
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.technical_details = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //shipping weight
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.shipping_weight = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //product dimensions
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.product_dimensions = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //image(s)
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.image = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //variants
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.variants = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //sku
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.variants = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //product url
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.product_url = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //stock
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.stock = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //product details
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.product_details = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //product dimensions
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.dimensions = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //product color
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.color = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //ingredients
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.ingredients = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //directions to use
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.directions_to_use = deemptyify_string(S);
            line_pos[0] = line_pos[1] + 1;

            //is amazon seller
            line_pos[1] = skip_false_comma_delimeters(line, line_pos[0]);
            S = line.substr(line_pos[0], line_pos[1] - line_pos[0]);
            item.is_amazon_seller = deemptyify_string(S) == "Y"; //just stores if S == "Y" in item.is_amazon_seller

            Tuple<std::string, Item> new_tuple(item.product_id, item); //A tuple containing all information store in item this iteration
            inventory.insert(new_tuple);

            //iterates through each item in item.product_category, append the product id to the corresponding product
            // category if it exists, else it creates a new product category and appends the product id there
            for(auto it = item.product_category.begin(); it != item.product_category.end(); it++) {
                new_category_tuple = default_string_string_list_tuple;
                new_category_tuple.first = lowercaseify(*it);

                //if the category already exists, append product id to the list contained in tuple, else create a new category
                if(categories.find(new_category_tuple)) {
                    *(categories.find(new_category_tuple)->second.append_new_node()) = item.product_id;
                } else {
                    new_category_tuple.first = lowercaseify(*it); //ensures categories are not capitalization-sensitive
                    *(new_category_tuple.second.append_new_node()) = item.product_id;
                    *(categories.append_new_node()) = new_category_tuple;
                }
            }

        }

    }


    //find
    void find(std::string const inventory_id) {
        Item found_item = inventory.find(lowercaseify(inventory_id));

        if(found_item != default_string_item_tuple.second) {
            found_item.print();
        } else {
            std::cout << "Inventory/product '" + inventory_id + "' not found" << std::endl;
        }
    }

    //list_inventory
    void list_inventory(std::string category_string) {
        std::string product_id = "";
        Tuple<std::string, List<std::string> > temp_string_string_list_tuple = default_string_string_list_tuple, *found_tuple = nullptr;
        Item temp_item = default_string_item_tuple.second;

        temp_string_string_list_tuple.first = category_string;

        found_tuple = categories.find(temp_string_string_list_tuple);

        if(found_tuple) {

            for(int i = 0; i < found_tuple->second.get_length(); i++) {
                temp_item = inventory.find(*found_tuple->second.get_data_ptr_at_index(i));
                std::cout << "ID: " + temp_item.product_id << std::endl << "Product name: " + temp_item.product_name << std::endl;
            }

        } else {
            std::cout << "Category '" + category_string + "' not found" << std::endl;
        }
    }
};


class Container_Tests {
private:
    Container test_container {"marketing_sample.csv"};

public:
    Container_Tests() = default;

    //runs all tests
    void do_all_tests() {
        test_container.import_data();

        assert(deemptify_string_test());
        std::cout << "deemptifys_string test passed" << std::endl;

        assert(skip_false_comma_delimeters_test());
        std::cout << "skip_false_comma_delimeters test passed" << std::endl;

        assert(test_lowercaseify());
        std::cout << "lowercaseify test passed" << std::endl;

        assert(basic_membership_test());
        std::cout << "basic membership test passed" << std::endl;

        assert(full_membership_test());
        std::cout << "full membership test passed" << std::endl;

        assert(full_rehash_membership_test());
        std::cout << "full membership test passed after rehashing" << std::endl << std::endl;
    }

    //tests if a few of the elements are present in test_container.inventory
    bool basic_membership_test() {
        bool output = true;
        std::vector<std::string> product_ids = {"4c69b61db1fc16e7013b43fc926e502d","66d49bbed043f5be260fa9f7fbff5957",
                                                "2c55cae269aebf53838484b0d7dd931a","18018b6bc416dab347b1b7db79994afa",
                                                "e04b990e95bf73bbe6a3fa09785d7cd0","f8c32a45e507a177992973cf0d46d20c",
                                                "40d3cd16b41970ae6872e914aecf2c8e","bc178f33a04dbccefa95b165f8b56830",
                                                "cc2083338a16c3fe2f7895289d2e98fe","69828c5570dcdbd1609216d33fbad0db",
                                                "5bb4a9aa52085ada20006d166b1e2f87","fca4a2170dbe85896ac3daff0a7f1e1b"};

        for(auto it = product_ids.begin(); it != product_ids.end() && output; it++) {
            if(test_container.inventory.find(*it) == test_container.default_string_item_tuple.second) {
                output = false;
            }
        }

        return output;
    }

    bool deemptify_string_test() {
        bool output = true;
        std::string test_string1 = test_container.common_trailing_characters, test_string2 = "\"Big\nFrog...";

        if(test_container.deemptyify_string(test_string1) != "") { output = false; }
        if(test_container.deemptyify_string(test_string2) != "Big\nFrog") { output = false; }

        return output;
    }

    //tests if test_container.lowercaseify() works with a few cases
    bool test_lowercaseify() {
        bool output = true;
        std::string str1 = "nkvcxoiuou\tqwrbsmvxzlj", str2 = "BIGBROWNDOGgotsenttothegulag", str2_2 = "bigbrowndoggotsenttothegulag";

        if(test_container.lowercaseify(str1) != str1) { output = false; }
        if(test_container.lowercaseify(str2).compare(str2_2)) { output = false; }

        return output;
    }

    //tests if every product id read by test_container.import_data() is present in test_container.inventory
    bool full_membership_test() {
        bool output = true;
        std::vector<std::string> deleted_ids = {};
        for(auto it = test_container.all_product_ids.begin(); it != test_container.all_product_ids.end() && output; it++) {
            if(test_container.inventory.find(*it) == test_container.default_string_item_tuple.second) {
                output = false;
            }
        }

        return output;
    }

    //tests if every product id read by test_container.import_data() is present in test_container.inventory after rehashing
    bool full_rehash_membership_test() {
        test_container.inventory.rehash();

        return full_membership_test();
    }

    bool skip_false_comma_delimeters_test() {
        bool output = true;
        int str_pos[] = {0, 0};
        std::string str = "before false delim, after false delim,after real,,,delim";


        str_pos[1] = test_container.skip_false_comma_delimeters(str, str_pos[0]);
        if(str_pos[1] != 37) { output = false; }
        str_pos[0] = str_pos[1] + 1;

        str_pos[1] = test_container.skip_false_comma_delimeters(str, str_pos[0]);
        if(str_pos[1] != 48) { output = false; }
        str_pos[0] = str_pos[1] + 1;

        str_pos[1] = test_container.skip_false_comma_delimeters(str, str_pos[0]);
        if(str_pos[1] != 49) { output = false; }
        str_pos[0] = str_pos[1] + 1;

        str_pos[1] = test_container.skip_false_comma_delimeters(str, str_pos[0]);
        if(str_pos[1] != 50) { output = false; }
        str_pos[0] = str_pos[1] + 1;

        return output;
    }

};

#endif //PA3_CONTAINER_H
