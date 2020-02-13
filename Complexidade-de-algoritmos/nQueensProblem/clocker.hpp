#ifndef CLOCKER_HPP
#define CLOCKER_HPP

#include <functional>
#include <chrono>

namespace clocker {
    using hr_clock = std::chrono::high_resolution_clock;

    template <typename ResultType, typename Fn>
    auto time(Fn function) -> std::pair<ResultType, std::chrono::duration<double>> {
        auto then = hr_clock::now();

        ResultType res = function();

        auto elapsed = std::chrono::duration<double>(hr_clock::now() - then);

        return std::make_pair(res, elapsed);
    }
}

#endif // CLOCKER_HPP
