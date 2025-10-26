/*
** EPITECH PROJECT, 2025
** Rsa.hpp
** File description:
** Rsa algorythm
*/

#pragma once

#include <string>
#include <tuple>
#include <gmpxx.h>
#include <string>

#include "ICrypto.hpp"

namespace crypto {
    std::tuple<std::string, std::string> RSAkeys(const std::string& p_hex, const std::string& q_hex);

    class Rsa : public ICrypto {
    private:
        mpz_class exp;
        mpz_class n;

        std::vector<uint8_t> buff;

    public:
        Rsa(const std::string &k);

        std::size_t cipher(io::Input &is, io::Output &os, bool block) override;
        std::vector<uint8_t> cipher(const std::vector<uint8_t> &in) override;

        std::size_t decipher(io::Input &is, io::Output &os, bool block) override;
        std::vector<uint8_t> decipher(const std::vector<uint8_t> &in) override;
    };
};

std::string bigintToHex(const mpz_class& num);
mpz_class hexToBigint(const std::string& littleEndian);
