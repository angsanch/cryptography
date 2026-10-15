/*
** EPITECH PROJECT, 2025
** Pgp-aes.hpp
** File description:
** PGP cryptosystem combining RSA and AES
*/

#pragma once

#include <string>

#include "ICrypto.hpp"

namespace crypto {
    class PgpAes : public ICrypto {
    private:
        std::string symmetricPart;
        std::string rsaKey;

    public:
        PgpAes(const std::string &k);

        std::size_t cipher(io::Input &is, io::Output &os, bool block) override;
        std::vector<uint8_t> cipher(const std::vector<uint8_t> &in) override;

        std::size_t decipher(io::Input &is, io::Output &os, bool block) override;
        std::vector<uint8_t> decipher(const std::vector<uint8_t> &in) override;
    };
};
