#include "s21_matrix_oop.h"
#include "gtest/gtest.h"

// for (int i = 0; i < a.GetRows(); ++i) {
//     for (int j = 0; j < a.GetCols(); ++j) {
//         std::cout << a(i + 1, j + 1);
//     }
// }

// accessors & mutators

TEST(AccessorMutator, GetRowsTest) {
  S21Matrix a(3, 4);
  EXPECT_EQ(a.GetRows(), 3);
}
TEST(AccessorMutator, GetColsTest) {
  S21Matrix a(3, 4);
  EXPECT_EQ(a.GetCols(), 4);
}
TEST(AccessorMutator, SetRowsOne) {
  S21Matrix a(1, 1);
  a(1, 1) = 6;
  a.SetRows(2);
  ASSERT_FLOAT_EQ(6, a(1, 1));
  ASSERT_FLOAT_EQ(0, a(2, 1));
}
TEST(AccessorMutator, SetRowsTwo) {
  S21Matrix a(4, 3);
  a.SetRows(3);
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_FALSE(a.GetRows() == 4);
}
TEST(AccessorMutator, SetColsOne) {
  S21Matrix a(1, 1);
  a(1, 1) = 6;
  a.SetCols(2);
  ASSERT_FLOAT_EQ(6, a(1, 1));
  ASSERT_FLOAT_EQ(0, a(1, 2));
}
TEST(AccessorMutator, SetColsTwo) {
  S21Matrix a(3, 4);
  a.SetCols(3);
  a(3, 3) = 6;
  EXPECT_EQ(a.GetCols(), 3);
  EXPECT_FALSE(a.GetCols() == 4);
  ASSERT_FLOAT_EQ(6, a(3, 3));
}

// constructors & destructor

TEST(ConstructorDestructor, Base) {
  S21Matrix a;
  EXPECT_EQ(a.GetRows(), 3);
  EXPECT_EQ(a.GetCols(), 3);
  for (auto i = 1; i <= 3; ++i) {
    for (auto j = 1; j <= 3; ++j) {
      EXPECT_TRUE(a(i, j) == 0.0);
    }
  }
}
TEST(ConstructorDestructor, Parameters) {
  S21Matrix a(23, 45);
  EXPECT_EQ(a.GetRows(), 23);
  EXPECT_EQ(a.GetCols(), 45);
  for (auto i = 1; i <= 23; ++i) {
    for (auto j = 1; j <= 45; ++j) {
      EXPECT_TRUE(a(i, j) == 0.0);
    }
  }
}
TEST(ConstructorDestructor, Copy) {
  S21Matrix a(23, 45);
  for (int i = 1; i <= 23; ++i) {
    for (int j = 1; j <= 45; ++j) {
      a(i, j) = i * j;
    }
  }
  S21Matrix b(a);
  EXPECT_EQ(b.GetRows(), 23);
  EXPECT_EQ(b.GetCols(), 45);
  for (auto i = 1; i <= 23; ++i) {
    for (auto j = 1; j <= 45; ++j) {
      EXPECT_TRUE(b(i, j) == i * j);
    }
  }
}
TEST(ConstructorDestructor, Move) {
  S21Matrix a(23, 45);
  for (int i = 1; i <= 23; ++i) {
    for (int j = 1; j <= 45; ++j) {
      a(i, j) = i * j;
    }
  }
  S21Matrix b(std::move(a));
  EXPECT_EQ(b.GetRows(), 23);
  EXPECT_EQ(b.GetCols(), 45);
  for (auto i = 1; i <= 23; ++i) {
    for (auto j = 1; j <= 45; ++j) {
      EXPECT_TRUE(b(i, j) == i * j);
    }
  }
  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetCols(), 0);
  // EXPECT_THROW(a(1, 1), std::out_of_range);
}
TEST(ConstructorDestructor, Destructor) {
  S21Matrix a(23, 45);
  a.~S21Matrix();
  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetCols(), 0);
}

// operators overload

