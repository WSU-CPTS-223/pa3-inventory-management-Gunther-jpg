//
// Created by Hunter Whitlock on 10/24/25.
//

#ifndef PA3_HASHMAP_H
#define PA3_HASHMAP_H

#include <functional>

#include "Vector.h"
#include "Tuple.h"

template <typename T1, typename T2>
class HashMap {
    friend class Container_Tests;
private:
    using Map = Vector<Tuple<T1, T2> >;
    using Key = T1;
    using Value = T2;
    using Pair = Tuple<T1,T2>;

    Map* phash_map;
    std::hash<T1> hash_function;
    Pair default_pair;

    int size;
    int num_entries;
    int max_insertion_attempts;

    float max_lambda = 0.5;

    bool is_prime(int num) {
        bool output = false;

        if(num == 2 || num == 3) {
            output = true;
        } else if (num % 2 != 0) {
            output = true;
            for(int i = 3; i * i < num && output; i += 2) {
                if(num % i == 0) {
                    output = false;
                }
            }
        }
        return output;
    }

    int next_prime(int starting_point) {

        if(starting_point % 2 == 0) { starting_point++; } //ensures starting point is odd

        while(!is_prime(starting_point)) { starting_point += 2; }

        return starting_point;
    }

    int quadratic_probing(int attempts) {
        return attempts * attempts;
    }

    int hash (const Pair& pair, int size_of_hash_map, int attempts) {
        return (hash_function(pair.first) + quadratic_probing(attempts)) % size_of_hash_map;
    }

    int hash (const Key& key, int size_of_hash_map, int attempts) {
        return (hash_function(key) + quadratic_probing(attempts)) % size_of_hash_map;
    }

    //inserts a pair into a hash map without updating size, max insertion attempts, or triggering rehashing, used for rehashing,
    // returns number of insertion attempts
    int insert(Map &map, int map_size, Pair const &item) {
        int attempts = 0, index = hash(item, map_size, attempts++);

        while(attempts < INT_MAX && map[index] != default_pair) {
            index = hash(item, map_size, attempts++);
        }

        map[index] = item;

        return attempts;
    }

    void rehash() {
        int index = 0, new_max_insertions = 0, attempts = 0, new_size = next_prime((int)size*2);
        Map* new_hash_map = new Map(default_pair, new_size);

        for(int i = 0; i < size; i++) { //iterate through hash_map, copying all values to new_hash_map
            if(phash_map->at(i) != default_pair) {

                attempts = insert(*new_hash_map, new_size, phash_map->at(i));
                if(attempts > new_max_insertions) { new_max_insertions = attempts; }
            }
        }

        phash_map = new_hash_map;
        max_insertion_attempts = new_max_insertions;
        size = new_size;

    }

public:
    //constructor
    HashMap(int initial_size, Pair default_pair, Key nil_key) : size(initial_size), max_insertion_attempts(0),
    default_pair(default_pair), num_entries(0) {
        phash_map = new Map(default_pair, initial_size);
    }

    //copy constructor
    HashMap(const HashMap<T1,T2> &old_hash) {

        delete phash_map;
        size = old_hash.size;
        num_entries = old_hash.num_entries;
        max_insertion_attempts = old_hash.max_insertion_attempts;
        max_lambda = old_hash.max_lambda;
        default_pair = old_hash.default_pair;

        phash_map = new Map(default_pair, size);
        for(int i = 0; i < size; i++) {
            insert(old_hash.phash_map->at(i));
        }
    }

    //deep-copy assignment operator
    HashMap<T1,T2>& operator=(const HashMap<T1,T2> &rhs) {
        delete phash_map;
        size = rhs.size;
        num_entries = rhs.num_entries;
        max_insertion_attempts = rhs.max_insertion_attempts;
        max_lambda = rhs.max_lambda;
        default_pair = rhs.default_pair;

        phash_map = new Map(default_pair, size);
        for(int i = 0; i < size; i++) {
            insert(rhs.phash_map->at(i));
        }

        return *this;
    }

    ~HashMap() {
        delete phash_map;
    }

    void insert(Pair const &item) {
        int attempts = 0, index = hash(item, size, attempts++);

        while(attempts < INT_MAX && phash_map->at(index) != default_pair) {
            index = hash(item, size, attempts++);
        }

        phash_map->at(index) = item;

        if(attempts - 1 > max_insertion_attempts) { max_insertion_attempts = attempts - 1; }
        num_entries += 1;

        if((float)num_entries / size >= max_lambda) {
            rehash();
        }
    }

    T2& find(Key key) {
        int index = 0, count = -1;
        T2 &output = default_pair.second;

        do {
            count += 1;
            index = hash(key,size,count);
        } while(count < max_insertion_attempts && phash_map->at(index).first != key);

        if((phash_map->at(index)).first == key) {
            output = phash_map->at(index).second;
        }

        return output;
    }

    int get_size() { return size; }
    int get_num_entries() { return num_entries; }
    float get_lambda() { return (float)size / num_entries; }
};


#endif //PA3_HASHMAP_H
