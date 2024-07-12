#include "account.h"


std::map<std::string, unsigned long long> balances;
std::map<std::string, unsigned long long> nonces;

unsigned long long CAccount::getBalance(std::string key) {
	return balances[key];
}

unsigned long long CAccount::getNonce(std::string key) {
	return nonces[key];
}

void CAccount::set(std::string key, unsigned long long value) {
	if (value > Constants::CEILING)
		return;
	balances[key] = value;
}

void CAccount::transfer(std::string from, std::string to, unsigned long long value) {
	balances[from] = CSafeMath::sub(balances[from], value);
	balances[to] = CSafeMath::add(balances[to], value);
}