# SudokuSolver

## Build instruction
### 1. Get the required tools
#### 1.1. ***Git***

Any recent version will do. Install from [here](https://git-scm.com/download).

#### 1.2. ***CMake***
Minimum required version is **3.16**. Install from [here](https://cmake.org/download/).

### 2. Build (Windows / Linux)

```sh
git clone https://github.com/GabovYegor/SudokuSolver.git <SudokuSolver-source-dir>
pushd <SudokuSolver-source-dir>
git checkout main
popd
cmake -S <SudokuSolver-source-dir> -B <SudokuSolver-build-dir>
cmake --build <SudokuSolver-build-dir> --config Release
```

### 3. Run tests

You can ensure that ***SudokuSolver*** built correctly and run tests in one of the following ways:

#### 3.1. Via *Windows* CLI

Run `<SudokuSolver-build-dir>\test\Release\SudokuSolver_tests.exe`

#### 3.2. Via *Linux* CLI

Run `<SudokuSolver-build-dir>/test/Release/SudokuSolver_tests`
