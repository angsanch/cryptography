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

#include "Streams.hpp"

namespace crypto {
    class ICrypto {
    public:
        virtual ~ICrypto() = default;

        virtual std::size_t cipher(io::Input &is, io::Output &os, bool block = false) = 0;
        virtual std::vector<uint8_t> cipher(const std::vector<uint8_t> &in) = 0;

        virtual std::size_t decipher(io::Input &is, io::Output &os, bool block = false) = 0;
        virtual std::vector<uint8_t> decipher(const std::vector<uint8_t> &in) = 0;
    };
};
