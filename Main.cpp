#include <iostream>
#include "Manager.h"
using namespace std;

void copytheArrays(char* newarr, const char* old) {
    while (*old)
    {
        *newarr++ = *old++;
    }
    *newarr = '\0';
}

void generateAccountNumber(int accountIndex, char* accountNum)
{
    int num = 0, firstDigit = 0, secDigit = 0, thDigit = 0;
    num = accountIndex + 1;
    firstDigit = accountIndex / 100;
    secDigit = accountIndex % 100;
    thDigit = secDigit % 10;
    secDigit /= 10;
    accountNum[0] = 'P';
    accountNum[1] = 'K';
    accountNum[2] = '0' + firstDigit;
    accountNum[3] = '0' + secDigit;
    accountNum[4] = '0' + thDigit;
    accountNum[5] = '\0';
}

bool isAllDigits(const char* input, int requiredLength) 
{
    int length = 0;
    while (input[length] != '\0') 
    {
        if (input[length] < '0' || input[length] > '9')
        {
            return false;
        }
        length++;
    }
    return length == requiredLength;
}
bool CustomerAccount::isValidAccountNumber(const char* accountNum) 
{
    return (accountNum[0] == 'P' && accountNum[1] == 'K' && accountNum[2] >= '0' && accountNum[2] <= '9' && accountNum[3] >= '0' && accountNum[3] <= '9' &&
            accountNum[4] >= '0' && accountNum[4] <= '9' && accountNum[5] == '\0'); 
}

void CustomerAccount::OpenCustomerAccount(CustomerAccount* customers[], int& accountsOpen) {
    if (accountsOpen >= 100) 
    {
        cout << "Max accounts reached. Cannot open a new account." << endl;
        return;
    }

    char name[100], address[100], city[50], state[50];
    int zipcode;
    long long phone;
    float balance;

    // Input Name
    while (true) {
        cout << "Enter Name: ";
        cin.ignore();
        cin.getline(name, 100);

        if (name[0] != '\0') break;
        cout << "Name cannot be empty. Try again.\n";
    }

    // Input Address
    while (true) {
        cout << "Enter Address: ";
        cin.getline(address, 100);

        if (address[0] != '\0') break;
        cout << "Address cannot be empty. Try again.\n";
    }

    // Input City
    while (true) {
        cout << "Enter City: ";
        cin.getline(city, 50);

        if (city[0] != '\0') break;
        cout << "City cannot be empty. Try again.\n";
    }

    // Input State
    while (true) {
        cout << "Enter State: ";
        cin.getline(state, 50);

        if (state[0] != '\0') break;
        cout << "State cannot be empty. Try again.\n";
    }

    // Input ZIP Code (5 digits)
    char zipStr[10];
    while (true) {
        cout << "Enter ZIP Code (5 digits): ";
        cin >> zipStr;

        if (isAllDigits(zipStr, 5)) {
            zipcode = 0;
            for (int i = 0; i < 5; i++) {
                zipcode = zipcode * 10 + (zipStr[i] - '0');
            }
            break;
        }
        cout << "Invalid ZIP Code. Must be 5 digits.\n";
    }

    // Input Phone Number (11 digits)
    char phoneStr[20];
    while (true) {
        cout << "Enter Phone Number (11 digits, No dashes): ";
        cin >> phoneStr;

        if (isAllDigits(phoneStr, 11)) {
            phone = 0;
            for (int i = 0; i < 11; i++) {
                phone = phone * 10 + (phoneStr[i] - '0');
            }
            break;
        }
        cout << "Invalid phone number. Must be 11 digits and No -.\n";
    }

    // Input Initial Balance
    while (true) {
        cout << "Enter Initial Balance: ";
        cin >> balance;

        if (balance > 0) 
            break;
        cout << "Balance must be greater than zero.\n";
    }

    // Allocate memory for new account
    customers[accountsOpen] = new CustomerAccount;
    generateAccountNumber(accountsOpen, customers[accountsOpen]->accountNum);

    customers[accountsOpen]->name = new char[100];
    copytheArrays(customers[accountsOpen]->name, name);

    customers[accountsOpen]->address.address = new char[100];
    copytheArrays(customers[accountsOpen]->address.address, address);

    customers[accountsOpen]->address.city = new char[50];
    copytheArrays(customers[accountsOpen]->address.city, city);

    customers[accountsOpen]->address.state = new char[50];
    copytheArrays(customers[accountsOpen]->address.state, state);

    customers[accountsOpen]->address.zip_code = zipcode;
    customers[accountsOpen]->phoneNum = phone;
    customers[accountsOpen]->balance = balance;

    cout << "Account " << customers[accountsOpen]->accountNum << " opened successfully." << endl;
    accountsOpen++;
}
int CustomerAccount::SearchCustomer(CustomerAccount* customers[], int accountsOpen, const char* accountNum)
{
    for (int i = 0; i < accountsOpen; ++i)
    {
        bool match = true;
        for (int j = 0; j < 6; ++j) {
            if (customers[i]->accountNum[j] != accountNum[j])
            {
                match = false;
                break;
            }
        }
        if (match)
            return i;
    }
    return -1;
}

