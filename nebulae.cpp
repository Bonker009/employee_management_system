#include <optional>
#include <list>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <regex>
using namespace std;
// contact information of employee which includes email,address,phone number
struct ContactInfo
{
    string email;
    string phoneNumber;
    string address;
};

class Employee
{
private:
    int id;
    string name;
    double salary;
    int age;
    string department;
    ContactInfo contactInfo;
    string sex;
    string designation;

public:
    void setID(int id)
    {
        this->id = id;
    }
    void setName(string name)
    {
        this->name = name;
    }
    void setSalary(double salary)
    {
        this->salary = salary;
    }
    void setAge(int age)
    {
        this->age = age;
    }
    void setDepartment(string department)
    {
        this->department = department;
    }
    void setContactInfo(ContactInfo contactInfo)
    {
        this->contactInfo = contactInfo;
    }
    void setSex(string sex)
    {
        this->sex = sex;
    }
    void setDesignation(string designation)
    {
        this->designation = designation;
    }
    int getID() const
    {
        return id;
    }
    string getName() const
    {
        return name;
    }
    double getSalary() const
    {
        return salary;
    }
    int getAge() const
    {
        return age;
    }
    string getDepartment() const
    {
        return department;
    }
    ContactInfo getContactInfo() const
    {
        return contactInfo;
    }
    string getSex() const
    {
        return sex;
    }
    string getDesignation() const
    {
        return designation;
    }

    // default constructor for employees
    Employee() : id(0), name("N/A"), salary(0), age(0), department("N/A") {}
    // initial constructor for employees
    Employee(int id, string name, double salary, int age, string department, string sex, string designation, const ContactInfo &contactInfo)
        : id(id), name(name), salary(salary), age(age), department(department), sex(sex), designation(designation), contactInfo(contactInfo) {}
    // checking the age of employee
    bool validateAge(int age)
    {
        const int minAge = 18;
        const int maxAge = 65;
        return (age >= minAge && age <= maxAge);
    }
    // check if employee is already existed
    bool searchByIdValidation(int id)
    {
        return (this->id == id);
    }
    optional<Employee> searchEmployeeById(const list<Employee> &employees, int id)
    {
        for (const auto &emp : employees)
        {
            if (emp.id == id)
                return emp;
        }

        return std::nullopt; // Employee not found
    }

