#ifndef _Employees_H
#define _Employees_H

#include <string>
#include "../libs/json.hpp"

using namespace std;
using json = nlohmann::json;

class Employees{
public:
	int EmployeeID;
	string LastName, FirstName, BirthDate, Photo, Notes;
public:
	Employees();
	Employees(int EmployeeID, string LastName, string FirstName, string BirthDate, string Photo, string Notes);
	string ToString();
	json ToJson();
};

#endif
