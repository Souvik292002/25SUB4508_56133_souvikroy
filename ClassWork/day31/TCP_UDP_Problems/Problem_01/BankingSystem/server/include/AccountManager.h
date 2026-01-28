#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include <unordered_map>
#include <string>
#include <mutex>
#include "Account.h"

/*
 AccountManager:
 - Loads account data from disk
 - Provides fast in-memory lookup
 - Handles synchronization
*/
class AccountManager {
private:
    std::unordered_map<int, Account> accounts;
    std::mutex accountMutex;

public:
    explicit AccountManager(const std::string& filePath);

    bool verifyAccount(int accountNumber, int pin, double& balance);
};

#endif
