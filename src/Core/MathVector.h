#pragma once
#include <vector>
class MathVector {
public:
	using iterator = typename std::vector<double>::iterator;
	using const_iterator = typename std::vector<double>::const_iterator;

private:
	std::vector<double> values_;
public:
	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;

	std::vector<double> getValues() const;
	MathVector(std::vector<double> const & values);
	MathVector(std::initializer_list<double> list);
	MathVector(MathVector const &);
	MathVector();
	MathVector(size_t const & size_of_vec);
	MathVector& operator += (MathVector const & another_vector);
	MathVector& operator -= (MathVector const & another_vector);
	MathVector& operator *= (MathVector const & another_vector);
	MathVector& operator /= (MathVector const & another_vector);
	MathVector& operator ^= (MathVector const & another_vector);
	double& operator [] (size_t const & el);
	size_t size() const;
	double at(size_t const & el) const;
	double& at(size_t const & el);
};