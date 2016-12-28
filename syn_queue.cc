#include "syn_queue.h"

template<class T>
void syn_queue<T>::put(const T& value) {
    std::unique_lock<std::mutex> lck{m};
    q.push(value);
    cond.notify_one();
}

template<class T>
void syn_queue<T>::put(T&& value) {
    std::unique_lock<std::mutex> lck{m};
    q.push(value);
    cond.notify_one();
}


template<class T>
void syn_queue<T>::get(T& val) {
    std::unique_lock<std::mutex> lck{m};
    while (q.empty())
        cond.wait(lck);
    val = q.front();
    q.pop();
}


