#include <stdio.h>
#include <stdlib.h>

/*
    @param inputFile: The file to get the size of
    @param fileSize: A pointer to a long variable to store the file size in
*/
void getFileSize(FILE *inputFile, long *fileSize) {
    fseek(inputFile, 0, SEEK_END);  // Move to the end of the file
    *fileSize = ftell(inputFile);   // Get the current file pointer position (file size)
    rewind(inputFile);              // Move back to the beginning of the file
}



int main() {
    FILE *inputFile;
    FILE *outputFile;
    char *buffer;
    long fileSize;

    // Open the input file
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    // Find the size of the file
    getFileSize(inputFile, &fileSize);
  

    // Allocate memory for the buffer
    buffer = (char *)malloc(fileSize * sizeof(char));
    if (buffer == NULL) {
        printf("Error: Memory allocation failed.\n");
        fclose(inputFile);
        return 1;
    }

    // Read the file into the buffer
    fread(buffer, sizeof(char), fileSize, inputFile);

    // Open the output file
    outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Error: Could not open output file.\n");
        free(buffer); // Free the allocated memory
        fclose(inputFile);
        return 1;
    }

    // Write the buffer to the output file
    fwrite(buffer, sizeof(char), fileSize, outputFile);

    // Clean up
    free(buffer);     // Free the allocated memory
    fclose(inputFile);
    fclose(outputFile);

    printf("File copied successfully.\n");

    return 0;
}
