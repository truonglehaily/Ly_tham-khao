/** @file EmployeesData.h
 *  @brief EmployeesData stores all Employees objects
 *  
 *  @author Ly Truong (truonglehaily)
 *  @bug No known bugs.
 */

#include "EmployeesData.h"
#include <fstream>
#include "../libs/json.hpp" //https://github.com/nlohmann/json

using json = nlohmann::json;

/** @brief Function constructors an object.
 *  
 *  Function constructors an object.
 */
EmployeesData::EmployeesData(){
    maxId = 0;
    _data.resize(0);
}

/** @brief Function constructors an object.
 *  
 *  Function constructors an object, read data from file then load data to this object.
 */
EmployeesData::EmployeesData(string filename){
    maxId = 0;
    _data.resize(0);
    ifstream inFile(filename);
    const int maxSize = 255;
    char buff[maxSize];
    while (inFile.getline(buff, maxSize)){
        json j = json::parse(buff);
        Employees e(
            j["EmployeeID"],
            j["LastName"],
            j["FirstName"],
            j["BirthDate"],
            j["Photo"],
            j["Notes"]
        );
        _data.push_back(e);
    };
    inFile.close();
}

/** @brief Function add a Employees object to the end of the list inside EmployeesData.
 *  
 *  Function add a Employees object to the end of the list inside EmployeesData.
 *  @return maxId of Employees object inside EmployeesData;
 */
int EmployeesData::CreateEmployee(Employees e){
    if(maxId < e.EmployeeID) maxId = e.EmployeeID;

    _data.push_back(e);
    return maxId;
}

/** @brief Function updates a Employees object at a position inside the list inside EmployeesData.
 *  
 *  Function updates a Employees object at a position inside the list inside EmployeesData.
 *  @return maxId of Employees object inside EmployeesData;
 *  if fail, return -1;
 */
int EmployeesData::UpdateEmployee(int id, Employees e){
    if(id < 0) return -1;
    if(id >= _data.size()) return -1;
    _data[id] = e;
    if(maxId < e.EmployeeID) maxId = e.EmployeeID;
    return maxId;
}

/** @brief Function return a Employees object at a position inside the list inside EmployeesData.
 *  
 *  Function return a Employees object at a position inside the list inside EmployeesData.
 *  @return Employees object;
 */
Employees EmployeesData::Get(int id){
    return _data[id];
}

/** @brief Function return a Employees object at a position inside the list inside EmployeesData.
 *  
 *  Function return a Employees object at a position inside the list inside EmployeesData.
 *  @return Employees object;
 *  if fail, return NULL;
 */
Employees* EmployeesData::GetPointer(int id){
    Employees* e = nullptr;
    if(id < 0) return e;
    if(id >= _data.size()) return e;
    e = &_data[id];
    return e;
}

/** @brief Function return size of EmployeesData.
 *  
 *  Function return size of EmployeesData. This is the quantity of Employees objects inside EmployeesData.
 *  @return number of Employees objects;
 */
int EmployeesData::GetSize(){
    return _data.size();
}

/** @brief Function write all data in EmployeesData to file.
 *  
 *  Function write all data in EmployeesData to file.
 *  @return 1 if success, 0 if fail;
 */
int EmployeesData::ExportToFile(string filename){
    ofstream outFile(filename, ios::out);
    if (!outFile) return 0;
    for(Employees e:_data){
        outFile << e.ToJson() << endl;
    }
    outFile.close();
    return 1;
}