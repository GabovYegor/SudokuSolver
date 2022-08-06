#include "Board.h"

namespace Board {
    Board::Board(const board_t &board) : board_{ board } {}

    Board Board::get_board() const {
        return board_;
    }

    Board Board::get_transposed_board() const {
        board_t transposed_board;
        for(size_t i = 0; i < board_.size(); ++i) {
            for(size_t j = 0; j < board_[i].size(); ++j) {
                transposed_board[j][i] = board_[i][j];
            }
        }
        return transposed_board;
    }

    grid_t Board::grid_at(const size_t row_index, const size_t col_index) const {
        auto rounded_row_index = row_index / GRID_SIZE * GRID_SIZE;
        auto rounded_col_index = col_index / GRID_SIZE * GRID_SIZE;

        grid_t result_grid;
        for(size_t i = rounded_row_index, k = 0; i < rounded_row_index + GRID_SIZE; ++i) {
            for(size_t j = rounded_col_index; j < rounded_col_index + GRID_SIZE; ++j, ++k) {
                result_grid[k] = board_[i][j];
            }
        }
        return result_grid;
    }

    row_t& Board::row_at(const size_t row_index) {
        return board_.at(row_index);
    }

    row_t Board::row_at(const size_t row_index) const {
        return board_.at(row_index);
    }

    char &Board::elem_at(const size_t row_index, const size_t col_index) {
        return board_.at(row_index).at(col_index);
    }

    char Board::elem_at(const size_t row_index, const size_t col_index) const {
        return board_.at(row_index).at(col_index);
    }

    Board Board::get_grids() const {
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

    size_t Board::board_size() const {
        return board_.size();
    }

    board_t::iterator Board::begin() {
        return board_.begin();
    }

    board_t::const_iterator Board::begin() const {
        return board_.begin();
    }

    board_t::iterator Board::end() {
        return board_.end();
    }

    board_t::const_iterator Board::end() const {
        return board_.end();
    }

    std::ostream& operator<<(std::ostream &os, const Board &board) {
        for (const auto row: board.board_) {
            for (const auto el: row) {
                os << static_cast<int>(el) << ' ';
            }
            os << std::endl;
        }
        return os;
    }

    bool operator==(const Board &lhs, const Board &rhs) {
       return lhs.board_ == rhs.board_;
    }
}
