#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[1024];

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Port number
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding");
        exit(EXIT_FAILURE);
    }

    // Listen
    listen(serverSocket, 5);
    printf("Server listening...\n");

    socklen_t clientLen = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &clientLen);
    if (clientSocket == -1) {
        perror("Error accepting connection");
        exit(EXIT_FAILURE);
    }

    while (1) {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived == -1) {
            perror("Error receiving data");
            exit(EXIT_FAILURE);
        } else if (bytesReceived == 0) {
            printf("Client disconnected\n");
            break;
        } else {
            printf("Received: %s\n", buffer);
        }
    }

    close(clientSocket);
    close(serverSocket);
    return 0;
}
