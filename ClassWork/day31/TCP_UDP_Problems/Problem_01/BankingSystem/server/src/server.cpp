#include <iostream>
#include <thread>
#include <netinet/in.h>
#include <unistd.h>
#include "../include/AccountManager.h"
#include "../include/Logger.h"

#define SERVER_PORT 8080

/*
 TCP is chosen because:
 - Account verification is CRITICAL
 - Packet loss is unacceptable
 - Order and reliability are mandatory
*/
AccountManager accountManager("data/accounts.txt");
Logger logger("logs/server.log");

void handleClient(int clientSocket) {
    int accountNumber, pin;

    recv(clientSocket, &accountNumber, sizeof(accountNumber), 0);
    recv(clientSocket, &pin, sizeof(pin), 0);

    double balance;
    bool valid = accountManager.verifyAccount(accountNumber, pin, balance);

    if (valid) {
        send(clientSocket, &balance, sizeof(balance), 0);
    } else {
        logger.log("Invalid login attempt for Account: " +
                   std::to_string(accountNumber));
        double error = -1;
        send(clientSocket, &error, sizeof(error), 0);
    }

    close(clientSocket);
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));
    listen(serverSocket, 10);

    std::cout << "Bank Server running on port "
              << SERVER_PORT << std::endl;

    while (true) {
        int clientSocket = accept(serverSocket, nullptr, nullptr);
        std::thread(handleClient, clientSocket).detach();
    }
}
