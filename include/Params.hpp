/*
** EPITECH PROJECT, 2025
** Params.hpp
** File description:
** Manage params
*/

#pragma once

#include <map>
#include <memory>

#include "ICrypto.hpp"
#include "Crypto/Factory.hpp"

namespace params {
    enum class Mode {
        NONE,
        CIPHER,
        DECIPHER,
        GENERATE,
    };

    class Params {
    private:
        std::string system;
        Mode mode;
        bool block = false;
        std::string key;
        bool providedKey = false;
        std::tuple<std::string, std::string> primes;

        crypto::SystemFactory factory;

    public:
        Params(int argc, char **argv);

        std::unique_ptr<crypto::ICrypto> getSystem();
        Mode getMode() const;
        bool isBlock() const;
        const std::tuple<std::string, std::string> &getPrimes() const;
    };
};
