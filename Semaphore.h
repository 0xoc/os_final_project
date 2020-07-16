#pragma once
#include <iostream>
#include <stdio.h>
#include <mutex>
#include <condition_variable>

using namespace std;

#include <mutex>
#include <condition_variable>

class Semaphore {
public:
    Semaphore(int count_ = 0)
        : count(count_)
    {
    }

    inline void signal(string msg) {
 //       cout << "signal " << msg << endl;
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
    inline void wait(string msg) {
 //       cout << "wait " << msg << endl;
        std::unique_lock<std::mutex> lock(mtx);
        while (count == 0) {
            cv.wait(lock);
        }
        count--;
    }
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;
};