TEST(OperatorsOverload, Equal) {
  S21Matrix a(3, 4);
  S21Matrix b(3, 4);
  S21Matrix c(3, 33);
  EXPECT_TRUE(a == b);
  EXPECT_FALSE(a == c);
}
TEST(OperatorsOverload, Ravno) {
  S21Matrix a(3, 3);
  S21Matrix c(3, 33);
  a = c;
  EXPECT_TRUE(a == c);
}
TEST(OperatorsOverload, PlusOne) {
  S21Matrix a(22, 32);
  S21Matrix b(24, 43);
  // EXPECT_THROW(a + b, std::out_of_range);
}
TEST(OperatorsOverload, PlusTwo) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a(1, 1) = 2.4;
  a(1, 2) = 5.8;
  a(2, 1) = 3.2;
  a(2, 2) = 333.89;
  b(1, 1) = 3.6;
  b(1, 2) = -5.8;
  b(2, 1) = 3.8;
  b(2, 2) = -0.89;
  c(1, 1) = 6;
  c(1, 2) = 0;
  c(2, 1) = 7;
  c(2, 2) = 333;
  ASSERT_TRUE(a + b == c);
}
TEST(OperatorsOverload, PlusThree) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  for (int i = 1; i <= 2; ++i) {
    for (int j = 1; j <= 2; ++j) {
      a(i, j) = i * j * 6.6;
      b(i, j) = i * j * 7.7;
      c(i, j) = i * j * (6.6 + 7.7);
    }
  }
  ASSERT_TRUE(a + b == c);
}
TEST(OperatorsOverload, MinusOne) {
  S21Matrix a(22, 32);
  S21Matrix b(24, 43);
  // EXPECT_THROW(a - b, std::out_of_range);
}
TEST(OperatorsOverload, MinusTwo) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a(1, 1) = 2.4;
  a(1, 2) = 5.8;
  a(2, 1) = 3.2;
  a(2, 2) = 333.89;
  b(1, 1) = 3.6;
  b(1, 2) = -5.8;
  b(2, 1) = 3.8;
  b(2, 2) = -0.89;
  c(1, 1) = -1.2;
  c(1, 2) = 11.6;
  c(2, 1) = -0.6;
  c(2, 2) = 334.78;
  ASSERT_TRUE(a - b == c);
}
TEST(OperatorsOverload, MinusThree) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  for (int i = 1; i <= 2; ++i) {
    for (int j = 1; j <= 2; ++j) {
      a(i, j) = i * j * 6.6;
      b(i, j) = i * j * 7.7;
      c(i, j) = i * j * (6.6 - 7.7);
    }
  }
  ASSERT_TRUE(a - b == c);
}
TEST(OperatorsOverload, PlusEqualOne) {
  S21Matrix a(22, 32);
  S21Matrix b(24, 43);
  // EXPECT_THROW(a += b, std::out_of_range);
}
TEST(OperatorsOverload, PlusEqualTwo) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a(1, 1) = 2.4;
  a(1, 2) = 5.8;
  a(2, 1) = 3.2;
  a(2, 2) = 333.89;
  b(1, 1) = 3.6;
  b(1, 2) = -5.8;
  b(2, 1) = 3.8;
  b(2, 2) = -0.89;
  c(1, 1) = 6;
  c(1, 2) = 0;
  c(2, 1) = 7;
  c(2, 2) = 333;
  a += b;
  ASSERT_TRUE(a == c);
}
TEST(OperatorsOverload, PlusEqualThree) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  for (int i = 1; i <= 2; ++i) {
    for (int j = 1; j <= 2; ++j) {
      a(i, j) = i * j * 6.6;
      b(i, j) = i * j * 7.7;
      c(i, j) = i * j * (6.6 + 7.7);
    }
  }
  a += b;
  ASSERT_TRUE(a == c);
}
TEST(OperatorsOverload, MinusEqualOne) {
  S21Matrix a(22, 32);
  S21Matrix b(24, 43);
  // EXPECT_THROW(a -= b, std::out_of_range);
}
TEST(OperatorsOverload, MinusEqualTwo) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  a(1, 1) = 2.4;
  a(1, 2) = 5.8;
  a(2, 1) = 3.2;
  a(2, 2) = 333.89;
  b(1, 1) = 3.6;
  b(1, 2) = -5.8;
  b(2, 1) = 3.8;
  b(2, 2) = -0.89;
  c(1, 1) = -1.2;
  c(1, 2) = 11.6;
  c(2, 1) = -0.6;
  c(2, 2) = 334.78;
  a -= b;
  ASSERT_TRUE(a == c);
}
TEST(OperatorsOverload, MinusEqualThree) {
  S21Matrix a(2, 2);
  S21Matrix b(2, 2);
  S21Matrix c(2, 2);
  for (int i = 1; i <= 2; ++i) {
    for (int j = 1; j <= 2; ++j) {
      a(i, j) = i * j * 6.6;
      b(i, j) = i * j * 7.7;
      c(i, j) = i * j * (6.6 - 7.7);
    }
  }
  a -= b;
  ASSERT_TRUE(a == c);
}
TEST(OperatorsOverload, MultNumberOne) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      a(i, j) = 2;
      b(i, j) = 2 * 3.14;
    }
  }
  S21Matrix c = a * 3.14;
  ASSERT_TRUE(c == b);
}
TEST(OperatorsOverload, MulNumberTwo) {
  S21Matrix e(2, 2);
  S21Matrix f(2, 2);
  e(1, 1) = 10;
  e(1, 2) = 8;
  e(2, 1) = 6;
  e(2, 2) = 4;
  f(1, 1) = -5;
  f(1, 2) = -4;
  f(2, 1) = -3;
  f(2, 2) = -2;
  S21Matrix c = e * -0.5;
  ASSERT_TRUE(c == f);
}
TEST(OperatorsOverload, MulMatrixOne) {
  S21Matrix a(3, 9);
  S21Matrix b(3, 9);
  // EXPECT_THROW(a * b, std::out_of_range);
}
TEST(OperatorsOverload, MulMatrixTwo) {
  S21Matrix a(2, 4);
  S21Matrix b(4, 1);
  S21Matrix c(2, 1);
  a(1, 1) = 1.0;
  a(1, 2) = 2;
  a(1, 3) = 3;
  a(1, 4) = 4;
  a(2, 1) = 5;
  a(2, 2) = 6;
  a(2, 3) = 7;
  a(2, 4) = -8;
  b(1, 1) = 10;
  b(2, 1) = 9;
  b(3, 1) = 8;
  b(4, 1) = -7;
  c(1, 1) = 24;
  c(2, 1) = 216;
  S21Matrix d = a * b;
  ASSERT_TRUE(d == c);
}
TEST(OperatorsOverload, MulMatrixThree) {
  S21Matrix a(5, 4);
  S21Matrix b(4, 4);
  S21Matrix c(5, 4);
  a(1, 1) = 2.987654;
  a(1, 2) = -5.3456;
  a(2, 1) = 6.23;
  a(2, 2) = -3.9292;
  b(1, 1) = 4.838;
  b(1, 2) = 8.0987;
  b(1, 3) = 8.09;
  b(1, 4) = -987;
  b(2, 1) = -8;
  b(2, 2) = -0.921;
  b(2, 3) = -0.91;
  b(2, 4) = 21;
  c(1, 1) = 57.219070052;
  c(1, 2) = 29.1194110498;
  c(1, 3) = 29.03461686;
  c(1, 4) = -3061.072098;
  c(2, 1) = 61.57434;
  c(2, 2) = 54.0736942;
  c(2, 3) = 53.976272;
  c(2, 4) = -6231.5232;
  S21Matrix d = a * b;
  ASSERT_TRUE(d == c);
}
TEST(OperatorsOverload, MultNumberEqualOne) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      a(i, j) = 2;
      b(i, j) = 2 * 3.14;
    }
  }
  a *= 3.14;
  ASSERT_TRUE(a == b);
}
TEST(OperatorsOverload, MulNumberEqualTwo) {
  S21Matrix e(2, 2);
  S21Matrix f(2, 2);
  e(1, 1) = 10;
  e(1, 2) = 8;
  e(2, 1) = 6;
  e(2, 2) = 4;
  f(1, 1) = -5;
  f(1, 2) = -4;
  f(2, 1) = -3;
  f(2, 2) = -2;
  e *= -0.5;
  ASSERT_TRUE(e == f);
}
TEST(OperatorsOverload, MulMatrixEqualOne) {
  S21Matrix a(3, 9);
  S21Matrix b(3, 9);
  // EXPECT_THROW(a *= b, std::out_of_range);
}
TEST(OperatorsOverload, MulMatrixEqualTwo) {
  S21Matrix a(2, 4);
  S21Matrix b(4, 1);
  S21Matrix c(2, 1);
  a(1, 1) = 1.0;
  a(1, 2) = 2;
  a(1, 3) = 3;
  a(1, 4) = 4;
  a(2, 1) = 5;
  a(2, 2) = 6;
  a(2, 3) = 7;
  a(2, 4) = -8;
  b(1, 1) = 10;
  b(2, 1) = 9;
  b(3, 1) = 8;
  b(4, 1) = -7;
  c(1, 1) = 24;
  c(2, 1) = 216;
  a *= b;
  ASSERT_TRUE(a == c);
}
TEST(OperatorsOverload, MulMatrixEqualThree) {
  S21Matrix a(5, 4);
  S21Matrix b(4, 4);
  S21Matrix c(5, 4);
  a(1, 1) = 2.987654;
  a(1, 2) = -5.3456;
  a(2, 1) = 6.23;
  a(2, 2) = -3.9292;
  b(1, 1) = 4.838;
  b(1, 2) = 8.0987;
  b(1, 3) = 8.09;
  b(1, 4) = -987;
  b(2, 1) = -8;
  b(2, 2) = -0.921;
  b(2, 3) = -0.91;
  b(2, 4) = 21;
  c(1, 1) = 57.219070052;
  c(1, 2) = 29.1194110498;
  c(1, 3) = 29.03461686;
  c(1, 4) = -3061.072098;
  c(2, 1) = 61.57434;
  c(2, 2) = 54.0736942;
  c(2, 3) = 53.976272;
  c(2, 4) = -6231.5232;
  a *= b;
  ASSERT_TRUE(a == c);
}
TEST(OperatorsOverload, IndexOne) {
  S21Matrix a(5, 5);
  // EXPECT_THROW(a(5, 7), std::out_of_range);
  // EXPECT_THROW(a(8, 3), std::out_of_range);
  // EXPECT_THROW(a(5, -5), std::out_of_range);
  // EXPECT_THROW(a(-5, 1), std::out_of_range);
  // EXPECT_THROW(a(0, 5), std::out_of_range);
  // EXPECT_THROW(a(2, 0), std::out_of_range);
}
TEST(OperatorsOverload, IndexTwo) {
  S21Matrix a(34, 36);
  a(21, 21) = 21;
  ASSERT_TRUE(a(21, 21) == 21);
}

