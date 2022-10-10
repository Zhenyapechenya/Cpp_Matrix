#ifndef __S21MATRIX_H__
#define __S21MATRIX_H__

class S21Matrix {
private:
  // attributes
  int rows_, cols_; // rows and columns attributes
  double **matrix_; // pointer to the memory where the matrix will be allocated

  // help function
  void CreateMemory();

public:
  // accessors & mutators
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);

  // constructors & destructor
  S21Matrix();                   // default constructor
  S21Matrix(int rows, int cols); // parameterized constructor
  S21Matrix(const S21Matrix &o); // copy cnstructor
  S21Matrix(S21Matrix &&o);      // move cnstructor
  ~S21Matrix();                  // destructor

  // some operators overloads
  S21Matrix operator+(const S21Matrix &o);
  S21Matrix operator-(const S21Matrix &o);
  S21Matrix &operator=(const S21Matrix &o);
  S21Matrix &operator+=(const S21Matrix &o);
  S21Matrix &operator-=(const S21Matrix &o);
  bool operator==(const S21Matrix &o);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix &o);
  S21Matrix &operator*=(const double num);
  S21Matrix &operator*=(const S21Matrix &o);
  double &operator()(int row, int col);

  // some public matrix methods
  void SumMatrix(const S21Matrix &o);
  void SubMatrix(const S21Matrix &o);
  bool EqMatrix(const S21Matrix &o);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  // help functions
  bool ElemEqual(double elem1, double elem2);
  S21Matrix GetSmallMatrix(int row, int column);
};

#endif
