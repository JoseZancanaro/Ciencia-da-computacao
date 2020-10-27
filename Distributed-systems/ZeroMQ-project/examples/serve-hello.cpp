//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <thread>
#include <chrono>
#include <zmq.hpp>
#include <string>
#include <iostream>

auto main() -> int {
    using namespace std::chrono_literals;

    //  Prepare our context and socket
    auto context = zmq::context_t(1);
    auto socket = zmq::socket_t(context, zmq::socket_type::rep);
    socket.bind("tcp://*:5555");

    while (true) {
        auto request = zmq::message_t();

        //  Wait for next request from client
        socket.recv(request, zmq::recv_flags::none);
        std::cout << "Received " << request.to_string() << std::endl;

        //  Do some 'work'
        std::this_thread::sleep_for(1s);

        //  Send reply back to client
        socket.send(zmq::str_buffer("World"), zmq::send_flags::none);
    }

    return 0;
}