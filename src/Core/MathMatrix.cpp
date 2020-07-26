#include "MathMatrix.h"
#include "MathVector.h"
#include "MathUtils.h"
#include <algorithm>
#include <functional>

MathMatrix::iterator MathMatrix::begin()
{
	return values_.begin();
}

MathMatrix::iterator MathMatrix::end()
{
	return values_.end();
}

MathMatrix::const_iterator MathMatrix::cbegin() const
{
	return values_.cbegin();
}

MathMatrix::const_iterator MathMatrix::cend() const
{
	return values_.cend();
}

std::vector<MathVector> MathMatrix::getValues() const
{
	return values_;
}

MathMatrix::MathMatrix(std::vector<MathVector> const & values):
	values_(values)
{
	if (!values_.empty())
	{
		size_t size_of_row = values_.at(0).size();
		for (auto &math_vec : values_)
		{
			if (math_vec.size() != size_of_row)
			{
				throw std::runtime_error("invalid matrix!");
			}
		}
	}
}

MathMatrix::MathMatrix(std::initializer_list<MathVector> list):
	values_(list)
{
	if (!values_.empty())
	{
		size_t size_of_row = values_.at(0).size();
		for (auto &math_vec : values_)
		{
			if (math_vec.size() != size_of_row)
			{
				throw std::runtime_error("invalid matrix!");
			}
		}
	}
}

MathMatrix::MathMatrix(MathMatrix const & matrix):
	values_(matrix.getValues())
{
}

MathMatrix::MathMatrix()
{

}

MathMatrix::MathMatrix(size_t const & rows, size_t const & columns):
	values_(rows)
{
	for (auto & rows : values_)
	{
		rows = MathVector(columns);
	}
}

MathMatrix & MathMatrix::operator+=(MathMatrix const & another_matrix)
{
	auto another_values = another_matrix.getValues();

	if (this->values_.size() != another_values.size())
	{
		throw std::runtime_error("different sizes of matrixes in += operator");
		
	}
	for (size_t i = 0; i < values_.size(); ++i)
	{
		if (values_[i].size() != another_values[i].size())
		{
			throw std::runtime_error("different sizes of matrixes in += operator");
		}
	}

	std::transform(values_.begin(), values_.end(), another_values.begin(), values_.begin(), std::plus<MathVector>());

	return *this;
}
//
MathMatrix & MathMatrix::operator-=(MathMatrix const & another_vector)
{
	auto another_values = another_vector.getValues();

	if (this->values_.size() != another_values.size())
	{
		throw std::runtime_error("different sizes of matrixes in += operator");

	}
	for (size_t i = 0; i < values_.size(); ++i)
	{
		if (values_[i].size() != another_values[i].size())
		{
			throw std::runtime_error("different sizes of matrixes in += operator");
		}
	}

	std::transform(values_.begin(), values_.end(), another_values.begin(), values_.begin(), std::minus<MathVector>());

	return *this;
}

MathMatrix & MathMatrix::operator*=(MathMatrix const & another_vector)
{
	//just multiply elements of current matrix with another

	auto another_values = another_vector.getValues();
	if (this->values_.size() != another_values.size())
	{
		throw std::runtime_error("different sizes of matrixes in *= operator");

	}
	for (size_t i = 0; i < values_.size(); ++i)
	{
		if (values_[i].size() != another_values[i].size())
		{
			throw std::runtime_error("different sizes of matrixes in *= operator");
		}
	}

	std::transform(values_.begin(), values_.end(), another_values.begin(), values_.begin(), std::multiplies<MathVector>());

	return *this;
}

MathMatrix & MathMatrix::operator/=(MathMatrix const & another_vector)
{
	//just divide elements of current matrix with another

	auto another_values = another_vector.getValues();
	if (this->values_.size() != another_values.size())
	{
		throw std::runtime_error("different sizes of matrixes in *= operator");

	}
	for (size_t i = 0; i < values_.size(); ++i)
	{
		if (values_[i].size() != another_values[i].size())
		{
			throw std::runtime_error("different sizes of matrixes in *= operator");
		}
	}

	std::transform(values_.begin(), values_.end(), another_values.begin(), values_.begin(), std::divides<MathVector>());

	return *this;
}

MathMatrix & MathMatrix::operator^=(MathMatrix const & another_vector)
{

	auto another_values = another_vector.getValues();
	if (this->values_.size() != another_values.size())
	{
		throw std::runtime_error("different sizes of matrixes in *= operator");

	}
	for (size_t i = 0; i < values_.size(); ++i)
	{
		if (values_[i].size() != another_values[i].size())
		{
			throw std::runtime_error("different sizes of matrixes in *= operator");
		}
	}

	for (size_t i = 0; i < another_values.size(); ++i)
	{
		values_[i] ^= another_values[i];
	}

	return *this;
}

MathVector & MathMatrix::operator[](size_t const & el)
{
	return values_[el];
}

size_t MathMatrix::rows() const
{
	return this->getValues().size();
}

size_t MathMatrix::columns() const
{
	return this->getValues().at(0).size();
}

MathVector MathMatrix::at(size_t const & el) const
{
	return values_.at(el);
}

MathVector & MathMatrix::at(size_t const & el)
{
	return values_.at(el);
}
