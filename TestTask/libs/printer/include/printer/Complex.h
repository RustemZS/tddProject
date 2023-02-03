#ifndef COMPLEX_H
#define COMPLEX_H

#include <vector>
#include <math.h>
#include <cstdint>
#define PI 3.14159

// Комплексный отсчёт
template <class T>
struct Complex {
	Complex()
	{
		re = 0;
		im = 0;
	}
	Complex(T re, T im)
	{
		this->re = re;
		this->im = im;
	}

	// Нахождение модуля комплексного числа
	T abs()
	{
		return sqrt(re * re + im * im);
	}

	// Нахождение фазы комплексного числа
	T arg()
	{
		return atan2(im, re);
	}

	// Нахождение фазы комплексного числа в градусах
	T argDeg()
	{
		return atan2(im, re) * 180/PI;
	}

	// Перегрузки операторов
	Complex operator=(int const& number) const
	{
		return Complex(number, 0);
	}
	Complex operator+(Complex const& summand) const
	{
		return Complex(re + summand.re, im + summand.im);
	}
	Complex operator-(Complex const& subtrahend) const
	{
		return Complex(re - subtrahend.re, im - subtrahend.im);
	}
	Complex operator*(Complex const& multiplier) const
	{
		return Complex((re * multiplier.re) - (im * multiplier.im), (re * multiplier.im) + (im * multiplier.re));
	}
	Complex operator/(Complex const& divider) const
	{
		return Complex(((re * divider.re) + (im * divider.im)) / (divider.re * divider.re + divider.im * divider.im), ((im * divider.re) - (re * divider.im)) / (divider.re * divider.re + divider.im * divider.im));
	}
	Complex operator/(uint32_t const& divider) const
	{
		return Complex(re / divider, im / divider);
	}

private:
	T re;
	T im;
};

#endif
