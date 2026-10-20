/*
** EPITECH PROJECT, 2025
** Xor.cpp
** File description:
** Xor algorithm
*/

#include "Crypto/Xor.hpp"

namespace crypto {
    Xor::Xor(const std::string &k)
    {
        using io::operator >>;
        k >> key;
    }

    std::size_t Xor::cipher(io::Input &is, io::Output &os, bool block)
    {
        std::size_t len = 0;

        while (true) {
            std::vector<uint8_t> data;
            std::size_t read = is.readChunk(data, key.size());

            if (read == 0 && !block)
                break;
            if (read < key.size() && !block)
                while(data.size() < key.size())
                    data.push_back(0);
            len += data.size();
            data = cipher(data);
            os.writeChunk(data);
            if (block)
                break;
        }
        return (len);
    }
    std::vector<uint8_t> Xor::cipher(const std::vector<uint8_t> &in)
    {
        if (in.size() != key.size()) {
            throw std::runtime_error("Key and data are not the same size");
        }
        std::vector<uint8_t> result(key.size(), 0);
        for (std::size_t i = 0; i < key.size(); i ++) {
            result[i] = key[i] ^ in[i];
        }
        return (result);
    }

    std::size_t Xor::decipher(io::Input &is, io::Output &os, bool block)
    {
        return (cipher(is, os, block));
    }
    std::vector<uint8_t> Xor::decipher(const std::vector<uint8_t> &in)
    {
        return (cipher(in));
    }
};
