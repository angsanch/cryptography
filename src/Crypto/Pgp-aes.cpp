/*
** EPITECH PROJECT, 2025
** Pgp-aes.cpp
** File description:
** PGP cryptosystem combining RSA and AES
*/

#include "Crypto/Pgp-aes.hpp"

#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "Crypto/Aes.hpp"
#include "Crypto/Rsa.hpp"

namespace crypto {
    namespace {
        constexpr std::size_t aesKeyHexSizes[] = {32, 48, 64};

        std::string bytesToHex(const std::vector<uint8_t> &bytes)
        {
            std::ostringstream ss;

            io::operator <<(ss, bytes);
            return (ss.str());
        }

        std::vector<uint8_t> hexToNumberBytes(const std::string &hex)
        {
            std::vector<uint8_t> bytes;

            {
                using io::operator >>;
                hex >> bytes;
            }
            std::reverse(bytes.begin(), bytes.end());
            return (bytes);
        }

        std::string padAesKey(std::string hex)
        {
            for (std::size_t size : aesKeyHexSizes) {
                if (hex.size() <= size) {
                    hex.append(size - hex.size(), '0');
                    return (hex);
                }
            }
            return (hex);
        }
    }

    PgpAes::PgpAes(const std::string &k)
    {
        auto sep = k.find(':');

        if (sep == std::string::npos)
            throw std::invalid_argument("PGP-AES key must be SYMMETRIC_KEY:RSA_KEY");
        symmetricPart = k.substr(0, sep);
        rsaKey = k.substr(sep + 1);
        if (symmetricPart.empty())
            throw std::invalid_argument("PGP-AES symmetric key is missing");
    }

    std::size_t PgpAes::cipher(io::Input &is, io::Output &os, bool block)
    {
        Aes aes(symmetricPart);
        Rsa rsa(rsaKey);

        os.writeString(bytesToHex(rsa.cipher(hexToNumberBytes(symmetricPart))) + "\n");
        return (aes.cipher(is, os, block));
    }

    std::vector<uint8_t> PgpAes::cipher(const std::vector<uint8_t> &)
    {
        throw std::runtime_error("PGP-AES only works on streams");
    }

    std::size_t PgpAes::decipher(io::Input &is, io::Output &os, bool block)
    {
        Rsa rsa(rsaKey);

        Aes aes(padAesKey(bytesToHex(rsa.decipher(hexToNumberBytes(symmetricPart)))));
        return (aes.decipher(is, os, block));
    }

    std::vector<uint8_t> PgpAes::decipher(const std::vector<uint8_t> &)
    {
        throw std::runtime_error("PGP-AES only works on streams");
    }
};
