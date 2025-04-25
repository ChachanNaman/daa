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
    int partition(int l, int r);
    void quickSort(int l, int r);
    void binarySearch();
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

int record::partition(int l, int r) {
    long int pivot = uid[r].mobnum;
    int i = l - 1;

    for (int j = l; j < r; j++) {
        if (uid[j].mobnum < pivot) {
            i++;
            swap(uid[i], uid[j]);
        }
    }
    swap(uid[i + 1], uid[r]);
    return i + 1;
}

void record::quickSort(int l, int r) {
    if (l < r) {
        int pI = partition(l, r);
        quickSort(l, pI - 1);
        quickSort(pI + 1, r);
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

    r1.quickSort(0, r1.n - 1);
    r1.display();

    r1.binarySearch();

    return 0;

}