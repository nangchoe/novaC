#include <stdio.h>
#include "runtime/server.h"

int main(){
#include "runtime/io.h"
#include "runtime/timer.h"
#include "runtime/interrupt.h"
IO::out(13,1);
IO::out(13,1);
Timer::delay(1000);
IO::out(13,0);
IO::out(13,0);
return 0;
}
