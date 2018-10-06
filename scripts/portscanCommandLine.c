#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(int argc, char *argv[]){
    int socketnumber, length, result;
    unsigned int portnumber;
    struct sockaddr_in addressinfo;
    char *ip_address;

    if (argc != 2)
        printf("\nUsage: bin/portscanCommandline <ip-address>\n");
    else {
        ip_address = argv[1];
        printf("\nVerbindungsaufbau an IP-Adresse: %s", ip_address);

        for (portnumber = 0; portnumber < 65535; portnumber++) {
            socketnumber = socket(AF_INET, SOCK_STREAM, 0);
            addressinfo.sin_family = AF_INET;
            inet_pton(AF_INET, ip_address, &addressinfo.sin_addr.s_addr);
            addressinfo.sin_port = htons(portnumber);
            length = sizeof(addressinfo);
            result = connect(
                socketnumber,
                (struct sockaddr *)&addressinfo,
                length
            );

            if (result == 0) {
                printf("\nVerbindungsaufbau erfolgreich");
                printf("\nIP-Adresse %s\nPort %u", ip_address, portnumber);
            }

            close(socketnumber);
        }
        printf("\n");
    }

    return(0);
}
