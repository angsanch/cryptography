/*
** EPITECH PROJECT, 2025
** Pgp.cpp
** File description:
** PGP cryptosystem combining RSA and any symmetric cryptosystem
*/

#include "Crypto/Pgp.hpp"

#include <algorithm>
#include <sstream>
#include <stdexcept>

#include "Crypto/Rsa.hpp"

namespace crypto {
    namespace {
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
    }

    Pgp::Pgp(const std::string &k, AlgorithmCreator creator)
    : createAlgorithm(std::move(creator))
    {
        auto sep = k.find(':');

        if (sep == std::string::npos)
            throw std::invalid_argument("PGP key must be SYMMETRIC_KEY:RSA_KEY");
        symmetricPart = k.substr(0, sep);
        rsaKey = k.substr(sep + 1);
        if (symmetricPart.empty())
            throw std::invalid_argument("PGP symmetric key is missing");
    }

    std::unique_ptr<ICrypto> Pgp::algorithm(const std::string &key) const
    {
        return (createAlgorithm(key));
    }

    std::size_t Pgp::cipher(io::Input &is, io::Output &os, bool block)
    {
        Rsa rsa(rsaKey);
        auto alpha = algorithm(symmetricPart);

        os.writeString(bytesToHex(rsa.cipher(hexToNumberBytes(symmetricPart))) + "\n");
        return (alpha->cipher(is, os, block));
    }

    std::vector<uint8_t> Pgp::cipher(const std::vector<uint8_t> &)
    {
        throw std::runtime_error("PGP only works on streams");
    }

    std::size_t Pgp::decipher(io::Input &is, io::Output &os, bool block)
    {
        Rsa rsa(rsaKey);
        auto alpha = algorithm(bytesToHex(rsa.decipher(hexToNumberBytes(symmetricPart))));

        return (alpha->decipher(is, os, block));
    }

    std::vector<uint8_t> Pgp::decipher(const std::vector<uint8_t> &)
    {
        throw std::runtime_error("PGP only works on streams");
    }
};
