#pragma once

#include <array>
#include <iostream>

namespace Board {
    constexpr size_t EMPTY_CELL = 0;
    constexpr size_t BOARD_SIZE = 9;
    constexpr size_t GRID_SIZE = BOARD_SIZE / 3;

    // std::array was chosen because we know the size in compile time
    using row_t = std::array<char, BOARD_SIZE>;

    // std::array was chosen because we know the size in compile time
    using board_t = std::array<row_t, BOARD_SIZE>;

    class Board {
    public:
        Board(const board_t& board);

        Board get_transposed_board() const;

        Board get_grids() const;

        row_t& row_at(const size_t row_index) {
            return board_.at(row_index);
        }

        char& elem_at(const size_t row_index, const size_t column_index) {
            return board_.at(row_index).at(column_index);
        }

        size_t board_size();

        board_t::iterator begin();
        board_t::const_iterator begin() const;

        board_t::iterator end();
        board_t::const_iterator end() const;

        friend std::ostream& operator<<(std::ostream &os, const Board &p);

    private:
        // The inner array is an array of row's elements
        // The outer array is an array of rows
        board_t board_;
    };

    std::ostream& operator<<(std::ostream &os, const Board &p);
}
