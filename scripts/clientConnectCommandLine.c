#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>



int main(int argc, char *argv[]){
    int socket_number, length, result;
    unsigned int port_number;
    struct sockaddr_in addressinfo;
    char *ip_address;

    if (argc != 3){
        printf("\nFalsche Anzahl von Parametern!");
        printf("\nBitte IP-Adresse und Portnummer eingeben!");
        printf("\n");
    }
    else{
        ip_address = argv[1];
        port_number = atoi(argv[2]);

        printf("\nZiel = %s Port %u", ip_address, port_number);
        socket_number = socket(AF_INET, SOCK_STREAM, 0);
        addressinfo.sin_family = AF_INET;
        inet_pton(AF_INET, ip_address, &addressinfo.sin_addr.s_addr);
        addressinfo.sin_port = htons(port_number);
        length = sizeof(addressinfo);
        result = connect(
            socket_number,
            (struct sockaddr *)&addressinfo,
            length
        );

        if (result == 0)
            printf("\nVerbindungsaufbau erfolgreich");
        else
            perror("\nVerbindungsaufbau fehlgeschlagen");

        close(socket_number);
    }

    printf("\n");
}
