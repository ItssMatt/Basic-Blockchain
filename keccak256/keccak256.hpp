/*
 * Bitcoin cryptography library
 * Copyright (c) Project Nayuki
 *
 * https://www.nayuki.io/page/bitcoin-cryptography-library
 * https://github.com/nayuki/Bitcoin-Cryptography-Library
 */

#pragma once

#include <cstddef>
#include <cstdint>


 /*
  * Computes the Keccak-256 hash of a sequence of bytes.
  * Provides just one static method.
  */
class Keccak256 final {

public: static constexpr int HASH_LEN = 40;
public: static constexpr int ADDR_LEN = 20;
private: static constexpr int BLOCK_SIZE = 200 - HASH_LEN * 2;
private: static constexpr int NUM_ROUNDS = 24;


		
public: static void getHash(const std::uint8_t msg[], std::size_t len, std::uint8_t hashResult[HASH_LEN]);
public: static void getAddrHash(const std::uint8_t msg[], std::size_t len, std::uint8_t hashResult[ADDR_LEN]);


private: static void absorb(std::uint64_t state[5][5]);


	   // Requires 0 <= i <= 63
private: static std::uint64_t rotl64(std::uint64_t x, int i);


	   Keccak256() = delete;  // Not instantiable


private: static const unsigned char ROTATION[5][5];

};