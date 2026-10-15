/*
** EPITECH PROJECT, 2025
** Aes.hpp
** File description:
** AES-128 algorithm
*/

#pragma once

#include "ICrypto.hpp"

#include <span>
#include <vector>

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

        enum AESAction {
            AES_ENCRYPT,
            AES_DECRYPT,
        };

        typedef union Word {
            uint32_t word;
            uint8_t bytes[4];
        } t_word;
        std::vector<t_word> mKey;

        std::vector<uint8_t> processVector(const std::vector<uint8_t> &in, enum AESAction action);
        std::size_t processStream(io::Input &is, io::Output &os, bool block, enum AESAction action);

        void encryptBlock(std::span<uint8_t, 16> state);
        void decryptBlock(std::span<uint8_t, 16> state);

        void addRoundKey(std::span<uint8_t, 16> state, std::size_t wordIndex, enum AESAction action);
        void shiftRows(std::span<uint8_t, 16> state, enum AESAction action);
        void subBytes(std::span<uint8_t, 16> state, enum AESAction action);
        void mixColumns(std::span<uint8_t, 16> state, enum AESAction action);


    public:
        Aes(const std::string &k);

        inline uint8_t getNr() const {
            switch (mSize) {
                case AES_SIZE_128:
                    return (10);
                case AES_SIZE_192:
                    return (12);
                case AES_SIZE_256:
                    return (14);
                default:
                    return (0);
            }
        }

        inline std::size_t cipher(io::Input &is, io::Output &os, bool block) override
        { return (processStream(is, os, block, AES_ENCRYPT)); }
        inline std::vector<uint8_t> cipher(const std::vector<uint8_t> &in) override
        { return (processVector(in, AES_ENCRYPT)); }

        inline std::size_t decipher(io::Input &is, io::Output &os, bool block) override
        { return (processStream(is, os, block, AES_DECRYPT)); }
        inline std::vector<uint8_t> decipher(const std::vector<uint8_t> &in) override
        { return (processVector(in, AES_DECRYPT)); }
    };
}
