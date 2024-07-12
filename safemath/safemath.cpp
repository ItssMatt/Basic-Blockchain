#include "safemath.h"

unsigned long long CSafeMath::add(unsigned long long a, unsigned long long b) {
	return !(b > Constants::CEILING - a || a > Constants::CEILING - b) ? a + b : throw CRevert("SafeMath: Unsafe addition.", 10);
}

unsigned long long CSafeMath::sub(unsigned long long a, unsigned long long b) {
	return !((b > 0 && a <= Constants::CEILING + b) || (b < 0 && a >= Constants::CEILING + b)) ? a - b : throw CRevert("SafeMath: Unsafe subtraction.", 11);
}