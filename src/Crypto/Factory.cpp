/*
** EPITECH PROJECT, 2025
** Factory.cpp
** File description:
** Create systems
*/

#include "Crypto/Factory.hpp"

#include "Crypto/Xor.hpp"
#include "Crypto/Aes.hpp"

namespace crypto {
    SystemFactory::SystemFactory()
    {
        functions["xor"] = &crypto::SystemFactory::_xor;
        functions["aes"] = &crypto::SystemFactory::_aes;
    }

    std::unique_ptr<ICrypto> SystemFactory::create(const std::string &name, const std::string &key)
    {
        auto f = functions.find(name);
        if (f == functions.end()) {
            throw std::runtime_error("System not found");
        }
        return (this->*f->second)(key);
    }

    std::unique_ptr<ICrypto> SystemFactory::_xor(const std::string &key)
    {
        return (std::make_unique<Xor>(key));
    }

    std::unique_ptr<ICrypto> SystemFactory::_aes(const std::string &key)
    {
        // return (std::make_unique<Aes>(key));
        (void) key;
        return (nullptr);
    }
};
