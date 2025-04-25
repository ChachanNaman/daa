#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#define size 10

class record {
public:
    int roll_no;
    string name;
    int marks;
    friend class Student;
};

class HashTable {
    int roll_no,pos;
    public: HashTable(){
        roll_no = -1;
        pos = -1;
    }
    friend class Student;
};
class Student{
    record rec;
    HashTable h[size];

    int s,relt;
    public:Student();
    void create_without_replacing();
    void create_with_replacing();
    void display();
    void displayall();
    void retrieve();
    void modify();  

};

Student::Student(){
    s = sizeof(record);
    for (int i = 0; i < size; i++) {
        h[i].roll_no = -1;
        h[i].pos = -1;
    }
    relt = 0; 
}

void Student::create_with_replacing(){
    char ans;
    int nloc;
    HashTable temp;
    fstream f;
    f.open("student.txt", ios::binary | ios::out);
    int loc;
    do{
        cout<<"\n Enter the Details of the Student: \n";
        cout<<"Roll No: ";
        cin>>rec.roll_no;
        cout<<"Name: ";
        cin>>rec.name;
        cout<<"Marks: ";
        cin>>rec.marks;
        loc = rec.roll_no % size;

        if(h[loc].roll_no == -1){
            h[loc].roll_no = rec.roll_no;
            h[loc].pos = relt;
            f.write((char*)&rec, s);
            relt = relt + 1;
        }
        else{
            temp.roll_no = rec.roll_no;
            temp.pos = relt;
            f.write((char*)&rec, s);
            relt = relt + 1;

            if(loc!=(h[loc].roll_no % size)){
                temp.roll_no = h[loc].roll_no;
                temp.pos = h[loc].pos;
                h[loc].roll_no = rec.roll_no;
                h[loc].pos = relt-1;
          }
            nloc = (loc+1)%size;
            
            while(nloc!=loc){
                if(h[nloc].roll_no == -1){
                    h[nloc].roll_no = temp.roll_no;
                    h[nloc].pos = temp.pos;
                    break;
                }
                nloc = (nloc+1)%size;
            }
        }
        cout<<"Want to add more records? (y/n): ";
        cin>>ans;
    }while(ans == 'y' || ans == 'Y');
    f.close();
}

void Student::create_without_replacing() {
    char ans;
    fstream f;
    f.open("student.txt", ios::binary | ios::out);
    int loc;
    
    do {
        cout << "\n Enter the Details of the Student: \n";
        cout << "Roll No: ";
        cin >> rec.roll_no;
        cout << "Name: ";
        cin >> rec.name;
        cout << "Marks: ";
        cin >> rec.marks;
        
        loc = rec.roll_no % size;
        
        while (h[loc].roll_no != -1) {
            loc = (loc + 1) % size;
        }
        
        h[loc].roll_no = rec.roll_no;
        h[loc].pos = relt;
        
        f.write((char*)&rec, s);
        relt = relt + 1;
        
        cout << "Want to add more records? (y/n): ";
        cin >> ans;
    } while(ans == 'y' || ans == 'Y');
    
    f.close();
}

void Student::display(){
    cout<<rec.roll_no<<"\t"<<rec.name<<"\t"<<rec.marks<<endl;
}

void Student::displayall(){
    cout << "\n Displaying HashTable: \n";
    cout << "Index\tRoll No\tPosition in File\n";
    for (int i = 0; i < size; i++) {
        cout << i << "\t" << h[i].roll_no << "\t" << h[i].pos << endl;
    }

   cout << "\nRecords in order of insertion:\n";
    cout << "Roll No\tName\tMarks\n";
    fstream f;
    f.open("student.txt", ios::binary | ios::in);
    
    for (int i = 0; i < relt; i++) {
        f.seekg(i * s, ios::beg);
        f.read((char*)&rec, s);
        display();
    }
    
    f.close();
}



void Student::retrieve() {
    fstream f;
    f.open("student.txt", ios::binary | ios::in);
    cout << "Enter the Roll No of the Student you want to find: ";
    cin >> rec.roll_no;
    
    int loc = rec.roll_no % size, i;
    for (i = 0; i < size; i++) {
        if (h[loc].roll_no == rec.roll_no) {
            int p = h[loc].pos * s;
            f.seekg(p, ios::beg);
            f.read((char*)&rec, s);
            display();
            break;
        } else {
            loc = (loc + 1) % size;
        }
    }
    
    if (i == size) {  
        cout << "Record not found!\n";
    }
    f.close();
}

void Student::modify() {
    fstream f;
    f.open("student.txt", ios::binary | ios::in | ios::out);
    cout << "Enter the Roll No of the Student to change: ";
    cin >> rec.roll_no;
    
    int loc = rec.roll_no % size, i;
    for (i = 0; i < size; i++) {
        if (h[loc].roll_no == rec.roll_no) {
            int p = h[loc].pos * s;
            f.seekg(p, ios::beg);
            f.read((char*)&rec, s);
            cout << "Enter the new Name: ";
            cin >> rec.name;
            cout << "Enter the new Marks: ";
            cin >> rec.marks;
            p = h[loc].pos * s;
            f.seekp(p, ios::beg);
            f.write((char*)&rec, s);
            break;
        } else {
            loc = (loc + 1) % size;
        }
    }
    
    if (i == size) {  
        cout << "Record not found!\n";
    }
    f.close();
}


int main() {
    Student s;
    int choice;
    string name;

    do {
        cout << "\n1.Insert With Replacement\n2. Insert Without Replacement \n3. Display\n4. Retrieve\n5. Modify\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                s.create_with_replacing();
                break;
            case 2:
                s.create_without_replacing();
                break;
            case 3:
                cout << "\nDisplaying all records:\n";
                s.displayall();
                break;
            case 4:
                s.retrieve();
                break;
            case 5:
                s.modify();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 6);

    return 0;
}