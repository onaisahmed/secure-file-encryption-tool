#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/aes.h>

#define AES_KEY_SIZE 16  // 128-bit key for AES-128
#define AES_BLOCK_SIZE 16 // AES block size

void encryptAES(const unsigned char *key, const unsigned char *plaintext, unsigned char *ciphertext, int size) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int ciphertext_len;

    ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, NULL);
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, size);
    ciphertext_len = len;
    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertext_len += len;
    EVP_CIPHER_CTX_free(ctx);
}

void decryptAES(const unsigned char *key, const unsigned char *ciphertext, unsigned char *plaintext, int size) {
    EVP_CIPHER_CTX *ctx;
    int len;
    int plaintext_len;

    ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, NULL);
    EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, size);
    plaintext_len = len;
    EVP_DecryptFinal_ex(ctx, plaintext + len, &len);
    plaintext_len += len;
    EVP_CIPHER_CTX_free(ctx);
}

void getFileSize(FILE *inputFile, long *fileSize) {
    fseek(inputFile, 0, SEEK_END);
    *fileSize = ftell(inputFile);
    rewind(inputFile);
}

int main(int argc, char *argv[]) {
    FILE *inputFile;
    FILE *outputFile;
    char *buffer = NULL;
    unsigned char *ciphertext = NULL;
    unsigned char *decryptedText = NULL;
    long fileSize;

    if (argc != 5) {
        printf("Usage: %s <encrypt|decrypt> <input file> <output file> <key>\n", argv[0]);
        return 1;
    }

    char *mode = argv[1];
    char *inputFileName = argv[2];
    char *outputFileName = argv[3];
    unsigned char key[AES_KEY_SIZE];
    strncpy((char *)key, argv[4], AES_KEY_SIZE); // Copy key from argv[4] to key

    if (strlen(argv[4]) != AES_KEY_SIZE) {
        printf("Error: Key must be %d bytes long.\n", AES_KEY_SIZE);
        return 1;
    }


    inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL) {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    getFileSize(inputFile, &fileSize);

    buffer = (char *)malloc(fileSize * sizeof(char));
    if (buffer == NULL) {
        printf("Error: Memory allocation failed for buffer.\n");
        fclose(inputFile);
        return 1;
    }

    fread(buffer, sizeof(char), fileSize, inputFile);
    fclose(inputFile);

    if (strcmp(mode, "encrypt") == 0) {
        ciphertext = (unsigned char *)malloc(fileSize + AES_BLOCK_SIZE);  // Allocate extra space for padding
        if (ciphertext == NULL) {
            printf("Error: Memory allocation failed for ciphertext.\n");
            free(buffer);
            return 1;
        }

        encryptAES(key, (unsigned char *)buffer, ciphertext, fileSize);

        outputFile = fopen(outputFileName, "wb");
        if (outputFile == NULL) {
            printf("Error: Could not open output file for encryption.\n");
            free(buffer);
            free(ciphertext);
            return 1;
        }

        fwrite(ciphertext, sizeof(char), fileSize + AES_BLOCK_SIZE, outputFile);
        fclose(outputFile);
        printf("File encrypted successfully.\n");

        free(ciphertext);
    } else if (strcmp(mode, "decrypt") == 0) {
        decryptedText = (unsigned char *)malloc(fileSize);
        if (decryptedText == NULL) {
            printf("Error: Memory allocation failed for decrypted text.\n");
            free(buffer);
            return 1;
        }

        decryptAES(key, (unsigned char *)buffer, decryptedText, fileSize);

        outputFile = fopen(outputFileName, "wb");
        if (outputFile == NULL) {
            printf("Error: Could not open output file for decryption.\n");
            free(buffer);
            free(decryptedText);
            return 1;
        }

        fwrite(decryptedText, sizeof(char), fileSize, outputFile);
        fclose(outputFile);
        printf("File decrypted successfully.\n");

        free(decryptedText);
    } else {
        printf("Error: Invalid mode. Use 'encrypt' or 'decrypt'.\n");
        free(buffer);
        return 1;
    }

    free(buffer);
    return 0;
}
