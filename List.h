//
// Created by Hunter Whitlock on 10/24/25.
//

#ifndef PA3_LIST_H
#define PA3_LIST_H

//Node for list
template <typename T> class Node {
private:
    T data;
    Node<T> *pnext {nullptr};
public:
    Node() = default;

    void set_pnext(Node<T>* pointer) {
        pnext = pointer;
    }

    Node<T>* get_pnext() { return pnext; }

    T* get_data_ptr() { return &(data); }

};

//Linked list with the index starting at 0
template <typename T> class List {
private:
    Node<T>* phead;
    Node<T>* ptail;
    int length;
public:
    List() : phead(nullptr), ptail(nullptr), length(0) {}


    ~List() {
        while(phead != nullptr) {
            destroy_node_at_index(0);
        }
    }

    T* find(T item) {
        T* found_node = nullptr;

        for(auto *ptr = phead; ptr != nullptr && !found_node; ptr = ptr->get_pnext()) {
            if((*(*ptr).get_data_ptr()) == item) {
                found_node = ptr->get_data_ptr();
            }
        }

        return found_node;
    }

    //creates a new node, appends it to the end of the list, updates length, ptail, & phead accordingly,
    // returns a pointer to the new data in the node
    T* append_new_node() {
        auto new_node = new Node<T>;

        if(!length) { //if length == 0
            ptail = phead = new_node;
        } else {
            ptail->set_pnext(new_node);
            ptail = ptail->get_pnext();
        }

        length += 1;

        return ptail->get_data_ptr();
    }

    //allows direct access/manipulation of whatever data at a given node is stored by returning a pointer,
    // updates length, phead, and ptail accordingly
    T* get_data_ptr_at_index(const int &index) {
        T* output = nullptr;

        if (index == length-1 || index == -1) {
            output = ptail->get_data_ptr();

        } else if (index < length && index >= 0) {
            Node<T>* pointer = phead;

            for(int i = 0; i < index; i++) { pointer = pointer->get_pnext(); }

            output = pointer->get_data_ptr();
        }

        return output;
    }

    //destroys a node given an index
    void destroy_node_at_index(const int &index) {

        //if there is only 1 node, delete it
        if (length == 1 && index == 0) {
            delete phead;
            phead = ptail = nullptr;
            length -= 1;

        } else if (index == -1) { //delete the last node
            Node<T> *ptr = this->phead;

            while(ptr->get_pnext() != this->ptail) { ptr = ptr->get_pnext(); }
            delete this->ptail;
            this->ptail = ptr;
            ptr->set_pnext(nullptr);

            this->length -= 1;

        } else if (index < length && index >= 0) { //delete any other node
            Node<T> *ptr1 = this->phead, *ptr2 = nullptr;

            for (int i = 0; i < index; i++) {
                ptr2 = ptr1;
                ptr1 = ptr1->get_pnext();
            }

            if (ptr1 == this->phead) {
                this->phead = ptr1->get_pnext();
            } else if (ptr1 == this->ptail) {
                this->ptail = ptr2;
            } else {
                ptr2->set_pnext(ptr1->get_pnext());
            }

            delete ptr1;
            this->length -= 1;
        }
    }

    //returns the current length of the list
    int get_length() { return length; }

};


#endif //PA3_LIST_H
