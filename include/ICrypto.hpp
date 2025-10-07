/*
** EPITECH PROJECT, 2025
** Crypto.hpp
** File description:
** CryptoSystem Interface
*/

#pragma once

#include <iostream>
#include <cstdint>
#include <vector>

namespace crypto {
    class ICrypto {
    public:
        virtual ~ICrypto() = default;

        virtual std::size_t cipher(std::istream &is, std::ostream &os, bool block = false) = 0;
        virtual std::vector<uint8_t> cipher(const std::vector<uint8_t> &in) = 0;

        virtual std::size_t decipher(std::istream &is, std::ostream &os, bool block = false) = 0;
        virtual std::vector<uint8_t> decipher(const std::vector<uint8_t> &in) = 0;
    };

    std::ostream &operator <<(std::ostream &os, const std::vector<uint8_t> &data);
    const std::string &operator >>(const std::string &in, std::vector<uint8_t> &data);
};
