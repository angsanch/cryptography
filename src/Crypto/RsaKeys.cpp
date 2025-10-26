/*
** EPITECH PROJECT, 2025
** RsaKeys.cpp
** File description:
** Generate keys
*/

#include <iostream>
#include <gmpxx.h>
#include <string>

#include "Crypto/Rsa.hpp"

std::string bigintToHex(const mpz_class& num)
{
    std::string bigEndian = num.get_str(16);
    if (bigEndian.size() % 2 != 0)
        bigEndian = "0" + bigEndian;

    std::string littleEndian;
    for (size_t i = 0; i < bigEndian.size(); i += 2) {
        littleEndian = bigEndian.substr(i, 2) + littleEndian;
    }
    return littleEndian;
}

mpz_class hexToBigint(const std::string& littleEndian)
{
    std::string hex = littleEndian;
    if (hex.size() % 2 != 0)
        hex = "0" + hex;

    std::string bigEndian;
    for (size_t i = 0; i < hex.size(); i += 2) {
        bigEndian = hex.substr(i, 2) + bigEndian;
    }

    try {
        return mpz_class(bigEndian, 16);
    } catch(const std::exception &err) {
        throw std::runtime_error(std::string("Invalid prime: ") + err.what() + ": " + littleEndian);
    }
}

// MCD
static mpz_class gcd(const mpz_class& a, const mpz_class& b)
{
    mpz_class g;

    mpz_gcd(g.get_mpz_t(), a.get_mpz_t(), b.get_mpz_t());
    return g;
}

static mpz_class modInverse(const mpz_class& e, const mpz_class& m)
{
    mpz_class inv;

    if (mpz_invert(inv.get_mpz_t(), e.get_mpz_t(), m.get_mpz_t()) == 0)
        throw std::runtime_error("No modular inverse exists");
    return inv;
}

static mpz_class chooseFermatPrime(const mpz_class& lambda)
{
    int fermats[] = {65537, 257, 17, 5, 3};
    
    for (int f : fermats) {
        mpz_class e = f;
        if (e < lambda && gcd(e, lambda) == 1)
            return e;
    }
    throw std::runtime_error("No valid Fermat prime found");
}

std::tuple<std::string, std::string> crypto::RSAkeys(const std::string& p_hex, const std::string& q_hex)
{
    mpz_class p = hexToBigint(p_hex);
    mpz_class q = hexToBigint(q_hex);

    mpz_class n = p * q;
    mpz_class lambda = lcm(p - 1, q - 1);
    mpz_class e = chooseFermatPrime(lambda);
    mpz_class d = modInverse(e, lambda);

    std::string prod = bigintToHex(n);

    return (std::make_tuple(bigintToHex(e) + "-" + prod,
                bigintToHex(d) + "-" + prod));
}
