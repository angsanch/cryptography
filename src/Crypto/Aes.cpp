/*
** EPITECH PROJECT, 2025
** Aes.cpp
** File description:
** AES-128 algorithm implementation
*/

#include "Crypto/Aes.hpp"
#include <stdexcept>
#include <algorithm>

namespace crypto {
    const uint8_t Aes::sbox[256] = {
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
    };

    const uint8_t Aes::inv_sbox[256] = {
        0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
        0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
        0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
        0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
        0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
        0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
        0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
        0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
        0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
        0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
        0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
        0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
        0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
        0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
        0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
        0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d
    };

    const uint8_t Aes::rcon[11] = {
        0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
    };

    Aes::Aes(const std::string &k)
    {
        if (k.length() != 32)
            throw std::invalid_argument("AES error, key must be 32 hex characters (128 bits)");

        for (size_t i = 0; i < 4; i++) {
            std::string word = k.substr(i * 8, 8); // tomar los 8 chars
            key[i] = std::stoul(word, nullptr, 16);  // convertir en número
        }
        keyExpansion(); // genera 44 palabras (11 rondas * 4 palabras)
    }

    uint32_t Aes::rotWord(uint32_t word)
    {
        return (word << 8) | (word >> 24);
    }

    uint32_t Aes::subWord(uint32_t word)
    {
        uint32_t result = 0;
        result |= sbox[(word >> 0) & 0xff] << 0;
        result |= sbox[(word >> 8) & 0xff] << 8;
        result |= sbox[(word >> 16) & 0xff] << 16;
        result |= sbox[(word >> 24) & 0xff] << 24;
        return result;
    }

    void Aes::keyExpansion()
    {
        for (int i = 0; i < 4; i++) // Copia clave original
            roundKeys[i] = key[i];

        for (int i = 4; i < 44; i++) {
            uint32_t temp = roundKeys[i - 1];
            if (i % 4 == 0) {
                temp = subWord(rotWord(temp)) ^ (rcon[i / 4] << 0);
            }
            roundKeys[i] = roundKeys[i - 4] ^ temp;
        }
    }

    void Aes::subBytes(std::array<uint8_t, 16> &state)
    {
        for (int i = 0; i < 16; i++)
            state[i] = sbox[state[i]];
    }

    void Aes::invSubBytes(std::array<uint8_t, 16> &state)
    {
        for (int i = 0; i < 16; i++)
        state[i] = inv_sbox[state[i]];
    }

    void Aes::shiftRows(std::array<uint8_t, 16> &state)
    {
        uint8_t temp;

        temp = state[1];
        state[1] = state[5];
        state[5] = state[9];
        state[9] = state[13];
        state[13] = temp;

        temp = state[2];
        state[2] = state[10];
        state[10] = temp;
        temp = state[6];
        state[6] = state[14];
        state[14] = temp;

        temp = state[15];
        state[15] = state[11];
        state[11] = state[7];
        state[7] = state[3];
        state[3] = temp;
    }

    void Aes::invShiftRows(std::array<uint8_t, 16> &state)
    {
        uint8_t temp;

        temp = state[13];
        state[13] = state[9];
        state[9] = state[5];
        state[5] = state[1];
        state[1] = temp;

        temp = state[2];
        state[2] = state[10];
        state[10] = temp;
        temp = state[6];
        state[6] = state[14];
        state[14] = temp;

        temp = state[3];
        state[3] = state[7];
        state[7] = state[11];
        state[11] = state[15];
        state[15] = temp;
    }

    uint8_t Aes::gmul(uint8_t a, uint8_t b)
    {
        uint8_t result = 0;

        for (size_t i = 0; i < 8; i++) { //multiplicar bit a bit (2^8)
            if (b & 1) // Si b es 1 xor con a
                result ^= a;
            bool bit_more = (a & 0x80);
            a <<= 1;
            if (bit_more)
                a ^= 0x1b;
            b >>= 1;
        }
        return result;
    }

    void Aes::mixColumns(std::array<uint8_t, 16> &state)
    {
        for (int column = 0; column < 4; column++) {
            uint8_t w0 = state[column * 4 + 0];
            uint8_t w1 = state[column * 4 + 1];
            uint8_t w2 = state[column * 4 + 2];
            uint8_t w3 = state[column * 4 + 3];

            state[column * 4 + 0] = gmul(w0, 2) ^ gmul(w1, 3) ^ w2 ^ w3;
            state[column * 4 + 1] = w0 ^ gmul(w1, 2) ^ gmul(w2, 3) ^ w3;
            state[column * 4 + 2] = w0 ^ w1 ^ gmul(w2, 2) ^ gmul(w3, 3);
            state[column * 4 + 3] = gmul(w0, 3) ^ w1 ^ w2 ^ gmul(w3, 2);
        }
    }

