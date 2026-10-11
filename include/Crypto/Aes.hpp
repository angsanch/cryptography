/*
** EPITECH PROJECT, 2025
** Aes.hpp
** File description:
** AES-128 algorithm
*/

#pragma once

#include "ICrypto.hpp"

namespace crypto {


    class Aes : public ICrypto {
    private:
        enum AESSize {
            AES_SIZE_UNDEFINED = 0,
            AES_SIZE_128,
            AES_SIZE_192,
            AES_SIZE_256,
        };
        enum AESSize mSize;

    public:
        Aes(const std::string &k);

        inline uint8_t keySize() const {
            switch (mSize) {
                case AES_SIZE_128:
                    return (16);
                case AES_SIZE_192:
                    return (24);
                case AES_SIZE_256:
                    return (32);
                default:
                    return (0);
            }
        }

        std::size_t cipher(io::Input &is, io::Output &os, bool block) override;
        std::vector<uint8_t> cipher(const std::vector<uint8_t> &in) override;

        std::size_t decipher(io::Input &is, io::Output &os, bool block) override;
        std::vector<uint8_t> decipher(const std::vector<uint8_t> &in) override;
    };
}
