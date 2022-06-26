#include <iostream>
#include <string>
#include <fstream>
#define MAX 100
using namespace std;

typedef struct bang_diem
{
	float Mac = 0;
	float dai_so = 0;
	float cpp = 0;
}bang_diem;
typedef struct sv
{
	string ma_sv;
	string ho_ten;
	string phai;
	string ngay_sinh;
	bang_diem ds_diem;
}sv;

struct node
{
	//--- data --
	sv data;
	//-- pointer ---
	node* pnext;
};
typedef struct node node;

typedef struct ds_sv
{
	node* phead = NULL;
	node* ptail = NULL;
}ds_sv;
//=====================================
istream& operator >>(istream& is, sv& a);
ostream& operator <<(ostream& os, sv a);
ostream& operator <<(ostream& os, bang_diem a);
void xuat_ds_sv(ds_sv ds, int lc);
//----
node* createNote(sv a);
void add_tail(ds_sv& ds, sv a);
void load_file(ds_sv& ds);
void out_file(ds_sv ds);
void remove_list(ds_sv& ds, string vt);
void _sort(ds_sv& ds);

//============================================
void main()
{
	ds_sv ds;
	bool kt_menu = true;
	load_file(ds);
	while (kt_menu == true)
	{
		system("cls");
		cout << "1. Nhap sv" << endl;
		cout << "2. Xuat danh sach sinh vien" << endl;
		cout << "3. Xoa sinh vien co ma sv nhap tu ban phim" << endl;
		cout << "4. Sap xep" << endl;

		cout << "0. Thoat" << endl;
		int lc; cout << "Nhap lua chon: "; cin >> lc;
		switch (lc)
		{
		case 1:
		{
			int sl; cout << "Nhap sl sv can them: "; cin >> sl;
			cin.ignore();
			for (int i = 1; i <= sl; i++)
			{
				cout << "\t\t---- Nhap sv thu " << i << " ---" << endl;
				sv a;
				cin >> a;
				add_tail(ds, a);
			}
			break;
		}
		case 2:
		{
			xuat_ds_sv(ds, 1);
			system("pause");
			break;
		}
		case 3:
		{
			string vt;
			cin.ignore();
			cout << "Nhap ma sv can xoa: "; getline(cin, vt);
			remove_list(ds, vt);
			break;
		}
		case 4:
		{
			_sort(ds);
			break;
		}
		case 0:
		{
			out_file(ds);
			kt_menu = false;
			break;
		}
		}
	}
	//-- ghi file ----

}
istream& operator >>(istream& is, sv& a)
{
	cout << "Nhap ma sv: "; getline(is, a.ma_sv);
	cout << "Nhap ho ten: "; getline(is, a.ho_ten);
	cout << "Nhap phai: "; getline(is, a.phai);
	cout << "Nhap ngay sinh: "; getline(is, a.ngay_sinh);
	return is;
}
ostream& operator <<(ostream& os, sv a)
{
	os << "Ma sv: " << a.ma_sv << endl;
	os << "Ho ten: " << a.ho_ten << endl;
	os << "Phai: " << a.phai << endl;
	os << "Ngay sinh: " << a.ngay_sinh << endl;
	return os;
}
ostream& operator <<(ostream& os, bang_diem a)
{
	os << "Diem Mac-Lenin: " << a.Mac << endl;
	os << "Diem dai so: " << a.dai_so << endl;
	os << "Diem cpp: " << a.cpp << endl;
	return os;
}
void xuat_ds_sv(ds_sv ds, int lc)
{
	cout << "\t\t===== DS SV ======" << endl;
	int i = 1;
	for (node* k = ds.phead; k != NULL; k = k->pnext)
	{
		cout << "\t\t----- SV thu " << i++ << " ----" << endl;
		cout << k->data;
		if (lc == 1)
		{
			cout << "------ Bang diem ----" << endl;
			cout << k->data.ds_diem;
		}
	}
}

node* createNote(sv a)
{
	node* p = new node;
	p->data = a;
	p->pnext = NULL;
	return p;
}
void add_tail(ds_sv& ds, sv a)
{
	node* p = createNote(a);
	if (ds.phead == NULL)
	{
		ds.phead = ds.ptail = p;
	}
	else
	{
		ds.ptail->pnext = p;
		ds.ptail = p;
	}
}
void load_file(ds_sv& ds)
{
	ifstream fi("dslk.txt");
	while (fi.eof() == false)
	{
		sv a;
		getline(fi, a.ma_sv, ',');
		getline(fi, a.ho_ten, ',');
		getline(fi, a.phai, ',');
		getline(fi, a.ngay_sinh, ',');
		fi >> a.ds_diem.Mac;
		fi.ignore();
		fi >> a.ds_diem.dai_so;
		fi.ignore();
		fi >> a.ds_diem.cpp;
		fi.ignore();//Bỏ
		//--- thêm ---
		add_tail(ds, a);
	}
	fi.close();
}
void out_file(ds_sv ds)
{
	ofstream fo("output.txt");

	for (node* k = ds.phead; k != NULL; k = k->pnext)
	{
		sv a = k->data;
		fo << a.ma_sv << "," << a.ho_ten << "," << a.phai << "," << a.ngay_sinh << ",";
		fo << a.ds_diem.Mac << "," << a.ds_diem.dai_so << "," << a.ds_diem.cpp;
		if (k->pnext != NULL)
		{
			fo << endl;
		}
	}
	fo.close();
}

void remove_list(ds_sv& ds, string vt)
{
	if (ds.phead != NULL)
	{
		while (_stricmp(ds.phead->data.ma_sv.c_str(), vt.c_str()) == 0)
		{
			node* tam = ds.phead;
			ds.phead = ds.phead->pnext;
			delete tam;
			if (ds.phead == NULL)
			{
				ds.ptail = NULL;
				return;
			}
		}

		node* h = NULL;
		for (node* k = ds.phead; k != NULL; k = k->pnext)
		{
			if (_stricmp(k->data.ma_sv.c_str(), vt.c_str()) == 0)
			{

				h->pnext = k->pnext;
			
				delete k;
			
				k = h;

				if (h->pnext == NULL)
				{
					ds.ptail = h;
					break;
				}
			}
			h = k;
		}
	}
}
float _sum(float Mac, float dai_so, float cpp)
{
	return (Mac + dai_so + cpp) / 3;
}
void sap_xep(ds_sv& ds)
{
	for (node* k = ds.phead; k->pnext != NULL; k = k->pnext)
	{
		float dtb_k = _sum(k->data.ds_diem.Mac, k->data.ds_diem.dai_so, k->data.ds_diem.cpp);
		for (node* h = k->pnext; h != NULL; h = h->pnext)
		{
			float dtb_h = _sum(h->data.ds_diem.Mac, h->data.ds_diem.dai_so, h->data.ds_diem.cpp);
			if (dtb_h < dtb_k)
			{
				swap(k->data, h->data);
			}
		}
	}
}