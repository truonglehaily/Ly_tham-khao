#ifndef _Customers_Data_H
#define _Customers_Data_H

#include <string>
#include <vector>
#include "../businessobjects/Customers.h"

using namespace std;

class CustomersData{
public:
    int maxId;
private:
    vector<Customers> _data;
public:
    CustomersData();
    CustomersData(string s);
	int CreateCustomer(Customers c);
    int UpdateCustomer(int id, Customers c);
    int DeleteCustomer(int id, Customers c);
    Customers Get(int id);
    Customers* GetPointer(int id);
    int GetSize();
    int ExportToFile(string filename);
};

#endif