#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Base Class
class Employee {
public:
    int id;
    string name, department;

    Employee(int i, string n, string d) {
        id = i;
        name = n;
        department = d;
    }

    virtual double salary(int days, int hours) = 0;
    virtual string type() = 0;

    virtual void display() {
        cout << "\nID: " << id;
        cout << "\nName: " << name;
        cout << "\nDepartment: " << department;
        cout << "\nType: " << type() << endl;
    }

    virtual ~Employee() {}
};

// Full Time Employee
class FullTime : public Employee {
public:
    double rate;

    FullTime(int i, string n, string d, double r)
        : Employee(i, n, d) {
        rate = r;
    }

    double salary(int days, int hours) override {
        return rate / 30 * days;
    }

    string type() override {
        return "FullTime";
    }
};

// Part Time Employee
class PartTime : public Employee {
public:
    double rate;

    PartTime(int i, string n, string d, double r)
        : Employee(i, n, d) {
        rate = r;
    }

    double salary(int days, int hours) override {
        return rate * hours;
    }

    string type() override {
        return "PartTime";
    }
};

// Contract Employee
class Contract : public Employee {
public:
    double rate;

    Contract(int i, string n, string d, double r)
        : Employee(i, n, d) {
        rate = r;
    }

    double salary(int days, int hours) override {
        return rate * days;
    }

    string type() override {
        return "Contract";
    }
};

// Attendance
struct Attendance {
    int id, days, hours;
};

vector<Employee*> employees;
vector<Attendance> records;

// Find Employee
Employee* findEmployee(int id) {
    for (int i = 0; i < employees.size(); i++) {
        if (employees[i]->id == id)
            return employees[i];
    }
    return NULL;
}

// Add Employee
void addEmployee() {
    int id, choice;
    string name, dept;
    double rate;

    cout << "Enter ID: ";
    cin >> id;

    if (findEmployee(id) != NULL) {
        cout << "ID already exists!\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> name;
    cout << "Enter Department: ";
    cin >> dept;

    cout << "1.Full Time  2.Part Time  3.Contract\n";
    cin >> choice;

    cout << "Enter Salary Rate: ";
    cin >> rate;

    if (rate <= 0) {
        cout << "Invalid Rate!\n";
        return;
    }

    if (choice == 1)
        employees.push_back(new FullTime(id, name, dept, rate));
    else if (choice == 2)
        employees.push_back(new PartTime(id, name, dept, rate));
    else if (choice == 3)
        employees.push_back(new Contract(id, name, dept, rate));
    else {
        cout << "Invalid Choice!\n";
        return;
    }

    cout << "Employee Added!\n";
}

// View Employees
void viewEmployees() {
    for (int i = 0; i < employees.size(); i++)
        employees[i]->display();
}

// Search Employee
void searchEmployee() {
    int id;
    cout << "Enter ID: ";
    cin >> id;

    Employee* emp = findEmployee(id);

    if (emp != NULL)
        emp->display();
    else
        cout << "Employee Not Found!\n";
}

// Record Attendance
void recordAttendance() {
    int id;
    Attendance a;

    cout << "Enter Employee ID: ";
    cin >> id;

    if (findEmployee(id) == NULL) {
        cout << "Employee Not Found!\n";
        return;
    }

    a.id = id;

    cout << "Enter Present Days: ";
    cin >> a.days;
    cout << "Enter Hours Worked: ";
    cin >> a.hours;

    if (a.days < 0 || a.days > 30 || a.hours < 0) {
        cout << "Invalid Attendance!\n";
        return;
    }

    records.push_back(a);
    cout << "Attendance Saved!\n";
}

// Generate Payslip
void payslip() {
    int id;
    cout << "Enter Employee ID: ";
    cin >> id;

    Employee* emp = findEmployee(id);

    if (emp == NULL) {
        cout << "Employee Not Found!\n";
        return;
    }

    for (int i = 0; i < records.size(); i++) {
        if (records[i].id == id) {
            double basic = emp->salary(records[i].days,
                                       records[i].hours);
            double allowance = basic * 0.10;
            double deduction = basic * 0.05;
            double net = basic + allowance - deduction;

            cout << "\n------ PAYSLIP ------\n";
            emp->display();
            cout << "Basic Salary: " << basic << endl;
            cout << "Allowance: " << allowance << endl;
            cout << "Deduction: " << deduction << endl;
            cout << "Net Salary: " << net << endl;

            ofstream file("payroll.txt", ios::app);
            file << id << " " << net << endl;
            file.close();
            return;
        }
    }

    cout << "Record Attendance First!\n";
}

// Save Employee Data
void saveData() {
    ofstream file("employees.txt");

    for (int i = 0; i < employees.size(); i++) {
        file << employees[i]->id << " "
             << employees[i]->name << " "
             << employees[i]->department << " "
             << employees[i]->type() << endl;
    }

    file.close();
    cout << "Data Saved!\n";
}

// Main Function
int main() {
    int choice;

    do {
        cout << "\n--- EMPLOYEE PAYROLL SYSTEM ---";
        cout << "\n1. Add Employee";
        cout << "\n2. View Employees";
        cout << "\n3. Search Employee";
        cout << "\n4. Record Attendance";
        cout << "\n5. Generate Payslip";
        cout << "\n6. Save Data";
        cout << "\n0. Exit";
        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: recordAttendance(); break;
            case 5: payslip(); break;
            case 6: saveData(); break;
            case 0: saveData(); break;
            default: cout << "Invalid Choice!\n";
        }

    } while (choice != 0);

    for (int i = 0; i < employees.size(); i++)
        delete employees[i];

    return 0;
}