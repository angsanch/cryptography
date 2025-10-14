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
    static std::vector<uint8_t> hex_to_bytes(const std::string &hex) {
        std::vector<uint8_t> bytes;
        bytes.reserve(hex.length() / 2);
        for (size_t i = 0; i < hex.length(); i += 2) {
            uint8_t byte = std::stoi(hex.substr(i, 2), nullptr, 16);
            bytes.push_back(byte);
        }
        return bytes;
    }

    Xor::Xor(const std::string &key_)
    {
        key = hex_to_bytes(key_);
        if (key.empty())
            throw std::invalid_argument("XOR error, empty key");
    }

    static std::vector<uint8_t> xor_args(const std::vector<uint8_t> &data, const std::vector<uint8_t> &key)
    {
        std::vector<uint8_t> result(data.size());
        for (size_t i = 0; i < data.size(); i++)
        {
            result[i] = data[i] ^ key[i % key.size()];
        }
        return result;
    }

    std::vector<uint8_t> Xor::cipher(const std::vector<uint8_t> &in)
    {
        return xor_args(in, key);
    }

    std::vector<uint8_t> Xor::decipher(const std::vector<uint8_t> &in)
    {
        return xor_args(in, key);
    }

    std::size_t Xor::cipher(std::istream &is, std::ostream &os, bool block)
    {
        std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(is), {});

        if (block && buffer.size() != key.size())
            throw std::invalid_argument("When used block mode the msg and key needs to be the same size");

        while (!block && buffer.size() % key.size() != 0)
            buffer.push_back(0x00);

        auto result = xor_args(buffer, key);
        os.write(reinterpret_cast<const char*>(result.data()), result.size());

        return result.size();
    }

    std::size_t Xor::decipher(std::istream &is, std::ostream &os, bool block)
    {
        std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(is), {});

        if (block && buffer.size() != key.size())
            throw std::invalid_argument("When used block mode the msg and key needs to be the same size");

        auto result = xor_args(buffer, key);
        os.write(reinterpret_cast<const char*>(result.data()), result.size());

        return result.size();
    }
}