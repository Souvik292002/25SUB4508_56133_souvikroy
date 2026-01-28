#include "../include/AccountManager.h"
#include <fstream>
#include <sstream>

/*
 Loads account data from file into memory.
 Using unordered_map gives O(1) average lookup time,
 critical for peak ATM traffic.
*/
AccountManager::AccountManager(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int accNo, pin;
        double balance;
        char comma;

        ss >> accNo >> comma >> pin >> comma >> balance;
        accounts[accNo] = { pin, balance };
    }
}

/*
 Verifies account number & PIN.
 Mutex ensures thread-safe access
 when multiple ATMs query simultaneously.
*/
bool AccountManager::verifyAccount(int accountNumber, int pin, double& balance) {
    std::lock_guard<std::mutex> lock(accountMutex);

    auto it = accounts.find(accountNumber);
    if (it == accounts.end())
        return false;

    if (it->second.pin != pin)
        return false;

    balance = it->second.balance;
    return true;
}
