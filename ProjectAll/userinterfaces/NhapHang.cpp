#include "NhapHang.h"
#include <iostream>

using namespace std;

void NhapHang::UINhapHang(){
    int select;
	do{
        system("cls");
        cout << "PHAN MEM QUAN LY BAN HANG" << endl;
        cout << "=========================" << endl;
        cout << "---------Quan ly hang nhap" << endl;
        cout << "0.Quay lai" << endl;
        cout << "=========================" << endl;
        cout << "Lua chon thao tac: ";
        // cin >> select;
        // cin.ignore();
        cin >> select;
        switch (select){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                break;
        }
    }while(select!=0);
    // getch();
    
}