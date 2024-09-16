#include "decryption.h"
#include <openssl/evp.h>
#include <string.h>

/**
 * Decrypts the ciphertext using AES-128-CBC with a given key.
 * 
 * @param key The decryption key (must be 16 bytes for AES-128).
 * @param ciphertext The encrypted data to decrypt.
 * @param plaintext The buffer to store the decrypted data.
 * @param size The size of the ciphertext data.
 */
void decryptAES(const unsigned char *key, const unsigned char *ciphertext, unsigned char *plaintext, int size) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        printf("Error: Could not create context for decryption.\n");
        exit(1);
    }

    // Initialize the decryption operation with AES-128-CBC mode
    if (EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, NULL) != 1) {
        printf("Error: Could not initialize decryption.\n");
        EVP_CIPHER_CTX_free(ctx);
        exit(1);
    }

    int len;
    int plaintext_len;

    // Decrypt the ciphertext
    if (EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, size) != 1) {
        printf("Error: Decryption failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        exit(1);
    }
    plaintext_len = len;

    // Finalize decryption
    if (EVP_DecryptFinal_ex(ctx, plaintext + len, &len) != 1) {
        printf("Error: Finalizing decryption failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        exit(1);
    }
    plaintext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
}
