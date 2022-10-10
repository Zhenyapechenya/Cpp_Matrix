#include "s21_matrix_oop.h"
#include <cmath>
#include <iostream>

// accessors & mutators

int S21Matrix::GetRows() const { return rows_; }
int S21Matrix::GetCols() const { return cols_; }
void S21Matrix::SetRows(int rows) {
  S21Matrix result(rows, cols_);
  for (auto i = 0; i < rows; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      if (i >= rows_) {
        result.matrix_[i][j] = 0;
      } else {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = result;
}

void S21Matrix::SetCols(int cols) {
  S21Matrix result(rows_, cols);
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols; ++j) {
      if (j >= cols_) {
        result.matrix_[i][j] = 0;
      } else {
        result.matrix_[i][j] = matrix_[i][j];
      }
    }
  }
  *this = result;
}

// constructors & destructor

S21Matrix::S21Matrix() {
  rows_ = cols_ = 3;
  CreateMemory();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMemory();
}

S21Matrix::S21Matrix(const S21Matrix &o) : S21Matrix(o.rows_, o.cols_) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = o.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&o) : S21Matrix(o) { o.~S21Matrix(); }
S21Matrix::~S21Matrix() {
  if (matrix_) {
    for (int i = 0; i < rows_; ++i) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
  }
  rows_ = 0;
  cols_ = 0;
}

// operators overload

S21Matrix &S21Matrix::operator=(const S21Matrix &o) {
  if (this != &o) {
    this->~S21Matrix();
    cols_ = o.cols_;
    rows_ = o.rows_;
    CreateMemory();
  }
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = o.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix S21Matrix::operator+(const S21Matrix &o) {
  S21Matrix result = *this;
  result.SumMatrix(o);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &o) {
  S21Matrix result = *this;
  result.SubMatrix(o);
  return result;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &o) {
  SumMatrix(o);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &o) {
  SubMatrix(o);
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &o) { return EqMatrix(o); }
S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix result = *this;
  result.MulNumber(num);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &o) {
  S21Matrix result = *this;
  result.MulMatrix(o);
  return result;
}

S21Matrix &S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &o) {
  MulMatrix(o);
  return *this;
}

double &S21Matrix::operator()(int row, int col) {
  if (row < 1 || row > rows_ || col < 1 || col > cols_) {
    throw std::out_of_range("Incorrect input, index is out of range");
  }
  return matrix_[row - 1][col - 1];
}

// matrix operations

void S21Matrix::SumMatrix(const S21Matrix &o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] + o.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &o) {
  if (rows_ != o.rows_ || cols_ != o.cols_) {
    throw std::out_of_range(
        "Incorrect input, matrices should have the same size");
  }
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] - o.matrix_[i][j];
    }
  }
}

bool S21Matrix::EqMatrix(const S21Matrix &o) {
  if ((rows_ == o.rows_) && (cols_ == o.cols_)) {
    int flag = 0;
    for (auto i = 0; i < rows_; ++i) {
      for (auto j = 0; j < cols_; ++j) {
        if (ElemEqual(matrix_[i][j], o.matrix_[i][j])) {
          flag++;
        }
      }
    }
    return flag == rows_ * cols_;
  } else {
    return false;
  }
}

void S21Matrix::MulNumber(const double num) {
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      matrix_[i][j] = matrix_[i][j] * num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &o) {
  if (cols_ != o.rows_) {
    throw std::out_of_range("Incorrect input, число столбцов первой матрицы не "
                            "равно числу строк второй матрицы");
  }
  S21Matrix temp(rows_, o.cols_);
  for (auto i = 0; i < temp.rows_; ++i) {
    for (auto j = 0; j < temp.cols_; ++j) {
      temp.matrix_[i][j] = 0.0;
      for (auto k = 0; k < cols_; k++) {
        temp.matrix_[i][j] =
            temp.matrix_[i][j] + matrix_[i][k] * o.matrix_[k][j];
      }
    }
  }
  *this = temp;
}

S21Matrix S21Matrix::Transpose() { // Создает новую транспонированную матрицу из
                                   // текущей и возвращает ее
  S21Matrix result(cols_, rows_);
  for (auto i = 0; i < rows_; ++i) {
    for (auto j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::out_of_range("Incorrect input, матрица не является квадратной");
  }
  double determinant = 0;
  if (rows_ == 1) {
    determinant = matrix_[0][0];
  } else if (rows_ == 2) {
    determinant = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    int degree = 1;
    for (auto i = 0; i < rows_; ++i) {
      S21Matrix newMatrix = GetSmallMatrix(i, 0);
      determinant =
          determinant + degree * matrix_[i][0] * newMatrix.Determinant();
      degree = -degree;
    }
  }
  return determinant;
}

S21Matrix
S21Matrix::CalcComplements() { // Вычисляет матрицу алгебраических дополнений
  // текущей матрицы и возвращает ее
  if (rows_ != cols_) {
    throw std::out_of_range("Incorrect input, матрица не является квадратной "
                            "или состоит из одного элемента");
  }
  S21Matrix result = *this;
  if (rows_ == 1) {
    result.matrix_[0][0] = 1.0;
  } else {
    for (auto i = 0; i < rows_; ++i) {
      for (auto j = 0; j < cols_; ++j) {
        S21Matrix newMatrix = GetSmallMatrix(i, j);
        result.matrix_[i][j] = newMatrix.Determinant() * pow(-1, i + j + 2);
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  double det = Determinant();
  if (fabs(det) < 1e-7) {
    throw std::out_of_range("Incorrect input, определитель матрицы равен 0 или "
                            "NAN или матрица не квадратная");
  }
  // S21Matrix one = CalcComplements();
  // S21Matrix two = one.Transpose();
  // two *= (1.0 / det);

  S21Matrix one = CalcComplements().Transpose();
  one *= (1.0 / det);

  return one;
}

// help functions

void S21Matrix::CreateMemory() {
  matrix_ = new double *[rows_];
  for (auto i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{};
  }
}

bool S21Matrix::ElemEqual(double elem1, double elem2) {
  return fabs(elem1 - elem2) < 1e-7;
}

S21Matrix S21Matrix::GetSmallMatrix(int row, int column) {
  S21Matrix smallMatrix(rows_ - 1, cols_ - 1);
  int rowOffset = 0;
  for (auto i = 0; i < smallMatrix.rows_; ++i) {
    if (i == row) {
      rowOffset = 1;
    }
    int colOffset = 0;
    for (auto j = 0; j < smallMatrix.cols_; ++j) {
      if (j == column) {
        colOffset = 1;
      }
      smallMatrix.matrix_[i][j] = matrix_[i + rowOffset][j + colOffset];
    }
  }
  return smallMatrix;
}

// // S21Matrix m1(2, 5);
// // S21Matrix m(m1);
// // S21Matrix m3 = m1;
// // S21Matrix m2(std::move(m1));