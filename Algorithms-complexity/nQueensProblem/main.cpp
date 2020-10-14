#include <iostream>
#include <fstream>
#include "clocker.hpp"
#include "nqcli.hpp"
#include <regex>

auto makeFile(std::string const& filename) -> std::ofstream {
    return std::ofstream (filename);
}

auto sample() -> void {
    nqueens::Board reseBoard(8);
    nqueens::seed(reseBoard, {3, 3});

    auto call = [&reseBoard]() -> bool {
        return nqueens::enhancedSolve(reseBoard);
    };

    auto timedReturn = clocker::time<bool>(call);

    if (timedReturn.first) {
        auto output = makeFile("output.board");
        std::cout << "Solution found in " << timedReturn.second.count()
                  << " seconds." << std::endl;

        nqueens::io::print(reseBoard, output);
        output << "[timedReturn]: " << timedReturn.second.count() << std::endl;
    }
    else {
        std::cout << "No solution found!" << std::endl;
    }
}

auto main() -> int {
    return nqueens::cli::main();
}
