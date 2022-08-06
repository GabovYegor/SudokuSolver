#include "SudokuSolver.h"

static bool verify_sudoku_row_rule(const Board::Board &board) {
    for(const auto& row : board) {
        const auto number_of_non_empty_el = std::count_if(row.begin(), row.end(),
                                                          [](auto el){ return el != Board::EMPTY_CELL; });
        std::unordered_set<char> unique_set;
        for(const auto el : row) {
            unique_set.emplace(el);
        }
        unique_set.erase(0);
        if(unique_set.size() != number_of_non_empty_el)
            return false;
    }
    return true;
}

static bool verify_sudoku_column_rule(const Board::Board &board) {
    const auto transposed_board = board.get_transposed_board();
    return verify_sudoku_row_rule(transposed_board);
}

static bool verify_sudoku_grid_rule(const Board::Board &board) {
    // Prepare grids
    const auto board_separated_by_grids = board.get_grids();
    return verify_sudoku_row_rule(board_separated_by_grids);
}

// Verify all Sudoku rules
static bool verify_sudoku(const Board::Board &board) {
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

static bool solve_sudoku_impl(Board::Board& board) {
    for(size_t i = 0; i < board.board_.size(); ++i) {
        for (size_t j = 0; j < board.board_[i].size(); ++j) {
            if(board.board_[i][j] == Board::EMPTY_CELL) {
                for(char possible_sln = 1; possible_sln <= 9; ++possible_sln) {
                    board.board_[i][j] = possible_sln;
                    if(verify_sudoku(board)) {
                        auto res = solve_sudoku_impl(board);
                        if(!res) {
                            board.board_[i][j] = Board::EMPTY_CELL;
                        }
                        else {
                            return true;
                        }
                    }
                }
                if(!verify_sudoku(board)) {
                    board.board_[i][j] = Board::EMPTY_CELL;
                    return false;
                }
            }
        }
    }
    return true;
}

std::pair<bool, Board::Board> SudokuSolver::solve_sudoku(const Board::Board& board) {
    auto copied_board = board;
    const auto is_resolvable = solve_sudoku_impl(copied_board);
    return {is_resolvable, copied_board };
}
