//
// Created by Hunter Whitlock on 10/27/25.
//

#ifndef PA3_TUPLE_H
#define PA3_TUPLE_H

template <typename T1, typename T2>
class Tuple {
public:
    T1 first;
    T2 second;

    //an empty constructor, when values need to be given later
    Tuple() {}

    Tuple(T1 first, T2 second) : first(first), second(second) {};

    explicit Tuple(T1 first) : first(first) {};
    explicit Tuple(T2 second) : second(second) {};


    //copy by reference
    Tuple(Tuple<T1, T2> const &old_tuple) {
        first = old_tuple.first;
        second = old_tuple.second;
    }

    //copy assignment
    Tuple<T1, T2>& operator=(Tuple<T1, T2> const &rhs) {
        first = rhs.first;
        second = rhs.second;
        return *this;
    }

    bool operator== (Tuple<T1, T2> &rhs) {
        return first == rhs.first;
    }

    bool operator!=(Tuple<T1, T2> &rhs) {
        return first != rhs.first;
    }
};


#endif //PA3_TUPLE_H
