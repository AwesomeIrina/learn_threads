#include <QCoreApplication>
#include <thread>
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include "safequeue.h"
#include "safequeue.cpp"
#include "QVariant"
#include <string>
#include <typeinfo>
#include <Windows.h>

void fill_array(int*&arr, int thread_num, int cell_num){
    for(int i = cell_num; i<cell_num+thread_num; i++){
        arr[i] = 20;
    }
    std::cout<<"ID-FILL_FUNC: "<<std::this_thread::get_id()<<std::endl;
}

void first_task(){
    int array_size = 0;
    std::cout<<"Input array size"<<std::endl;
    std::cin>>array_size;

    if(array_size <= 0){
        std::cout<<"There is no array to fill"<<std::endl;
        //проработай выход из проги в этом случае!!!
    }

    int *arr = new int[array_size]{};
    int thread_num = 0;
    std::cout<<"Input number of threads"<<std::endl;
    std::cin>>thread_num;

    if(array_size <= 0){
        std::cout<<"Array will fill in the main thread"<<std::endl;
    }

    //размер массива меньше количества потоков, уменьшаем количество потоков
    if(thread_num>array_size){
        while(thread_num>array_size){
            thread_num--;
        }
    }

    //запихиваем в вектор потоки, которые обрабатывают заполнение массива
    std::vector<std::thread> threads;
    int part_num = array_size/thread_num;
    int last_part = array_size%thread_num;
    int cell_num = 0;

    if(last_part != 0){
        thread_num -= 1;
        cell_num = array_size - last_part;
        threads.push_back(std::thread(fill_array, std::ref(arr), last_part, cell_num));
    }
    for(int i = 0; i<thread_num; i++){
        threads.push_back(std::thread(fill_array, std::ref(arr), part_num, cell_num));
        cell_num+=part_num;
    }



    for(auto &th : threads){
        th.join();
    }


    for(int i = 0; i<array_size; i++){
        std::cout<<"cell:"<<arr[i]<<std::endl;
    }
    std::cout<<"ID-MAIN_FUNC: "<<std::this_thread::get_id()<<std::endl;
    delete []arr;
}

void second_task()
{
    setlocale(LC_ALL, "PL_pl.UTF-8");
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);

    Queue<int> *lst = new Queue<int>;
    std::thread th([&](){
        for(int i = 13; i<30; i++){
            lst->push_back(i);
        }
    });
    int res = lst->front();
    if(res == -1){
        std::cout<<"The queue is empty"<<std::endl;
    }
    res = lst->back();
    if(res == -1){
        std::cout<<"The queue still empty"<<std::endl;
    }

    std::thread th1([&](){
        res = lst->front();
    });
    int res1;
    std::thread th2([&](){
        res1 = lst->back();
    });

    std::cout<<"front:"<<res<<std::endl;
    std::cout<<"back:"<<res1<<std::endl;
    std::cout<<"size: "<<lst->size()<<std::endl;

    std::thread th3([&](){
        lst->pop_front();
    });
    std::thread th4([&](){
        lst->push_back(7);
    });
    std::cout<<"front after pop:"<<lst->front()<<std::endl;
    std::cout<<"back after push:"<<lst->back()<<std::endl;
    std::cout<<"size after all: "<<lst->size()<<std::endl;

    th.join();
    th1.join();
    th2.join();
    th3.join();
    th4.join();
}

int main()
{
    //first_task();
    second_task();
    system("pause");
    return 0;
}
