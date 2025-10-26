/*
** EPITECH PROJECT, 2025
** Aes.hpp
** File description:
** AES-128 algorithm
*/

#pragma once

#include "ICrypto.hpp"
#include <array>

namespace crypto {
    class Aes : public ICrypto {
    private:
        std::array<uint32_t, 4> key;
        std::array<uint32_t, 44> roundKeys;

        static const uint8_t sbox[256];
        static const uint8_t inv_sbox[256];

        static const uint8_t rcon[11];

        void keyExpansion();
        uint32_t subWord(uint32_t word);
        uint32_t rotWord(uint32_t word);

        void subBytes(std::array<uint8_t, 16> &state);
        void invSubBytes(std::array<uint8_t, 16> &state);
        void shiftRows(std::array<uint8_t, 16> &state);
        void invShiftRows(std::array<uint8_t, 16> &state);
        void mixColumns(std::array<uint8_t, 16> &state);
        void invMixColumns(std::array<uint8_t, 16> &state);
        void addRoundKey(std::array<uint8_t, 16> &state, int round);

        uint8_t gmul(uint8_t a, uint8_t b);

        void encryptBlock(std::array<uint8_t, 16> &block);
        void decryptBlock(std::array<uint8_t, 16> &block);

    public:
        Aes(const std::string &k);

        std::size_t cipher(io::Input &is, io::Output &os, bool block) override;
        std::vector<uint8_t> cipher(const std::vector<uint8_t> &in) override;

        std::size_t decipher(io::Input &is, io::Output &os, bool block) override;
        std::vector<uint8_t> decipher(const std::vector<uint8_t> &in) override;
    };
}
