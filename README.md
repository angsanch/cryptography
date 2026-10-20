# my_pgp

A song of ciphers and primes.

Project for semester 5 of the Epitech Math module.

### Description

This project implements a PGP-like cryptosystem in C++. It ciphers and deciphers messages using:

1. A symmetric algorithm:
   - XOR
   - AES (128, 192 and 256-bit)

2. An asymmetric algorithm, RSA, with:
   - public/private key pair generation from two prime numbers
   - ciphering/deciphering using those keys

3. Hybrid PGP cryptosystems combining RSA with either XOR (`pgp-xor`) or AES (`pgp-aes`).

The message is always read from the standard input. Numbers are always represented as little-endian hexadecimal values.

## Getting Started

### Dependencies

- [CMake](https://cmake.org/) (>= 3.12)
- A C++23 compatible compiler (e.g. [GCC](https://gcc.gnu.org/))
- [GMP](https://gmplib.org/)

### Installation

* Download/Clone the repository and enter its directory.
* Build the project with CMake:
```
$> cmake -B build
$> cmake --build build
```
* Now you are ready to run the code.

## Usage

**Execution:** `./my_pgp CRYPTO_SYSTEM MODE [OPTIONS] [key]`

### Arguments
- **`CRYPTO_SYSTEM`**: Algorithm to use, among `xor`, `aes`, `rsa`, `pgp-xor` and `pgp-aes`.
- **`MODE`**:
  - `-c`: cipher the message
  - `-d`: decipher the message
  - `-g P Q`: RSA only, don't read a message but generate a public and private key pair from the prime numbers `P` and `Q`
- **`OPTIONS`**:
  - `-b`: only works on one block, the message and the symmetric key must be the same size
- **`key`**: Key used to cipher/decipher the message (incompatible with `-g`).

Without the `-b` option, the algorithm works in stream mode and the message can be of any length.

### Examples

To cipher a message with XOR:
```
$> echo "You know nothing, Jon Snow" | ./my_pgp xor -c -b 576861742069732064656164206d6179206e6576657220646965
20070f2700071c6a4449060a490515164e4e12190b190011063c
```

To cipher a message with PGP using XOR:
```
$> echo "WF" | ./my_pgp pgp-xor -c -b 5768:0101-19bb
b0a5
113f
```

To generate an RSA key pair and use it:
```
$> ./my_pgp rsa -g d3 e3
public key: 0101-19bb
private key: 9d5b-19bb
$> echo "WF" | ./my_pgp rsa -c 0101-19bb
8f84
$> echo "8f84" | ./my_pgp rsa -d 9d5b-19bb
WF
```

## Acknowledgments

* [Epitech](https://www.epitech.eu/)

## Authors

* **Daniel Sanchez** ([GitHub](https://github.com/angsanch) / [LinkedIn](https://www.linkedin.com/in/angeldanielsanchez/))
* **Raquel Costumero** ([GitHub](https://github.com/raquelcostumerofernandez) / [LinkedIn](https://www.linkedin.com/in/raquel-costumero-fern%C3%A1ndez/))

## License

This project is licensed under the GNU Public License version 3.0 - see the [LICENSE](LICENSE) file for details.
