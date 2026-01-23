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
    int sd, csd;
    socklen_t clientLen;
    struct sockaddr_in serv_addr, client_addr;
    char msg[MAXBUFF], reply[MAXBUFF];

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("socket");
        return 1;
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    bind(sd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(sd, 5);

    cout << "[server] listening on 127.0.0.1:" << PORT << endl;

    clientLen = sizeof(client_addr);
    csd = accept(sd, (struct sockaddr*)&client_addr, &clientLen);

    cout << "[server] client connected from "
         << inet_ntoa(client_addr.sin_addr)
         << ":" << ntohs(client_addr.sin_port) << endl;

    while (1) {
        memset(msg, 0, MAXBUFF);
        int n = read(csd, msg, MAXBUFF);

        if (n <= 0) {
            cout << "[server] client disconnected unexpectedly\n";
            break;
        }

        cout << "[server] received from client: " << msg << endl;

        // Client wants to quit
        if (strcmp(msg, "quit") == 0) {
            strcpy(reply, "[server], bye");
            write(csd, reply, strlen(reply));

            cout << "[server] sent to client: [server], bye\n";
            cout << "[server] closing connection\n";
            break;
        }

        // Normal reply
        strcpy(reply, "[server], ");
        strcat(reply, msg);

        write(csd, reply, strlen(reply));
        cout << "[server] sent to client: " << reply << endl;
    }

    close(csd);
    close(sd);

    cout << "[server] server shutdown\n";
    return 0;
}