bool CustomerAccount::UpdateCustomerAccount(CustomerAccount* customers[], int accountsOpen, const char* accountNumVal)
{
    int index = SearchCustomer(customers, accountsOpen, accountNumVal);
    if (index == -1) {
        cout << "Sorry! Account not found." << endl;
        return false;
    }

    char newAddress[100], newCity[50], newState[50];
    char zipStr[10];
    int newZipcode;

    // Address
    while (true) {
        cout << "Enter New Address: ";
        cin.ignore();
        cin.getline(newAddress, 100);
        if (newAddress[0] != '\0') break;
        cout << "Address cannot be empty. Try again.\n";
    }

    // City
    while (true) {
        cout << "Enter New City: ";
        cin.getline(newCity, 50);
        if (newCity[0] != '\0') break;
        cout << "City cannot be empty. Try again.\n";
    }

    // State
    while (true) {
        cout << "Enter New State: ";
        cin.getline(newState, 50);
        if (newState[0] != '\0') break;
        cout << "State cannot be empty. Try again.\n";
    }

    // ZIP Code (5 digits)
    while (true) {
        cout << "Enter New ZIP Code (5 digits): ";
        cin >> zipStr;
        if (isAllDigits(zipStr, 5)) {
            newZipcode = 0;
            for (int i = 0; i < 5; i++)
                newZipcode = newZipcode * 10 + (zipStr[i] - '0');
            break;
        }
        cout << "Invalid ZIP Code. Must be 5 digits.\n";
    }

    copytheArrays(customers[index]->address.address, newAddress);
    copytheArrays(customers[index]->address.city, newCity);
    copytheArrays(customers[index]->address.state, newState);
    customers[index]->address.zip_code = newZipcode;

    cout << "Address updated successfully for account " << accountNumVal << endl;
    return true;
}

bool CustomerAccount::UpdateCustomerAccount(CustomerAccount* customers[], int accountsOpen, const char* accountNumVal, long long phoneVal)
{
    int index = SearchCustomer(customers, accountsOpen, accountNumVal);
    if (index == -1) {
        cout << "Sorry! Account not found." << endl;
        return false;
    }

    char phoneStr[20];  // buffer for phone input as string
    cin.clear(); // clear any error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    while (true) {
        cout << "Enter New Phone Number (11 digits): ";
        cin.getline(phoneStr, 20);

        if (isAllDigits(phoneStr, 11)) 
        {
            for (int i = 0; i < 11; i++) 
            {
                phoneVal = phoneVal * 10 + (phoneStr[i] - '0');
            }
            customers[index]->phoneNum = phoneVal;
            cout << "Phone number updated successfully for account " << accountNumVal << endl;
            return true;
        }
        cout << "Invalid phone number. Must be exactly 11 digits.\n";
    }
}

bool CustomerAccount::UpdateCustomerAccount(CustomerAccount* customers[], int accountsOpen, const char* accountNumVal, float balanceVal)
{
    int index = SearchCustomer(customers, accountsOpen, accountNumVal);
    if (index == -1) {
        cout << "Sorry! Account not found." << endl;
        return false;
    }

    float newBalance;

    cout << "Current balance: " << customers[index]->balance << endl;

    while (true) {
        cout << "Enter New Balance (must be > 0): ";
        cin >> newBalance;

        if (newBalance > 0) {
            customers[index]->balance = newBalance;
            cout << "Balance updated successfully for account " << accountNumVal << endl;
            return true;
        }
        else {
            cout << "Invalid balance. Please enter a non-negative value." << endl;
        }
    }
}

