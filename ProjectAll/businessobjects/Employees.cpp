#include "Employees.h"

using namespace std;

/** @brief Function constructors an object.
 *  
 *  Function constructors an object.
 */
Employees::Employees(){
	
}

/** @brief Function constructors an object with params.
 *  
 *  Function constructors an object with params.
 */
Employees::Employees(int EmployeeID, string LastName, string FirstName, string BirthDate, string Photo, string Notes){
	this->EmployeeID = EmployeeID;
	this->LastName = LastName;
	this->FirstName = FirstName;
    this->BirthDate = BirthDate;
	this->Photo = Photo;
    this->Notes = Notes;
}

/** @brief Function converts this object to string.
 *  
 *  Function converts this object to string.
 *  @return a string;
 *  Example: Employees e(1, "HaiLy", "TruongLe", "22-9-1992", "avatar.jpg", "LyTruong") -> {1, HaiLy, TruongLe, 22-9-1992, avatar.jpg, LyTruong}
 */
string Employees::ToString(){
	string s;
	s += "{";
	s += to_string(EmployeeID) + ", ";
	s += LastName + ", ";
	s += FirstName + ", ";
	s += BirthDate + ", ";
	s += Photo + ", ";
	s += Notes;
	s += "}";
	return s;
}

/** @brief Function converts this object to json object.
 *  
 *  Function converts this object to json object.
 *  @return a json object;
 *  Example: Employees e(1, "HaiLy", "TruongLe", "22-9-1992", "avatar.jpg", "LyTruong") -> {"EmployeeID":1, "LastName":"TruongLe", "FirstName":"HaiLy", "BirthDate":"22-9-1992", "Photo":"avatar.jpg", "Notes":"LyTruong"}
 */
json Employees::ToJson(){
	json j;
	j["EmployeeID"] = EmployeeID;
	j["LastName"] = LastName;
	j["FirstName"] = FirstName;
	j["BirthDate"] = BirthDate;
	j["Photo"] = Photo;
	j["Notes"] = Notes;
	return j;
}