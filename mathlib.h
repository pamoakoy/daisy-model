// mathlib.h

#ifndef MATHLIB_H
#define MATHLIB_H

#include <vector>

void
tridia (int from,
	unsigned int size,
	const vector<double>& a,
	const vector<double>& b, 
	const vector<double>& c,
	const vector<double>& d,
	vector<double>::iterator x);

double
single_positive_root_of_cubic_equation 
(double a, double b, double c, double d);

int abs (int);
double abs (double);

#endif MATHLIB_H
