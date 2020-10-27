#include <zmq.hpp>
#include <iostream>
#include <string>
#include "reading.hpp"

auto main(int argc, char *argv[]) -> int
{
    if (argc == 1)
    {
        std::cout << "Usage: watcher <target_zone>" << std::endl;
    }
    else
    {
        //  Socket to talk to client
        std::cout << "Collecting updates from weather server...\n"
                  << std::endl;

        auto target = std::string(argv[1]) + " ";

        auto context = zmq::context_t(1);
        auto subscriber = zmq::socket_t(context, zmq::socket_type::sub);
        subscriber.connect("tcp://localhost:5560");

        //  Subscribe to target
        subscriber.setsockopt(ZMQ_SUBSCRIBE, target.c_str(), target.size());

        auto idx = 1l, total_temp = 0l, total_wave = 0l;
        while (true) {
            auto update = zmq::message_t();
            subscriber.recv(update, zmq::recv_flags::none);

            auto reading = deserialize(update.to_string());

            total_temp += reading.temp;
            total_wave += reading.wave_height;

            std::cout << "[" << update.to_string() << "] "
                      << "Avg Temp: " << (total_temp / idx) << ", "
                      << "Avg Wave H.: " << (total_wave / idx) << std::endl;

            ++idx;
        }
    }

    return 0;
}
