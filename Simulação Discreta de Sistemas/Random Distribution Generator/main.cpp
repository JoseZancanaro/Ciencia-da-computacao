#include <iostream>
#include <ctime>

#include "distribution.hpp"

#include <iomanip>
#include <fstream>
#include <string>

namespace test {
    namespace dst = distribution;

    const std::string prefix = "../test-output";

    template<typename F>
    auto generate(std::string filename, F d, size_t quantity = 500) -> void {
        std::ofstream file(filename);

        auto values = dst::random_interval(d, quantity);

        for (auto i : values) {
            file << std::setprecision(4) << i << std::endl;
        }

        file.close();
    }

    auto uniform() -> void {
        auto u = dst::uniform(1, 500);
        generate(prefix + "/uniform.dst", u);
    }

    auto triangular() -> void {
        auto t = dst::triangular(1, 500, 200);
        generate(prefix + "/triangular.dst", t);
    }

    auto exponential() -> void {
        auto e = dst::exponential(0.5);
        generate(prefix + "/exponential.dst", e);
    }

    auto normal() -> void {
        auto n = dst::normal(1.0, 5);
        generate(prefix + "/normal.dst", n);
    }

    auto histogram() -> void {
        auto const d = dst::normal(1.5, 15);
        auto const v = dst::random_interval(d, 500);
        auto const h = dst::histogram(v);

        std::ofstream f("histogram.csv");
        f << "bucket,count," << std::endl;

        for (auto const& i: h) {
            f << i.first << "," << i.second << std::endl;
        }

        f.close();

        std::vector<double> keys;
        std::vector<double> values;
        for (auto const& v : h) {
            keys.push_back(v.first);
            values.push_back(v.second);
        }

        auto smoothen = dst::smooth(values);

        std::map<double, double> smoothenMap;
        for(size_t i = 0; i < smoothen.size(); i++) {
            smoothenMap.insert({ keys.at(i), smoothen.at(i) });
        }

        std::ofstream sf("smoothen-histogram.csv");
        sf << "bucket,count," << std::endl;

        for (auto const& i : smoothenMap) {
            sf << i.first << "," << i.second << "," << std::endl;
        }

        sf.close();
    }

    auto main() -> int {
        srand(time(nullptr));

        uniform();
        triangular();
        exponential();
        normal();
        histogram();

        return 0;
    }
}

auto main() -> int
{
    return test::main();
}
