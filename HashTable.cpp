//
// Created by raz29 on 10/03/2024.
//
#ifndef HASH_TABLE_CPP
#define HASH_TABLE_CPP
#include "HashTable.h"

template<class Key , class Data>
HashTable<Key,Data>::HashTable(HashFunction functionPtr) : m_size(0) , m_table_size(INIT_SIZE)
,m_tree_table(new AvlTree<Key,Data>*[m_table_size]) ,m_hash_func(functionPtr) {
    for (int i = 0; i < m_table_size; ++i) {
        m_tree_table[i] = nullptr;
    }
}

template<class Key , class Data>
HashTable<Key,Data>::~HashTable() {
    //deletes the tree nodes not the data
    for (int i = 0; i < m_table_size; ++i) {
          if(m_tree_table[i] != nullptr){
              m_tree_table[i]->deleteTreeData(m_tree_table[i]->getRoot());//deletes the newcpp
              delete m_tree_table[i];
          }
    }
    delete[] m_tree_table;
}

template<class Key , class Data>
StatusType HashTable<Key, Data>::insert(Key& key,Data& val) {//change to bool

    if (this->search(key,val) != nullptr){
        return StatusType::FAILURE;//already exist in the data structure
    }
    if(this->m_size + 1 >= this->m_table_size * INCREASE_FACTOR){
        this->Increase_size();
    }
    int hash_index = m_hash_func(key,m_table_size);

    if(m_tree_table[hash_index] == nullptr){//no tree in slot yet
        m_tree_table[hash_index] = new AvlTree<Key,Data>();
    }

    m_tree_table[hash_index]->insert(key,val);//see what is the change in AVL
    m_size++;
    return StatusType::SUCCESS;
}

template<class Key , class Data>
const Data* HashTable<Key, Data>::search(Key& key,Data& val) {

    int hash_index = m_hash_func(key, m_table_size);
    if (m_tree_table[hash_index] == nullptr){
        return nullptr;
    }
    return m_tree_table[hash_index]->find(key) == nullptr ? nullptr : &m_tree_table[hash_index]->find(key)->getData();
}

template<class Key , class Data>
StatusType HashTable<Key, Data>::remove(Key& key,Data& val) {

    if (this->search(key,val) == nullptr){
        return StatusType::FAILURE;//doesn't exist in the data structure
    }
    int hash_index = m_hash_func(key,m_table_size);
    m_tree_table[hash_index]->remove(key);
    m_size--;
    if(m_size < m_table_size * DECREASE_FACTOR && m_table_size* DECREASE_FACTOR > MIN_SIZE){
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
    size_t newsize = m_table_size*factor;
    AvlTree<Key ,Data>** newtable = new AvlTree<Key ,Data>*[newsize];
    for (int i = 0; i < newsize; ++i) {
        newtable[i] = nullptr;
    }

    int hashed_index;
    int temp_tree_size;
    typename AvlTree<Key,Data>::Key_Data_pair** keyDataPair_array = nullptr;

    for (int i = 0; i < m_table_size && m_tree_table[i] != nullptr; ++i) {
        keyDataPair_array = m_tree_table[i]->get_tree_as_array(); //get the data from old tree in the i slot
        temp_tree_size = m_tree_table[i]->getSize();

        for (int j = 0; j < temp_tree_size; ++j) { // re-hashing the data
            hashed_index = m_hash_func(keyDataPair_array[j]->key,newsize);
            if(newtable[hashed_index] == nullptr){
                newtable[hashed_index] = new AvlTree<Key , Data>();
            }
            newtable[hashed_index]->insert(keyDataPair_array[j]->key,keyDataPair_array[j]->data);
            delete keyDataPair_array[j];
        }

        delete m_tree_table[i];//deletes old tree;
        m_tree_table[i] = nullptr;
        delete[] keyDataPair_array;
        keyDataPair_array = nullptr;
    }
    delete[] m_tree_table;
    m_table_size = newsize ;
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
#endif



