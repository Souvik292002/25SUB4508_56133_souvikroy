#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

#define PORT 4003
#define MAXBUFF 1024

int main()
{
    int sd;
    struct sockaddr_in serv_addr;
    char msg[MAXBUFF];

    sd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    while (1) {
        memset(msg, 0, MAXBUFF);

        cout << "client_s: ";
        cin.getline(msg, MAXBUFF);

        write(sd, msg, strlen(msg));

        memset(msg, 0, MAXBUFF);
        read(sd, msg, MAXBUFF);

        cout << "client_r: " << msg << endl << endl;

        if (strcmp(msg, "[server], bye") == 0)
            break;
    }

    close(sd);
    return 0;
}
