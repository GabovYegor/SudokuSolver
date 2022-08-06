#pragma once

#include <array>
#include <iostream>

namespace Board {
    constexpr char EMPTY_CELL = 0;
    constexpr char BOARD_SIZE = 9;
    constexpr char GRID_SIZE = BOARD_SIZE / 3;

    // std::array was chosen because we know the size in compile time
    using row_t = std::array<char, BOARD_SIZE>;

    // std::array was chosen because we know the size in compile time
    using board_t = std::array<row_t, BOARD_SIZE>;

    class Board {
    public:
        Board(const board_t& board) : board_{ board } {}

        void print() const {
            std::cout << "-------------------------------------------" << std::endl;
            for (const auto row: board_) {
                for (const auto el: row) {
                    std::cout << static_cast<int>(el) << ' ';
                }
                std::cout << std::endl;
            }
        }

        Board get_transposed_board() const {
            board_t transposed_board;
            for(size_t i = 0; i < board_.size(); ++i) {
                for(size_t j = 0; j < board_[i].size(); ++j) {
                    transposed_board[j][i] = board_[i][j];
                }
            }
            return transposed_board;
        }

        Board get_grids() const {
            board_t grids;

            for(size_t row_grid_i = 0; row_grid_i < GRID_SIZE; ++row_grid_i) {
                for(size_t column_grid_i = 0; column_grid_i < GRID_SIZE; ++column_grid_i) {
                    for (size_t i = row_grid_i * GRID_SIZE, k = 0; i < row_grid_i * GRID_SIZE + GRID_SIZE; ++i) {
                        for (size_t j = column_grid_i * GRID_SIZE; j < column_grid_i * GRID_SIZE + GRID_SIZE; ++j, ++k) {
                            grids[row_grid_i * GRID_SIZE + column_grid_i][k] = board_[i][j];
                        }
                    }
                }
            }
            return grids;
        }

        auto begin() {
            return board_.begin();
        }

        auto begin() const {
            return board_.begin();
        }

        auto end() {
            return board_.end();
        }

        auto end() const {
            return board_.end();
        }

        // The inner array is an array of row's elements
        // The outer array is an array of rows
        board_t board_;
    };
}
