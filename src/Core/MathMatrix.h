#pragma once
#include <vector>

class MathVector;

class MathMatrix {
public:
	using iterator = typename std::vector<MathVector>::iterator;
	using const_iterator = typename std::vector<MathVector>::const_iterator;

private:
	std::vector<MathVector> values_;
public:
	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;

	std::vector<MathVector> getValues() const;
	MathMatrix(std::vector<MathVector> const & values);
	MathMatrix(std::initializer_list<MathVector> list);
	MathMatrix(MathMatrix const &);
	MathMatrix();
	MathMatrix(size_t const & rows, size_t const & columns);
	MathMatrix& operator += (MathMatrix const & another_vector);
	MathMatrix& operator -= (MathMatrix const & another_vector);
	MathMatrix& operator *= (MathMatrix const & another_vector);
	MathMatrix& operator /= (MathMatrix const & another_vector);
	MathMatrix& operator ^= (MathMatrix const & another_vector);
	MathVector& operator [] (size_t const & el);
	size_t rows() const;
	size_t columns() const;
	MathVector at(size_t const & el) const;
	MathVector& at(size_t const & el);
};