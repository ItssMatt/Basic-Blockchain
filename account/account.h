#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <map>
#include <string>

#include "../constants.h"
#include "../safemath/safemath.h"

extern std::map<std::string, unsigned long long> balances;
extern std::map<std::string, unsigned long long> nonces;

class CAccount final {
public: 
	static unsigned long long getBalance(std::string key);
	static unsigned long long getNonce(std::string key);
	static void set(std::string key, unsigned long long value); // LOW-LEVEL
	static void transfer(std::string from, std::string to, unsigned long long value);
};

#endif