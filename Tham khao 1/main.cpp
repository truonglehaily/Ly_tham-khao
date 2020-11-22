#include<iostream>
#include<iomanip>
using namespace std;
int pc=10000,cc=10000;
class Nguoi{
	protected:
	string hoten, dc, sdt;
	public:
	Nguoi(){
		hoten="", dc="", sdt="";
	}
};
class Nguoimua: public Nguoi{
	private:
	string loai;
	int ID;
	public:
	Nguoimua(){
		int temp;
		cout<< "nhap ten nguoi mua: ";getline(cin,hoten);
		cout<< "dia chi: ";getline(cin,dc);
		cout<< "sdt: ";getline(cin,sdt);
		cout<< "loai nguoi mua: \n1.mua le\n2.mua tap the\n3.mua qua mang\n  ";cin>>temp;cin.ignore();
		if(temp==1) loai="mua le";
		if(temp==2) loai="mua tap the";
		if(temp==3) loai="mua qua mang";
		ID=pc;
		pc++;
	}
	void INTT(){
		cout<<endl<<left<<setw(10)<<"ID"<<setw(20)<<"hoten"<<setw(20)<<"dia chi"<<setw(20)<<"sdt"<<setw(20)<<"loai nguoi mua";
		cout<<endl<<left<<setw(10)<<ID<<setw(20)<<hoten<<setw(20)<<dc<<setw(20)<<sdt<<setw(20)<<loai<<endl;
	}
	string gethoten(){
		return hoten;
	}
	friend class HoaDon;
};
class Vetau{
	int ID,dongia;
	string loaighe;
	public:
		Vetau(){
			int temp;
			cout<< "nhap loai ghe: ";getline(cin,loaighe);
			cout<< "don gia: ";cin>>dongia;cin.ignore();
			ID=cc;
			cc++;
		}
		void INTT(){
			cout<<endl<<left<<setw(10)<<"ma ve"<<setw(20)<<"loai ghe"<<setw(20)<<"don gia";
			cout<<endl<<left<<setw(10)<<ID<<setw(20)<<loaighe<<setw(20)<<dongia<<endl;	
		}
		int getmv(){
			return ID;
		}
		friend class HoaDon;
};
class HoaDon{
	public: 
	Nguoimua *nm;
	Vetau **vt;
	void setnm(Nguoimua *nm){
		this->nm=nm;
	}
	Nguoimua getnm(){
		return *this->nm;
	}
	void setsl(int sl){
		vt= new Vetau *[sl];
	}
	void setvt(int i, Vetau *VT){
		this->vt[i]=VT;
	}
	Vetau getvt(int i){
		return *this->vt[i];
	}
};
Nguoimua *nm;
Vetau *vt;
HoaDon *hd;
int m,n,sloai[50],sl[50][50];
void menu(){
	cout<<"\n_________MENU_________"
	<< "\n1.nhap va xuat tt nguoi mua"
	<< "\n2.nhap va xuat tt ve tau"
	<< "\n3.nhap tt hoa don"
	<< "\n4.xuat tt hoa don"
	<< "\n5.sap xep danh sach hoa don"
	<< "\n6.lap bang ke so tien phai tra"
	<<"\n.nhap lua chon(nhap 0 de thoat): ";
}
void nv1(){	
	cout<< "\nNhap thong tin nguoi mua: ";
	cout<< "\nnhap so nguoi mua: ";cin>>m;cin.ignore();
	nm= new Nguoimua[m];
	cout<< "\nThong tin nguoi mua: ";
	for(int i=0;i<m;i++){
		nm[i].INTT();
	}	
}
void nv2(){
	cout<< "\nNhap thong tin ve tau: ";
	cout<< "\nnhap so luong ve tau: ";cin>>n;cin.ignore();
	vt= new Vetau[n];
	cout<< "\nThong tin ve tau: ";
	for(int i=0;i<n;i++){
		vt[i].INTT();
	}
}
void nv3(){
	int mv;
	cout<< "\nNhap thong tin hoa don: ";
	hd= new HoaDon[m];
	for(int i=0;i<m;i++){
		hd[i].setnm(nm+i);
		hd[i].getnm().INTT();
		do{
			cout<< "nhap so loai ve can mua(<=4): ";cin>>sloai[i];
		}while(sloai[i]>4);
		hd[i].setsl(sloai[i]);
		for(int j=0;j<sloai[i];j++){
			do{
				cout<< "nhap ma ve(100**): "; cin>>mv;
			}while(mv<vt[0].getmv()|| mv>vt[n-1].getmv());
			for(int k=0;k<n;k++){
				if(mv==vt[k].getmv())
					hd[i].setvt(j,vt+k);
			}
			do{
				cout<< "nhap so luong ve(<=20): ";cin>>sl[i][j];
			}while(sl[i][j]>20);
		}
	}
}
void nv4(){
	for(int i=0;i<m;i++){
		cout<<endl;
		cout<< "Thong tin khach hang: ";hd[i].getnm().INTT();
		cout<< "Thong tin hoa don: ";
		for(int j=0;j<sloai[i];j++){
			hd[i].getvt(j).INTT();
			cout<<" so luong ve tau: "<<sl[i][j];
		}
		cout<<endl;
	}
}
void ad_swap(HoaDon &hd1, HoaDon &hd2){
	HoaDon temp=hd1;
	hd1=hd2;
	hd2=temp;
}
void sx1(){
	for(int i=0;i<m;i++){
		for(int j=i+1;j<m;j++){
			if(hd[i].getnm().gethoten()>=hd[j].getnm().gethoten()){
				cout<<hd[i].getnm().gethoten()<<" > "<<hd[j].getnm().gethoten();
				ad_swap(hd[i],hd[j]);
			}
		}
	}
	nv4();
}
void sx2(){
	int total=0,k;
	for(int i=0;i<m;i++){
		total+=sloai[i];
	}	
	for(int i=0;i<total;i++){
		k=sloai[i];
		for(int j=0;j<total;j++){
			if(sl[i/k][i%k] > sl[j/k][j%k]){
				swap(sl[i/k][i%k],sl[j/k][j%k]);
			}
		}
	}
	for(int i=0;i<m;i++){
		for(int j=0;j<sloai[i];j++){
			cout<< "so luong ve: "<<sl[i][j];
			cout<<endl;
		}
	}
}
void nv5(){
	int lc;
	cout<< "Lua chon cach sap xep ds: "
	<< "\n1.theo ho ten\n2.theo so luong ve mua(giam dan) ";cin>>lc;
	if(lc==1) sx1();
	else sx2();
}
int main(){
	int lc;
	do{
		menu();
		cin>>lc;cin.ignore();
		switch(lc){
			case 1:nv1();break;
			case 2:nv2();break;
			case 3:nv3();break;
			case 4:nv4();break;
			case 5:nv5();break;
			//case 6:mv6();break;
			default: break;
		}
	}while(lc!=0);
}
