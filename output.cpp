#include <stdio.h>
#include "runtime/server.h"

#include "runtime/io.h"
#include "runtime/timer.h"
#include "runtime/interrupt.h"
int main(){
Server::get("/sensor");
Server::post("/led");
Server::start(3000);
return 0;
}
