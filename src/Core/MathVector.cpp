#include "MathVector.h"
#include <algorithm>
#include <functional>

MathVector::iterator MathVector::begin()
{
	return values_.begin();
}

MathVector::iterator MathVector::end()
{
	return values_.end();
}

MathVector::const_iterator MathVector::cbegin() const
{
	return values_.cbegin();
}

MathVector::const_iterator MathVector::cend() const
{
	return values_.cend();
}

std::vector<double> MathVector::getValues() const
{
	return values_;
}

MathVector::MathVector(std::vector<double> const & values):
	values_(values)
{
}

MathVector::MathVector(std::initializer_list<double> list):
	values_(list)
{
}

MathVector::MathVector(MathVector const & vec):
	values_(vec.getValues())
{
}

MathVector::MathVector()
{
}

MathVector::MathVector(size_t const & size_of_vec) :
	values_(size_of_vec)
{

}

MathVector & MathVector::operator+=(MathVector const & another_vector)
{
	auto another_values = another_vector.getValues();

	if (this->values_.size() != another_values.size())
	{
		return *this;
	}

	std::transform(values_.begin(), values_.end(), another_values.begin(), values_.begin(), std::plus<double>());

	return *this;
}

MathVector & MathVector::operator-=(MathVector const & another_vector)
{
	auto another_values = another_vector.getValues();

	if (this->values_.size() != another_values.size())
	{
		return *this;
	}

	std::transform(values_.begin(), values_.end(), another_values.begin(), values_.begin(), std::minus<double>());

	return *this;
}

MathVector & MathVector::operator*=(MathVector const & another_vector)
{
	auto another_values = another_vector.getValues();

	if (this->values_.size() != another_values.size())
	{
		return *this;
	}

	std::transform(values_.begin(), values_.end(), another_values.begin(), values_.begin(), std::multiplies<double>());

	return *this;
}

MathVector & MathVector::operator/=(MathVector const & another_vector)
{
	auto another_values = another_vector.getValues();

	if (this->values_.size() != another_values.size())
	{
		return *this;
	}

	std::transform(values_.begin(), values_.end(), another_values.begin(), values_.begin(), std::divides<double>());

	return *this;
}

MathVector & MathVector::operator^=(MathVector const & another_vector)
{
	auto another_values = another_vector.getValues();

	if (this->values_.size() != another_values.size())
	{
		return *this;
	}

	for (size_t i = 0; i < another_values.size(); ++i)
	{
		values_[i] = std::pow(values_[i], another_values[i]);
	}

	return *this;
}

double & MathVector::operator[](size_t const & el)
{
	return values_[el];
}

size_t MathVector::size() const
{
	return values_.size();
}

double MathVector::at(size_t const & el) const
{
	return values_.at(el);
}

double & MathVector::at(size_t const & el)
{
	return values_.at(el);
}
