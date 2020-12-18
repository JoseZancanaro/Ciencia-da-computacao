#include <zmq.hpp>
#include <iostream>

auto main() -> int {
    
    auto context = zmq::context_t(1);

    auto frontend = zmq::socket_t(context, zmq::socket_type::sub);
    frontend.bind("tcp://*:5559");
    frontend.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    auto backend = zmq::socket_t(context, zmq::socket_type::pub);
    backend.bind("tcp://*:5560");
    
    /*
    while (true) {
        auto msg = zmq::message_t();
        frontend.recv(msg, zmq::recv_flags::none);

        std::cout << msg.to_string() << std::endl;
        
        backend.send(msg, zmq::send_flags::none);
    }
    */

    zmq::proxy(zmq::socket_ref(frontend), zmq::socket_ref(backend), nullptr);

    return 0;
}