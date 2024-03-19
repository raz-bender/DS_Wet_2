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
    Node<T>* m_tail;

public:
    List():m_head(nullptr) , m_tail(nullptr){}

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
        if(m_tail == nullptr){
            m_tail = newNode;
        }
    }

    T& pop(){
        T& rtn = m_head->data;
        Node<T>* newHead = m_head->next;
        delete m_head;
        m_head = newHead;
        if (newHead == nullptr){
            m_tail = nullptr;
        }
        return rtn;
    }
    T& get_head(){
        return m_head->data;
    }
    void set_head(Node<T>* node){
        m_head = node;
    }
    /// connects list2 such that list 2 is at the head
    /// \param list2
    void connect_list(List<T>& list2){
        list2.m_tail->next = this->m_head;
        this->m_head = list2.m_head;
        if (!this->m_tail){
            m_tail = list2.m_tail;
        }
    }
    void print(){
        auto temp = m_head;
        while (temp != nullptr){
            temp->data->print();
            temp = temp->next;
        }
    }

};


#endif //WET24_TO_PUBLISH_LIST_H
