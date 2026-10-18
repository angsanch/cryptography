/*
** EPITECH PROJECT, 2025
** Pgp.hpp
** File description:
** PGP cryptosystem combining RSA and any symmetric cryptosystem
*/

#pragma once

#include <functional>
#include <memory>
#include <string>

#include "ICrypto.hpp"

namespace crypto {
    class Pgp : public ICrypto {
    private:
        using AlgorithmCreator = std::function<std::unique_ptr<ICrypto>(const std::string &)>;

        std::string symmetricPart;
        std::string rsaKey;
        AlgorithmCreator createAlgorithm;

        std::unique_ptr<ICrypto> algorithm(const std::string &key) const;

    public:
        Pgp(const std::string &k, AlgorithmCreator creator);

        std::size_t cipher(io::Input &is, io::Output &os, bool block) override;
        std::vector<uint8_t> cipher(const std::vector<uint8_t> &in) override;

        std::size_t decipher(io::Input &is, io::Output &os, bool block) override;
        std::vector<uint8_t> decipher(const std::vector<uint8_t> &in) override;
    };
};
