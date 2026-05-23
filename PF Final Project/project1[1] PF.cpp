#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Structure to hold bank account information
struct Account {
    int accountID;
    string accountHolderName;
    string accountType;
    double balance;
    double loanAmount = 0.0;
    double RepayAmount = 0.0;
    double DepositAmount = 0.0;
    double WithdrawAmount = 0.0;
    double TransferAmount = 0.0;
    string complain;
};

// Function declarations
void addRecord();
void editRecord();
void viewRecords();
void searchRecord();
void deleteRecord();
void applyLoan();
void repayLoan();
void DepositAmount();
void WithdrawAmount();
void TransferAmount();
void CustomerReport();

int main() {
    int choice;
    do {
        // Displaying the main menu to the user
        cout << "\n--------------------------------------------------------------------------------\n";
        cout << "\t\t\tBanking Management System";
        cout << "\n--------------------------------------------------------------------------------\n";
        cout << "1. Add Record\n";
        cout << "2. Edit Record\n";
        cout << "3. View Records\n";
        cout << "4. Search Record\n";
        cout << "5. Delete Record\n";
        cout << "6. Apply for Loan\n";
        cout << "7. Repay for Loan\n";
        cout << "8. Deposit Amount\n";
        cout << "9. Withdraw Amount\n";
        cout << "10. Transfer Amount\n";
        cout << "11. Customer Complaints\n"; 
        cout << "12. Exit\n";
        cout << "\n--------------------------------------------------------------------------------\n";
        cout << "--------------------------------------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addRecord();  // Function to add a new account record
                break;
            case 2:
                editRecord();  // Function to edit an existing account record
                break;
            case 3:
                viewRecords();  // Function to view all account records
                break;
            case 4:
                searchRecord();  // Function to search an account record by ID
                break;
            case 5:
                deleteRecord();  // Function to delete an account record
                break;
            case 6:
                applyLoan();  // Function to apply for a loan
                break;
            case 7:
                repayLoan();  // Function to repay a loan
                break;
            case 8:
                DepositAmount();  // Function to deposit amount into an account
                break;
            case 9:
                WithdrawAmount();  // Function to withdraw amount from an account
                break;
            case 10:
                TransferAmount();  // Function to transfer amount between accounts
                break;
            case 11:
                CustomerReport();  // Function to view customer complaints
                break;
            case 12:
                cout << "Exiting program.\n";  // Exit the system
                break;
            default:
                cout << "Invalid choice. Please try again.\n";  // Error message for invalid input
        }
    } while (choice != 12);  // Keep the menu open until the user chooses to exit

    return 0;
}

// Function to add a new account record to the file
void addRecord() {
    ofstream file("accounts.txt", ios::app); 
    Account acc;

    cout << "Enter Account ID: ";
    cin >> acc.accountID;
    cin.ignore(); // Ignore leftover newline
    cout << "Enter Account Holder Name: ";
    getline(cin, acc.accountHolderName);
    cout << "Enter Account Type: ";
    getline(cin, acc.accountType);
    cout << "Enter Balance: ";
    cin >> acc.balance;

    file << acc.accountID << " " << acc.accountHolderName << " " << acc.accountType << " " 
         << acc.balance << " " << acc.loanAmount << "\n";
    file.close();

    cout << "Record added successfully!\n";  // Confirmation message
}

// Function to edit an existing account record
void editRecord() {
    ifstream file("accounts.txt");
    ofstream tempFile("temp.txt");
    Account acc;
    int searchID;
    bool found = false;

    cout << "Enter Account ID to edit: ";
    cin >> searchID;

    while (file >> acc.accountID >> acc.accountHolderName >> acc.accountType >> acc.balance >> acc.loanAmount) {
        if (acc.accountID == searchID) {
            found = true;
            cout << "Enter new Account Holder Name: ";
            cin.ignore();
            getline(cin, acc.accountHolderName);
            cout << "Enter new Account Type: ";
            getline(cin, acc.accountType);
            cout << "Enter new Balance: ";
            cin >> acc.balance;
        }
        tempFile << acc.accountID << " " << acc.accountHolderName << " " << acc.accountType << " " 
                 << acc.balance << " " << acc.loanAmount << "\n";  // Write the updated record to the temporary file
    }

    file.close();
    tempFile.close();

    // Replace the original file with the updated one
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        cout << "Record updated successfully!\n";  // Success message
    else
        cout << "Record not found.\n";  // Error message if record is not found
}

