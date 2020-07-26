#include "MathUtils.h"
#include "MathMatrix.h"
#include "MathVector.h"
#include <iostream>
MathVector operator*(MathVector const & first_vec, MathVector const & second_vec)
{
	MathVector temp_vector(first_vec);
	temp_vector *= second_vec;
	return temp_vector;
}

MathVector operator/(MathVector const & first_vec, MathVector const & second_vec)
{
	MathVector temp_vector(first_vec);
	temp_vector /= second_vec;
	return temp_vector;
}

MathVector operator+(MathVector const & first_vec, MathVector const & second_vec)
{
	MathVector temp_vector(first_vec);
	temp_vector += second_vec;
	return temp_vector;
}

MathVector operator-(MathVector const & first_vec, MathVector const & second_vec)
{
	MathVector temp_vector(first_vec);
	temp_vector -= second_vec;
	return temp_vector;
}

MathVector operator^(MathVector const & first_vec, MathVector const & second_vec)
{
	MathVector temp_vector(first_vec);
	temp_vector ^= second_vec;
	return temp_vector;
}

bool operator==(MathVector const & first_vec, MathVector const & second_vec)
{
	return first_vec.getValues() == second_vec.getValues();
}

MathMatrix operator*(MathMatrix const & first_matr, MathMatrix const & second_matr)
{
	MathMatrix matr(first_matr);

	matr *= second_matr;

	return matr;

}

MathMatrix operator/(MathMatrix const & first_matr, MathMatrix const & second_matr)
{
	MathMatrix matr(first_matr);

	matr /= second_matr;

	return matr;

}

MathMatrix operator+(MathMatrix const & first_matr, MathMatrix const & second_matr)
{
	MathMatrix matr(first_matr);

	matr += second_matr;

	return matr;

}

MathMatrix operator-(MathMatrix const & first_matr, MathMatrix const & second_matr)
{
	MathMatrix matr(first_matr);

	matr -= second_matr;

	return matr;

}

MathMatrix operator^(MathMatrix const & first_matr, MathMatrix const & second_matr)
{
	MathMatrix matr(first_matr);

	matr ^= second_matr;

	return matr;

}

bool operator==(MathMatrix const & first_vec, MathMatrix const & second_vec)
{
	return first_vec.getValues() == second_vec.getValues();
}

double dotProduct(MathVector const & first_vec, MathVector const & second_vec)
{

	if (first_vec.size() != second_vec.size())
	{
		throw std::runtime_error("vectors with different sizes in dotProduct");
	}

	double result = 0.0;

	for (size_t i = 0; i < first_vec.size(); ++i)
	{
		result += first_vec.at(i) * second_vec.at(i);
	}

	return result;
}

MathMatrix Transpose(MathMatrix const & matrix)
{
	MathMatrix transposed_matr(matrix.columns(), matrix.rows());

	for (size_t i = 0; i < transposed_matr.rows(); ++i)
	{
		for (size_t j = 0; j < transposed_matr.columns(); ++j)
		{
			transposed_matr.at(i).at(j) = matrix.at(j).at(i);
		}
	}

	return transposed_matr;
}

MathMatrix GaussJordanElimination(MathMatrix const & matrix_of_left_sides, MathVector const & free_values)
{
	
	if (matrix_of_left_sides.rows() != free_values.size() || matrix_of_left_sides.rows() != matrix_of_left_sides.columns())
	{
		throw std::runtime_error("this system can't be solved with single solution");
	}

	MathMatrix source_matrix(matrix_of_left_sides);


	MathMatrix identity_matrix(source_matrix.rows(), source_matrix.columns());

	for (size_t i = 0; i < matrix_of_left_sides.rows(); ++i)
	{
		for (size_t j = 0; j < matrix_of_left_sides.columns(); ++j)
		{
			if (i == j)
			{
				identity_matrix.at(i).at(j) = 1;
			}
		}
	}

	MathMatrix combine_matrix(source_matrix.rows(), 2 * source_matrix.columns());
	for (size_t i = 0; i < source_matrix.rows(); ++i)
		for (size_t j = 0; j < source_matrix.columns(); ++j)
		{
			combine_matrix.at(i).at(j) = source_matrix.at(i).at(j);
			combine_matrix.at(i).at(j + source_matrix.columns()) = identity_matrix.at(i).at(j);
		}

	for (size_t k = 0; k < source_matrix.rows(); ++k) //k-number of row
	{
		for (size_t i = 0; i < 2 * source_matrix.columns(); ++i) //i-number of column
			combine_matrix.at(k).at(i) = combine_matrix.at(k).at(i) / source_matrix.at(k).at(k); //division k-row by first element !=0 for transformation into one
		for (size_t i = k + 1; i < source_matrix.rows(); ++i) //number i of the next row after k
		{
			double coefficient = combine_matrix.at(i).at(k) / combine_matrix.at(k).at(k);
			for (int j = 0; j < 2 * source_matrix.columns(); ++j)
				combine_matrix.at(i).at(j) = combine_matrix.at(i).at(j)- combine_matrix.at(k).at(j) * coefficient; //transform  elements into zero under current element
		}
		for (size_t i = 0; i < source_matrix.rows(); ++i) //Updating, making changes into source matrix
			for (size_t j = 0; j < source_matrix.columns(); ++j)
				source_matrix.at(i).at(j) = combine_matrix.at(i).at(j);
	}

	//Reverse path
	for (size_t  k = source_matrix.rows() - 1; k > -1; --k)
	{
		for (size_t i = 2 * source_matrix.columns() - 1; i > -1; --i)
			combine_matrix.at(k).at(i) = combine_matrix.at(k).at(i) / source_matrix.at(k).at(k);
		for (size_t i = k - 1; i > -1; i--)
		{
			double coefficient = combine_matrix.at(i).at(k) / combine_matrix.at(k).at(k);
			for (size_t j = 2 * source_matrix.columns() - 1; j > -1; --j)
				combine_matrix.at(i).at(j) = combine_matrix.at(i).at(j) - combine_matrix.at(k).at(j) * coefficient;
		}
	}

	
	for (size_t i = 0; i < source_matrix.rows(); ++i)
		for (size_t j = 0; j < source_matrix.columns(); ++j)
			identity_matrix.at(i).at(j) = combine_matrix.at(i).at(j + source_matrix.rows());

	return identity_matrix;
}

MathMatrix MatrixProduct(MathMatrix const & first_matr, MathMatrix const & second_matr)
{
	if (first_matr.rows() == 0 || second_matr.rows() == 0)
		return MathMatrix();
	if (first_matr.at(0).size() != second_matr.rows())
	{
		throw std::runtime_error("unnable to get matrixProduct of these matrixes (incorrect sizes)");
	}

	MathMatrix matr(first_matr.rows(), second_matr.at(0).size());
	MathMatrix second_transposed = Transpose(second_matr);

	for (size_t i = 0; i < matr.rows(); ++i)
	{
		for (size_t j = 0; j < matr.at(0).size(); ++j)
		{
			matr[i][j] = dotProduct(first_matr.at(i), Transpose(second_matr)[j]);
			//first[i] * Transpose(second[j])
		}
	}

	return matr;
}




