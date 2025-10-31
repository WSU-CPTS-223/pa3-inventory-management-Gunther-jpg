//
// Created by Hunter Whitlock on 10/24/25.
//

#ifndef PA3_ITEM_H
#define PA3_ITEM_H

#include <string>
#include <set>
#include <iostream>

//just to hold all the information associated with a single product
class Item {
public:
    std::string product_id {"EMPTY"};
    std::string product_name {"EMPTY"};
    std::string brand_name {"EMPTY"};
    std::string asin {"EMPTY"};
    std::set<std::string> product_category;
    std::string epc_code {"EMPTY"};
    std::string list_price {"EMPTY"};
    std::string selling_price {"EMPTY"};
    std::string quantity {"EMPTY"};
    std::string model_number {"EMPTY"};
    std::string about {"EMPTY"};
    std::string specification {"EMPTY"};
    std::string technical_details {"EMPTY"};
    std::string shipping_weight {"EMPTY"};
    std::string product_dimensions {"EMPTY"};
    std::string image {"EMPTY"};
    std::string variants {"EMPTY"};
    std::string sku {"EMPTY"};
    std::string product_url {"EMPTY"};
    std::string stock {"EMPTY"};
    std::string product_details {"EMPTY"};
    std::string dimensions {"EMPTY"};
    std::string color {"EMPTY"};
    std::string ingredients {"EMPTY"};
    std::string directions_to_use {"EMPTY"};
    bool is_amazon_seller {false};
    std::string size_quantity_variant {"EMPTY"};
    std::string product_description {"EMPTY"};


    Item& operator=(Item const &rhs) {

        if(rhs != *this) {
            product_id = rhs.product_id;
            product_name = rhs.product_name;
            brand_name = rhs.brand_name;
            asin = rhs.asin;

            //remove all items in product_category and add all items that are in rhs.product_category
            product_category.clear();
            for(const auto & it : rhs.product_category) {
                product_category.insert(it);
            }

            epc_code = rhs.epc_code;
            list_price = rhs.list_price;
            selling_price = rhs.selling_price;
            quantity = rhs.quantity;
            model_number = rhs.model_number;
            about = rhs.about;
            specification = rhs.specification;
            technical_details = rhs.technical_details;
            shipping_weight = rhs.shipping_weight;
            product_dimensions = rhs.product_dimensions;
            image = rhs.image;
            variants = rhs.variants;
            sku = rhs.sku;
            product_url = rhs.product_url;
            stock = rhs.stock;
            product_details = rhs.product_details;
            dimensions = rhs.dimensions;
            color = rhs.color;
            ingredients = rhs.ingredients;
            directions_to_use = rhs.directions_to_use;
            is_amazon_seller = rhs.is_amazon_seller;
            size_quantity_variant = rhs.size_quantity_variant;
            product_description = rhs.product_description;
        }

        return *this;
    }

    void print() {
        std::cout << "product_id: " + product_id << std::endl;
        std::cout << "product_name: " + product_name << std::endl;
        std::cout << "brand_name: " + brand_name << std::endl;
        std::cout << "asin: " + asin << std::endl;
        std::cout << "product_categories: " << std::endl;
        for(auto it = product_category.begin(); it != product_category.begin(); it++) {
            std::cout << *it << std::endl;
        }

        std::cout << "epc_code: " + epc_code << std::endl;
        std::cout << "list_price: " + list_price << std::endl;
        std::cout << "selling_price: " + selling_price << std::endl;
        std::cout << "quantity: " + quantity << std::endl;
        std::cout << "model_number: " + model_number << std::endl;
        std::cout << "about: " + about << std::endl;
        std::cout << "specification: " + specification << std::endl;
        std::cout << "technical_details: " + technical_details << std::endl;
        std::cout << "shipping_weight: " + shipping_weight << std::endl;
        std::cout << "product_dimensions: " + product_dimensions << std::endl;
        std::cout << "image: " + image << std::endl;
        std::cout << "variants: " + variants << std::endl;
        std::cout << "sku: " + sku << std::endl;
        std::cout << "product_url: " + product_url << std::endl;
        std::cout << "stock: " + stock << std::endl;
        std::cout << "product_details: " + product_details << std::endl;
        std::cout << "dimensions: " + dimensions << std::endl;
        std::cout << "color: " + color << std::endl;
        std::cout << "ingredients: " + ingredients << std::endl;
        std::cout << "directions_to_use: " + directions_to_use << std::endl;
        std::cout << "is_amazon_seller: " + std::to_string(is_amazon_seller) << std::endl;
        std::cout << "size_quantity_variant: " + size_quantity_variant << std::endl;
        std::cout << "product_description: " + product_description << std::endl;
    }

    bool operator==(Item &rhs) const {
        return product_id == rhs.product_id;
    }

    bool operator!= (Item &rhs) const{
        return product_id.compare(rhs.product_id);
    }

};


#endif