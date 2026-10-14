import os
import subprocess
import unittest

ROOT = os.path.dirname(os.path.abspath(__file__))
BINARY = os.path.join(ROOT, "build", "my_pgp")

# Keys and values taken from my_pgp.pdf
XOR_KEY = "576861742069732064656164206d6179206e6576657220646965"
XOR_CIPHER = "20070f2700071c6a4449060a490515164e4e12190b190011063c"
XOR_CLEAR = "You know nothing, Jon Snow"

AES_KEY = "57696e74657220697320636f6d696e67"
AES_CLEAR = "All men must die"
AES_CIPHER = "744ce22c385958348f0df26eceb62eef"

RSA_SHORT_PUB = "0101-19bb"
RSA_SHORT_PRIV = "9d5b-19bb"
RSA_SHORT_CLEAR = "WF"
RSA_SHORT_CIPHER = "8f84"

RSA_P = "4b1da73924978f2e9c1f04170e46820d648edbee12ccf4d4462af89b080c86e1"
RSA_Q = "bb3ca1e126f7c8751bd81bc8daa226494efb3d128f72ed9f6cacbe96e14166cb"
RSA_LONG_PUB = "010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"
RSA_LONG_PRIV = "81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3"
RSA_LONG_CLEAR = "The night is dark and full of terrors"
RSA_LONG_CIPHER = "445b349e7318ad6af16b0bbb718be88ba1c41751f95751cd58857f88fe31f970405c6ec3f16d79172543bf4e571b5596d212f3e79cd08ef14abd244e325b80"

PGP_AES_PUB = AES_KEY + ":" + RSA_LONG_PUB
PGP_AES_ENCRYPTED_KEY = "97f2af4c1b712008c1e46935f446756443a8a700f20581d138e4e6916afe5c5f9b9d6eaa0a870374b686f1a024f9bbb88c23c766654579339caf55afd149d41d"
PGP_AES_PRIV = PGP_AES_ENCRYPTED_KEY + ":" + RSA_LONG_PRIV


def run_binary(args, stdin=""):
    return subprocess.run([BINARY, *args], input=stdin, capture_output=True, text=True)


class MyPgpTests(unittest.TestCase):
    def assertOutput(self, result, expected):
        """Successful run whose stdout is `expected` followed by one newline (as shown by `cat -e` in the PDF)."""
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout, expected + "\n")

    # Usage

    def test_help(self):
        result = run_binary(["-h"])
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertIn("USAGE", result.stdout)
        self.assertIn("./my_pgp CRYPTO_SYSTEM MODE [OPTIONS] [key]", result.stdout)

    # XOR

    def test_xor_cipher_block(self):
        result = run_binary(["xor", "-c", "-b", XOR_KEY], XOR_CLEAR + "\n")
        self.assertOutput(result, XOR_CIPHER)

    def test_xor_decipher_block(self):
        result = run_binary(["xor", "-d", "-b", XOR_KEY], XOR_CIPHER + "\n")
        self.assertOutput(result, XOR_CLEAR)

    # AES

    def test_aes_cipher_block(self):
        result = run_binary(["aes", "-c", "-b", AES_KEY], AES_CLEAR + "\n")
        self.assertOutput(result, AES_CIPHER)

    def test_aes_decipher_block(self):
        result = run_binary(["aes", "-d", "-b", AES_KEY], AES_CIPHER + "\n")
        self.assertOutput(result, AES_CLEAR)

    # RSA

    def test_rsa_generate_short(self):
        result = run_binary(["rsa", "-g", "d3", "e3"])
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout,
                         "public key: " + RSA_SHORT_PUB + "\n"
                         "private key: " + RSA_SHORT_PRIV + "\n")

    def test_rsa_cipher_short(self):
        result = run_binary(["rsa", "-c", RSA_SHORT_PUB], RSA_SHORT_CLEAR + "\n")
        self.assertOutput(result, RSA_SHORT_CIPHER)

    def test_rsa_decipher_short(self):
        result = run_binary(["rsa", "-d", RSA_SHORT_PRIV], RSA_SHORT_CIPHER + "\n")
        self.assertOutput(result, RSA_SHORT_CLEAR)

    def test_rsa_generate_long(self):
        result = run_binary(["rsa", "-g", RSA_P, RSA_Q])
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(result.stdout,
                         "public key: " + RSA_LONG_PUB + "\n"
                         "private key: " + RSA_LONG_PRIV + "\n")

    def test_rsa_cipher_long(self):
        result = run_binary(["rsa", "-c", RSA_LONG_PUB], RSA_LONG_CLEAR + "\n")
        self.assertOutput(result, RSA_LONG_CIPHER)

    def test_rsa_decipher_long(self):
        result = run_binary(["rsa", "-d", RSA_LONG_PRIV], RSA_LONG_CIPHER + "\n")
        self.assertOutput(result, RSA_LONG_CLEAR)

    # PGP (RSA + AES)

    def test_pgp_aes_cipher_block(self):
        result = run_binary(["pgp-aes", "-c", "-b", PGP_AES_PUB], AES_CLEAR + "\n")
        self.assertOutput(result, PGP_AES_ENCRYPTED_KEY + "\n" + AES_CIPHER)

    def test_pgp_aes_decipher_block(self):
        result = run_binary(["pgp-aes", "-d", "-b", PGP_AES_PRIV], AES_CIPHER + "\n")
        self.assertOutput(result, AES_CLEAR)


if __name__ == "__main__":
    unittest.main()
