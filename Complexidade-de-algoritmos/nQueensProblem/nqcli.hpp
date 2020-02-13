#ifndef NQCLI_H
#define NQCLI_H

#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include "nqueens.hpp"
#include "clocker.hpp"

/* Interactive Nqueens CLI application */

namespace nqueens {
namespace cli {
    struct NQAppMemory;

    using MatchCommand = std::pair<std::regex, std::function<bool(NQAppMemory &, std::smatch const&)>>;

    struct NQAppMemory {
        std::vector<MatchCommand> commands;
        std::map<std::string, nqueens::Board> boards;
    };

    namespace impl {
        auto board(NQAppMemory & nqApp, std::smatch const& input) -> bool {
            std::string boardName = input.str(3);
            size_t n = static_cast<size_t>(std::stoi(input.str(5)));

            if (nqApp.boards.find(boardName) == nqApp.boards.end()
                    && n > 0) {
                nqApp.boards.insert({ boardName, nqueens::Board(n) });
            }
            else {
                std::cout << "Error: Board exists or zero size informed." << std::endl;
            }

            return true;
        }

        auto copy(NQAppMemory & nqApp, std::smatch const& input) -> bool {
            std::string from = input.str(3);
            std::string into = input.str(5);

                if (nqApp.boards.find(from) != nqApp.boards.end()
                        && nqApp.boards.find(into) == nqApp.boards.end()) {
                    nqueens::Board copied = nqApp.boards.at(from);
                    nqApp.boards.insert({ into, copied });
                }
                else {
                    std::cout << "Error: Board exists or zero size informed." << std::endl;
                }

                return true;
            }

            auto seed(NQAppMemory & nqApp, std::smatch const& input) -> bool {
                std::string boardName = input.str(3);

                if (nqApp.boards.find(boardName) != nqApp.boards.end()) {
                    auto & board = nqApp.boards.at(boardName);
                    size_t i = static_cast<size_t>(std::stoi(input.str(5)));
                    size_t j = static_cast<size_t>(std::stoi(input.str(7)));

                    if (i < board.queensMax && j < board.queensMax
                            && nqueens::seed(board, { i, j })) {
                        nqueens::io::print(nqApp.boards.at(boardName));
                    }
                    else {
                        std::cout << "Error: Board doesn't exist, i and/or j are bigger than queensMax, board is solved or the seed is bad." << std::endl;
                    }
                }

                return true;
            }

            auto print(NQAppMemory & nqApp, std::smatch const& input) -> bool {
                std::string boardName = input.str(3);

                if (nqApp.boards.find(boardName) != nqApp.boards.end()) {
                    nqueens::io::print(nqApp.boards.at(boardName));
                    if (input.size() == 7) {
                        std::ofstream os (input.str(6));
                        nqueens::io::print(nqApp.boards.at(boardName), os);
                    }
                    else {
                        nqueens::io::print(nqApp.boards.at(boardName));
                    }
                }
                else {
                    std::cout << "Error: Board doesn't exist." << std::endl;
                }

                return true;
            }

            auto solve(NQAppMemory & nqApp, std::smatch const& input) -> bool {
                std::string boardName = input.str(3);

                if (nqApp.boards.find(boardName) != nqApp.boards.end()) {
                    auto & board = nqApp.boards.at(boardName);
                    auto counter = new unsigned long;
                    *counter = 0;

                    if (!nqueens::isSolved(board)) {
                        auto call = [&board, &counter]() -> bool {
                            return nqueens::solve(board, counter);
                        };

                        auto timedReturn = clocker::time<bool>(call);

                        std::cout << "[Solve Time]: " << timedReturn.second.count()
                                  << " seconds." << std::endl
                                  << "[No. Ops   ]: " << *counter << std::endl;

                        if (timedReturn.first) {
                            nqueens::io::print(board);
                        } else {
                            std::cout << "Cannot be solved" << std::endl;
                        }
                    }
                    else {
                        std::cout << "Error: Board is already solved." << std::endl;
                    }
                }
                else {
                    std::cout << "Error: Board doesn't exist." << std::endl;
                }

                return true;
            }

