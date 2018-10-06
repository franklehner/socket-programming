#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>


int main() {
    int socket_number, length, result;
    unsigned int port_number;
    struct sockaddr_in addressinfo;
    char ip_address[] = "127.0.0.1";

    for (port_number = 0; port_number < 65535; port_number++){
        socket_number = socket(AF_INET, SOCK_STREAM, 0);
        addressinfo.sin_family = AF_INET;
        inet_pton(AF_INET, ip_address, &addressinfo.sin_addr.s_addr);
        addressinfo.sin_port = htons(port_number);
        length = sizeof(addressinfo);
        result = connect(socket_number, (struct sockaddr *)&addressinfo, length);

        if (result == 0){
            printf("Verbindungsaufbau erfolgreich an");
            printf(" IP %s - Port %d\n", ip_address, port_number);
        }

        close(socket_number);
    }

    return(0);
}
