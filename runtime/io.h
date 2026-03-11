#pragma once
#include <iostream>

class IO{

public:

    static void out(int pin,int value){

        std::cout<<"GPIO "<<pin<<" -> "<<value<<"\n";

    }

    static int scan(int pin){

        std::cout<<"Read GPIO "<<pin<<"\n";

        return 0;

    }

};