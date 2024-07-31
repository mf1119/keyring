"""Print some pseudorandom numbers."""

"""
X[n + 1] = (a * X[n] + c) % m

Modulus:        0 < m
Multiplier:     0 < a < m
Increment:      0 <= c < m
Seed:           0 <= X0 < m
"""
import sys

ASCII_CHARS = 95
PINS = 69
KEY_PIN = 14
PASSWORD = "This is my password."

M_MOD = ASCII_CHARS
A_MULT = PINS
C_INCR = KEY_PIN
SEED = len(PASSWORD)


def val_is_in_array(arr, val, len):
    for i in range(0, len):
        if arr[i] == val:
            return True
    return False


def cipher_next_val(arr, length):
    last_x = arr[length - 1]
    new_x = ((A_MULT * last_x) + C_INCR) % M_MOD
    return new_x


def generate_cipher(length):
    cipher = []
    cipher.append(SEED)
    print(cipher[0])
    for i in range(1, length):
        adding_iteration = 0
        new_val = cipher_next_val(cipher, i)
        while val_is_in_array(cipher, new_val, i):
            new_val = (new_val + 1) % length
            adding_iteration += 1
            if adding_iteration > length:
                print("Couldn't add value! Something went wrong. :(")
                sys.exit(-1)
        cipher.append(new_val)
        print(new_val)
    return cipher


def main():
    cipher = generate_cipher(ASCII_CHARS)


if __name__ == "__main__":
    main()
