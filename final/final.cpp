```cpp
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

int num;
int cont = 0;
int sizev = 0;
int noacc = 0;

class account;
vector<account> v;

class account {
private:
    string fname, lname;
    int accountno;
    float balance;
    float amount;

public:
    account() {
        fname = "";
        lname = "";
        accountno = cont + 1;
        balance = 0.0;
        cont++;
    }

    // mutators
    void setfname(string f);
    void setlname(string l);
    void setaccountno(int accno);
    void setbalance(float b);

    // accessors
    string getfname();
    string getlname();
    int getaccountno();
    float getbalance();

    // major functions
    void openanaccount();
    void display();
    void balanceenquiry();
    void deposit();
    void withdraw();
    void closeanacc();
    void printall();

    // file functions
    friend ifstream& operator>>(ifstream& ifs, account& ac);
    friend ofstream& operator<<(ofstream& fos, account& ac);
};

// file functions
ofstream& operator<<(ofstream& fos, account& ac) {
    fos << ac.fname << endl << ac.lname << endl << ac.accountno << endl << ac.balance << endl;
    return fos;
}

ifstream& operator>>(ifstream& ifs, account& ac) {
    ifs >> ac.fname;
    ifs >> ac.lname;
    ifs >> ac.accountno;
    ifs >> ac.balance;
    return ifs;
}

// accessors
string account::getfname() {
    return fname;
}

string account::getlname() {
    return lname;
}

int account::getaccountno() {
    return accountno;
}

float account::getbalance() {
    return balance;
}

// mutators
void account::setfname(string f) {
    fname = f;
}

void account::setlname(string l) {
    lname = l;
}

void account::setbalance(float b) {
    balance = b;
}

void account::setaccountno(int accno) {
    accountno = accno;
}

// open an account
void account::openanaccount() {
    cout << "enter your first name: ";
    cin >> fname;
    cout << "enter your last name: ";
    cin >> lname;
    cout << "enter your initial balance: ";
    cin >> balance;
    v.push_back(*this);
    cout << endl;
    cout << "congratulations account created" << endl;
    cout << endl;
    display();
    sizev++;
}

// display function
void account::display() {
    cout << "the account no.is: " << accountno << endl;
    cout << "account holder name: " << fname << " " << lname << endl;
    cout << "current balance of the account: " << balance << endl;
}

// balance enquiry
void account::balanceenquiry() {
    cout << "enter account number:" << endl;
    cin >> num;
    vector<account>::iterator it;
    for (it = v.begin(); it != v.end(); it++) {
        int temp = it->getaccountno();
        if (temp == num) {
            cout << "the balance of this account is:" << endl;
            cout << it->getbalance() << endl;
            return;
        }
    }
    cout << "invalid account number:" << endl;
    cout << endl;
}

// deposit function
void account::deposit() {
    cout << "enter the account number:" << endl;
    cin >> num;
    cout << "enter amount to be deposited:" << endl;
    cin >> amount;
    vector<account>::iterator itr;
    for (itr = v.begin(); itr != v.end(); itr++) {
        int temp = itr->getaccountno();
        if (temp == num) {
            float tempb = itr->getbalance();
            cout << "current balance" << endl;
            itr->setbalance(tempb + amount);
            cout << itr->getbalance() << endl;
            return;
        }
    }
    cout << "invalid account number" << endl;
    cout << endl;
}

// withdraw function
void account::withdraw() {
    cout << "enter the account number:" << endl;
    cin >> num;
    cout << "enter amount to be withdrawn:" << endl;
    cin >> amount;
    vector<account>::iterator itr;
    for (itr = v.begin(); itr != v.end(); itr++) {
        int temp = itr->getaccountno();
        if (temp == num) {
            float tempb = itr->getbalance();
            if (tempb >= amount) {
                cout << "current balance" << endl;
                itr->setbalance(tempb - amount);
                cout << itr->getbalance() << endl;
            } else {
                cout << "insufficient balance" << endl;
            }
            return;
        }
    }
    cout << "invalid account number" << endl;
    cout << endl;
}

// close an account function
void account::closeanacc() {
    cout << "enter account number:" << endl;
    cin >> num;
    vector<account>::iterator itr;
    for (itr = v.begin(); itr != v.end(); itr++) {
        int temp = itr->getaccountno();
        if (temp == num) {
            itr->display();
            v.erase(itr);
            cout << "account closed" << endl;
            sizev--;
            return;
        }
    }
    cout << "invalid account number" << endl;
    cout << endl;
}

// print all function
void account::printall() {
    vector<account>::iterator itr;
    for (itr = v.begin(); itr != v.end(); itr++) {
        itr->display();
    }
}

int main() {
    account acc;
    int option;
    ifstream infile("bank.txt");
    if (infile.is_open()) {
        infile >> noacc;
        infile >> sizev;
        v.resize(sizev);
        vector<account>::iterator itr;
        for (itr = v.begin(); itr != v.end(); itr++) {
            infile >> *itr;
        }
        infile.close();
        cont = noacc;
    }

    do {
        cout << "**********************BANKING SYSTEM*********************" << endl;
        cout << "Menu options:" << endl;
        cout << "\t 1 Open An Account " << endl;
        cout << "\t 2 Balance Enquiry " << endl;
        cout << "\t 3 Deposit" << endl;
        cout << "\t 4 Withdrawal" << endl;
        cout << "\t 5 Close An Account" << endl;
        cout << "\t 6 Show All Account " << endl;
        cout << "\t 7 Quit " << endl;

        cout << "choose an option" << endl;
        cin >> option;
        switch (option) {
        case 1:
            acc.openanaccount();
            break;
        case 2:
            acc.balanceenquiry();
            break;
        case 3:
            acc.deposit();
            break;
        case 4:
            acc.withdraw();
            break;
        case 5:
            acc.closeanacc();
            break;
        case 6:
            acc.printall();
            break;
        case 7:
            cout << "thanks for using the app";
            break;
        default:
            cout << "invalid input" << endl;
        }
    } while (option != 7);

    noacc = cont;
    ofstream outfile("bank.txt", ios::trunc);
    if (outfile.is_open()) {
        outfile << noacc << endl;
        outfile << sizev << endl;
        vector<account>::iterator itr;
        for (itr = v.begin(); itr != v.end(); itr++) {
            outfile << *itr;
        }
        outfile.close();
    }
    return 0;
}
```