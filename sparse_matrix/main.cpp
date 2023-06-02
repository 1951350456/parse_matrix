#include <bits/stdc++.h>

using namespace std;

class SparseMatrix {
public:
    int rows;
    int cols;
    vector<vector<int>> data;

    SparseMatrix(int r, int c) {
        rows = r;
        cols = c;
    }

    void add(const SparseMatrix& other) {
        if (rows != other.rows || cols != other.cols) {
            cout << "Error" << endl;
            return;
        }
        vector<vector<int>> result;
        int i = 0, j = 0;
        while (i < data.size() && j < other.data.size()) {
            if (data[i][0] == other.data[j][0] && data[i][1] == other.data[j][1]) {
                int value = data[i][2] + other.data[j][2];
                if (value != 0) {
                    result.push_back({data[i][0], data[i][1], value});
                }
                i++;
                j++;
            } else if (data[i][0] < other.data[j][0] || (data[i][0] == other.data[j][0] && data[i][1] < other.data[j][1])) {
                result.push_back(data[i]);
                i++;
            } else {
                result.push_back(other.data[j]);
                j++;
            }
        }
        while (i < data.size()) {
            result.push_back(data[i]);
            i++;
        }
        while (j < other.data.size()) {
            result.push_back(other.data[j]);
            j++;
        }
        data = result;
    }

    void multiply(const SparseMatrix& other) {
        if (cols != other.rows) {
            cout << "Error" << endl;
            return;
        }
        vector<vector<int>> result;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                int value = 0;
                for (int k = 0; k < cols; k++) {
                    int a = getValue(i, k);
                    int b = other.getValue(k, j);
                    value += a * b;
                }
                if (value != 0) {
                    result.push_back({i, j, value});
                }
            }
        }
        data = result;
        cols = other.cols;
    }

    int getValue(int row, int col) const {
        for (int i = 0; i < data.size(); i++) {
            if (data[i][0] == row && data[i][1] == col) {
                return data[i][2];
            }
        }
        return 0;
    }
};

int main() {
    SparseMatrix matrix1(3, 3);
    matrix1.data = {{0, 0, 1}, {0, 2, 2}, {1, 1, 3}, {2, 0, 4}, {2, 2, 5}};
    SparseMatrix matrix2(3, 3);
    matrix2.data = {{0, 1, 2}, {1, 2, 3}, {2, 0, 4}};
    matrix1.add(matrix2);
    cout << "matrix1 + matrix2:" << endl;
    for (int i = 0; i < matrix1.rows; i++) {
        for (int j = 0; j < matrix1.cols; j++) {
            cout << matrix1.getValue(i, j) << " ";
        }
        cout << endl;
    }
    SparseMatrix matrix3(3, 2);
    matrix3.data = {{0, 0, 1}, {0, 1, 2}, {1, 0, 3}, {2, 1, 4}};
    SparseMatrix matrix4(2, 3);
    matrix4.data = {{0, 1, 2}, {1, 0, 3}, {1, 2, 4}};
    matrix3.multiply(matrix4);
    cout << "matrix3 * matrix4:" << endl;
    for (int i = 0; i < matrix3.rows; i++) {
        for (int j = 0; j < matrix3.cols; j++) {
            cout << matrix3.getValue(i, j) << " ";
        }
        cout << endl;
    }
    return 0;
}
