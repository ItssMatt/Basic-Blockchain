#ifndef SAFEMATH_H
#define SAFEMATH_H

#include "../constants.h"
#include "../revert/revert.h"

class CSafeMath {
public:
	static unsigned long long add(unsigned long long a, unsigned long long b);
	static unsigned long long sub(unsigned long long a, unsigned long long b);
	static unsigned long long div(unsigned long long a, unsigned long long b);
	static unsigned long long mul(unsigned long long a, unsigned long long b);
};

#endif