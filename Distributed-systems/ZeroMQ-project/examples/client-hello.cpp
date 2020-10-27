//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>

int main ()
{
    //  Prepare our context and socket
    auto context = zmq::context_t(1);
    auto socket = zmq::socket_t(context, zmq::socket_type::req);

    std::cout << "Connecting to hello world server..." << std::endl;
    socket.connect("tcp://localhost:5555");

    //  Do 10 requests, waiting each time for a response
    for (int request_n = 0; request_n != 10; request_n++) {
        std::cout << "Sending Hello " << request_n << "..." << std::endl;
        socket.send(zmq::str_buffer("Hello"), zmq::send_flags::none);

        //  Get the reply.
        auto reply = zmq::message_t();
        socket.recv(reply, zmq::recv_flags::none);

        std::cout << "Received " << reply.to_string() << " " << request_n << std::endl;
    }

    return 0;
}