/*
** EPITECH PROJECT, 2025
** Main.cpp
** File description:
** Main
*/

#include <stdexcept>
#include <iostream>

#include "Params.hpp"
#include "Streams.hpp"

#include "Crypto/Rsa.hpp"

static void print_help(void)
{
    std::cout <<
        "USAGE\n"
        "\t./my_pgp CRYPTO_SYSTEM MODE [OPTIONS] [key]\n"
        "\nDESCRIPTION\n"
        "Cipher or decipher MESSAGE using a given CRYPTO_SYSTEM. The MESSAGE is read from the standard input.\n"
        "\n\tCRYPTO_SYSTEM\n"
        "\t\t\"xor\"\tcomputation using XOR algorithm\n"
        "\t\t\"aes\"\tcomputation using 128-bit AES algorithm\n"
        "\t\t\"rsa\"\tcomputation using RSA algorithm\n"
        "\t\t\"pgp-xor\"\tcomputation using both RSA and XOR algorithm\n"
        "\t\t\"pgp-aes\"\tcomputation using both RSA and 128-bit AES algorithm\n"
        "\n\tMODE\n"
        "\t\t-c MESSAGE is clear and we want to cipher it\n"
        "\t\t-d MESSAGE is ciphered and we want to decipher it\n"
        "\t\t-g P Q for RSA only: Don't read a MESSAGE, but instead generate a public and private key pair from the prime number P and Q\n"
        "\n\tOPTIONS\n"
        "\t\t-b for XOR, AES and PGP, only works on one block. The MESSAGE and the symmetric key must be the same size\n"
        "\n\tkey Key used to cipher/decipher MESSAGE (incompatible with -g MODE)\n";
}

int main(int argc, char **argv)
{
    if (argc == 2) {
        if (std::string(argv[1]) == "-h") {
            print_help();
            return (0);
        }
    }

    try {
        params::Params args(argc, argv);

        switch (args.getMode()) {
        case params::Mode::CIPHER:
        {
            auto system = args.getSystem();
            io::Input in(std::cin, false);
            io::Output out(std::cout, true);
            std::cerr << system->cipher(in, out, args.isBlock()) << std::endl;
            std::cout << std::endl;
        }
            break;
        case params::Mode::DECIPHER:
        {
            auto system = args.getSystem();
            io::Input in(std::cin, true);
            io::Output out(std::cout, false);
            std::cerr << system->decipher(in, out, args.isBlock()) << std::endl;
            std::cout << std::endl;
        }
            break;
        case params::Mode::GENERATE:
        {
            auto &primes = args.getPrimes();
            auto keys = crypto::RSAkeys(std::get<0>(primes), std::get<1>(primes));

            std::cout << "public key: " << std::get<0>(keys) <<
                "\nprivate key: " << std::get<1>(keys) << std::endl;
        }
            break;
        default:
            throw std::runtime_error("Invalid mode");
        }
    } catch(const std::exception &err) {
        std::cerr << err.what() << std::endl;
        return (84);
    }
    return (0);
}
