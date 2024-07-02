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
int main()
{
    int sock, len, n;
    char buf[N], * msg = "Сообщение клиенту от сервера.";
    struct sockaddr_in servAddr, clientAddr;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror(" Сокет не открылся.");
        return 1;
    }
    bzero(&servAddr, sizeof(servAddr));
    bzero(&clientAddr, sizeof(clientAddr));

    servAddr.sin_family = AF_INET;
    servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servAddr.sin_port = 0;
    if (bind(sock, (const struct sockaddr*)&servAddr, sizeof(servAddr)) < 0)
    {
        perror(" Сервер не удалось связать.");
        return 1;
    }
    
    len = sizeof(servAddr);
    if (getsockname(sock, (struct sockaddr*)&servAddr, &len))
    {
        perror(" Проблема с getsockname.");
        return 1;
    }
    printf(" Номер порта сервера: %d\n", ntohs(servAddr.sin_port));

    len = sizeof(clientAddr);
    if ((n = recvfrom(sock, (char*)buf, N, MSG_WAITALL, (struct sockaddr*)&clientAddr, &len)) < 0)
    {
        perror(" Проблема сокетом клиента.");
        return 1;
    }
    buf[n] = '\0';

    printf(" Полученная информация от клиента:\n");
    printf(" IP адрес клиента: %s\n", inet_ntoa(clientAddr.sin_addr));
    printf(" PORT клиента: %d\n", ntohs(clientAddr.sin_port));
    printf(" Длина сообщения: %d\n", n);
    printf(" Сообщение: %s\n\n", buf);

    printf(" Отправлено сообщение клиенту.\n");
    sendto(sock, (const char*)msg, strlen(msg), 0, (const struct sockaddr*)&clientAddr, sizeof(clientAddr));
    return 0;
}