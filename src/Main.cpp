/*
** EPITECH PROJECT, 2025
** Main.cpp
** File description:
** Main
*/

#include <stdexcept>
#include <iostream>

#include "Params.hpp"

int main(int argc, char **argv)
{
    try {
        params::Params args(argc, argv);

        std::cout << (int)args.getMode() << " " << args.isBlock() << std::endl;
    } catch(const std::exception &err) {
        std::cerr << err.what() << std::endl;
        return (84);
    }
    return (0);
}