    void Aes::invMixColumns(std::array<uint8_t, 16> &state)
    {
        for (int column = 0; column < 4; column++) {
            uint8_t w0 = state[column * 4 + 0];
            uint8_t w1 = state[column * 4 + 1];
            uint8_t w2 = state[column * 4 + 2];
            uint8_t w3 = state[column * 4 + 3];

            state[column * 4 + 0] = gmul(w0, 0x0e) ^ gmul(w1, 0x0b) ^ gmul(w2, 0x0d) ^ gmul(w3, 0x09);
            state[column * 4 + 1] = gmul(w0, 0x09) ^ gmul(w1, 0x0e) ^ gmul(w2, 0x0b) ^ gmul(w3, 0x0d);
            state[column * 4 + 2] = gmul(w0, 0x0d) ^ gmul(w1, 0x09) ^ gmul(w2, 0x0e) ^ gmul(w3, 0x0b);
            state[column * 4 + 3] = gmul(w0, 0x0b) ^ gmul(w1, 0x0d) ^ gmul(w2, 0x09) ^ gmul(w3, 0x0e);
        }
    }

    void Aes::addRoundKey(std::array<uint8_t, 16> &state, int round)
    {
        for (int column = 0; column < 4; column++) {
            uint32_t rk = roundKeys[round * 4 + column];
            state[column * 4 + 0] ^= (rk >> 0) & 0xFF;
            state[column * 4 + 1] ^= (rk >> 8) & 0xFF;
            state[column * 4 + 2] ^= (rk >> 16) & 0xFF;
            state[column * 4 + 3] ^= (rk >> 24) & 0xFF;
        }
    }

    void Aes::encryptBlock(std::array<uint8_t, 16> &block)
    {
        addRoundKey(block, 0);

        for (int round = 1; round <= 9; round++) {
            subBytes(block);
            shiftRows(block);
            mixColumns(block);
            addRoundKey(block, round);
        }

        subBytes(block);
        shiftRows(block);
        addRoundKey(block, 10);
    }

    void Aes::decryptBlock(std::array<uint8_t, 16> &block)
    {
        addRoundKey(block, 10);

        for (int round = 9; round >= 1; round--) {
            invShiftRows(block);
            invSubBytes(block);
            addRoundKey(block, round);
            invMixColumns(block);
        }

        invShiftRows(block);
        invSubBytes(block);
        addRoundKey(block, 0);
    }

    std::size_t Aes::cipher(std::istream &is, std::ostream &os, bool block)
    {
        std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(is), {});

        if (block && !buffer.empty() && buffer.back() == '\n')
            buffer.pop_back();

        if (block && buffer.size() != 16)
            throw std::invalid_argument("AES error, input size must be 16 bytes in block mode");

        while (buffer.size() % 16 != 0)
            buffer.push_back(0x00);

        std::vector<uint8_t> result;
        for (size_t i = 0; i < buffer.size(); i += 16) {
            std::vector<uint8_t> block(buffer.begin() + i, buffer.begin() + i + 16);
            auto encryptedBlock = cipher(block);
            result.insert(result.end(), encryptedBlock.begin(), encryptedBlock.end());
        }
        os.write(reinterpret_cast<const char*>(result.data()), result.size());
        return result.size();
    }

    std::vector<uint8_t> Aes::cipher(const std::vector<uint8_t> &in)
    {
        if (in.size() != 16)
            throw std::invalid_argument("AES error, input size must be 16 bytes");

        std::array<uint8_t, 16> block;
        std::copy(in.begin(), in.end(), block.begin());
        encryptBlock(block);
        return std::vector<uint8_t>(block.begin(), block.end());
    }

    std::size_t Aes::decipher(std::istream &is, std::ostream &os, bool block)
    {
        std::vector<uint8_t> buffer(std::istreambuf_iterator<char>(is), {});

        if (block && !buffer.empty() && buffer.back() == '\n')
            buffer.pop_back();

        if (block && buffer.size() != 16)
            throw std::invalid_argument("AES error, input size must be 16 bytes in block mode");

        if (buffer.size() % 16 != 0)
            throw std::invalid_argument("AES error, input size must be 16 bytes in block mode");

        std::vector<uint8_t> result;
        for (size_t i = 0; i < buffer.size(); i += 16) {
            std::vector<uint8_t> block(buffer.begin() + i, buffer.begin() + i + 16);
            auto decryptedBlock = decipher(block);
            result.insert(result.end(), decryptedBlock.begin(), decryptedBlock.end());
        }
        os.write(reinterpret_cast<const char*>(result.data()), result.size());
        return result.size();
    }

    std::vector<uint8_t> Aes::decipher(const std::vector<uint8_t> &in)
    {
        if (in.size() != 16)
            throw std::invalid_argument("AES error, input size must be 16 bytes");

        std::array<uint8_t, 16> block;
        std::copy(in.begin(), in.end(), block.begin());
        decryptBlock(block);
        return std::vector<uint8_t>(block.begin(), block.end());
    }
}
