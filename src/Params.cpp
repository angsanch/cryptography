/*
** EPITECH PROJECT, 2025
** Params.cpp
** File description:
** Param manager
*/

#include "Params.hpp"

#include <vector>
#include <map>

namespace params {
    Params::Params(int argc, char **argv)
    {
        if (argc < 3)
            throw std::runtime_error("Not enough arguments");

        int offset = 1;
        std::vector<std::string> args(argc);

        std::map<std::string, Mode> modes;
        modes["-c"] = Mode::CIPHER;
        modes["-d"] = Mode::DECIPHER;
        modes["-g"] = Mode::GENERATE;

        for (int i = 0; i < argc; i ++) {
            args[i] = argv[i];
        }
        offset += 1;
        mode = modes[args[offset]];
        if (mode == Mode::GENERATE) {
            offset += 2;
        }
        offset += 1;
        if (offset < argc) {
            if (args[offset] == "-b") {
                block = true;
                offset ++;
            }
        }
        if (offset < argc) {
            key = args[offset];
            providedKey = true;
            offset ++;
        }

        if (offset != argc) {
            throw std::runtime_error("Incorrect ammount of parameters");
        }
        if (providedKey && mode == Mode::GENERATE) {
            throw std::runtime_error("Cannot provide GENERATE MODE and a key at the same time");
        }
    }

    std::unique_ptr<crypto::ICrypto> Params::getSystem() const
    {
        return (nullptr);
    }

    Mode Params::getMode() const
    {
        return (mode);
    }

    bool Params::isBlock() const
    {
        return (block);
    }
};
