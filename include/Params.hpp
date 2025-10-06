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

namespace params {
    enum class Mode {
        NONE,
        CIPHER,
        DECIPHER,
        GENERATE,
    };

    class Params {
    private:
        Mode mode;
        bool block = false;
        std::string key;
        bool providedKey = false;

    public:
        Params(int argc, char **argv);

        std::unique_ptr<crypto::ICrypto> getSystem() const;
        Mode getMode() const;
        bool isBlock() const;
    };
};
