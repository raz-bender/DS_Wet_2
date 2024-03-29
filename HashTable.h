//
// Created by raz29 on 10/03/2024.
//

#ifndef WET24_TO_PUBLISH_HASHTABLE_H
#define WET24_TO_PUBLISH_HASHTABLE_H

#include "wet2util.h"
#include "AvlTree.h"
static int INIT_SIZE = 32;
static double INCREASE_FACTOR = 8;
static double DECREASE_FACTOR = 0.25;//1/4
static int MIN_SIZE = 8;

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

    StatusType remove(Key& key);

    size_t get_table_size()const;

    size_t get_size()const;
};



template<class Key, class Data>
HashTable<Key, Data>::HashTable(HashFunction functionPtr) : m_size(0), m_table_size(INIT_SIZE)
, m_hash_func(functionPtr), m_tree_table(new AvlTree<Key, Data*>* [m_table_size]) {
    for (int i = 0; i < m_table_size; ++i) {
        m_tree_table[i] = nullptr;
    }
}

template<class Key, class Data>
HashTable<Key, Data>::~HashTable() {
    for (int i = 0; i < m_table_size; ++i) {
        if (m_tree_table[i] != nullptr) {
            m_tree_table[i]->deleteTreeData(m_tree_table[i]->getRoot());//deletes the tree data i.e teams
            delete m_tree_table[i];
        }
    }
    delete[] m_tree_table;
}

template<class Key, class Data>
StatusType HashTable<Key, Data>::insert(Key& key, Data* val) {//change to bool

    if (this->search(key) != nullptr) {
        return StatusType::FAILURE;//already exist in the data structure
    }
    if (this->m_size + 1 >= this->m_table_size * INCREASE_FACTOR) {
        this->Increase_size();
    }
    int hash_index = m_hash_func(key, m_table_size);

    if (m_tree_table[hash_index] == nullptr) {//no tree in slot yet
        m_tree_table[hash_index] = new AvlTree<Key, Data*>();
    }

    m_tree_table[hash_index]->insert(key, val);//see what is the change in AVL
    m_size++;
    return StatusType::SUCCESS;
}

template<class Key, class Data>
Data* HashTable<Key, Data>::search(Key& key) const {

    int hash_index = m_hash_func(key, m_table_size);
    if (m_tree_table[hash_index] == nullptr) {
        return nullptr;
    }
    return m_tree_table[hash_index]->find(key) == nullptr ? nullptr : m_tree_table[hash_index]->find(key)->getData();
}

template<class Key, class Data>
StatusType HashTable<Key, Data>::remove(Key& key) {

    if (this->search(key) == nullptr) {
        return StatusType::FAILURE;//doesn't exist in the data structure
    }
    int hash_index = m_hash_func(key, m_table_size);
    m_tree_table[hash_index]->remove(key);
    m_size--;
    if (m_size < m_table_size * DECREASE_FACTOR && m_table_size * DECREASE_FACTOR > MIN_SIZE) {
        this->Decrease_size();
    }
    return StatusType::SUCCESS;
}

template<class Key, class Data>
void HashTable<Key, Data>::Increase_size() {
    change_size(INCREASE_FACTOR);
}

template<class Key, class Data>
void HashTable<Key, Data>::Decrease_size() {
    change_size(DECREASE_FACTOR);
}

template<class Key, class Data>
void HashTable<Key, Data>::change_size(const double factor) {
    int newsize = m_table_size * factor;
    AvlTree<Key, Data*>** newtable = new AvlTree<Key, Data*>*[newsize];
    for (int i = 0; i < newsize; ++i) {
        newtable[i] = nullptr;
    }

    int hashed_index;
    int temp_tree_size;
    typename AvlTree<Key, Data*>::Key_Data_pair** keyDataPair_array = nullptr;

    for (int i = 0; i < m_table_size ; ++i) {
        if(m_tree_table[i] == nullptr){
            continue;
        }
        keyDataPair_array = m_tree_table[i]->get_tree_as_array(); //get the data from old tree in the i slot
        temp_tree_size = m_tree_table[i]->getSize();

        for (int j = 0; j < temp_tree_size; ++j) { // re-hashing the data
            hashed_index = m_hash_func(keyDataPair_array[j]->key, newsize);
            if (newtable[hashed_index] == nullptr) {
                newtable[hashed_index] = new AvlTree<Key, Data*>();
            }
            newtable[hashed_index]->insert(keyDataPair_array[j]->key, keyDataPair_array[j]->data);
            delete keyDataPair_array[j];
        }

        delete m_tree_table[i];//deletes old tree;
        m_tree_table[i] = nullptr;
        delete[] keyDataPair_array;
        keyDataPair_array = nullptr;
    }
    delete[] m_tree_table;
    m_table_size = newsize;
    m_tree_table = newtable;
}
template<class Key, class Data>
size_t HashTable<Key, Data>::get_size() const {
    return m_size;
}

template<class Key, class Data>
size_t HashTable<Key, Data>::get_table_size() const {
    return m_table_size;
}


#endif //WET24_TO_PUBLISH_HASHTABLE_H
