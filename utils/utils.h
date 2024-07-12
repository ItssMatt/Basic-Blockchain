#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

#include "../keccak256/keccak256.hpp"

std::string getAddressFromString(std::string key);
std::string getHashFromString(std::string key);

#endif