"""Print some pseudorandom numbers."""

"""
X[n + 1] = (a * X[n] + c) % m

Modulus:        0 < m
Multiplier:     0 < a < m
Increment:      0 <= c < m
Seed:           0 <= X0 < m
"""

import sys

CHARSET_N = r"0123456789"
CHARSET_A = r"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
CHARSET_AN = CHARSET_N + CHARSET_A

PINS = 69


def val_is_in_array(arr, val, len):
    for i in range(0, len):
        if arr[i] == val:
            return True
    return False


def generate_cipher_linear_congruential(password, char_set, key):
    M_MOD = len(char_set)
    A_MULT = PINS
    C_INCR = key
    seed = ((A_MULT * (len(password) + key)) + C_INCR) % M_MOD
    print(f"Seed: {seed}, {char_set[seed]}")
    collisions = 0

    cipher = ""
    cipher += char_set[seed]
    for i in range(1, len(char_set)):
        adding_iteration = 0
        new_val_ind = ((A_MULT * char_set.index(cipher[i - 1])) + C_INCR) % M_MOD
        while val_is_in_array(cipher, char_set[new_val_ind], i):
            collisions += 1
            # print(f"Collision {collisions}: {char_set[new_val_ind]}")

            new_val_ind = (new_val_ind + 1) % M_MOD
            adding_iteration += 1
            if adding_iteration > len(char_set):
                print("Couldn't add value! Something went wrong. :(")
                sys.exit(-1)
        # print(f"Adding: {char_set[new_val_ind]}")
        cipher += char_set[new_val_ind]
    return cipher


def encode_password(str, cipher, char_set):
    encoded_string = ""
    for c in str:
        encoded_string += cipher[char_set.index(c)]
    return encoded_string


def main():
    password = "MyPassword"
    key = 5
    cipher = generate_cipher_linear_congruential(password, CHARSET_AN, key)
    print(f"Cipher: {cipher}")
    print(f"Encoded password: {encode_password(password, cipher, CHARSET_AN)}")


if __name__ == "__main__":
    main()
