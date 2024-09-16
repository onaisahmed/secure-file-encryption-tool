#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <openssl/evp.h>  // Include OpenSSL for encryption functions

// Function to encrypt data using AES
void encryptAES(const unsigned char *key, const unsigned char *plaintext, unsigned char *ciphertext, int size);

#endif // ENCRYPTION_H
