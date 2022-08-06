#include <gtest/gtest.h>

#include "SudokuSolver.h"

struct TestInputData {
    Board::Board initial_board;
    bool expected_result;
    Board::Board expected_board;
};

class SudokuSolverDataDrivenTest : public testing::TestWithParam<TestInputData> {};

// Tests payload
TEST_P(SudokuSolverDataDrivenTest, _) {
    const auto board_copy = GetParam().initial_board;
    auto [is_resolvable, output_board] = SudokuSolver::solve_sudoku(GetParam().initial_board);

    EXPECT_TRUE(GetParam().expected_result == is_resolvable);
    EXPECT_TRUE(GetParam().initial_board == board_copy);
    EXPECT_TRUE(GetParam().expected_board == output_board);

    std::cout << output_board << std::endl;
}

// Edge case tests
namespace EmptyBoardRegressionTest
{
    const Board::Board initial_board =
        Board::board_t { Board::row_t{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        };

    const bool expected_result = true;

    const Board::Board expected_board =
        Board::board_t { Board::row_t { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                         { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
                         { 7, 8, 9, 1, 2, 3, 4, 5, 6 },
                         { 2, 1, 4, 3, 6, 5, 8, 9, 7 },
                         { 3, 6, 5, 8, 9, 7, 2, 1, 4 },
                         { 8, 9, 7, 2, 1, 4, 3, 6, 5 },
                         { 5, 3, 1, 6, 4, 2, 9, 7, 8 },
                         { 6, 4, 2, 9, 7, 8, 5, 3, 1 },
                         { 9, 7, 8, 5, 3, 1, 6, 4, 2 },
        };

    INSTANTIATE_TEST_SUITE_P(EmptyBoardRegressionTest,
                             SudokuSolverDataDrivenTest,
                             testing::Values(TestInputData{initial_board, expected_result, expected_board}));
}

namespace OneElementExistsRegressionTest
{
    const Board::Board initial_board =
        Board::board_t { Board::row_t{ 1, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                         { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        };

    const bool expected_result = true;

    const Board::Board expected_board =
        Board::board_t { Board::row_t { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                         { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
                         { 7, 8, 9, 1, 2, 3, 4, 5, 6 },
                         { 2, 1, 4, 3, 6, 5, 8, 9, 7 },
                         { 3, 6, 5, 8, 9, 7, 2, 1, 4 },
                         { 8, 9, 7, 2, 1, 4, 3, 6, 5 },
                         { 5, 3, 1, 6, 4, 2, 9, 7, 8 },
                         { 6, 4, 2, 9, 7, 8, 5, 3, 1 },
                         { 9, 7, 8, 5, 3, 1, 6, 4, 2 },
        };

    INSTANTIATE_TEST_SUITE_P(OneElementExistsRegressionTest,
                             SudokuSolverDataDrivenTest,
                             testing::Values(TestInputData{initial_board, expected_result, expected_board}));
}

namespace FullFillBoardRegressionTest
{
    const Board::Board initial_board =
        Board::board_t { Board::row_t { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                         { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
                         { 7, 8, 9, 1, 2, 3, 4, 5, 6 },
                         { 2, 1, 4, 3, 6, 5, 8, 9, 7 },
                         { 3, 6, 5, 8, 9, 7, 2, 1, 4 },
                         { 8, 9, 7, 2, 1, 4, 3, 6, 5 },
                         { 5, 3, 1, 6, 4, 2, 9, 7, 8 },
                         { 6, 4, 2, 9, 7, 8, 5, 3, 1 },
                         { 9, 7, 8, 5, 3, 1, 6, 4, 2 },
        };

    const bool expected_result = true;

    const Board::Board expected_board =
        Board::board_t { Board::row_t { 1, 2, 3, 4, 5, 6, 7, 8, 9 },
                         { 4, 5, 6, 7, 8, 9, 1, 2, 3 },
                         { 7, 8, 9, 1, 2, 3, 4, 5, 6 },
                         { 2, 1, 4, 3, 6, 5, 8, 9, 7 },
                         { 3, 6, 5, 8, 9, 7, 2, 1, 4 },
                         { 8, 9, 7, 2, 1, 4, 3, 6, 5 },
                         { 5, 3, 1, 6, 4, 2, 9, 7, 8 },
                         { 6, 4, 2, 9, 7, 8, 5, 3, 1 },
                         { 9, 7, 8, 5, 3, 1, 6, 4, 2 },
        };

    INSTANTIATE_TEST_SUITE_P(FullFillBoardRegressionTest,
                             SudokuSolverDataDrivenTest,
                             testing::Values(TestInputData{initial_board, expected_result, expected_board}));
}

// Negative tests
namespace IncorrectBoardRegressionTest
{
    const Board::Board initial_board =
            Board::board_t { Board::row_t{ 1, 1, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            };

    const bool expected_result = false;

    const Board::Board expected_board =
            Board::board_t { Board::row_t{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                             { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
            };

    INSTANTIATE_TEST_SUITE_P(IncorrectBoardRegressionTest,
                             SudokuSolverDataDrivenTest,
                             testing::Values(TestInputData{initial_board, expected_result, expected_board}));
}

// Positive tests
namespace EasyBoard_RegressionTest
{
    const Board::Board initial_board =
        Board::board_t { Board::row_t{ 0, 1, 3, 8, 0, 0, 4, 0, 5 },
                                     { 0, 2, 4, 6, 0, 5, 0, 0, 0 },
                                     { 0, 8, 7, 0, 0, 0, 9, 3, 0 },
                                     { 4, 9, 0, 3, 0, 6, 0, 0, 0 },
                                     { 0, 0, 1, 0, 0, 0, 5, 0, 0 },
                                     { 0, 0, 0, 7, 0, 1, 0, 9, 3 },
                                     { 0, 6, 9, 0, 0, 0, 7, 4, 0 },
                                     { 0, 0, 0, 2, 0, 7, 6, 8, 0 },
                                     { 1, 0, 2, 0, 0, 8, 3, 5, 0 },
        };

    const bool expected_result = true;

    const Board::Board expected_board =
            Board::board_t { Board::row_t{ 6, 1, 3, 8, 7, 9, 4, 2, 5 },
                                         { 9, 2, 4, 6, 3, 5, 1, 7, 8 },
                                         { 5, 8, 7, 1, 2, 4, 9, 3, 6 },
                                         { 4, 9, 8, 3, 5, 6, 2, 1, 7 },
                                         { 7, 3, 1, 9, 8, 2, 5, 6, 4 },
                                         { 2, 5, 6, 7, 4, 1, 8, 9, 3 },
                                         { 8, 6, 9, 5, 1, 3, 7, 4, 2 },
                                         { 3, 4, 5, 2, 9, 7, 6, 8, 1 },
                                         { 1, 7, 2, 4, 6, 8, 3, 5, 9 },
            };

    INSTANTIATE_TEST_SUITE_P(EasyBoard_RegressionTest,
                             SudokuSolverDataDrivenTest,
                             testing::Values(TestInputData{initial_board, expected_result, expected_board}));
}

namespace ComplexBoard_RegressionTest
{
    const Board::Board initial_board =
            Board::board_t { Board::row_t{ 0, 0, 2, 0, 0, 0, 0, 4, 1 },
                             { 0, 0, 0, 0, 8, 2, 0, 7, 0 },
                             { 0, 0, 0, 0, 4, 0, 0, 0, 9 },
                             { 2, 0, 0, 0, 7, 9, 3, 0, 0 },
                             { 0, 1, 0, 0, 0, 0, 0, 8, 0 },
                             { 0, 0, 6, 8, 1, 0, 0, 0, 4 },
                             { 1, 0, 0, 0, 9, 0, 0, 0, 0 },
                             { 0, 6, 0, 4, 3, 0, 0, 0, 0 },
                             { 8, 5, 0, 0, 0, 0, 4, 0, 0 },
            };

    const bool expected_result = true;

    const Board::Board expected_board =
            Board::board_t { Board::row_t{ 6, 3, 2, 9, 5, 7, 8, 4, 1 },
                             { 4, 9, 1, 6, 8, 2, 5, 7, 3 },
                             { 7, 8, 5, 3, 4, 1, 2, 6, 9 },
                             { 2, 4, 8, 5, 7, 9, 3, 1, 6 },
                             { 3, 1, 9, 2, 6, 4, 7, 8, 5 },
                             { 5, 7, 6, 8, 1, 3, 9, 2, 4 },
                             { 1, 2, 4, 7, 9, 5, 6, 3, 8 },
                             { 9, 6, 7, 4, 3, 8, 1, 5, 2 },
                             { 8, 5, 3, 1, 2, 6, 4, 9, 7 },
            };

    INSTANTIATE_TEST_SUITE_P(ComplexBoard_RegressionTest,
                             SudokuSolverDataDrivenTest,
                             testing::Values(TestInputData{initial_board, expected_result, expected_board}));
}