    // // for sorting by salary in ascending
    // static bool salaryAscend(const Employee &emp1, const Employee &emp2)
    // {
    //     return emp1.salary < emp2.salary;
    // }
    // // for sorting by salary in descending
    // static bool salaryDescend(const Employee &emp1, const Employee &emp2)
    // {
    //     return emp1.salary > emp2.salary;
    // }
    // for displaying the information about employees
    friend ostream &operator<<(ostream &os, const Employee &emp)
    {
        os << left << setw(8) << "ID"
           << setw(15) << "Name"
           << setw(12) << "Salary"
           << setw(8) << "Age"
           << setw(20) << "Department"
           << setw(10) << "Sex"
           << setw(20) << "Designation"
           << setw(30) << "Email"
           << setw(18) << "Phone Number"
           << setw(35) << "Address" << endl;

        os << left << setw(8) << emp.id
           << setw(15) << emp.name
           << setw(12) << fixed << setprecision(2) << emp.salary
           << setw(8) << emp.age
           << setw(20) << emp.department
           << setw(10) << emp.sex
           << setw(20) << emp.designation
           << setw(30) << emp.contactInfo.email
           << setw(18) << emp.contactInfo.phoneNumber
           << setw(35) << emp.contactInfo.address;

        return os;
    }
    // for inputing the information about employees
    friend istream &operator>>(istream &is, Employee &emp)
    {
        cout << "Enter employee ID: ";
        is >> emp.id;

        cout << "Enter employee fullname: ";
        is.ignore();
        getline(is, emp.name);

        cout << "Enter employee salary: ";
        is >> emp.salary;

        cout << "Enter employee age: ";
        is >> emp.age;
        while (!emp.validateAge(emp.age))
        {
            is.clear();
            is.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter employee age: ";
            is >> emp.age;
        }

        cout << "Enter employee department: ";
        is.ignore();
        getline(is, emp.department);

        cout << "Enter employee sex: ";
        is >> emp.sex;

        cout << "Enter employee designation: ";
        is.ignore();
        getline(is, emp.designation);

        while (true)
        {
            cout << "Enter employee Email: ";
            is >> emp.contactInfo.email;
            const regex emailRegex(R"(\b[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]{2,}\b)");
            if (regex_match(emp.contactInfo.email, emailRegex))
                break;
            cout << "Invalid email format! Please enter a valid email address." << endl;
        }
        while (true)
        {
            cout << "Enter employee Phone Number: ";
            is >> emp.contactInfo.phoneNumber;
            const regex phoneRegex(R"(\d{9,10})");
            if (regex_match(emp.contactInfo.phoneNumber, phoneRegex))
                break;
            cout << "Invalid phone number format! Please enter a valid phone number." << endl;
        }
        cout << "Enter employee address: ";
        is.ignore();
        getline(is, emp.contactInfo.address);

        return is;
    }
};
int main()
{
    list<Employee> employees;
    int press;
    int choice;

    do
    {
        system("cls");
        cout << "Employee Management System" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. Search Employee by ID" << endl;
        cout << "3. Display All Employees" << endl;
        cout << "4. Update Employee" << endl;
        cout << "5. Delete Employee" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            fstream file("employees.dat", ios::app);
            Employee emp;
            cin >> emp;
            employees.push_back(emp);
            const ContactInfo &info = emp.getContactInfo();
            cout << "Employee added successfully." << endl;
            file << emp.getID() << " " << emp.getName() << " " << emp.getSalary() << " " << emp.getAge() << " " << emp.getDepartment() << " "
                 << emp.getSex() << " " << emp.getDesignation() << " " << info.email << " " << info.phoneNumber
                 << " " << info.address << endl;
            break;
        }
        case 2:
        {
            system("cls");
            int searchId;
            cout << "Enter employee ID to search: ";
            cin >> searchId;

            Employee emp; // Create an instance of the Employee class
            optional<Employee> result = emp.searchEmployeeById(employees, searchId);
            if (result.has_value())
            {
                const Employee &foundEmployee = result.value();
                cout << "Employee found: " << endl
                     << foundEmployee << endl;
            }
            else
            {
                system("cls");
                cout << "Employee not found." << endl;
            }
            cout << endl;
            cout << "Press Enter to continue..." << endl;
            cin.ignore();
            cin.get();
            break;
        }
        case 3:
        {
            system("cls");
            fstream file("employees.dat", ios::in);
            if (!file)
            {
                cout << "File not found!" << endl;
                break;
            }

            // Clear the employees list before loading data
            employees.clear();

            int empId;
            string empName;
            double empSalary;
            int empAge;
            string empDepartment;
            string empSex;
            string empDesignation;
            string empEmail;
            string empPhoneNumber;
            string empAddress;

            while (file >> empId >> empName >> empSalary >> empAge >> empDepartment >> empSex >> empDesignation >> empEmail >> empPhoneNumber >> empAddress)
            {
                ContactInfo empContactInfo = {empEmail, empPhoneNumber, empAddress};
                Employee emp(empId, empName, empSalary, empAge, empDepartment, empSex, empDesignation, empContactInfo);
                employees.push_back(emp);
            }

            file.close();
            if (employees.empty())
            {
                cout << "No employees to display." << endl;
            }
            else
            {
                cout << "All Employees:" << endl;
                cout << endl;
                for (const auto &emp : employees)
                {
                    cout << emp << endl;
                }

                int sortChoice;
                cout << endl;
                cout << "Sort employees by: " << endl;
                cout << "1.(Ascending)" << endl;
                cout << "2.(Descending)" << endl;
                cout << "Enter your choice: ";
                cin >> sortChoice;

                switch (sortChoice)
                {
                case 1:
                    system("cls");
                    employees.sort([](const Employee &emp1, const Employee &emp2)
                                   { return emp1.getID() < emp2.getID(); });
                    cout << "Employees sorted by ID (Ascending)." << endl;
                    break;
                case 2:
                    system("cls");
                    employees.sort([](const Employee &emp1, const Employee &emp2)
                                   { return emp1.getID() > emp2.getID(); });
                    cout << "Employees sorted by ID (Descending)." << endl;
                    break;
                default:
                    cout << "Invalid choice. Sorting skipped." << endl;
                    break;
                }
                cout << endl;
                cout << "Sorted Employees:" << endl;
                for (const auto &emp : employees)
                {
                    cout << emp << endl;
                }
            }
            cout << endl;
            cout << "Press Enter to continue..." << endl;
            cin.ignore();
            cin.get();
            break;
        }
        case 4:
        {
            int upID;
            system("cls");
            cout << "Enter employee ID to update: ";
            cin >> upID;
            auto check_search = [upID](const Employee &employee)
            {
                return employee.getID() == upID;
            };

            bool is_employee_found = false;
            for (auto &employee : employees)
            {
                if (check_search(employee))
                {
                    is_employee_found = true;

                    cout << "Enter updated information for employee with ID " << upID << ":" << endl;

                    cout << "Enter the new name: ";
                    string newName;
                    cin >> newName;
                    employee.setName(newName);

                    // Continue capturing and updating other fields as required.
                    // For example:
                    cout << "Enter the new age: ";
                    int newAge;
                    cin >> newAge;
                    employee.setAge(newAge);

                    cout << "Enter the new salary: ";
                    double newSalary;
                    cin >> newSalary;
                    employee.setSalary(newSalary);

                    cout << "Enter the new department: ";
                    string newDepartment;
                    cin >> newDepartment;
                    employee.setDepartment(newDepartment);

                    // Update ContactInfo
                    cout << "Enter the new email: ";
                    string newEmail;
                    cin >> newEmail;
                    ContactInfo contactInfo = employee.getContactInfo();
                    contactInfo.email = newEmail;
                    employee.setContactInfo(contactInfo);

                    cout << "Enter the new phone number: ";
                    string newPhoneNumber;
                    cin >> newPhoneNumber;
                    contactInfo.phoneNumber = newPhoneNumber;
                    employee.setContactInfo(contactInfo);

                    cout << "Enter the new address: ";
                    string newAddress;
                    cin.ignore();
                    getline(cin, newAddress);
                    contactInfo.address = newAddress;
                    employee.setContactInfo(contactInfo);

                    cout << "Employee information updated successfully." << endl;

                    // Save the updated employee information to the file
                    fstream file("employees.dat", ios::out);
                    for (const auto &emp : employees)
                    {
                        const ContactInfo &info = emp.getContactInfo();
                        file << emp.getID() << " " << emp.getName() << " " << emp.getSalary() << " " << emp.getAge() << " " << emp.getDepartment() << " "
                             << emp.getSex() << " " << emp.getDesignation() << " " << info.email << " " << info.phoneNumber
                             << " " << info.address << endl;
                    }
                    file.close();

                    break;
                }
            }

            if (!is_employee_found)
            {
                cout << "Employee with ID " << upID << " not found." << endl;
            }

            cout << "Press Enter to continue..." << endl;
            cin.ignore();
            cin.get();

            break;
        }

        case 5:
        {
            int delID; // delete ID
            system("cls");
            if (employees.empty())
            {
                cout << "No employees to delete." << endl;
            }
            else
            {
                cout << "Enter employee ID to delete: ";
                cin >> delID;
                system("cls");
                auto predicate = [delID](const Employee &employee)
                {
                    return employee.getID() == delID;
                };

                auto removeIt = remove_if(employees.begin(), employees.end(), predicate);
                if (removeIt != employees.end())
                {
                    cout << "This employee information will be deleted" << endl;
                    cout << endl;
                    cout << *removeIt << endl;
                    cout << endl;

                    employees.erase(removeIt, employees.end());
                    cout << "Employee deleted successfully." << endl;
                }
                else
                {
                    cout << "Employee with ID " << delID << " not found." << endl;
                }
            }

            cout << "Press Enter to continue..." << endl;
            cin.ignore();
            cin.get();

            break;
        }

        case 6:
        {
            system("cls");
            cout << "Bye Bye....." << endl;
            break;
        }
        default:
            system("cls");
            cout << "Invalid choice. Please try again." << endl;
            cout << "Press Enter to continue..." << endl;
            cin.ignore();
            cin.get();
        }

        cout << endl;
    } while (choice != 6);
    return 0;
}