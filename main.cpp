#include "SudokuSolver.h"

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

    Board::Board b { test_board_1 };
    auto [is_resolvable, output_board] = SudokuSolver::solve_sudoku(b);
    std::cout << output_board << std::endl;
    return 0;
}
