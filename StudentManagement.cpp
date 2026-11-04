
#include <iostream>
#include <string>
#include <limits>
using namespace std;

const int MAX_SIZE = 50;

struct Student {
    int rollNo;
    string name;
    int age;
    string course;
    float cgpa;
};

class Stack {
private:
    Student arr[MAX_SIZE];
    int top;

public:
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX_SIZE - 1;
    }

    bool push(Student s) {
        if (isFull())
            return false;

        arr[++top] = s;
        return true;
    }

    bool pop(Student &s) {
        if (isEmpty())
            return false;

        s = arr[top--];
        return true;
    }

    bool peek(Student &s) {
        if (isEmpty())
            return false;

        s = arr[top];
        return true;
    }
};

// Display student details
void displayStudent(const Student &s) {
    cout << "\nRoll Number : " << s.rollNo;
    cout << "\nName        : " << s.name;
    cout << "\nAge         : " << s.age;
    cout << "\nCourse      : " << s.course;
    cout << "\nCGPA        : " << s.cgpa << endl;
}

// Check duplicate roll number
bool rollNumberExists(Stack &mainStack, int rollNo) {
    Stack temp;
    Student s;
    bool found = false;

    while (mainStack.pop(s)) {
        if (s.rollNo == rollNo)
            found = true;

        temp.push(s);
    }

    while (temp.pop(s))
        mainStack.push(s);

    return found;
}

// Display all students
void displayAllStudents(Stack &mainStack) {
    if (mainStack.isEmpty()) {
        cout << "\nNo students available.\n";
        return;
    }

    Stack temp;
    Student s;

    cout << "\n========== ALL STUDENTS ==========\n";

    while (mainStack.pop(s)) {
        displayStudent(s);
        temp.push(s);
    }

    while (temp.pop(s))
        mainStack.push(s);
}

// Search student
void searchStudent(Stack &mainStack, int rollNo) {
    Stack temp;
    Student s;
    bool found = false;

    while (mainStack.pop(s)) {
        if (s.rollNo == rollNo) {
            cout << "\nStudent Found!";
            displayStudent(s);
            found = true;
        }

        temp.push(s);
    }

    while (temp.pop(s))
        mainStack.push(s);

    if (!found)
        cout << "\nStudent not found.\n";
}

// Main function
int main() {
    Stack mainStack;
    Stack historyStack;

    int choice;

    while (true) {
        cout << "\n====================================";
        cout << "\n      STUDENT MANAGEMENT SYSTEM";
        cout << "\n             STACK BASED";
        cout << "\n====================================";
        cout << "\n1. Add Student";
        cout << "\n2. Remove Last Added Student";
        cout << "\n3. View Recent Student";
        cout << "\n4. Display All Students";
        cout << "\n5. Search Student";
        cout << "\n6. Undo Last Delete";
        cout << "\n7. Exit";
        cout << "\n------------------------------------";
        cout << "\nEnter your choice: ";

        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid input!\n";
            continue;
        }

        if (choice == 1) {
            if (mainStack.isFull()) {
                cout << "\nStack is full!\n";
                continue;
            }

            Student s;

            cout << "\nEnter Roll Number: ";
            cin >> s.rollNo;

            if (cin.fail() || s.rollNo <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid Roll Number!\n";
                continue;
            }

            if (rollNumberExists(mainStack, s.rollNo)) {
                cout << "\nRoll Number already exists!\n";
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Name: ";
            getline(cin, s.name);

            if (s.name.empty()) {
                cout << "\nName cannot be empty!\n";
                continue;
            }

            cout << "Enter Age: ";
            cin >> s.age;

            if (cin.fail() || s.age <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid Age!\n";
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter Course: ";
            getline(cin, s.course);

            if (s.course.empty()) {
                cout << "\nCourse cannot be empty!\n";
                continue;
            }

            cout << "Enter CGPA: ";
            cin >> s.cgpa;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid CGPA!\n";
                continue;
            }

            if (s.cgpa < 0 || s.cgpa > 10) {
                cout << "\nCGPA must be between 0 and 10!\n";
                continue;
            }

            mainStack.push(s);
            cout << "\nStudent added successfully!\n";
        }

        else if (choice == 2) {
            Student s;

            if (mainStack.isEmpty()) {
                cout << "\nStack is empty!\n";
            }
            else if (historyStack.isFull()) {
                cout << "\nUndo history is full! Cannot delete.\n";
            }
            else {
                mainStack.pop(s);
                historyStack.push(s);

                cout << "\nStudent removed successfully!";
                displayStudent(s);
            }
        }

        else if (choice == 3) {
            Student s;

            if (mainStack.peek(s)) {
                cout << "\nMost Recently Added Student:";
                displayStudent(s);
            }
            else {
                cout << "\nStack is empty!\n";
            }
        }

        else if (choice == 4) {
            displayAllStudents(mainStack);
        }

        else if (choice == 5) {
            int rollNo;

            cout << "\nEnter Roll Number: ";
            cin >> rollNo;

            if (cin.fail() || rollNo <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nInvalid Roll Number!\n";
                continue;
            }

            searchStudent(mainStack, rollNo);
        }

        else if (choice == 6) {
            Student s;

            if (historyStack.isEmpty()) {
                cout << "\nNothing to undo!\n";
            }
            else if (mainStack.isFull()) {
                cout << "\nMain stack is full! Cannot restore.\n";
            }
            else {
                historyStack.pop(s);
                mainStack.push(s);

                cout << "\nUndo successful!";
                displayStudent(s);
            }
        }

        else if (choice == 7) {
            cout << "\nThank you for using Student Management System!\n";
            break;
        }

        else {
            cout << "\nInvalid choice! Select 1 to 7.\n";
        }
    }

    return 0;
}