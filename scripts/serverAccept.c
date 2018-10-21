/*
 * serverAccept.c
 * ==============
 */

#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]) {
    int server_socket, neuer_socket;
    int laenge;
    struct sockaddr_in serverinfo, clientinfo;
    unsigned short int portnummer = 5000;
    char server_ip[] = "127.0.0.1";
    char client_ip[INET_ADDRSTRLEN];

    printf("\nServer: socket()...");

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    serverinfo.sin_family = AF_INET;
    inet_pton(AF_INET, server_ip, &serverinfo.sin_addr.s_addr);
    serverinfo.sin_port = htons(portnummer);
    laenge = sizeof(serverinfo);

    printf("\nServer: bind()...");

    bind(server_socket, (struct sockaddr *)&serverinfo, laenge);

    printf("\nServer: listen()...");
    printf("\nServer mit IP %s", server_ip);
    printf(" an Port %d wartet...", portnummer);

    listen(server_socket, 3);

    printf("\nServer: accept()...");

    neuer_socket = accept(
        server_socket,
        (struct sockaddr *)&clientinfo,
        &laenge
    );
    inet_ntop(AF_INET, &clientinfo.sin_addr.s_addr, client_ip, INET_ADDRSTRLEN);

    printf("\nVerbindung mit %s", client_ip);

    printf("\nServer: close()...");

    close(server_socket);
    close(neuer_socket);

    printf("\nServerprogramm beendet.\n\n");
    return 0;
}
