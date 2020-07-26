#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include "../catch2.hpp"
#include "MathVector.h"
#include "MathUtils.h"
#include "MathMatrix.h"

TEST_CASE("Check math vector operators")
{

	SECTION("different sizes")
	{
		MathVector vect({ 3.0,4.1,5.2 });

		vect += std::vector<double>({ 7.6,1.2 });
		REQUIRE(vect.getValues() == std::vector<double>{ 3.0, 4.1, 5.2 });

	}
	SECTION("Check +=")
	{
		MathVector vect({ 3.0,4.1,5.2 });
		vect += std::vector<double>({3.3,7.6,1.2});
		REQUIRE(vect.getValues() == std::vector<double>{6.3, 11.7, 6.4});
	}

	SECTION("Check -=")
	{
		MathVector vect({ 3.0,4.1,5.2 });
		vect -= std::vector<double>({ 3.3,7.6,1.2 });

		std::vector<double>b{ 3.0, 4.1, 5.2 };
		std::vector<double>c{ 3.3,7.6,1.2 };

		std::transform(b.begin(),b.end(), c.begin(), b.begin(), std::minus<double>());
		REQUIRE(vect.getValues() == b);
	}

	SECTION("Check *=")
	{
		MathVector vect({ 3.0,4.1,5.2 });
		vect *= std::vector<double>({ 3.3,7.6,1.2 });

		std::vector<double>b{ 3.0, 4.1, 5.2 };
		std::vector<double>c{ 3.3,7.6,1.2 };

		std::transform(b.begin(), b.end(), c.begin(), b.begin(), std::multiplies<double>());
		REQUIRE(vect.getValues() == b);
	}

	SECTION("Check /=")
	{
		MathVector vect({ 3.0,4.1,5.2 });
		vect /= std::vector<double>({ 3.3,7.6,1.2 });

		std::vector<double>b{ 3.0, 4.1, 5.2 };
		std::vector<double>c{ 3.3,7.6,1.2 };

		std::transform(b.begin(), b.end(), c.begin(), b.begin(), std::divides<double>());
		REQUIRE(vect.getValues() == b);
	}

	SECTION("Check /=")
	{
		MathVector vect({ 3.0,4.1,5.2 });
		vect ^= std::vector<double>({ 3.3,7.6,1.2 });

		std::vector<double>b{ 3.0, 4.1, 5.2 };
		std::vector<double>c{ 3.3,7.6,1.2 };

		for (size_t i = 0; i < b.size(); ++i)
		{
			b[i] = std::pow(b[i], c[i]);
		}
		
		REQUIRE(vect.getValues() == b);
	}

	

}

TEST_CASE("Math utils")
{
	SECTION("dot product (different sizes)")
	{
		MathVector vect1({ 3.0,4.1,5.2 });
		MathVector vect2({ 3.0,4.1,5.2, 3.4 });

		REQUIRE_THROWS(dotProduct(vect1, vect2));
	}

	SECTION("dot product (different sizes)")
	{
		MathVector vect1({ 3.0,4.1,5.2 });
		MathVector vect2({ 3.0,4.1,3.4 });

		REQUIRE(dotProduct(vect1, vect2)- 43.49 < std::numeric_limits<double>::epsilon());
	}

	SECTION("Transpose")
	{
		MathMatrix matr({ { 3.1, 2.4, 1.7 }, { 2.2,3.2, 5.4 } });

		MathMatrix transposed_matr({ {3.1, 2.2} ,{2.4, 3.2}, {1.7, 5.4} });

		REQUIRE(Transpose(matr) == transposed_matr);
	}

	SECTION("Matrix Product (invalid sizes)")
	{
		MathMatrix matr({ { 3.1, 2.4, 1.7 }, { 2.2,3.2, 5.4 } });
		MathMatrix matr2({ { 2.1 } });

		REQUIRE_THROWS(MatrixProduct(matr, matr2));

	}

	SECTION("Matrix Product")
	{
		MathMatrix matr({ { 3.0, 2.0, 1.0 }, { 2.0,3.0, 5.0 } });
		MathMatrix transposed_matr({ {3.1, 2.2} ,{2.4, 3.2}, {1.7, 5.4} });

		MathMatrix result({ { 15.8, 18.4 }, { 21.9 , 41 } });
		REQUIRE(MatrixProduct(matr, transposed_matr) == result);

	}

	SECTION("GaussJordanElimiation (invalid size)")
	{
		MathMatrix matr({ { 3.0, 2.0, 1.0 }, { 2.0,3.0, 5.0 } });
		MathVector free_values({ 1.0 });

		REQUIRE_THROWS(GaussJordanElimination(matr, free_values));
	}

	SECTION("GaussJordanElimiation (invalid size)")
	{
		MathMatrix matr({ { 3.0, 2.0 }, { 2.0,3.0} });
		MathVector free_values({ 1.0, 2.0 });
		auto matrix_res = GaussJordanElimination(matr, free_values);

		for (size_t i = 0; i < matrix_res.rows(); ++i)
		{
			for (size_t j = 0; j < matrix_res.columns(); ++j)
			{
				std::cout << matrix_res.at(i).at(j)<<' ';
			}
			std::cout << '\n';
		}
		REQUIRE_THROWS(GaussJordanElimination(matr, free_values));
	}
}

