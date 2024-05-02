#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <regex>

using namespace std;

class Student {
private:
    string RollNo, Name, Address;
    vector<string> Subjects;
public:
    Student() : RollNo(""), Name(""), Address("") {}

    void setRollNo(string rollNo) {
        RollNo = rollNo;
    }

    void setName(string name) {
        Name = name;
    }

    void setAddress(string address) {
        Address = address;
    }

    string getRollNo() {
        return RollNo;
    }

    string getName() {
        return Name;
    }

    string getAddress() {
        return Address;
    }

    void addSubject(string subject) {
        Subjects.push_back(subject);
    }

    vector<string> getSubjects() {
        return Subjects;
    }
};

bool isValidRollNo(const string& rollNo) {
    // Validate roll number format (e.g., XXXX-XXXX)
    regex pattern("\\d{4}-\\d{4}");
    return regex_match(rollNo, pattern);
}

bool isValidName(const string& name) {
    // Validate name format (letters only)
    return all_of(name.begin(), name.end(), [](char c) { return isalpha(c) || isspace(c); });
}

bool isValidAddress(const string& address) {
    // Address can be any string, so it's always valid
    return true;
}

bool isValidSubject(const string& subject) {
    // Subject can be any string, so it's always valid
    return true;
}

void add(Student& student) {
    string rollNo, name, address;
    cout << "\tEnter RollNo of Student (XXXX-XXXX format): ";
    cin >> rollNo;
    while (!isValidRollNo(rollNo)) {
        cout << "\tInvalid RollNo format. Please enter in XXXX-XXXX format: ";
        cin >> rollNo;
    }

    cout << "\tEnter Name of the Student: ";
    cin.ignore();
    getline(cin, name);
    while (!isValidName(name)) {
        cout << "\tInvalid Name format. Please enter alphabets only: ";
        getline(cin, name);
    }

    cout << "\tEnter Address of Student: ";
    getline(cin, address);
    // No need to validate address as it can be any string.

    student.setRollNo(rollNo);
    student.setName(name);
    student.setAddress(address);

    int numSubjects;
    cout << "\tEnter number of subjects: ";
    cin >> numSubjects;

    for (int i = 0; i < numSubjects; ++i) {
        string subject;
        cout << "\tEnter Subject " << i + 1 << ": ";
        cin.ignore();
        getline(cin, subject);
        // No need to validate subject as it can be any string.
        student.addSubject(subject);
    }

    ofstream out("student_data.txt", ios::app);
    if (!out) {
        cout << "\tError: File can't open" << endl;
    }
    else {
        out << student.getRollNo() << " : " << student.getName() << " : " << student.getAddress() << endl;
        vector<string> subjects = student.getSubjects();
        for (const string& subject : subjects) {
            out << "\tSubject: " << subject << endl;
        }
        out << endl;
    }
    out.close();
    cout << "\tStudent Added Successfully" << endl;
}

void search() {
    string rollNo;
    cout << "\tEnter RollNo of Student: ";
    cin >> rollNo;
    ifstream in("student_data.txt");
    if (!in) {
        cout << "\tError: File can't Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(in, line)) {
        if (line.find(rollNo) != string::npos) {
            cout << "\t" << line << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "\tStudent doesn't Exist !" << endl;
    }
    in.close();
}

void update() {
    string rollNo;
    cout << "\tEnter RollNo of Student to Update: ";
    cin >> rollNo;

    ifstream infile("student_data.txt");
    ofstream outfile("temp.txt");
    if (!infile || !outfile) {
        cout << "\tError: File cannot Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(infile, line)) {
        if (line.find(rollNo) != string::npos) {
            string name, subject, address;
            cout << "\tEnter New Name: ";
            cin >> name;
            while (!isValidName(name)) {
                cout << "\tInvalid Name format. Please enter alphabets only: ";
                cin >> name;
            }

            cout << "\tEnter New Address: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, address);

            line = rollNo + " : " + name + " : " + address;
            found = true;
        }
        outfile << line << endl;
    }
    if (!found) {
        cout << "\tStudent Not Found!" << endl;
    }
    outfile.close();
    infile.close();
    remove("student_data.txt");
    rename("temp.txt", "student_data.txt");
    cout << "\tData Updated" << endl;
}

void removeStudent() {
    string rollNo;
    cout << "\tEnter RollNo of Student to Delete: ";
    cin >> rollNo;

    ifstream infile("student_data.txt");
    ofstream outfile("temp.txt");
    if (!infile || !outfile) {
        cout << "\tError: File cannot Open!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(infile, line)) {
        if (line.find(rollNo) != string::npos) {
            found = true;
        } else {
            outfile << line << endl;
        }
    }
    if (!found) {
        cout << "\tStudent Not Found!" << endl;
    } else {
        cout << "\tStudent Deleted Successfully" << endl;
    }
    outfile.close();
    infile.close();
    remove("student_data.txt");
    rename("temp.txt", "student_data.txt");
}

void displayAll() {
    ifstream infile("student_data.txt");
    if (!infile) {
        cout << "\tError: File cannot Open!" << endl;
        return;
    }

    string line;
    while (getline(infile, line)) {
        cout << "\t" << line << endl;
    }
    infile.close();
}

int main() {
    bool exit = false;
    Student newStudent; // Create a Student object outside the loop
    while (!exit) {
        system("cls");
        int var;

        cout << "\t Welcome To Student Management System" << endl;
        cout << "\t*****************************************" << endl;
        cout << "\t1.Add Student" << endl;
        cout << "\t2.Display All Students" << endl;
        cout << "\t3.Search Student" << endl;
        cout << "\t4.Update Student Data" << endl;
        cout << "\t5.Delete Student" << endl;
        cout << "\t6.Exit" << endl;
        cout << "\tEnter Your choice: ";
        cin >> var;

        switch (var) {
            case 1:
                system("cls");
                add(newStudent); // Pass newStudent by reference
                break;
            case 2:
                system("cls");
                displayAll();
                break;
            case 3:
                system("cls");
                search();
                break;
            case 4:
                system("cls");
                update();
                break;
            case 5:
            	system("cls");
                removeStudent();
                break;
            case 6:
                exit = true;
                cout << "\tGoodbye!" << endl;
                break;
            default:
                cout << "\tInvalid choice! Please enter a number from 1 to 6." << endl;
                break;
        }
        cout << "\n\tPress Enter to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
    }
    return 0;
}
