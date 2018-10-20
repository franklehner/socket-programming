/*
 * clientResponseAnalyze.c
 * =======================
*/

#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>


int main (int argc, char *argv[])
{
    int socket_nummer;
    int laenge;
    int ergebnis;
    int anzahl;
    struct sockaddr_in adresse;
    char empfangene_zeichen[65000];

    unsigned short int portnummer = 80;
    char ip_adresse[] = "127.0.0.1";

    char befehl[] = "GET /hallo.txt HTTP/1.1\r\nHost: Bubi\r\n\r\n";

    socket_nummer = socket(AF_INET, SOCK_STREAM, 0);

    adresse.sin_family = AF_INET;
    inet_pton(AF_INET, ip_adresse, &adresse.sin_addr.s_addr);
    adresse.sin_port = htons(portnummer);

    laenge = sizeof(adresse);

    ergebnis = connect(
        socket_nummer,
        (struct sockaddr *)&adresse,
        laenge
    );

    printf("\nVerbindung zu IP %s", ip_adresse);
    printf(" an Port %d", portnummer);

    if (ergebnis == -1)
        perror("\nKeine Verbindung erfolgt\n");
    else
    {
        printf("\nVerbindung erfolgt");
        printf(", sende HTTP-Befehl:\n\n%s", befehl);

        anzahl = write(socket_nummer, befehl, sizeof(befehl));

        printf("\nes wurden %d Zeichen gesendet", anzahl);

        anzahl = read(socket_nummer, empfangene_zeichen, sizeof(empfangene_zeichen));
        printf("\nes wurden %d Zeichen empfangen: ", anzahl);
        printf("\n\n%s", empfangene_zeichen);

        if (strstr(empfangene_zeichen, "200 OK") == NULL)
            printf("\nDer Server hat die Datei nicht gesendet.");
        else
            printf("\nDer Server hat die Datei gesendet");
    }

    close(socket_nummer);
    printf("\nProgramm beendet\n\n");
    return 0;
}
