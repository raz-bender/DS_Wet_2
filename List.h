//
// Created by raz29 on 09/03/2024.
//

#ifndef WET24_TO_PUBLISH_LIST_H
#define WET24_TO_PUBLISH_LIST_H
template<class T>
struct Node{
    T data;
    Node* next;
};

template<class T>
class List{
private:
    Node<T>* m_head;

public:
    List():m_head(nullptr){}

    ~List() {
        Node<T> *current = m_head;
        Node<T> *next = nullptr;
        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }
        m_head = nullptr;
    }
    void Delete_list_and_Data(bool is_array = false){
        Node<T> *current = m_head;
        Node<T> *next = nullptr;
        while (current != nullptr) {
            next = current->next;
            if (is_array){
             delete[] current->data;
            }else{
                delete current->data;
            }
            delete current;
            current = next;
        }
        m_head = nullptr;
    }

    void addNode(const T& value) {
        Node<T> *newNode = new Node<T>;
        newNode->data = value;
        newNode->next = m_head;
        m_head = newNode;
    }

};


#endif //WET24_TO_PUBLISH_LIST_H
