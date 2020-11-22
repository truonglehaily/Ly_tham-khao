#include "Customers.h"

using namespace std;

/** @brief Function constructors an object.
 *  
 *  Function constructors an object.
 */
Customers::Customers(){
	
}

/** @brief Function constructors an object with params.
 *  
 *  Function constructors an object with params.
 */
Customers::Customers(int CustomerID, string CustomerName, string ContactName, string Address, string City, string PostalCode, string Country){
	this->CustomerID = CustomerID;
	this->CustomerName = CustomerName;
	this->ContactName = ContactName;
	this->Address = Address;
	this->City = City;
	this->PostalCode = PostalCode;
	this->Country = Country;
}

/** @brief Function converts this object to string.
 *  
 *  Function converts this object to string.
 *  @return a string;
 *  Example: Customers c(1, "LG", "HaiLy", "LienChieu", "DaNang", "550000", "VietNam") -> {1, LG, HaiLy, LienChieu, DaNang, 550000, VietNam}
 */
string Customers::ToString(){
	string s;
	s += "{";
	s += to_string(CustomerID) + ", ";
	s += CustomerName + ", ";
	s += ContactName + ", ";
	s += Address + ", ";
	s += City + ", ";
	s += PostalCode + ", ";
	s += Country;
	s += "}";
	return s;
}

/** @brief Function converts this object to json object.
 *  
 *  Function converts this object to json object.
 *  @return a json object;
 *  Example: Customers c(1, "LG", "HaiLy", "LienChieu", "DaNang", "550000", "VietNam") -> {"CustomerID":1,"CustomerName":"LG","ContactName":"HaiLy","Address":"LienChieu","City":"DaNang","PostalCode":"550000","Country":"VietNam"}
 */
json Customers::ToJson(){
	json j;
	j["CustomerID"] = CustomerID;
	j["CustomerName"] = CustomerName;
	j["ContactName"] = ContactName;
	j["Address"] = Address;
	j["City"] = City;
	j["PostalCode"] = PostalCode;
	j["Country"] = Country;
	return j;
}