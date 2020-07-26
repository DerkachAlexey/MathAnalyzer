#pragma once
class MathVector;
class MathMatrix;
	
MathVector operator * (MathVector const & first_vec, MathVector const & second_vec);
MathVector operator / (MathVector const & first_vec, MathVector const & second_vec);
MathVector operator + (MathVector const & first_vec, MathVector const & second_vec);
MathVector operator - (MathVector const & first_vec, MathVector const & second_vec);
MathVector operator ^ (MathVector const & first_vec, MathVector const & second_vec);
bool	   operator == (MathVector const & first_vec, MathVector const & second_vec);
double dotProduct(MathVector const & first_vec, MathVector const & second_vec);

MathMatrix operator * (MathMatrix const & first_matr, MathMatrix const & second_matr);
MathMatrix operator / (MathMatrix const & first_matr, MathMatrix const & second_matr);
MathMatrix operator + (MathMatrix const & first_matr, MathMatrix const & second_matr);
MathMatrix operator - (MathMatrix const & first_matr, MathMatrix const & second_matr);
MathMatrix operator ^ (MathMatrix const & first_matr, MathMatrix const & second_matr);
bool	   operator == (MathMatrix const & first_matr, MathMatrix const & second_matr);
MathMatrix MatrixProduct(MathMatrix const & first_matr, MathMatrix const & second_matr);

MathMatrix Transpose(MathMatrix const & matrix);

MathMatrix GaussJordanElimination(MathMatrix const & matrix_of_equations, MathVector const & free_values);