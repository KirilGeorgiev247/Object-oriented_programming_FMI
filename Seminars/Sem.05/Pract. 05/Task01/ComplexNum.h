#pragma once

namespace Math {
	const double EPSYLON = 0.000001;
}

class ComplexNum {
private:
	double realPart;
	double imaginaryPart;

public:
	ComplexNum();
	ComplexNum(double realPart, double imaginaryPart);
	bool isEqual(const ComplexNum& other) const;
	ComplexNum add(const ComplexNum& other) const;
	ComplexNum substract(const ComplexNum& other) const;
	ComplexNum multiply(const ComplexNum& other) const;
	void conjugate();
	ComplexNum getConjugated() const;
	void print() const;
};