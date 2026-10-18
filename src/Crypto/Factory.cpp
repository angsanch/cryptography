/*
** EPITECH PROJECT, 2025
** Factory.cpp
** File description:
** Create systems
*/

#include "Crypto/Factory.hpp"

#include <stdexcept>
#include <string_view>

#include "Crypto/Xor.hpp"
#include "Crypto/Aes.hpp"
#include "Crypto/Rsa.hpp"
#include "Crypto/Pgp.hpp"

namespace crypto {
    constexpr std::string_view pgpPrefix = "pgp-";

    SystemFactory::SystemFactory()
    {
        functions["xor"] = &crypto::SystemFactory::_xor;
        functions["aes"] = &crypto::SystemFactory::_aes;
        functions["rsa"] = &crypto::SystemFactory::_rsa;
    }

    std::unique_ptr<ICrypto> SystemFactory::create(const std::string &name, const std::string &key)
    {
        auto f = functions.find(name);
        if (f != functions.end()) {
            return (this->*f->second)(key);
        }
        if (name.starts_with(pgpPrefix)) {
            return (_pgp(name.substr(pgpPrefix.size()), key));
        }
        throw std::runtime_error("System not found");
    }

    std::unique_ptr<ICrypto> SystemFactory::_xor(const std::string &key)
    {
        return (std::make_unique<Xor>(key));
    }

    std::unique_ptr<ICrypto> SystemFactory::_aes(const std::string &key)
    {
        return (std::make_unique<Aes>(key));
    }

    std::unique_ptr<ICrypto> SystemFactory::_rsa(const std::string &key)
    {
        return (std::make_unique<Rsa>(key));
    }

    std::unique_ptr<ICrypto> SystemFactory::_pgp(const std::string &name, const std::string &key)
    {
        return (std::make_unique<Pgp>(key, [this, name](const std::string &algorithmKey) {
            return (create(name, algorithmKey));
        }));
    }
};
