#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define DEBUG (0)

#define HID_REPORT_SIZE (8)
#define STRING_LEN(s) ((sizeof(s) / sizeof(s[0])) - 1)

#define NUMBER_OF_GPIO_PINS (69)
#define FIRST_PIN (2)

/*--------------------------------------------------------------------------------------------------
 * Local Variables
 *--------------------------------------------------------------------------------------------------*/

const char charset[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
static char cipher[STRING_LEN(charset) + 1];
const char password[] = "MyPassword";

/*--------------------------------------------------------------------------------------------------
 * Local Function Prototypes
 *--------------------------------------------------------------------------------------------------*/
static uint8_t get_index_in_array(const char* char_set, char target, uint8_t len);
static bool is_val_in_array(char* cipher, char new_val, uint8_t len);
static void generate_cipher_lincog(const char* password, uint8_t password_len, const char* char_set, uint8_t char_set_len, uint8_t key);
static void decode_string(char* dest_str, char* str, uint8_t str_len, char* cipher, uint8_t cipher_len, const char* char_set);
/*--------------------------------------------------------------------------------------------------
 * Global Function Definitions
 *--------------------------------------------------------------------------------------------------*/

int main() {
    // printf("Some words!\n");
    // printf("Charset Length: %li\n", STRING_LEN(charset));
    // printf("Password Length: %li\n", STRING_LEN(password));
    generate_cipher_lincog(password, STRING_LEN(password), charset, STRING_LEN(charset), 5);
    printf("%s\n", cipher);

    char encoded[] = "Iy1GssaSlX";
    char decoded[STRING_LEN(password) + 1];
    decode_string(decoded, encoded, STRING_LEN(encoded), cipher, STRING_LEN(cipher), charset);
    printf("%s\n", decoded);
    return 1;
}
/*--------------------------------------------------------------------------------------------------
 * Local Function Definitions
 *--------------------------------------------------------------------------------------------------*/
static uint8_t get_index_in_array(const char* char_set, char target, uint8_t len)
{
    for (uint8_t i = 0; i < len; i++)
    {
        if (char_set[i] == target)
        {
            return i;
        }
    }
    return 0xFF;
}

static bool is_val_in_array(char* cipher, char new_val, uint8_t len){
    for (uint8_t i = 0; i < len; i++)
    {
        // printf("%c ?= %c \n", cipher[i], new_val);
        if (cipher[i] == new_val){
            // printf("%c == %c \n", cipher[i], new_val);
            return true;
        }
    }
    return false;
}

static void generate_cipher_lincog(const char* password, uint8_t password_len, const char* char_set, uint8_t char_set_len, uint8_t key){
    uint16_t m_mod = char_set_len;
    uint16_t a_mult = NUMBER_OF_GPIO_PINS;
    uint16_t c_incr = key;
    uint16_t seed = (uint32_t) ((a_mult * (password_len + (uint16_t) key)) + c_incr) % m_mod;
    // printf("m_mod: %u\n", m_mod);
    // printf("key: %u\n", key);
    // printf("password_len: %u\n", password_len);
    // printf("(password_len + (uint16_t) key): %u, \n", (password_len + (uint16_t) key));
    // printf("a_mult * (password_len + (uint16_t) key): %u, \n", (a_mult * (password_len + (uint16_t) key)));
    // printf("((a_mult * (password_len + (uint16_t) key)) + c_incr): %u, \n", ((a_mult * (password_len + (uint16_t) key)) + c_incr));
    // printf("Seed: %u, %c\n", seed, char_set[seed]);
    cipher[0] = char_set[seed];

    for (uint8_t i = 1; i < char_set_len; i++)
    {
        // printf("=====\n");
        // uint8_t add_attempt = 0;
        // printf("Last char: %c, ind: %u\n", cipher[i - 1], get_index_in_array(char_set, cipher[i - 1], char_set_len));
        uint8_t new_val = (uint32_t) ((a_mult * get_index_in_array(char_set, cipher[i - 1], char_set_len)) + c_incr) % m_mod;
        // printf("new_val = %c, %u\n", char_set[new_val], new_val);
        while (is_val_in_array(cipher, char_set[new_val], i - 1))
        {
            new_val = (new_val + 1) % char_set_len;
            // printf("Collision! %c\n", char_set[new_val]);
        }
        cipher[i] = char_set[new_val];
        // printf("%s", cipher);
        // printf("\n");
    }
}

static void decode_string(char* dest_str, char* str, uint8_t str_len, char* cipher, uint8_t cipher_len, const char* char_set)
{
    for (uint8_t i = 0; i < str_len; i++)
    {
        uint8_t ind = get_index_in_array(cipher, str[i], cipher_len);
        dest_str[i] = charset[ind];
    }
}
