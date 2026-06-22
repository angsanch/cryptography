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

    class Word {
    private:
        using Union = union {
            uint32_t word;
            uint8_t bytes[4];
        };
        Union mUnion;

    public:
        Word()
        : mUnion(0)
        {}
        Word(uint8_t *arr)
        : Word(arr[0], arr[1], arr[2], arr[3])
        {}
        Word(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
        {
            mUnion.bytes[0] = a;
            mUnion.bytes[1] = b;
            mUnion.bytes[2] = c;
            mUnion.bytes[3] = d;
        }
        Word(uint32_t w)
        { mUnion.word = w; }

        uint32_t getWord() const { return (mUnion.word); }
        uint8_t getByte(uint8_t i) const { return (mUnion.bytes[i]); }

        Word &rotWord();
        Word &subBytes(bool reverse=false);
        Word &applyRcon(uint8_t i);

        inline Word operator ^(const Word &other)
        { return (Word(mUnion.word ^ other.mUnion.word)); }
        inline operator uint32_t() const
        { return (mUnion.word); }
    };

    std::ostream &operator <<(std::ostream &os, const Word &word);

    extern const uint8_t sbox[256];
    extern const uint8_t inv_sbox[256];
    extern const uint8_t rcon[11];

    class Aes : public ICrypto {
    private:
        std::array<Word, 44> roundKeys;

        void keyExpansion();

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
