#pragma once
#ifndef MANAGER_H
#define MANAGER_H
#include <iostream>
struct Address
{
    char* address;
    char* city;
    char* state;
    int zip_code;
};

struct CustomerAccount
{
    char* name;
    Address address;
    long long phoneNum;
    float balance;
    char accountNum[6];

    void OpenCustomerAccount(CustomerAccount* customers[], int& accountsOpen);
    int SearchCustomer(CustomerAccount* customers[], int accountsOpen, const char* accountNum);
    bool UpdateCustomerAccount(CustomerAccount* customers[], int accountsOpen, const char* accountNumVal);
    bool UpdateCustomerAccount(CustomerAccount* customers[], int accountsOpen, const char* accountNumVal, long long phoneVal);
    bool UpdateCustomerAccount(CustomerAccount* customers[], int accountsOpen, const char* accountNumVal, float balanceVal);
    void DisplayAllCustomers(CustomerAccount* customers[], int accountsOpen);
    bool isValidAccountNumber(const char* accountNum);
};
#endif