TEST_CASE("Math Matrix")
{

	SECTION("Initialize Matrix with incorrect size (vector initialization)")
	{
		MathVector math_vec_1({ 3.0,4.1,5.2 });
		MathVector math_vec_2({ 3.0,4.1});

		std::vector<MathVector> matr{ math_vec_1, math_vec_2 };
		REQUIRE_THROWS(MathMatrix(matr));
	}
	SECTION("Initialize Matrix with incorrect size (list initialization)")
	{

		REQUIRE_THROWS(MathMatrix({ { 3.0,4.1,5.2},{3.0,4.1} }));
	}
	SECTION("different sizes in +=")
	{
		MathMatrix matr1({ { 3.0,4.1,5.2},{3.0,4.1, 5.2} });
		MathMatrix matr2{ {2.2},{1.1} };

		REQUIRE_THROWS(matr1 += matr2);
	}
	SECTION("different sizes in +=")
	{
		MathMatrix matr1({ { 3.0,4.1,5.2},{3.0,4.1, 5.2} });
		MathMatrix matr2{ {2.2},{1.1},{2.1} };

		REQUIRE_THROWS(matr1 += matr2);
	}
	SECTION("Check +=")
	{
		MathMatrix matr1({ { 3.0,4.1,5.2},{3.0,4.1, 5.2} });
		MathMatrix matr2{ {3.0,4.1,5.2},{3.0,4.1, 5.2} };
		matr1 += matr2;
		MathMatrix matr3({ { 6.0,8.2,10.4},{6.0,8.2, 10.4} });
		REQUIRE(matr1.getValues() == matr3.getValues());
	}

	SECTION("Check -=")
	{

		MathMatrix matr1({ { 6.0,8.2,10.4},{6.0,8.2, 10.4} });
		MathMatrix matr2({ { 3.0,4.1,5.2},{3.0,4.1, 5.2} });
		
		matr1 -= matr2;
		MathMatrix matr3{ {3.0,4.1,5.2},{3.0,4.1, 5.2} };
		REQUIRE(matr1.getValues() == matr3.getValues());
	}

	SECTION("Check *= (throw diferent sizes)")
	{

		MathMatrix matr1({ { 6.0,8.2},{6.0,8.2} });
		MathMatrix matr2({ { 3.0,4.1,5.2},{3.0,4.1, 5.2} });
		REQUIRE_THROWS(matr1 *= matr2);
	}

	SECTION("Check *= ")
	{

		MathMatrix matr1({ { 6.0,8.2,10.4},{2.0,8.2, 10.3} });
		MathMatrix matr2({ { 3.0,4.1,5.2},{3.0,4.1, 5.2} });

		MathMatrix matr3{ {18.0,33.62,54.08},{6.0,33.62,53.56} };

		matr1 *= matr2;
		bool equal = true;

		for (size_t i = 0; i < matr1.rows(); ++i)
		{
			for (size_t j = 0; j < matr1[i].size(); ++j)
			{
				if (matr1[i][j] - matr3[i][j] > 0.001)
				{
					equal = false;
					break;
				}
			}
		}

		REQUIRE(equal == true);
	}

	SECTION("Check /= ")
	{
		MathMatrix matr3{ {18.0,33.62,54.08},{6.0,33.62,53.56} };
		MathMatrix matr1({ { 6.0,8.2,10.4},{2.0,8.2, 10.3} });
		MathMatrix matr2({ { 3.0,4.1,5.2},{3.0,4.1, 5.2} });

		

		matr3 /= matr2;
		bool equal = true;

		for (size_t i = 0; i < matr1.rows(); ++i)
		{
			for (size_t j = 0; j < matr1[i].size(); ++j)
			{
				if (matr3[i][j] - matr1[i][j] > 0.001)
				{
					equal = false;
					break;
				}
			}
		}

		REQUIRE(equal == true);
	}

	SECTION("Check ^= ")
	{
		MathMatrix matr3{ {2.261732,5.237,1.048},{27.131,3.973,208.919} };
		MathMatrix matr1({ { 2.1, 2.2, 1.1},{4.2, 1.4, 2.1} });
		MathMatrix matr2({ { 1.1, 2.1, 0.5},{2.3, 4.1, 7.2} });



		matr1 ^= matr2;
		bool equal = true;

		for (size_t i = 0; i < matr1.rows(); ++i)
		{
			for (size_t j = 0; j < matr1[i].size(); ++j)
			{
				if (matr1[i][j] - matr3[i][j] > 0.001)
				{
					equal = false;
					break;
				}
			}
		}

		REQUIRE(equal == true);
	}


}