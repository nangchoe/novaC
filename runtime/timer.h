#pragma once
#include <thread>
#include <chrono>

class Timer{

public:

    static void delay(int ms){

        std::this_thread::sleep_for(
            std::chrono::milliseconds(ms)
        );

    }

};