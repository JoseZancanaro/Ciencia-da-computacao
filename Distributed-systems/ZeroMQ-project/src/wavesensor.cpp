#include <zmq.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include "reading.hpp"

auto main(int argc, char* argv[]) -> int {
    using namespace std::chrono_literals;

    if (argc == 1) {
        std::cout << "Usage: wavesensor <target_zone>" << std::endl;
    } 
    else {
        //  Socket to talk to server
        std::cout << "Reading wavesensor...\n" << std::endl;
    
        auto target = std::string(argv[1]);

        //  Prepare our context and publisher
        auto context = zmq::context_t(1);
        auto publisher = zmq::socket_t(context, zmq::socket_type::pub);
        publisher.connect("tcp://localhost:5559");

        while (true) {
            auto reading = make_random_reading(target);
            auto msg = serialize(reading);

            //  Send message to all subscribers
            publisher.send(zmq::buffer(msg), zmq::send_flags::none);

            std::this_thread::sleep_for(400ms);
        }
    }

    return 0;
}