void CustomerAccount::DisplayAllCustomers(CustomerAccount* customers[], int accountsOpen)
{
    cout << "Here is the list of all customer accounts:" << endl;
    for (int i = 0; i < accountsOpen; ++i)
    {
        cout << "Account Number: " << customers[i]->accountNum << endl << "Name: " << customers[i]->name << endl << "Address: " << customers[i]->address.address << ", " << customers[i]->address.city << ", " << customers[i]->address.state << " - " << customers[i]->address.zip_code << endl << "Phone Number: " << customers[i]->phoneNum << endl << "Balance: $" << customers[i]->balance << endl;
        cout << "*************************************************" << endl << endl;
    }
}

int main()
{
    CustomerAccount* customers[100] = { nullptr };
    int accountsOpen = 0, choice = 0;
    CustomerAccount obj;
    do
    {
        cout << endl << "Welcome to the FORT NOX! How may we help you?" << endl << "Please select your desired action: " << endl << "1. Open New Account" << endl << "2. Search Customer" << endl << "3. Update Address" << endl << "4. Update Phone Number" << endl << "5. Update Balance" << endl << "6. Display All Customers" << endl << "0. Exit" << endl;
        cin >> choice;

        switch (choice)
        {
        case 1:
            obj.OpenCustomerAccount(customers, accountsOpen);
            break;
        case 2:
        {
            char accountNum[6];
            cout << "Enter Account Number (PK###): ";
            cin >> accountNum;
            if (!obj.isValidAccountNumber(accountNum)) {
                cout << "Invalid format. Please enter in format PK### (e.g., PK123).\n";
                break;
            }
            int index = obj.SearchCustomer(customers, accountsOpen, accountNum);
            if (index != -1)
            {
                cout << "Customer found at index " << index << endl;
            }
            else
            {
                cout << "Sorry! Customer not found." << endl;
            }
            break;
        }
        case 3:
        {
            char accountNum[6];
            cout << "Enter Account Number (PK###) to update address: ";
            cin >> accountNum;
            if (!(obj.isValidAccountNumber(accountNum))) {
                cout << "Invalid format. Please enter in format PK### (e.g., PK123).\n";
                break;
            }
            int index = obj.SearchCustomer(customers, accountsOpen, accountNum);
            if (index != -1)
            {
                obj.UpdateCustomerAccount(customers, accountsOpen, accountNum);
            }
            else
            {
                cout << "Account not found." << endl;
            }
            break;
        }
        case 4:
        {
            char accountNum[6];
            cout << "Enter Account Number (PK###) to update phone: ";
            cin >> accountNum;
            if (!obj.isValidAccountNumber(accountNum)) {
                cout << "Invalid format. Please enter in format PK### (e.g., PK123).\n";
                break;
            }
            int index = obj.SearchCustomer(customers, accountsOpen, accountNum);
            if (index != -1)
            {
                long long newPhone=0;
                obj.UpdateCustomerAccount(customers, accountsOpen, accountNum, newPhone);
            }
            else
            {
                cout << "Account not found." << endl;
            }
            break;
        }
        case 5:
        {
            char accountNum[6];
            cout << "Enter Account Number (PK###) to update balance: ";
            cin >> accountNum;
            if (!obj.isValidAccountNumber(accountNum)) {
                cout << "Invalid format. Please enter in format PK### (e.g., PK123).\n";
                break;
            }
            int index = obj.SearchCustomer(customers, accountsOpen, accountNum);
            if (index != -1)
            {
                float newBalance;
                cout << "Account found. Enter new balance: ";
                cin >> newBalance;
                obj.UpdateCustomerAccount(customers, accountsOpen, accountNum, newBalance);
            }
            else
            {
                cout << "Account not found." << endl;
            }
            break;
        }
        case 6:
            obj.DisplayAllCustomers(customers, accountsOpen);
            break;
        case 0:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    for (int i = 0; i < accountsOpen; ++i)
    {
        delete[] customers[i]->name;
        delete[] customers[i]->address.address;
        delete[] customers[i]->address.city;
        delete[] customers[i]->address.state;
        delete customers[i];
    }

    return 0;
}