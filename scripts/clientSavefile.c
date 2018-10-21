/*
 * clientSaveFile.c
 * ================
*/

#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>


int main (int argc, char *argv[])
{
    int socket_nummer, laenge, ergebnis, anzahl;
    struct sockaddr_in adresse;
    char empfangene_zeichen[65000];
    FILE *datei;
    unsigned short int portnummer = 80;
    char ip_adresse[] = "127.0.0.1";
    char befehl[] = "GET /hallo.txt HTTP/1.1\r\nHost: Bubi\r\n\r\n";
    char dateiname[] = "data/empfangen.txt";

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

    printf("\nVerbindung zu IP %s an Port %d\n", ip_adresse, portnummer);

    if (ergebnis == -1)
        perror("Keine Verbindung erfolgt\n");
    else
    {
        printf("Verbindung erfolgt");
        printf(", sende HTTP-Befehl\n\n%s\n", befehl);

        anzahl = write(socket_nummer, befehl, sizeof(befehl));
        printf("es wurden %d Zeichen gesendet\n", anzahl);

        anzahl = read(socket_nummer, empfangene_zeichen, sizeof(empfangene_zeichen));
        empfangene_zeichen[anzahl] = '\0';

        printf("Es wurden %d Zeichen empfangen", anzahl);
        printf("\n\n%s\n", empfangene_zeichen);

        if (strstr(empfangene_zeichen, "200 OK") == NULL)
            printf("Der Server hat die Datei nicht gesendet.\n");
        else
        {
            printf("Der Server hat die Datei gesendet\n");

            datei = fopen(dateiname, "wt");

            if (datei == NULL)
            {
                printf("Die Datei %s ", dateiname);
                printf("konnte nicht geöffnet werden\n");
            }
            else
            {
                printf("Empfangene Daten werden ");
                printf("in %s gespeichert\n", dateiname);

                fprintf(datei, "%s", empfangene_zeichen);
                fclose(datei);
            }
        }
    }
    close(socket_nummer);
    printf("\n\nProgramm beendet\n\n");
    return 0;
}