            auto solvePlus(NQAppMemory & nqApp, std::smatch const& input) -> bool {
                std::string boardName = input.str(3);

                if (nqApp.boards.find(boardName) != nqApp.boards.end()) {
                    auto & board = nqApp.boards.at(boardName);
                    auto counter = new unsigned long;
                    *counter = 0;

                    if (!nqueens::isSolved(board)) {
                        auto call = [&board, &counter]() -> bool {
                            return nqueens::enhancedSolve(board, 0, counter);
                        };

                        auto timedReturn = clocker::time<bool>(call);

                        std::cout << "[Solve Time]: " << timedReturn.second.count()
                                  << " seconds." << std::endl
                                  << "[No. Ops   ]: " << *counter << std::endl;

                        if (timedReturn.first) {
                            nqueens::io::print(board);
                        } else {
                            std::cout << "Cannot be solved." << std::endl;
                        }
                    }
                    else {
                        std::cout << "Error: Board is already solved." << std::endl;
                    }
                }
                else {
                    std::cout << "Error: Board doesn't exist." << std::endl;
                }

                return true;
            }

            auto quit(NQAppMemory &, std::smatch const&) -> bool {
                return false;
            }

            auto clear(NQAppMemory &, std::smatch const&) -> bool {
                std::system("clear");
                return true;
            }
        }

        auto addCommand(NQAppMemory & nqApp, MatchCommand const& command) -> void {
            nqApp.commands.push_back(command);
        }

        auto fetchCommand(NQAppMemory & nqApp, std::string input) -> bool {
            if (!input.empty()) {
                std::smatch match;

                for (auto command : nqApp.commands) {
                    try {
                        if (std::regex_match(input, match, command.first)) {
                            return command.second(nqApp, match);
                        }
                    }  catch (std::exception & e) {
                        std::cout << "Unknown. " << e.what() << std::endl;
                        return true;
                    }
                }

                std::cout << "Unknown command." << std::endl;
            }

            return true;
        }

        /**
          board s n
          copy s s
          seed s n n
          print s
          solve s
          solve+ s
          quit
        */
        auto populateCommands(NQAppMemory & nqApp) -> void {
            std::vector<std::regex> regexes {
                std::regex{"(board)( )([a-z]+[a-z0-9]*)( )([0-9]+)"},
                std::regex{"(copy)( )([a-z]+[a-z0-9]*)( )([a-z]+[a-z0-9]*)"},
                std::regex{"(seed)( )([a-z]+[a-z0-9]*)( )([0-9]+)( )([0-9]+)"},
                std::regex{"(print)( )([a-z]+[a-z0-9]*)(( )([a-z]+[a-z0-9]*))?"},
                std::regex{"(solve)( )([a-z]+[a-z0-9]*)"},
                std::regex{"(solve\\+)( )([a-z]+[a-z0-9]*)"},
                std::regex{"(quit)"},
                std::regex{"(clear)"},
            };

            std::vector<std::function<bool(NQAppMemory &, std::smatch const&)>> functions {
                impl::board, impl::copy, impl::seed, impl::print, impl::solve, impl::solvePlus, impl::quit, impl::clear
            };

            size_t commandsCount = regexes.size();

            if (commandsCount <= functions.size()) {
                for (size_t i = 0; i < commandsCount; i++) {
                    addCommand(nqApp, { regexes.at(i), functions.at(i) });
                }
            }
        }

        auto main() -> int {
            NQAppMemory nqApp;
            populateCommands(nqApp);

            std::string input;

            do {
                std::cout << "> ";
                std::getline(std::cin, input);
            } while (fetchCommand(nqApp, input));

            return 0;
        }
    }
}

#endif // NQCLI_H
