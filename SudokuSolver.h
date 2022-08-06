#pragma once

#include "Board.h"

namespace SudokuSolver {
    std::pair<bool, Board::Board> solve_sudoku(const Board::Board& board);
}