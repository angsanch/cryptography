/*
** EPITECH PROJECT, 2025
** Rsa.cpp
** File description:
** Rsa implementation
*/

#include "Crypto/Rsa.hpp"

std::string bigintToHex(const mpz_class& num)
{
    std::string bigEndian = num.get_str(16);
    if (bigEndian.size() % 2 != 0)
        bigEndian = "0" + bigEndian;

    std::string littleEndian(bigEndian.size(), '\0');
    for (size_t i = 0; i < bigEndian.size(); i += 2) {
        littleEndian[bigEndian.size() - 2 - i] = bigEndian[i];
        littleEndian[bigEndian.size() - 1 - i] = bigEndian[i + 1];
    }
    return littleEndian;
}

mpz_class hexToBigint(const std::string& littleEndian)
{
    std::string hex = littleEndian;
    if (hex.size() % 2 != 0)
        hex = "0" + hex;

    std::string bigEndian(hex.size(), '\0');
    for (size_t i = 0; i < hex.size(); i += 2) {
        bigEndian[hex.size() - 2 - i] = hex[i];
        bigEndian[hex.size() - 1 - i] = hex[i + 1];
    }

    try {
        return mpz_class(bigEndian, 16);
    } catch(const std::exception &err) {
        throw std::runtime_error(std::string("Invalid prime: ") + err.what() + ": " + littleEndian);
    }
}

mpz_class bytesToBigint(const std::vector<uint8_t> &data)
{
    mpz_class val = 0;
    for (int i = data.size() - 1; i >= 0; --i) {
        val <<= 8;
        val += data[i];
    }
    return val;
}

std::vector<uint8_t> bigintToBytes(const mpz_class &num)
{
    mpz_class tmp = num;
    std::vector<uint8_t> out;
    while (tmp > 0) {
        uint8_t byte = mpz_get_ui(tmp.get_mpz_t()) & 0xFF;
        out.push_back(byte);
        tmp >>= 8;
    }
    std::reverse(out.begin(), out.end());
    return out;
}

namespace crypto {
    Rsa::Rsa(const std::string &k)
    {
        auto dash = k.find('-');
        if (dash == std::string::npos)
            throw std::runtime_error("Invalid RSA key format (missing '-')");

        std::string expHex = k.substr(0, dash);
        std::string nHex = k.substr(dash + 1);

        exp = hexToBigint(expHex);
        n = hexToBigint(nHex);
    }

    std::vector<uint8_t> Rsa::cipher(const std::vector<uint8_t> &in)
    {
        mpz_class m = bytesToBigint(in);

        if (m >= n)
            throw std::runtime_error("Block too large for modulus");
        mpz_class c;
        mpz_powm(c.get_mpz_t(), m.get_mpz_t(), exp.get_mpz_t(), n.get_mpz_t());
        return bigintToBytes(c);
    }

    std::size_t Rsa::cipher(io::Input &is, io::Output &os, bool block)
    {
        std::size_t total = 0;
        size_t bitLen = mpz_sizeinbase(n.get_mpz_t(), 2);
        size_t chunkSize = is.getHex() ? 1 : (bitLen / 8 ? bitLen / 8 : 1);

        while (true) {
            std::vector<uint8_t> data = std::move(buff);

            while  (true) {
                std::vector<uint8_t> reader;
                if (is.readChunk(reader, chunkSize) == 0) {
                    block = true;
                    break;
                }
                data.insert(data.end(), reader.begin(), reader.end());
                if (bytesToBigint(data) >= n) {
                    while (!data.empty() && bytesToBigint(data) >= n) {
                        buff.push_back(data.back());
                        data.pop_back();
                    }
                    break;
                }
            }
            if (data.empty())
                break;
            auto out = cipher(data);
            if (!os.getHex())
                std::reverse(out.begin(), out.end());;
            os.writeChunk(out);
            total += data.size();
            if (block)
                break;
        }
        return total;
    }

    std::vector<uint8_t> Rsa::decipher(const std::vector<uint8_t> &in)
    {
        return cipher(in);
    }

    std::size_t Rsa::decipher(io::Input &is, io::Output &os, bool block)
    {
        return cipher(is, os, block);
    }
};
