//
// Created by raz29 on 10/03/2024.
//

#ifndef WET24_TO_PUBLISH_HASHTABLE_H
#define WET24_TO_PUBLISH_HASHTABLE_H

#include "wet2util.h"
#include "AvlTree.h"

template<class Key , class Data>
class HashTable {

    //key and range : f: U -> 0,1,2,...,range-1
    typedef int (*HashFunction)(Key , int);

    int m_size;
    int m_table_size;
    HashFunction m_hash_func;
    AvlTree<Key ,Data*>** m_tree_table;//an array to tree pointer

    void Increase_size();
    void Decrease_size();
    void change_size(double factor);
public:
    explicit HashTable(HashFunction functionPtr);
    HashTable() = delete;

    ~HashTable();

    StatusType insert(Key& key,Data* val);

    Data* search(Key& key)const;

    StatusType remove(Key& key,Data* val);

    size_t get_table_size()const;

    size_t get_size()const;
};




#endif //WET24_TO_PUBLISH_HASHTABLE_H
