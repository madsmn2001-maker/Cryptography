#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CAESAR_SHIFT 7

void caesar_encrypt(const char *text) {
    for (int i = 0; text[i]; i++) {
        if (isupper(text[i]))
            putchar((text[i] - 'A' + CAESAR_SHIFT) % 26 + 'A');
        else if (islower(text[i]))
            putchar((text[i] - 'a' + CAESAR_SHIFT) % 26 + 'a');
        else
            putchar(text[i]);
    }
    putchar('\n');
}

void caesar_decrypt(const char *text) {
    for (int i = 0; text[i]; i++) {
        if (isupper(text[i]))
            putchar((text[i] - 'A' - CAESAR_SHIFT + 26) % 26 + 'A');
        else if (islower(text[i]))
            putchar((text[i] - 'a' - CAESAR_SHIFT + 26) % 26 + 'a');
        else
            putchar(text[i]);
    }
    putchar('\n');
}

void vigenere_encrypt(const char *text, const char *key) {
    int keyLen = strlen(key);
    for (int i = 0, j = 0; text[i]; i++) {
        char c = text[i];
        if (isalpha(c)) {
            int shift = toupper(key[j % keyLen]) - 'A';
            if (isupper(c))
                putchar((c - 'A' + shift) % 26 + 'A');
            else
                putchar((c - 'a' + shift) % 26 + 'a');
            j++;
        } else {
            putchar(c);
        }
    }
    putchar('\n');
}

void vigenere_decrypt(const char *text, const char *key) {
    int keyLen = strlen(key);
    for (int i = 0, j = 0; text[i]; i++) {
        char c = text[i];
        if (isalpha(c)) {
            int shift = toupper(key[j % keyLen]) - 'A';
            if (isupper(c))
                putchar((c - 'A' - shift + 26) % 26 + 'A');
            else
                putchar((c - 'a' - shift + 26) % 26 + 'a');
            j++;
        } else {
            putchar(c);
        }
    }
    putchar('\n');
}

void usage() {
    printf("Usage:\n");
    printf("  crypto MODE ALGORITHM TEXT [KEY]\n");
    printf("\nModes:\n");
    printf("  e, encrypt     Encrypt the input text\n");
    printf("  d, decrypt     Decrypt the input text\n");
    printf("\nAlgorithms:\n");
    printf("  c, caesar      Caesar cipher\n");
    printf("  v, vigenere    Vigenère cipher\n");
    printf("\nExamples:\n");
    printf("  ./main e c HELLO\n");
    printf("  ./main d v LQVRRBOFTQJ UGLE\n");
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        usage();
        return 1;
    }

    char mode = argv[1][0];
    char algo = argv[2][0];
    char *text = argv[3];
    char *key = argc > 4 ? argv[4] : NULL;

    if (mode == 'e') {
        if (algo == 'c') {
            caesar_encrypt(text);
        } else if (algo == 'v') {
            if (!key) {
                fprintf(stderr, "Vigenère cipher requires a key.\n");
                return 1;
            }
            vigenere_encrypt(text, key);
        } else {
            usage();
            return 1;
        }
    } else if (mode == 'd') {
        if (algo == 'c') {
            caesar_decrypt(text);
        } else if (algo == 'v') {
            if (!key) {
                fprintf(stderr, "Vigenère cipher requires a key.\n");
                return 1;
            }
            vigenere_decrypt(text, key);
        } else {
            usage();
            return 1;
        }
    } else {
        usage();
        return 1;
    }

    return 0;
}
