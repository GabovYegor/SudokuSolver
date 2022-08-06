#include <algorithm>
#include <numeric>
#include <unordered_set>

#include "Board.h"

bool verify_sudoku_row_rule(const Board::Board& board) {
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

bool verify_sudoku_column_rule(const Board::Board& board) {
    const auto transposed_board = board.get_transposed_board();
    return verify_sudoku_row_rule(transposed_board);
}

bool verify_sudoku_grid_rule(const Board::Board& board) {
    // Prepare grids
    const auto board_separated_by_grids = board.get_grids();
    return verify_sudoku_row_rule(board_separated_by_grids);
}

bool verify_sudoku(const Board::Board& board) {
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

bool solve_sudoku(Board::Board& board) {
    for(size_t i = 0; i < board.board_.size(); ++i) {
        for (size_t j = 0; j < board.board_[i].size(); ++j) {
            if(board.board_[i][j] == Board::EMPTY_CELL) {
                for(char possible_sln = 1; possible_sln <= 9; ++possible_sln) {
                    board.board_[i][j] = possible_sln;
                    if(verify_sudoku(board)) {
                        auto res = solve_sudoku(board);
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

int main() {
    Board::board_t test_board_1 = {
            Board::row_t{ 0, 1, 3, 8, 0, 0, 4, 0, 5 },
                        { 0, 2, 4, 6, 0, 5, 0, 0, 0 },
                        { 0, 8, 7, 0, 0, 0, 9, 3, 0 },
                        { 4, 9, 0, 3, 0, 6, 0, 0, 0 },
                        { 0, 0, 1, 0, 0, 0, 5, 0, 0 },
                        { 0, 0, 0, 7, 0, 1, 0, 9, 3 },
                        { 0, 6, 9, 0, 0, 0, 7, 4, 0 },
                        { 0, 0, 0, 2, 0, 7, 6, 8, 0 },
                        { 1, 0, 2, 0, 0, 8, 3, 5, 0 },
    };

    Board::board_t test_board_2 = {
            Board::row_t{ 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                        { 7, 8, 9, 1, 2, 3, 4, 5, 6 },
                        { 4, 5, 6, 9, 8, 7, 1, 2, 3 },
                        { 3, 1, 2, 8, 4, 5, 9, 6, 7 },
                        { 9, 6, 7, 3, 1, 2, 8, 4, 5 },
                        { 8, 4, 5, 6, 7, 9, 3, 1, 2 },
                        { 2, 3, 1, 5, 9, 4, 6, 7, 8 },
                        { 6, 7, 8, 2, 3, 1, 5, 9, 4 },
                        { 5, 9, 4, 7, 6, 8, 2, 3, 1 },
    };

    Board::board_t test_board_3 = {
            Board::row_t{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                        { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    Board::Board b { test_board_3 };
    solve_sudoku(b);
    b.print();
    return 0;
}
