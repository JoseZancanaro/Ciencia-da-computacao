#ifndef NQUEENS_HPP
#define NQUEENS_HPP

#include <algorithm>
#include <iostream>
#include <vector>

namespace nqueens {
    using QueenType = unsigned short int;

    const QueenType QueenPresent = 1;
    const QueenType QueenAbsent = 0;

    struct Coordinate {
        size_t x;
        size_t y;
    };

    struct Board {
        std::vector<std::vector<QueenType>> positions;
        std::vector<QueenType> queens;
        size_t queensCount;
        size_t const queensMax;

        Board(size_t queensMax)
            : positions(std::vector<std::vector<QueenType>>(queensMax, std::vector<QueenType>(queensMax, QueenAbsent))),
            queens(std::vector<QueenType>(queensMax)),
            queensCount(0),
            queensMax(queensMax){}
    };

    auto getDiagonalIndex(Coordinate const& position) -> Coordinate {
        int posX = static_cast<int>(position.x),
            posY = static_cast<int>(position.y);

        size_t x = static_cast<size_t>(std::max(posX - posY, 0));
        size_t y = static_cast<size_t>(std::max(posY - posX, 0));

        return { x, y };
    }

    auto getReverseDiagonalIndex(Coordinate const& position, size_t rowsCount) -> Coordinate {
        int posX = static_cast<int>(position.x),
            posY = static_cast<int>(position.y),
            rows = static_cast<int>(rowsCount - 1);

        size_t x = static_cast<size_t>((posX + posY) > (rows) ? posX + posY - rows : 0);
        size_t y = static_cast<size_t>(std::min(posX + posY, rows));

        return { x, y };
    }

    auto isPeaceful(Board const& board, Coordinate const& position) -> bool {
        for (size_t i = 0; i < board.queensMax; i++) {
            if ((board.positions[position.x][i] == QueenPresent) || (board.positions[i][position.y] == QueenPresent)) {
                return false;
            }
        }

        Coordinate diagonal = getDiagonalIndex(position);
        for (size_t i = diagonal.x, j = diagonal.y; i < board.queensMax; i++, j++) {
            if (board.positions[i][j] == QueenPresent) {
                return false;
            }
        }

        Coordinate reverseDiagonal = getReverseDiagonalIndex(position, board.queensMax);
        for (size_t i = reverseDiagonal.x, j = reverseDiagonal.y; i < board.queensMax && j < board.queensMax; i++, j--) {
            if (board.positions[i][j] == QueenPresent) {
                return false;
            }
        }

        return true;
    }

    auto isSolved(Board const& board) -> bool {
        return board.queensCount == board.queensMax;
    }

    auto solve(Board& board, unsigned long* counter = nullptr) -> bool {
        if (board.queensCount == board.queensMax) {
            return true;
        }

        size_t current = board.queensCount;

        for (size_t i = 0; i < board.queensMax; i++) {
            for (size_t j = 0; j < board.queensMax; j++) {
                if (counter) (*counter)++;
                if (isPeaceful(board, { i, j })) {
                    board.positions[i][j] = QueenPresent;
                    board.queensCount = current + 1;

                    if (solve(board, counter)) {
                        return true;
                    }

                    board.positions[i][j] = QueenAbsent;
                    board.queensCount = current;
                }
            }
        }

        return false;
    }

    auto enhancedSolve(Board& board, size_t step = 0, unsigned long* counter = nullptr) -> bool {
        if (board.queensCount == board.queensMax) {
            return true;
        }

        if (board.queens[step] == QueenAbsent) {
            size_t current = board.queensCount;

            for (size_t i = 0; i < board.queensMax; i++) {
                if (counter) (*counter)++;
                if (isPeaceful(board, { i, step })) {
                    board.positions[i][step] = QueenPresent;
                    board.queens[step] = QueenPresent;
                    board.queensCount = current + 1;

                    if (enhancedSolve(board, step + 1, counter)) {
                        return true;
                    }

                    board.positions[i][step] = QueenAbsent;
                    board.queens[step] = QueenAbsent;
                    board.queensCount = current;
                }
            }
        }
        else {
            return enhancedSolve(board, step + 1, counter);
        }

        return false;
    }

    auto seed(Board& board, Coordinate const& position) -> bool {
        if (board.queensCount < board.queensMax
            && isPeaceful(board, position)
            && board.positions[position.x][position.y] == QueenAbsent) {
            board.positions[position.x][position.y] = QueenPresent;
            board.queens[position.y] = QueenPresent;
            board.queensCount++;
            return true;
        }
        return false;
    }

    /* Input/Output */
    namespace io {

        /* Write to ostream, defaults to std::cout */
        auto print(Board const& board, std::ostream &os = std::cout) -> void {
            for (size_t i = 0; i < board.queensMax; i++) {
                for (size_t j = 0 ; j < board.queensMax - 1; j++) {
                    os << board.positions[i][j] << " ";
                }
                os << board.positions[i][board.queensMax - 1] << std::endl;
            }
        }

    }
}

#endif // NQUEENS_HPP
