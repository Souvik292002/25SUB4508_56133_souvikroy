#include "../include/ATMClient.h"
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

#define SERVER_PORT 8080

void ATMClient::run() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr));

    int accNo, pin;
    std::cout << "Enter Account Number: ";
    std::cin >> accNo;
    std::cout << "Enter PIN: ";
    std::cin >> pin;

    send(sock, &accNo, sizeof(accNo), 0);
    send(sock, &pin, sizeof(pin), 0);

    double balance;
    recv(sock, &balance, sizeof(balance), 0);

    if (balance >= 0)
        std::cout << "Available Balance: " << balance << std::endl;
    else
        std::cout << "Authentication Failed" << std::endl;

    close(sock);
}

int main() {
    ATMClient client;
    client.run();
    return 0;
}
