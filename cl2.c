#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
const int N = 1024;
int main(int argc, char* argv[])
{
    int sock, len, n;
    char buf[N];
    struct sockaddr_in servAddr, clientAddr;
    struct hostent* hp, * gethostbyname();
    if (argc < 4)
    {
        printf(" Ввести IP_сервера порт сообщение\n");
        return 1;
    }
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror(" Сокет не открылся.");
        return 1;
    }
    bzero(&servAddr, sizeof(servAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(atoi(argv[2]));
    hp = gethostbyname(argv[1]);
    bcopy(hp->h_addr, &servAddr.sin_addr, hp->h_length);

    while (1)
    {
        sendto(sock, (const char*)argv[3], strlen(argv[3]), 0, (const struct sockaddr*)&servAddr, sizeof(servAddr));
        printf(" Сообщение отправлено.\n");
        sleep(atoi(argv[3]));
    }

    close(sock);
    return 0;
}