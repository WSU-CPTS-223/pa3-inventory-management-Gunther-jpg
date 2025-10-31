//
// Created by Hunter Whitlock on 10/27/25.
//

#ifndef PA3_VECTOR_H
#define PA3_VECTOR_H


#include <iostream>

template <typename T>
class Vector {
private:
    T* phead;
    T default_T;
    int size;

public:

    //constructor
    Vector(T default_value, int initial_size) {
        size = initial_size;
        default_T = default_value;
        phead = new T[size];

        //set all values to default_T
        for(int i = 0; i < size; i++) {
            phead[i] = default_T;
        }
    }

    //copy constructor
    Vector(Vector<T> const &old_vector) {
        size = old_vector.size;
        default_T = old_vector.default_T;
        phead = new T[size];

        for(int i = 0; i < size; i++) {
            phead[i] = old_vector[i];
        }
    }

    //copy assignment
    Vector<T>& operator=(Vector<T> const &rhs) {
        size = rhs.size;
        default_T = rhs.default_T;
        delete phead; //deallocates old array

        phead = new T[size]; //allocates new array

        for(int i = 0; i < size; i++) {
            phead[i] = rhs[i];
        }
    }

    //deconstructor
    ~Vector() {
        delete[] phead;
    }

    //access an element in array with bounds checking
    T& at(int index) {
        try {

            if(index < 0 || index >= size) {
                throw 0;
            } else {
                return phead[index];
            }

        } catch (...){
            std::cout << "index outside of valid range" << std::endl;
        }
    }

    //access an element in array with bounds checking
    T& operator[](int index) {
        try {

            if(index < 0 || index >= size) {
                throw 0;
            } else {
                return phead[index];
            }

        } catch (...){
            std::cout << "index outside of valid range" << std::endl;
        }
    }

};


#endif //PA3_VECTOR_H
