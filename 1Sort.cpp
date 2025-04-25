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
    void heapify(int n, int i);
    void heapSort();
    void binarySearch();
    void binarySearch_recursive(int l, int r, long int data);
    int partition(int l, int r);
    void quickSort(int l, int r);
    void merge(int l, int mid, int r);
    void mergeSort(int l, int r);
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

void record::heapify(int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && uid[l].billamount > uid[largest].billamount)
        largest = l;
    if (r < n && uid[r].billamount > uid[largest].billamount)
        largest = r;

    if (largest != i) {
        swap(uid[i], uid[largest]);
        heapify(n, largest);
    }
}

void record::heapSort() {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(uid[0], uid[i]);
        heapify(i, 0);
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

void record::merge(int l, int mid, int r) {
    int i = l, j = mid + 1, k = 0;
    user temp[r - l + 1];

    while (i <= mid && j <= r) {
        if (uid[i].mobnum <= uid[j].mobnum)
            temp[k++] = uid[i++];
        else
            temp[k++] = uid[j++];
    }

    while (i <= mid)
        temp[k++] = uid[i++];
    while (j <= r)
        temp[k++] = uid[j++];

    for (int i = l, k = 0; i <= r; i++, k++)
        uid[i] = temp[k];
}

void record::mergeSort(int l, int r) {
    if (l >= r)
        return;

    int mid = l + (r - l) / 2;
    mergeSort(l, mid);
    mergeSort(mid + 1, r);
    merge(l, mid, r);
}

int main() {
    record r1;
    int choice;

    cout << "Accept User Records:\n";
    r1.accept();

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Linear Search\n2. Heap Sort\n3. Quick Sort\n4. Binary Search\n5. Recursive Binary Search\n6. Merge Sort\n7. Display Records\n8. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: r1.linearSearch(); break;
            case 2: r1.heapSort(); r1.display(); break;
            case 3: r1.quickSort(0, r1.n - 1); r1.display(); break;
            case 4: r1.binarySearch(); break;
            case 5: { long int data; cout << "Enter mobile number: "; cin >> data; r1.binarySearch_recursive(0, r1.n - 1, data); } break;
            case 6: r1.mergeSort(0, r1.n - 1); r1.display(); break;
            case 7: r1.display(); break;
            case 8: return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}
