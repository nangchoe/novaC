import http

pin led = gpio.13

async fn main(){

    let server = http.new(8080)

    server.get("/on",fn(req){

        io.out(led,1)

        return "on"

    })

    server.get("/off",fn(req){

        io.out(led,0)

        return "off"

    })

    server.start()

}
