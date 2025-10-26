/*
** EPITECH PROJECT, 2025
** Streams.cpp
** File description:
** Manage io ops
*/

#include "Streams.hpp"

#include <iomanip>
#include <algorithm>

namespace io {
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

    Input::Input(std::istream &_is, bool _hex)
    : is(_is)
    , hex(_hex)
    {
    }

    std::size_t Input::readChunk(std::vector<uint8_t> &vec, std::size_t size)
    {
        if (hex) {
            std::string buff(size * 2, '\0');
            is.read(buff.data(), size * 2);
            buff >> vec;
        } else {
            vec.resize(size);
            is.read(reinterpret_cast<char *>(vec.data()), size);
        }
        return (vec.size());
    }

    Output::Output(std::ostream &_os, bool _hex)
    : os(_os)
    , hex(_hex)
    {
    }

    bool Output::writeChunk(std::vector<uint8_t> &vec)
    {
        if (hex) {
            os << vec;
        } else {
            os.write(reinterpret_cast<char *>(vec.data()), vec.size());
        }
        return (true);
    }
};
