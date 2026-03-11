pin led = gpio.13

fn main(){

loop{

    io.out(led,1)

    time.sleep(1000)

    io.out(led,0)

    time.sleep(1000)

}

}
