/*
** EPITECH PROJECT, 2025
** Xor.cpp
** File description:
** Xor algorithm
*/

#include "Crypto/Xor.hpp"
#include "ICrypto.hpp"
#include <stdexcept>
#include <algorithm>

namespace crypto {
    Xor::Xor(const std::string &k)
    {
        k >> key;
        if (key.empty())
            throw std::invalid_argument("XOR error, empty key");
    }

    std::vector<uint8_t> Xor::cipher(const std::vector<uint8_t> &in)
    {
        std::vector<uint8_t> result(in.size());
        for (size_t i = 0; i < in.size(); i++)
        {
            result[i] = in[i] ^ key[i % key.size()];
        }
        return result;
    }

    std::vector<uint8_t> Xor::decipher(const std::vector<uint8_t> &in)
    {
        return cipher(in);
    }

    std::size_t Xor::cipher(std::istream &is, std::ostream &os, bool block)
    {
        std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(is), {});

        if (block && !buffer.empty() && buffer.back() == '\n')
            buffer.pop_back();

        if (block && buffer.size() != key.size())
            throw std::invalid_argument("When used block mode the msg and key needs to be the same size");

        while (!block && buffer.size() % key.size() != 0)
            buffer.push_back(0x00);

        auto result = cipher(buffer);

        os << result;
        return result.size();
    }

    std::size_t Xor::decipher(std::istream &is, std::ostream &os, bool block)
    {
        return (cipher(is, os, block));
    }
}
