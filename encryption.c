#include "encryption.h"
#include <openssl/evp.h>
#include <string.h>

/**
 * Encrypts the plaintext using AES-128-CBC with a given key.
 * 
 * @param key The encryption key (must be 16 bytes for AES-128).
 * @param plaintext The plaintext data to encrypt.
 * @param ciphertext The buffer to store the encrypted data.
 * @param size The size of the plaintext data.
 */
void encryptAES(const unsigned char *key, const unsigned char *plaintext, unsigned char *ciphertext, int size) {
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) {
        printf("Error: Could not create context for encryption.\n");
        exit(1);
    }

    // Initialize the encryption operation with AES-128-CBC mode
    if (EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, NULL) != 1) {
        printf("Error: Could not initialize encryption.\n");
        EVP_CIPHER_CTX_free(ctx);
        exit(1);
    }

    int len;
    int ciphertext_len;

    // Encrypt the plaintext
    if (EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, size) != 1) {
        printf("Error: Encryption failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        exit(1);
    }
    ciphertext_len = len;

    // Finalize encryption
    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1) {
        printf("Error: Finalizing encryption failed.\n");
        EVP_CIPHER_CTX_free(ctx);
        exit(1);
    }
    ciphertext_len += len;

    // Clean up
    EVP_CIPHER_CTX_free(ctx);
}
