#include <zmq.hpp>

auto main () -> int {
    auto context = zmq::context_t(1);

    zmq::socket_t frontend(context, zmq::socket_type::sub);
    frontend.bind("tcp://*:5559");
    frontend.setsockopt(ZMQ_SUBSCRIBE, "", 0);

    zmq::socket_t backend(context, zmq::socket_type::pub);
    backend.bind("tcp://*:5560");

    zmq::proxy(zmq::socket_ref(frontend), zmq::socket_ref(backend), nullptr);

    return 0;
}
