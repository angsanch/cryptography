/*
** EPITECH PROJECT, 2025
** Streams.hpp
** File description:
** Manage io ops
*/
#pragma once

#include <iostream>
#include <vector>
#include <cstddef>
#include <cstdint>

namespace io {
    class Input {
    private:
        std::istream &is;
        bool hex;

    public:
        Input(std::istream &_is, bool _hex=false);

        std::size_t readChunk(std::vector<uint8_t> &vec, std::size_t size);
        bool getHex() const;
    };

    class Output {
    private:
        std::ostream &os;
        bool hex;

    public:
        Output(std::ostream &_os, bool _hex=false);

        bool writeChunk(std::vector<uint8_t> &vec);
        bool getHex() const;
    };

    std::ostream &operator <<(std::ostream &os, const std::vector<uint8_t> &data);
    const std::string &operator >>(const std::string &in, std::vector<uint8_t> &data);
};
