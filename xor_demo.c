#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void xor_bytes(uint8_t *bytes, size_t length, uint8_t key)
{
    for (size_t i = 0; i < length; i++) {
        bytes[i] ^= key;
    }
}

int main(int argc, char **argv)
{
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [\"text\"]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *message = argc == 2 ? argv[1] : "BOOK";
    const uint8_t key = 0x5A;
    size_t length = strlen(message);
    uint8_t *bytes = malloc(length + 1);
    if (bytes == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }
    memcpy(bytes, message, length + 1);

    printf("Plaintext:  %s\nKey:        %02X\n", message, (unsigned)key);
    xor_bytes(bytes, length, key);
    printf("Ciphertext:");
    for (size_t i = 0; i < length; i++) {
        printf(" %02X", (unsigned)bytes[i]);
    }
    putchar('\n');

    // An encoded byte can be zero. Use the original length on both passes.
    xor_bytes(bytes, length, key);
    printf("Recovered:  %s\n", (char *)bytes);
    free(bytes);
    return EXIT_SUCCESS;
}
