#include <algorithm>
#include <unordered_set>

#include "SudokuSolver.h"

// Verify that there is no the same elements in the set (except empty cell that may repeat several times)
static bool is_set_satisfy_sudoku_rules(const Board::row_t& set) {
    const auto number_of_non_empty_el = std::count_if(set.begin(), set.end(),
                                                      [](auto el){ return el != Board::EMPTY_CELL; });
    // std::unordered_set contains only unique elements by definition
    std::unordered_set<Board::elem_t> unique_set;
    for(const auto el : set) {
        unique_set.emplace(el);
    }
    unique_set.erase(0);
    if(unique_set.size() != number_of_non_empty_el)
        return false;
    return true;
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

// Verify all Sudoku rules for one element
static bool verify_sudoku_impl(const Board::Board& board, const size_t row_index, const size_t col_index) {
    // Verify that there are no the same elements in the row
    if(!verify_sudoku_row_rule(board, row_index, col_index))
        return false;

    // Verify that there are no the same elements in the column
    if(!verify_sudoku_column_rule(board, row_index, col_index))
        return false;

    // Verify that there are no the same elements in the grid
    if(!verify_sudoku_grid_rule(board, row_index, col_index))
        return false;

    return true;
}

// Insert element at the set position and verify all sudoku rules for it
static bool verify_sudoku(const Board::Board& board, const size_t row_index,
                          const size_t col_index, const Board::elem_t new_el) {
    auto board_with_new_element = board;
    board_with_new_element.elem_at(row_index, col_index) = new_el;
    return verify_sudoku_impl(board_with_new_element, row_index, col_index);
}

// Verify sudoku rules for the element at the set position
static bool verify_sudoku(const Board::Board& board, const size_t row_index, const size_t col_index) {
    return verify_sudoku_impl(board, row_index, col_index);
}

// Verify all Sudoku rules for all elements
static bool verify_sudoku(const Board::Board& board) {
    for(size_t i = 0; i < board.board_size(); ++i) {
        for (size_t j = 0; j < board.board_size(); ++j) {
            if(!verify_sudoku(board, i, j)) {
                return false;
            }
        }
    }
    return true;
}

// Here is implementation of Sudoku solver algorithm that uses backtracking
// It works in several steps:
// 1. Find empty cell
//    If there are no empty cell go to step 4
// 2. Pick number for the cell that fulfill all Sudoku rules
//    If it's not possible to pick the number that fulfill all Sudoku rules - take a step back
//    If it's not possible to pick the number and it's not possible to take step back - go to the step 3
//    If number was picked successfully - go to the step 1
// 3. If we are on this step - this means that there are no solutions for the Sudoku.
//    In this case function return false and empty board
// 4. If we are on this step - this means that sudoku was resolved.
//    In this case function return true and the board that is a solution of the given Sudoku
static bool solve_sudoku_impl(Board::Board& board) {
    for(size_t i = 0; i < board.board_size(); ++i) {
        for (size_t j = 0; j < board.board_size(); ++j) {
            if(board.elem_at(i, j) == Board::EMPTY_CELL) {
                // Go through all possible solutions
                for(Board::elem_t possible_sln = 1; possible_sln <= 9; ++possible_sln) {
                    if(verify_sudoku(board, i, j, possible_sln)) {
                        board.elem_at(i, j) = possible_sln;
                        auto res = solve_sudoku_impl(board);
                        if(!res) {
                            board.elem_at(i, j) = Board::EMPTY_CELL;
                        }
                        else {
                            return true;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

namespace SudokuSolver {
    // Wrapper around implementation
    std::pair<bool, Board::Board> solve_sudoku(const Board::Board &board) {
        auto copied_board = board;
        auto is_resolvable = solve_sudoku_impl(copied_board);
        // To avoid edge cases (according to ideas of defensive programming)
        is_resolvable = is_resolvable && verify_sudoku(copied_board);
        // If not resolvable - return empty board
        if(!is_resolvable) {
            Board::board_t empty_board;
            for(auto& empty_row : empty_board)
                std::fill(empty_row.begin(), empty_row.end(), 0);
            return {is_resolvable, empty_board };
        }
        return {is_resolvable, copied_board};
    }
}
