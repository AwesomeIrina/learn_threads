#include "safequeue.h"
#include <mutex>

std::mutex mtx;

template<typename T>
Queue<T>::Queue()
{
    head= nullptr;
    nodeCounter = 0;
}

template<typename T>
Queue<T>::~Queue()
{
    while(nodeCounter){
        pop_front();
    }
}

template<typename T>
void Queue<T>::push_back(T data)
{
    std::lock_guard<std::mutex> guard(mtx);
    if(head == nullptr){
        head = new Node<T>(data);
    }
    else{
        Node<T> *current = this->head;
        while(current->pNext != nullptr){
            current = current->pNext;
        }
        current->pNext = new Node<T>(data);
    }
    nodeCounter +=1;
}

template<typename T>
void Queue<T>::pop_front(){
    std::lock_guard<std::mutex> guard(mtx);
    Node<T> *tmp = head;
    head = head->pNext;
    delete tmp;
    nodeCounter -=1;
}

template<typename T>
int Queue<T>::size()
{
    std::lock_guard<std::mutex> guard(mtx);
    return nodeCounter;
}

template<typename T>
T Queue<T>::front()
{
    std::lock_guard<std::mutex> guard(mtx);
    if(head == nullptr){
        return -1;
    }
    return head->data;

}

template<typename T>
T Queue<T>::back()
{
    std::lock_guard<std::mutex> guard(mtx);
    if(head == nullptr){
        return -1;
    }
    Node<T> *current = this->head;
    while(current->pNext != nullptr){
        current = current->pNext;
    }
    return current->data;
}
