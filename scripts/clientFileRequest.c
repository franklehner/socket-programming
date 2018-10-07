#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>


int main() {
    int socketnumber, length, count, result;
    unsigned short int portnumber = 80;
    struct sockaddr_in adresse;
    char received_signs[65000];
    char ip_address[] = "127.0.0.1";
    char command[] = "GET /hallo.txt HTTP/1.1\r\nHost: Bubi\r\n\r\n";

    socketnumber = socket(AF_INET, SOCK_STREAM, 0);
    adresse.sin_family = AF_INET;
    inet_pton(AF_INET, ip_address, &adresse.sin_addr.s_addr);
    adresse.sin_port = htons(portnumber);
    length = sizeof(adresse);
    result = connect(
        socketnumber,
        (struct sockaddr *)&adresse,
        length
    );

    printf("\nVerbindung zu IP %s an Port %d", ip_address, portnumber);

    if (result == -1)
        perror("\nKeine Verbindung erfolgt: ");
    else {
        printf("\nVerbindung erfolgt");
        printf(", sende HTTP-Befehl:\n\n%s", command);

        count = write(socketnumber, command, sizeof(command));

        printf("\nEs wurden %d Zeichen gesendet", count);

        count = read(socketnumber, received_signs, sizeof(received_signs));

        received_signs[count] = '\0';

        printf("\nEs wurden %d Zeichen empfangen:", count);
        printf("\n\n%s", received_signs);
    }

    close(socketnumber);
    printf("\nProgramm beendet\n\n");
    return(0);
}
