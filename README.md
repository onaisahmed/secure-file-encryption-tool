# Secure File Encryption Tool

A C project for developing a secure file encryption tool. This project demonstrates key concepts in C programming, including file handling, dynamic memory management, and secure encryption algorithms.

## Features

- **File Encryption/Decryption**: Securely encrypt and decrypt files.
- **Dynamic Memory Management**: Efficiently handle file data using dynamic memory allocation.
- **File Handling**: Read and write encrypted data to and from files.
- **Secure Algorithms**: Implement encryption and decryption algorithms to protect file contents.

## Getting Started

### Prerequisites

- C Compiler (e.g., GCC)
- Basic knowledge of C programming, pointers, and memory management

### Installation

1. Clone the repository:
   git clone https://github.com/onaisahmed/secure-file-encryption-tool.git

2. Navigate to the project directory:
   cd secure-file-encryption-tool

3. Compile the project:
   gcc -o encryption_tool main.c encryption.c decryption.c

### Usage

1. Encrypt a File:
   ./encryption_tool encrypt input.txt output.enc

2. Decrypt a File:
   ./encryption_tool decrypt output.enc decrypted.txt
