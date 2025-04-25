#include <iostream>
using namespace std;

class user {
private:
    string name;
    long int mobnum;
    float billamount;

public:
    user() {
        name = "";
        mobnum = 0;
        billamount = 0;
    }

    friend class record;
};

class record {
public:
    int n;
    user uid[100];
    void accept();
    void display();
    void linearSearch();
    void binarySearch();
    void binarySearch_recursive(int l, int r, long int data);
};

void record::accept() {
    cout << "Enter the number of users: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "Enter name of the user: ";
        cin >> uid[i].name;
        cout << "Enter mobile number of the user: ";
        cin >> uid[i].mobnum;
        cout << "Enter bill amount of the user: ";
        cin >> uid[i].billamount;
    }
}

void record::display() {
    for (int i = 0; i < n; i++) {
        cout << uid[i].name << " ";
        cout << uid[i].mobnum << " ";
        cout << uid[i].billamount << endl;
    }
}

void record::linearSearch() {
    long int data;
    cout << "Enter the mobile number to search using Linear Search: ";
    cin >> data;
    for (int i = 0; i < n; i++) {
        if (data == uid[i].mobnum) {
            cout << "Found user: " << uid[i].name << " with bill amount: " << uid[i].billamount << endl;
            return;
        }
    }
    cout << "Mobile number not found!" << endl;
}

void record::binarySearch_recursive(int l, int r, long int data) {
    if (l <= r) {
        int mid = (l + r) / 2;
        if (uid[mid].mobnum == data) {
            cout << "Found user: " << uid[mid].name << " with bill amount: " << uid[mid].billamount << endl;
            return;
        } else if (uid[mid].mobnum < data) {
            binarySearch_recursive(mid + 1, r, data);
        } else {
            binarySearch_recursive(l, mid - 1, data);
        }
    } else {
        cout << "Mobile number not found!" << endl;
    }
}

void record::binarySearch() {
    long int data;
    cout << "Enter the mobile number to search using Binary Search: ";
    cin >> data;

    int l = 0, r = n - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (uid[mid].mobnum == data) {
            cout << "Found user: " << uid[mid].name << " with bill amount: " << uid[mid].billamount << endl;
            return;
        } else if (uid[mid].mobnum < data) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << "Mobile number not found!" << endl;
}

int main() {
    record r1;
    int choice;

    cout << "Accept User Records:\n";
    r1.accept();

    r1.linearSearch(); 
    r1.binarySearch();
    long int data; 
    cout << "Enter mobile number: "; 
    cin >> data;
    r1.binarySearch_recursive(0, r1.n - 1, data);
    return 0;
}