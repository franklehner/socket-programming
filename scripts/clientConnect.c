#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>


int main()
{
    int socket_number, length, result;
    struct sockaddr_in addressinfo;

    socket_number = socket(AF_INET, SOCK_STREAM, 0);
    addressinfo.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &addressinfo.sin_addr.s_addr);
    addressinfo.sin_port = htons(80);
    length = sizeof(addressinfo);
    result = connect(
        socket_number,
        (struct sockaddr *)&addressinfo,
        length
    );

    if (result == 0)
        printf("\nVerbindungsaufbau erfolgreich\n");
    else
        perror("\nFehler beim Verbindungsaufbau\n");

    return(0);
}
