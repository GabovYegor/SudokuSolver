#pragma once

#include <array>
#include <iostream>

namespace Board {
    using elem_t = uint8_t;

    constexpr elem_t EMPTY_CELL = 0;
    constexpr size_t BOARD_SIZE = 9;
    constexpr size_t GRID_SIZE = BOARD_SIZE / 3;

    // std::array was chosen because we know the size in compile time
    using row_t = std::array<elem_t, BOARD_SIZE>;
    using column_t = row_t;
    using grid_t = row_t;

    // std::array was chosen because we know the size in compile time
    using board_t = std::array<row_t, BOARD_SIZE>;

    class Board {
    public:
        Board(const board_t& board);

        Board get_board() const;

        Board get_transposed_board() const;

        grid_t grid_at(const size_t row_index, const size_t col_index) const;

        row_t& row_at(const size_t row_index);

        row_t row_at(const size_t row_index) const;

        elem_t& elem_at(const size_t row_index, const size_t col_index);

        elem_t elem_at(const size_t row_index, const size_t col_index) const;

        size_t board_size() const;

        board_t::iterator begin();
        board_t::const_iterator begin() const;

        board_t::iterator end();
        board_t::const_iterator end() const;

        friend std::ostream& operator<<(std::ostream &os, const Board &p);
        friend bool operator==(const Board& lhs, const Board& rhs);

    private:
        // The inner array is an array of row's elements
        // The outer array is an array of rows
        board_t board_;
    };

    std::ostream& operator<<(std::ostream &os, const Board &p);

    bool operator==(const Board& lhs, const Board& rhs);
}