// matrix operations

TEST(MatrixOperations, Equal) {
  S21Matrix a(3, 4);
  S21Matrix b(3, 4);
  S21Matrix c(3, 33);
  EXPECT_TRUE(a.EqMatrix(b));
  EXPECT_FALSE(a.EqMatrix(c));
}
TEST(MatrixOperations, SumOne) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix c(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      a(i, j) = i * j * 2;
      b(i, j) = i * j * 3;
      c(i, j) = i * j * (2 + 3);
    }
  }
  a.SumMatrix(b);
  ASSERT_TRUE(a == c);
}
TEST(MatrixOperations, SumTwo) {
  S21Matrix a(3, 3);
  S21Matrix d(2, 3);
  // EXPECT_THROW(a.SumMatrix(d), std::out_of_range);
}
TEST(MatrixOperations, SumThree) {
  S21Matrix e(2, 2);
  S21Matrix f(2, 2);
  S21Matrix g(2, 2);
  e(1, 1) = 1;
  e(1, 2) = 2;
  e(2, 1) = 3;
  e(2, 2) = 4;
  f(1, 1) = 5;
  f(1, 2) = 6;
  f(2, 1) = 7;
  f(2, 2) = -4;
  g(1, 1) = 6;
  g(1, 2) = 8;
  g(2, 1) = 10;
  g(2, 2) = 0;
  e.SumMatrix(f);
  ASSERT_TRUE(e == g);
}
TEST(MatrixOperations, SubOne) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  S21Matrix c(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      a(i, j) = i * j * 2;
      b(i, j) = i * j * 3;
      c(i, j) = i * j * (2 - 3);
    }
  }
  a.SubMatrix(b);
  ASSERT_TRUE(a == c);
}
TEST(MatrixOperations, SubTwo) {
  S21Matrix a(3, 3);
  S21Matrix d(2, 3);
  // EXPECT_THROW(a.SubMatrix(d), std::out_of_range);
}
TEST(MatrixOperations, SubThree) {
  S21Matrix e(2, 2);
  S21Matrix f(2, 2);
  S21Matrix g(2, 2);
  e(1, 1) = 10;
  e(1, 2) = 8;
  e(2, 1) = 6;
  e(2, 2) = 4;
  f(1, 1) = 5;
  f(1, 2) = 6;
  f(2, 1) = 7;
  f(2, 2) = -4;
  g(1, 1) = 5;
  g(1, 2) = 2;
  g(2, 1) = -1;
  g(2, 2) = 8;
  e.SubMatrix(f);
  ASSERT_TRUE(e == g);
}
TEST(MatrixOperations, MulNumberOne) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  for (int i = 1; i <= 3; ++i) {
    for (int j = 1; j <= 3; ++j) {
      a(i, j) = 2;
      b(i, j) = 2 * 3.14;
    }
  }
  a.MulNumber(3.14);
  ASSERT_TRUE(a == b);
}
TEST(MatrixOperations, MulNumberTwo) {
  S21Matrix e(2, 2);
  S21Matrix f(2, 2);
  e(1, 1) = 10;
  e(1, 2) = 8;
  e(2, 1) = 6;
  e(2, 2) = 4;
  f(1, 1) = -5;
  f(1, 2) = -4;
  f(2, 1) = -3;
  f(2, 2) = -2;
  e.MulNumber(-0.5);
  ASSERT_TRUE(e == f);
}
TEST(MatrixOperations, MulMatrixOne) {
  S21Matrix a(3, 9);
  S21Matrix b(3, 9);
  // EXPECT_THROW(a.MulMatrix(b), std::out_of_range);
}
TEST(MatrixOperations, MulMatrixTwo) {
  S21Matrix a(2, 4);
  S21Matrix b(4, 1);
  S21Matrix c(2, 1);
  a(1, 1) = 1.0;
  a(1, 2) = 2;
  a(1, 3) = 3;
  a(1, 4) = 4;
  a(2, 1) = 5;
  a(2, 2) = 6;
  a(2, 3) = 7;
  a(2, 4) = -8;
  b(1, 1) = 10;
  b(2, 1) = 9;
  b(3, 1) = 8;
  b(4, 1) = -7;
  c(1, 1) = 24;
  c(2, 1) = 216;
  a.MulMatrix(b);
  ASSERT_TRUE(a == c);
}
TEST(MatrixOperations, MulMatrixThree) {
  S21Matrix a(5, 4);
  S21Matrix b(4, 4);
  S21Matrix c(5, 4);
  a(1, 1) = 2.987654;
  a(1, 2) = -5.3456;
  a(2, 1) = 6.23;
  a(2, 2) = -3.9292;
  b(1, 1) = 4.838;
  b(1, 2) = 8.0987;
  b(1, 3) = 8.09;
  b(1, 4) = -987;
  b(2, 1) = -8;
  b(2, 2) = -0.921;
  b(2, 3) = -0.91;
  b(2, 4) = 21;
  c(1, 1) = 57.219070052;
  c(1, 2) = 29.1194110498;
  c(1, 3) = 29.03461686;
  c(1, 4) = -3061.072098;
  c(2, 1) = 61.57434;
  c(2, 2) = 54.0736942;
  c(2, 3) = 53.976272;
  c(2, 4) = -6231.5232;
  a.MulMatrix(b);
  ASSERT_TRUE(a == c);
}
TEST(MatrixOperations, TransposeOne) {
  S21Matrix a(2, 4);
  S21Matrix b(4, 2);
  a(1, 1) = 1.0;
  a(1, 2) = -2.1;
  a(1, 3) = 3.2;
  a(1, 4) = -4.3;
  a(2, 1) = 5.4;
  a(2, 2) = -6.5;
  a(2, 3) = 7.6;
  a(2, 4) = -8.9;
  b(1, 1) = 1.0;
  b(1, 2) = 5.4;
  b(2, 1) = -2.1;
  b(2, 2) = -6.5;
  b(3, 1) = 3.2;
  b(3, 2) = 7.6;
  b(4, 1) = -4.3;
  b(4, 2) = -8.9;
  S21Matrix c(a.Transpose());
  ASSERT_TRUE(c == b);
}
TEST(MatrixOperations, TransposeTwo) {
  S21Matrix a(2, 4);
  S21Matrix b(4, 2);
  S21Matrix c(a.Transpose());
  ASSERT_TRUE(c == b);
}
TEST(MatrixOperations, CalcComplementsOne) {
  S21Matrix a(2, 4);
  // ASSERT_THROW(a.CalcComplements(), std::out_of_range);
}
TEST(MatrixOperations, CalcComplementsTwo) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(1, 1) = 1;
  a(1, 2) = 2;
  a(1, 3) = 3;
  a(2, 1) = 0;
  a(2, 2) = 4;
  a(2, 3) = 2;
  a(3, 1) = 5;
  a(3, 2) = 2;
  a(3, 3) = 1;
  b(1, 1) = 0;
  b(1, 2) = 10;
  b(1, 3) = -20;
  b(2, 1) = 4;
  b(2, 2) = -14;
  b(2, 3) = 8;
  b(3, 1) = -8;
  b(3, 2) = -2;
  b(3, 3) = 4;
  S21Matrix c(std::move(a.CalcComplements()));
  ASSERT_TRUE(c == b);
}
TEST(MatrixOperations, CalcComplementsThree) {
  S21Matrix a(1, 1);
  ASSERT_TRUE(a.CalcComplements()(1, 1) == 1.0);
}
TEST(MatrixOperations, DeterminantOne) {
  S21Matrix a(23, 3);
  // ASSERT_THROW(a.Determinant(), std::out_of_range);
}
TEST(MatrixOperations, DeterminantTwo) {
  S21Matrix a(1, 1);
  a(1, 1) = 9;
  ASSERT_NEAR(a.Determinant(), 9, 1e-7);
}
TEST(MatrixOperations, DeterminantThree) {
  S21Matrix a(2, 2);
  a(1, 1) = 3;
  a(1, 2) = -7;
  a(2, 1) = 5.6;
  a(2, 2) = -0.45;
  ASSERT_NEAR(a.Determinant(), 37.85, 1e-7);
}
TEST(MatrixOperations, DeterminantFour) {
  S21Matrix a(4, 4);
  ASSERT_NEAR(a.Determinant(), 0.0, 1e-7);
}
TEST(MatrixOperations, DeterminantFive) {
  S21Matrix a(4, 4);
  a(1, 1) = 11.1;
  a(1, 2) = 2.2;
  a(1, 3) = 3.3;
  a(1, 4) = 4.4;
  a(2, 1) = 8.8;
  a(2, 2) = -9.9;
  a(2, 3) = 10.1;
  a(2, 4) = 11.11;
  a(3, 1) = 15.15;
  a(3, 2) = 16.16;
  a(3, 3) = 17.17;
  a(3, 4) = 18.18;
  a(4, 1) = -22.22;
  a(4, 2) = 23.23;
  a(4, 3) = 24.24;
  a(4, 4) = 25.25;
  ASSERT_NEAR(a.Determinant(), -11770.2443124, 1e-7);
}
TEST(MatrixOperations, InverseOne) {
  S21Matrix a(4, 4);
  // ASSERT_THROW(a.InverseMatrix(), std::out_of_range);
}
TEST(MatrixOperations, InverseTwo) {
  S21Matrix a(2, 4);
  // ASSERT_THROW(a.InverseMatrix(), std::out_of_range);
}
TEST(MatrixOperations, InverseThree) {
  S21Matrix a(3, 3);
  S21Matrix b(3, 3);
  a(1, 1) = 2;
  a(1, 2) = 1.3;
  a(1, 3) = 0.7;
  a(2, 1) = -1;
  a(2, 2) = 0;
  a(2, 3) = 3;
  a(3, 1) = 0.3;
  a(3, 2) = -0.3;
  a(3, 3) = 2;
  b(1, 1) = 45.0 / 289.0;
  b(1, 2) = -281.0 / 578.0;
  b(1, 3) = 195.0 / 289.0;
  b(2, 1) = 145.0 / 289.0;
  b(2, 2) = 379.0 / 578.0;
  b(2, 3) = -335.0 / 289.0;
  b(3, 1) = 15.0 / 289.0;
  b(3, 2) = 99.0 / 578.0;
  b(3, 3) = 65.0 / 289.0;
  S21Matrix c(a.InverseMatrix());
  ASSERT_TRUE(c == b);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}