#include "SudokuSolver.h"

static bool is_set_satisfy_sudoku_rules(const Board::row_t& set) {
    const auto number_of_non_empty_el = std::count_if(set.begin(), set.end(),
                                                      [](auto el){ return el != Board::EMPTY_CELL; });
    std::unordered_set<char> unique_set;
    for(const auto el : set) {
        unique_set.emplace(el);
    }
    unique_set.erase(0);
    if(unique_set.size() != number_of_non_empty_el)
        return false;
    return true;
}

static bool is_set_satisfy_sudoku_rules(const Board::Board& set) {
    for(const auto& subset : set) {
        if(!is_set_satisfy_sudoku_rules(subset)) {
            return false;
        }
    }
    return true;
}

static bool verify_sudoku_row_rule(const Board::Board& board) {
    return is_set_satisfy_sudoku_rules(board);
}

static bool verify_sudoku_column_rule(const Board::Board& board) {
    return is_set_satisfy_sudoku_rules(board.get_transposed_board());
}

static bool verify_sudoku_grid_rule(const Board::Board& board) {
    return is_set_satisfy_sudoku_rules(board.get_grids());
}

static bool verify_sudoku_row_rule(const Board::Board& board, const size_t row_index, const size_t col_index) {
    return is_set_satisfy_sudoku_rules(board.row_at(row_index));
}

static bool verify_sudoku_column_rule(const Board::Board& board, const size_t row_index, const size_t col_index) {
    return is_set_satisfy_sudoku_rules(board.get_transposed_board().row_at(col_index));
}

static bool verify_sudoku_grid_rule(const Board::Board& board, const size_t row_index, const size_t col_index) {
    return is_set_satisfy_sudoku_rules(board.grid_at(row_index, col_index));
}

// Verify all Sudoku rules
static bool verify_sudoku(const Board::Board& board) {
    // 1. Verify that there are no the same elements in the row
    if(!verify_sudoku_row_rule(board))
        return false;

    // 2. Verify that there are no the same elements in the column
    if(!verify_sudoku_column_rule(board))
        return false;

    // 3. Verify that there are no the same elements in the grid
    if(!verify_sudoku_grid_rule(board))
        return false;

    return true;
}

// Verify all Sudoku rules
static bool verify_sudoku(const Board::Board& board, const size_t row_index, const size_t col_index) {
    // 1. Verify that there are no the same elements in the row
    if(!verify_sudoku_row_rule(board, row_index, col_index))
        return false;

    // 2. Verify that there are no the same elements in the column
    if(!verify_sudoku_column_rule(board, row_index, col_index))
        return false;

    // 3. Verify that there are no the same elements in the grid
    if(!verify_sudoku_grid_rule(board, row_index, col_index))
        return false;

    return true;
}

static bool solve_sudoku_impl(Board::Board& board) {
    for(size_t i = 0; i < board.board_size(); ++i) {
        for (size_t j = 0; j < board.board_size(); ++j) {
            if(board.elem_at(i, j) == Board::EMPTY_CELL) {
                // Go through all possible solutions
                for(char possible_sln = 1; possible_sln <= 9; ++possible_sln) {
                    board.elem_at(i, j) = possible_sln;
                    if(verify_sudoku(board, i, j)) {
                        auto res = solve_sudoku_impl(board);
                        if(!res) {
                            board.elem_at(i, j) = Board::EMPTY_CELL;
                        }
                        else {
                            return true;
                        }
                    }
                }
                if(!verify_sudoku(board)) {
                    board.elem_at(i, j) = Board::EMPTY_CELL;
                    return false;
                }
            }
        }
    }
    return true;
}

namespace SudokuSolver {
    std::pair<bool, Board::Board> solve_sudoku(const Board::Board &board) {
        auto copied_board = board;
        const auto is_resolvable = solve_sudoku_impl(copied_board);
        // If not resolvable - return empty board
        if(!is_resolvable) {
            Board::board_t empty_board_t;
            for(auto& empty_row : empty_board_t)
                std::fill(empty_row.begin(), empty_row.end(), 0);
            return { is_resolvable, empty_board_t };
        }
        return {is_resolvable, copied_board};
    }
}
