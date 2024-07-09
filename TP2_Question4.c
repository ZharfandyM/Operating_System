#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void copyFile(const char *source, const char *destination) {
    int srcFD, destFD, n;
    char buffer[BUFFER_SIZE];

    // Buka file sumber
    srcFD = open(source, O_RDONLY);
    if (srcFD < 0) {
        perror("Error opening source file");
        exit(EXIT_FAILURE);
    }

    // Buka file tujuan
    destFD = open(destination, O_WRONLY | O_CREAT | O_EXCL, 0644);
    if (destFD < 0) {
        perror("Error opening destination file");
        close(srcFD);
        exit(EXIT_FAILURE);
    }

    // Baca dari sumber dan tulis ke tujuan
    while ((n = read(srcFD, buffer, BUFFER_SIZE)) > 0) {
        if (write(destFD, buffer, n) != n) {
            perror("Error writing to destination file");
            close(srcFD);
            close(destFD);
            exit(EXIT_FAILURE);
        }
    }

    if (n < 0) {
        perror("Error reading from source file");
    }

    close(srcFD);
    close(destFD);
    printf("File copied successfully.\n");
}

int main() {
    char source[100], destination[100];

    printf("Enter source file name: ");
    scanf("%s", source);
    printf("Enter destination file name: ");
    scanf("%s", destination);

    copyFile(source, destination);

    return 0;
}
