#include <optional>
#include <list>
#include <iostream>
#include <iomanip>
#include <math.h>
#include <algorithm>
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

    // for sorting by salary in ascending
    static bool salaryAscend(const Employee &emp1, const Employee &emp2)
    {
        return emp1.salary < emp2.salary;
    }
    // for sorting by salary in descending
    static bool salaryDescend(const Employee &emp1, const Employee &emp2)
    {
        return emp1.salary > emp2.salary;
    }
    // for displaying the information about employees
    friend ostream &operator<<(ostream &os, const Employee &emp)
    {
        os << left << setw(8) << "ID" << setw(15) << "Name" << setw(12) << "Salary" << setw(8) << "Age"
           << setw(20) << "Department" << setw(10) << "Sex" << setw(20) << "Designation"
           << setw(25) << "Email" << setw(18) << "Phone Number" << setw(35) << "Address" << endl;

        os << left << setw(8) << emp.id << setw(15) << emp.name << setw(12) << fixed << setprecision(2) << emp.salary << setw(8) << emp.age
           << setw(20) << emp.department << setw(10) << emp.sex << setw(20) << emp.designation
           << setw(25) << emp.contactInfo.email << setw(18) << emp.contactInfo.phoneNumber << setw(35) << emp.contactInfo.address;

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
}