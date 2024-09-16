#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <openssl/evp.h>  // Include OpenSSL for decryption functions

// Function to decrypt data using AES
void decryptAES(const unsigned char *key, const unsigned char *ciphertext, unsigned char *plaintext, int size);

#endif // DECRYPTION_H
