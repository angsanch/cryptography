/*
** EPITECH PROJECT, 2025
** Xor.hpp
** File description:
** Xor algorithm
*/

#pragma once

#include "ICrypto.hpp"

namespace crypto {
    class Xor : public ICrypto {
    private:
        std::vector<uint8_t> key;

    public:
        Xor(const std::string &k);

        std::size_t cipher(io::Input &is, io::Output &os, bool block) override;
        std::vector<uint8_t> cipher(const std::vector<uint8_t> &in) override;

        std::size_t decipher(io::Input &is, io::Output &os, bool block) override;
        std::vector<uint8_t> decipher(const std::vector<uint8_t> &in) override;
    };
};
