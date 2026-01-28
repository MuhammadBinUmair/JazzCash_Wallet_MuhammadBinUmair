#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class JazzCash {
private:
    string name;
    string phone;
    int pin;
    float balance;

public:
    JazzCash() {
        balance = 0;
        pin = 0;
    }

    void createAccount() {
        cin.ignore();

        cout << "Enter Name: ";
        getline(cin, name);

        cout << "Enter Phone Number: ";
        getline(cin, phone);

        cout << "Set 4-digit PIN: ";
        cin >> pin;

        cout << "Enter Initial Balance: ";
        cin >> balance;

        saveToFile();
        cout << endl << "Account Created Successfully!" << endl;
    }

    void saveToFile() {
        ofstream file("jazzcash.txt");
        file << name << endl;
        file << phone << endl;
        file << pin << endl;
        file << balance << endl;
        file.close();
    }

    bool loadFromFile() {
        ifstream file("jazzcash.txt");
        if (!file)
            return false;

        getline(file, name);
        getline(file, phone);
        file >> pin;
        file >> balance;

        file.close();
        return true;
    }

    bool login() {
        int enteredPin;
        cout << "Enter PIN: ";
        cin >> enteredPin;

        if (enteredPin == pin) {
            cout << endl << "Login Successful!" << endl;
            return true;
        } else {
            cout << endl << "Wrong PIN!" << endl;
            return false;
        }
    }

    void checkBalance() {
        cout << "Current Balance: Rs. " << balance << endl;
    }

    void sendMoney() {
        string receiver;
        float amount;

        cout << "Enter Receiver 11-digit Phone Number: ";
        cin >> receiver;

        if (receiver.length() != 11) {
            cout << "Invalid Phone Number!" << endl;
            return;
        }

        for (int i = 0; i < receiver.length(); i++) {
            if (receiver[i] < '0' || receiver[i] > '9') {
                cout << "Phone Number must contain digits only!" << endl;
                return;
            }
        }

        cout << "Enter Amount to Send: ";
        cin >> amount;

        if (amount > 0 && amount <= balance) {
            balance -= amount;
            saveToFile();
            cout << "Rs. " << amount << " sent to " << receiver << " successfully!" << endl;
        } else {
            cout << "Invalid or Insufficient Balance!" << endl;
        }
    }

    void mobileRecharge() {
        float amount;
        cout << "Enter Recharge Amount: ";
        cin >> amount;

        if (amount > 0 && amount <= balance) {
            balance -= amount;
            saveToFile();
            cout << "Recharge Successful!" << endl;
        } else {
            cout << "Invalid or Insufficient Balance!" << endl;
        }
    }

    void showDetails() {
        cout << endl << "Account Details";
        cout << endl << "Name: " << name;
        cout << endl << "Phone: " << phone;
        cout << endl << "Balance: Rs. " << balance << endl;
    }
};

int main() {
    JazzCash user;
    int choice;

    if (!user.loadFromFile()) {
        cout << "No Account Found." << endl;
        cout << "Creating New Account..." << endl;
        user.createAccount();
    }

    if (!user.login()) {
        return 0;
    }

    do {
        cout << endl << "----- JazzCash Menu -----" << endl;
        cout << "1. Check Balance" << endl;
        cout << "2. Send Money" << endl;
        cout << "3. Mobile Recharge" << endl;
        cout << "4. Account Details" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            user.checkBalance();
            break;
        case 2:
            user.sendMoney();
            break;
        case 3:
            user.mobileRecharge();
            break;
        case 4:
            user.showDetails();
            break;
        case 5:
            cout << "Thank You for Using JazzCash!" << endl;
            break;
        default:
            cout << "Invalid Choice!" << endl;
        }

    } while (choice != 5);

    return 0;
}