// Function to view all account records
void viewRecords() {
    ifstream file("accounts.txt");
    Account acc;

    cout << "\n-----------------------------------\n";
    cout << "\tAccount Records";
    cout << "\n-----------------------------------\n";
    // Display all account details from the file
    while (file >> acc.accountID >> acc.accountHolderName >> acc.accountType >> acc.balance >> acc.loanAmount) {
        cout << "Account ID: " << acc.accountID << "\n";
        cout << "Account Holder Name: " << acc.accountHolderName << "\n";
        cout << "Account Type: " << acc.accountType << "\n";
        cout << "Balance: " << acc.balance << "\n";
        cout << "Loan Amount: " << acc.loanAmount << "\n";
        cout << "-------------------------\n";
    }
    file.close();
}

// Function to search for an account record by ID
void searchRecord() {
    ifstream file("accounts.txt");
    Account acc;
    int searchID;
    bool found = false;

    cout << "Enter Account ID to search: ";
    cin >> searchID;

    // Search for the account by ID and display the details if found
    while (file >> acc.accountID >> acc.accountHolderName >> acc.accountType >> acc.balance >> acc.loanAmount) {
        if (acc.accountID == searchID) {
            cout << "\n-----------------------------------\n";
            cout << "\tAccount Found";
            cout << "\n-----------------------------------\n";
            cout << "Account ID: " << acc.accountID << "\n";
            cout << "Account Holder Name: " << acc.accountHolderName << "\n";
            cout << "Account Type: " << acc.accountType << "\n";
            cout << "Balance: " << acc.balance << "\n";
            cout << "Loan Amount: " << acc.loanAmount << "\n";
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Record not found.\n";  // Error message if record is not found

    file.close();
}

// Function to delete an account record by ID
void deleteRecord() {
    ifstream file("accounts.txt");
    ofstream tempFile("temp.txt");
    Account acc;
    int deleteID;
    bool found = false;

    cout << "Enter Account ID to delete: ";
    cin >> deleteID;


    while (file >> acc.accountID >> acc.accountHolderName >> acc.accountType >> acc.balance >> acc.loanAmount) {
        if (acc.accountID == deleteID) {
            found = true;
            continue;  // Skip the record to delete it
        }
        tempFile << acc.accountID << " " << acc.accountHolderName << " " << acc.accountType << " " 
                 << acc.balance << " " << acc.loanAmount << "\n";
    }

    file.close();
    tempFile.close();

    // Replace the original file with the updated one
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        cout << "Record deleted successfully!\n";  // Success message
    else
        cout << "Record not found.\n";  // Error message if record is not found
}

// Function to apply for a loan
void applyLoan() {
    ifstream file("accounts.txt");
    ofstream tempFile("temp.txt");
    Account acc;
    int searchID;
    bool found = false;

    cout << "Enter Account ID to apply for a loan: ";
    cin >> searchID;

    // Search for the account and apply the loan amount
    while (file >> acc.accountID >> acc.accountHolderName >> acc.accountType >> acc.balance >> acc.loanAmount) {
        if (acc.accountID == searchID) {
            cout << "Enter Loan Amount: ";
            cin >> acc.loanAmount;
            found = true;
        }
        tempFile << acc.accountID << " " << acc.accountHolderName << " " << acc.accountType << " " 
                 << acc.balance << " " << acc.loanAmount << "\n";
    }

    file.close();
    tempFile.close();

    // Replace the original file with the updated one
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        cout << "Loan applied successfully!\n";  // Success message
    else
        cout << "Account not found.\n";  // Error message if account is not found
}

// Function to repay a loan
void repayLoan() {
    ifstream file("accounts.txt");
    ofstream tempFile("temp.txt");
    Account acc;
    int searchID;
    bool found = false;

    cout << "Enter Account ID to repay for a loan: ";
    cin >> searchID;

    // Search for the account and reduce the loan amount
    while (file >> acc.accountID >> acc.accountHolderName >> acc.accountType >> acc.balance >> acc.loanAmount) {
        if (acc.accountID == searchID) {
            cout << "Enter Repay Loan Amount: ";
            cin >> acc.RepayAmount;
            acc.loanAmount -= acc.RepayAmount;  // Reduce the loan balance
            acc.balance -= acc.RepayAmount;  // Deduct the repayment from account balance
            found = true;
        }
        tempFile << acc.accountID << " " << acc.accountHolderName << " " << acc.accountType << " " 
                 << acc.balance << " " << acc.loanAmount << "\n";
    }

    file.close();
    tempFile.close();

    // Replace the original file with the updated one
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        cout << "Loan repaid successfully!\n";  // Success message
    else
        cout << "Account not found.\n";  // Error message if account is not found
}

// Function to deposit an amount into an account
void DepositAmount() {
    ifstream file("accounts.txt");
    ofstream tempFile("temp.txt");
    Account acc;
    int searchID;
    bool found = false;

    cout << "Enter Account ID to Deposit Amount: ";
    cin >> searchID;

    // Search for the account and add the deposit amount
    while (file >> acc.accountID >> acc.accountHolderName >> acc.accountType >> acc.balance >> acc.loanAmount) {
        if (acc.accountID == searchID) {
            cout << "Enter Deposit Amount: ";
            cin >> acc.DepositAmount;
            acc.balance += acc.DepositAmount;  // Add the deposit to the account balance
            found = true;
        }
        tempFile << acc.accountID << " " << acc.accountHolderName << " " << acc.accountType << " " 
                 << acc.balance << " " << acc.loanAmount << "\n";
    }

    file.close();
    tempFile.close();

    // Replace the original file with the updated one
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        cout << "Amount Deposited successfully!\n";  // Success message
    else
        cout << "Account not found.\n";  // Error message if account is not found
}

// Function to withdraw an amount from an account
void WithdrawAmount() {
    ifstream file("accounts.txt");
    ofstream tempFile("temp.txt");
    Account acc;
    int searchID;
    bool found = false;

    cout << "Enter Account ID to Withdraw Amount: ";
    cin >> searchID;

    // Search for the account and withdraw the amount
    while (file >> acc.accountID >> acc.accountHolderName >> acc.accountType >> acc.balance >> acc.loanAmount) {
        if (acc.accountID == searchID) {
            cout << "Enter Withdraw Amount: ";
            cin >> acc.WithdrawAmount;
            acc.balance -= acc.WithdrawAmount;  // Deduct the withdrawal from account balance
            found = true;
        }
        tempFile << acc.accountID << " " << acc.accountHolderName << " " << acc.accountType << " " 
                 << acc.balance << " " << acc.loanAmount << "\n";
    }

    file.close();
    tempFile.close();

    // Replace the original file with the updated one
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        cout << "Amount Withdraw successfully!\n";  // Success message
    else
        cout << "Account not found.\n";  // Error message if account is not found
}

// Function to transfer amount between two accounts
void TransferAmount() {
    ifstream file("accounts.txt");
    ofstream tempFile("temp.txt");
    Account acc;
    int senderID, receiverID;
    bool senderFound = false, receiverFound = false;

    cout << "Enter Sender Account ID: ";
    cin >> senderID;
    cout << "Enter Receiver Account ID: ";
    cin >> receiverID;
    cout << "Enter Transfer Amount: ";
    cin >> acc.TransferAmount;

    // Search for both sender and receiver accounts, and process the transfer
    while (file >> acc.accountID >> acc.accountHolderName >> acc.accountType >> acc.balance >> acc.loanAmount) {
        if (acc.accountID == senderID) {
            senderFound = true;
            if (acc.balance >= acc.TransferAmount) {
                acc.balance -= acc.TransferAmount;  // Deduct from sender's account
            } else {
                cout << "Insufficient balance in sender's account.\n";
                tempFile << acc.accountID << " " << acc.accountHolderName << " " << acc.accountType << " "
                         << acc.balance << " " << acc.loanAmount << "\n";
                continue;  // Skip this transaction for sender
            }
        } else if (acc.accountID == receiverID) {
            receiverFound = true;
            acc.balance += acc.TransferAmount;  // Add to receiver's account
        }

        tempFile << acc.accountID << " " << acc.accountHolderName << " " << acc.accountType << " " 
                 << acc.balance << " " << acc.loanAmount << "\n";
    }

    file.close();
    tempFile.close();

    // If both accounts are found, replace the original file with updated data
    if (!senderFound || !receiverFound) {
        cout << "One or both accounts not found. Transaction canceled.\n";
        remove("temp.txt");
    } else {
        remove("accounts.txt");
        rename("temp.txt", "accounts.txt");
        cout << "Money transferred successfully from Account " << senderID
             << " to Account " << receiverID << ".\n";
    }
}

// Function to display customer complaints
void CustomerReport() {
    ifstream file("reports.txt");
    int reportCount = 0;
    Account acc;

    // Count how many reports are in the file and display them
    while (file >> acc.accountID) {
        getline(file, acc.complain);
        cout << reportCount + 1 << ". " << acc.complain << "\n";
        reportCount++;
    }

    file.close();
    cout << "Total Customer Support Reports: " << reportCount << "\n";
}

