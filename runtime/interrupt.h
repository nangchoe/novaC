#pragma once
#include <iostream>

class Interrupt{

public:

    static void attach(int pin){

        std::cout<<"Interrupt attach "<<pin<<"\n";

    }

};