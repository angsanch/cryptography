/*
** EPITECH PROJECT, 2025
** Crypto.cpp
** File description:
** Utils
*/

#include "ICrypto.hpp"

#include <iomanip>
#include <algorithm>

namespace crypto {
    std::ostream &operator <<(std::ostream &os, const std::vector<uint8_t> &data)
    {
        os << std::hex << std::setfill('0');
        for (std::size_t i = data.size(); i > 0; i --) {
            os << std::setw(2) << static_cast<int>(data[i - 1]);
        }
        return (os);
    };

    const std::string &operator >>(const std::string &in, std::vector<uint8_t> &data)
    {
        if (in.size() % 2 != 0) {
            throw std::invalid_argument("Hex string must have even length");
        }
        data.clear();
        data.reserve(in.size() / 2);
        for (size_t i = 0; i < in.size(); i += 2) {
            uint8_t byte = static_cast<uint8_t>(std::stoi(in.substr(i, 2), nullptr, 16));
            data.push_back(byte);
        }
        std::reverse(data.begin(), data.end());
        return (in);
    }
};
