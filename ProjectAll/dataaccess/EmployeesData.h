#ifndef _Employees_Data_H
#define _Employees_Data_H

#include <string>
#include <vector>
#include "../businessobjects/Employees.h"

using namespace std;

class EmployeesData{
public:
    int maxId;
private:
    vector<Employees> _data;
public:
    EmployeesData();
    EmployeesData(string s);
	int CreateEmployee(Employees c);
    int UpdateEmployee(int id, Employees c);
    Employees Get(int id);
    Employees* GetPointer(int id);
    int GetSize();
    int ExportToFile(string filename);
};

#endif