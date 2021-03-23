#ifndef SAFEQUEUE_H
#define SAFEQUEUE_H
#include <iostream>

//очередь - необходимые методы:

//front - обращение к первому элементу очередт,
//back - обращение к последнему элементу очереди,


template <typename T>
class Queue
{
private:
    template<typename T>
    class Node
    {
        //поскольку класс находится в приватной секции другого класса
        //можно безопасно поместить в паблик секцию всю его реализацию
    public:
        Node *pNext;
        T data;

        Node(T data = T(), Node *pNext = nullptr)
        {
            this->data = data;
            this->pNext = pNext;
        }
    };

public:
    Node<T> *head;
    int nodeCounter;
    Queue();
    ~Queue();
    void push_back(T data);
    void pop_front();
    int size();
    T front();
    T back();
};

#endif // SAFEQUEUE_H
