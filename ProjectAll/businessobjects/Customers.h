#ifndef _Customers_H
#define _Customers_H

#include <string>
#include "../libs/json.hpp"

using namespace std;
using json = nlohmann::json;

class Customers{
public:
	int CustomerID;
	string CustomerName, ContactName, Address, City, PostalCode, Country;
public:
	Customers();
	Customers(int CustomerID, string CustomerName, string ContactName, string Address, string City, string PostalCode, string Country);
	string ToString();
	json ToJson();
};

#endif
