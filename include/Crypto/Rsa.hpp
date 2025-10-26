/*
** EPITECH PROJECT, 2025
** Rsa.hpp
** File description:
** Rsa algorythm
*/

#pragma once

#include <string>
#include <tuple>

namespace crypto {
    std::tuple<std::string, std::string> RSAkeys(const std::string& p_hex, const std::string& q_hex);
};
