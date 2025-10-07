/*
** EPITECH PROJECT, 2025
** Factory.hpp
** File description:
** Create system
*/

#pragma once

#include <map>
#include <memory>
#include <string>

#include "ICrypto.hpp"

namespace crypto {
    class SystemFactory {
    private:
        std::map<std::string, std::unique_ptr<ICrypto> (crypto::SystemFactory::*)(const std::string &)> functions;

        std::unique_ptr<ICrypto> _xor(const std::string &key);
    public:
        SystemFactory();

        std::unique_ptr<ICrypto> create(const std::string &name, const std::string &key);
    };
};
