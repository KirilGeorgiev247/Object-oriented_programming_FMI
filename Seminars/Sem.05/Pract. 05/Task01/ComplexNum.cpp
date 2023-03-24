#include "ComplexNum.h"
#include <iostream>

ComplexNum::ComplexNum() {
	realPart = 0;
	imaginaryPart = 0;
}

ComplexNum::ComplexNum(double realPart, double imaginaryPart) {
	this->realPart = realPart;
	this->imaginaryPart = imaginaryPart;
}

bool ComplexNum::isEqual(const ComplexNum& other) const {
	return ((this->realPart - other.realPart) < Math::EPSYLON) &&
		((this->imaginaryPart - other.imaginaryPart) < Math::EPSYLON);
}

ComplexNum ComplexNum::add(const ComplexNum& other) const {
	return ComplexNum(this->realPart + other.realPart, this->imaginaryPart + other.imaginaryPart);
}

ComplexNum ComplexNum::substract(const ComplexNum& other) const {
	return ComplexNum(this->realPart - other.realPart, this->imaginaryPart - other.imaginaryPart);
}

ComplexNum ComplexNum::multiply(const ComplexNum& other) const {
	double realPart = this->realPart * other.realPart - this->imaginaryPart * other.imaginaryPart;
	double imaginaryPart = this->realPart * other.imaginaryPart + this->imaginaryPart * other.realPart;
	return ComplexNum(realPart, imaginaryPart);
}

void ComplexNum::conjugate() {
	imaginaryPart * -1;
}

ComplexNum ComplexNum::getConjugated() const {
	return ComplexNum(realPart, imaginaryPart * -1);
}

void ComplexNum::print() const {
	std::cout << realPart << " + " << imaginaryPart << "i";
}