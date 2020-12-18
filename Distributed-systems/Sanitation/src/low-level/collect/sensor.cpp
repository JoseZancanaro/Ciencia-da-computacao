#include <zmq.hpp>
#include <string>
#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <functional>
#include "serialize_util.hpp"

auto distribution(double mean, double sd) -> std::function<double()> {
    auto randomizer = std::default_random_engine(std::random_device{}());
    auto normal = std::normal_distribution<>(mean, sd);

    return [normal, randomizer]() mutable {
        return normal(randomizer);
    };
}

auto sensor_healthy() -> bool {
    return  (rand() % 100 + 1) >= 5 ? true : false;
}

auto main(int argc, char* argv[]) -> int {
    using namespace std::chrono_literals;
    using namespace std::string_literals;

    if (argc == 1) {
        std::cout << "Usage: sensor <id>" << std::endl;
    } 
    else {
        std::cout << "Reading sensor...\n" << std::endl;
    
        auto id = std::string(argv[1]);
        auto healthy = sensor_healthy();
        auto flow = distribution(50, 2);
        auto height = distribution(6, 1);
        auto pressure = distribution(9, 0.5);

        auto context = zmq::context_t(1);
        auto publisher = zmq::socket_t(context, zmq::socket_type::pub);
        publisher.connect("tcp://localhost:5559");

        while (true) {
            auto msg = to_serial_json(json_keys("id", "healthy", "flow", "height", "pressure"),
                                        id, healthy, flow(), height(), pressure());

            publisher.send(zmq::buffer(msg), zmq::send_flags::none);

            std::cout << msg << std::endl;
            healthy = healthy ? sensor_healthy() : false;

            std::this_thread::sleep_for(10s);
        }
    }

    return 0;
}