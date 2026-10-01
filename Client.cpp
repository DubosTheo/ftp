#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char const* argv[])
{
    int sockD = socket(AF_INET, SOCK_STREAM, 0);
    if (sockD == -1) {
        perror("Socket creation failed");
        return 1;
    }
    struct sockaddr_in servAddr;
    memset(&servAddr, 0, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(4242); // Assure-toi que le port correspond à ton serveur
    servAddr.sin_addr.s_addr = INADDR_ANY;

    int connectStatus = connect(sockD, (struct sockaddr*)&servAddr, sizeof(servAddr));

    if (connectStatus == -1) {
        printf("Connection error...\n");
        close(sockD);
        return 1;
    }

    printf("[+] Connected to server!\n");

    // 1. Lire le message d'accueil du serveur (ex: "220 Service ready\r\n")
    char strData[BUFFER_SIZE];
    ssize_t bytesRead = recv(sockD, strData, sizeof(strData) - 1, 0);
    if (bytesRead > 0) {
        strData[bytesRead] = '\0'; // Securise la chaîne C
        printf("[Server] %s", strData);
    }

    // 2. Boucle d'envoi de commandes
    char inputBuffer[BUFFER_SIZE];
    while (1) {
        printf("> ");
        fflush(stdout);

        if (fgets(inputBuffer, sizeof(inputBuffer), stdin) == NULL) {
            break; // Ctrl+D
        }

        // Nettoyer le saut de ligne généré par fgets (\n -> \r\n)
        size_t len = strlen(inputBuffer);
        if (len > 0 && inputBuffer[len - 1] == '\n') {
            inputBuffer[len - 1] = '\0';
        }

        if (strcmp(inputBuffer, "exit") == 0) {
            break;
        }

        // Ajouter impérativement \r\n pour le parser de ton serveur
        char command[BUFFER_SIZE];
        snprintf(command, sizeof(command), "%s\r\n", inputBuffer);

        // Envoyer au serveur
        send(sockD, command, strlen(command), 0);

        // Attendre la réponse du serveur
        bytesRead = recv(sockD, strData, sizeof(strData) - 1, 0);
        if (bytesRead <= 0) {
            printf("[-] Server disconnected.\n");
            break;
        }

        strData[bytesRead] = '\0';
        printf("[Server] %s", strData);
    }

    close(sockD);
    return 0;
}
