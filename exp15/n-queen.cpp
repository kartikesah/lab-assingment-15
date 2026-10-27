#include <iostream>
#include <vector>
#include <string>

class NQueens {
    int n;
    std::vector<bool> cols;
    std::vector<bool> diag1; // row - col + (n - 1)
    std::vector<bool> diag2; // row + col
    std::vector<std::vector<std::string>> solutions;
    std::vector<std::string> board;

    void backtrack(int row) {
        if (row == n) {
            solutions.push_back(board);
            return;
        }

        for (int col = 0; col < n; ++col) {
            int d1 = row - col + n - 1;
            int d2 = row + col;

            // Check if the current position is under attack
            if (cols[col] || diag1[d1] || diag2[d2]) {
                continue;
            }

            // Place queen
            board[row][col] = 'Q';
            cols[col] = diag1[d1] = diag2[d2] = true;

            // Recurse to next row
            backtrack(row + 1);

            // Backtrack: remove queen
            board[row][col] = '.';
            cols[col] = diag1[d1] = diag2[d2] = false;
        }
    }

public:
    std::vector<std::vector<std::string>> solveNQueens(int n) {
        this->n = n;
        cols.assign(n, false);
        diag1.assign(2 * n - 1, false);
        diag2.assign(2 * n - 1, false);
        board.assign(n, std::string(n, '.'));
        solutions.clear();

        backtrack(0);
        return solutions;
    }
};

int main() {
    int n = 4;
    NQueens solver;
    auto solutions = solver.solveNQueens(n);

    std::cout << "Total distinct solutions for " << n << "-Queens: " << solutions.size() << "\n\n";

    for (size_t i = 0; i < solutions.size(); ++i) {
        std::cout << "Solution " << (i + 1) << ":\n";
        for (const auto& row : solutions[i]) {
            for (char cell : row) {
                std::cout << cell << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    return 0;
}