void handleClient(int clientSocket) {
    int accNo, pin;

    // --- AUTH PHASE ---
    recv(clientSocket, &accNo, sizeof(accNo), 0);
    recv(clientSocket, &pin, sizeof(pin), 0);

    double balance;
    if (!manager.authenticate(accNo, pin, balance)) {
        logger.log("Authentication failed for Account: " +
                   std::to_string(accNo));

        double err = AUTH_FAILED;
        send(clientSocket, &err, sizeof(err), 0);
        close(clientSocket);
        return;
    }

    // Send current balance
    send(clientSocket, &balance, sizeof(balance), 0);

    // --- TRANSACTION PHASE ---
    int choice;
    double amount;
    recv(clientSocket, &choice, sizeof(choice), 0);
    recv(clientSocket, &amount, sizeof(amount), 0);

    double updatedBalance;
    int status = manager.processTransaction(
        accNo,
        static_cast<TransactionType>(choice),
        amount,
        updatedBalance
    );

    if (status == 0) {
        send(clientSocket, &updatedBalance, sizeof(updatedBalance), 0);
    } else {
        logger.log("Transaction failed | Account: " +
                   std::to_string(accNo));
        double err = status;
        send(clientSocket, &err, sizeof(err), 0);
    }

    close(clientSocket);
}
