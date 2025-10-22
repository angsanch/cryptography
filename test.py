import unittest
import subprocess
import shlex

def run_binary(args, stdin=None):
    return subprocess.run(["build/my_pgp", *shlex.split(args)], input=stdin, capture_output=True, text=True)

class Crypto(unittest.TestCase):
    def test_xor_encrypt_block(self):
        result = run_binary("xor -c -b 576861742069732064656164206d6179206e6576657220646965", "You know nothing, Jon Snow")
        self.assertEqual(result.returncode, 0)
        self.assertEqual("20070f2700071c6a4449060a490515164e4e12190b190011063c", result.stdout)
    def test_xor_decrypt_block(self):
        result = run_binary("xor -d -b 576861742069732064656164206d6179206e6576657220646965", "20070f2700071c6a4449060a490515164e4e12190b190011063c")
        self.assertEqual(result.returncode, 0)
        self.assertEqual("You know nothing, Jon Snow", result.stdout)

    def test_aes_encrypt_block(self):
        result = run_binary("xor -c -b 57696e74657220697320636f6d696e67", "All men must die")
        self.assertEqual(result.returncode, 0)
        self.assertEqual("744ce22c385958348f0df26eceb62eef", result.stdout)
    def test_aes_decrypt_block(self):
        result = run_binary("xor -d -b 57696e74657220697320636f6d696e67", "744ce22c385958348f0df26eceb62eef")
        self.assertEqual(result.returncode, 0)
        self.assertEqual("All men must die", result.stdout)

    def test_rsa_generate_short(self):
        result = run_binary("rsa -g d3 e3")
        self.assertEqual(result.returncode, 0)
        self.assertEqual("public key: 0101-19bb\nprivate key: 9d5b-19bb\n", result.stdout)
    def test_rsa_encrypt_short(self):
        result = run_binary("rsa -c 0101-19bb", "WF")
        self.assertEqual(result.returncode, 0)
        self.assertEqual("8f84", result.stdout)
    def test_rsa_decrypt_short(self):
        result = run_binary("rsa -d 9d5b-19bb", "8f84")
        self.assertEqual(result.returncode, 0)
        self.assertEqual("WF", result.stdout)

    def test_rsa_generate_long(self):
        result = run_binary("rsa -g 4b1da73924978f2e9c1f04170e46820d648edbee12ccf4d4462af89b080c86e1 "
                            "bb3ca1e126f7c8751bd81bc8daa226494efb3d128f72ed9f6cacbe96e14166cb")
        self.assertEqual(result.returncode, 0)
        self.assertEqual("public key: 010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3\n"
                         "private key: 81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3\n", result.stdout)
    def test_rsa_encrypt_long(self):
        result = run_binary("rsa -c 010001-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3", "The night is dark and full of terrors")
        self.assertEqual(result.returncode, 0)
        self.assertEqual("445b349e7318ad6af16b0bbb718be88ba1c41751f95751cd58857f88fe31f970405c6ec3f16d79172543bf4e571b5596d212f3e79cd08ef14abd244e325b80", result.stdout)
    def test_rsa_decrypt_long(self):
        result = run_binary("rsa -d 81b08f4eb6dd8a4dd21728e5194dfc4e349829c9991c8b5e44b31e6ceee1e56a11d66ef23389be92ef7a4178470693f509c90b86d4a1e1831056ca0757f3e209-c9f91a9ff3bd6d84005b9cc8448296330bd23480f8cf8b36fd4edd0a8cd925de139a0076b962f4d57f50d6f9e64e7c41587784488f923dd60136c763fd602fb3", "445b349e7318ad6af16b0bbb718be88ba1c41751f95751cd58857f88fe31f970405c6ec3f16d79172543bf4e571b5596d212f3e79cd08ef14abd244e325b80")
        self.assertEqual(result.returncode, 0)
        self.assertEqual("The night is dark and full of terrors\n", result.stdout)

if __name__ == "__main__":
    unittest.main()
