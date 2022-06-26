
#include<iostream>
#include <fstream>
using namespace std;
void allocation_array(int *&init_array,int old_n ,int new_n) ;
void printArray(int *array, int amount);
void load_file (int * & array,int &n);
void add_array(int*&array , int &n, int location , int value);
void remove_array(int* &array, int &n, int location);
void right_array(int* &array, int &n);


int main()
{
    int* array = NULL;
    int n = 0;
    int amount;
    cout << "\nNhap so luong phan tu : " ;
    cin >> amount;
    for(int i = 1 ; i<=amount ;i++)
    {
        cout << "\nNhap phan tu thu " << i << " : ";
        allocation_array(array,n,n+1);
        cin >> array[n++];

    }
    printArray(array,n);
    // them 
    int location ; cout <<"\nNhap vi tri them : ";cin>> location;
    int value ; cout <<"\nNhap gia tri them : ";cin >> value;
    add_array(array,n,location,value);
    printArray(array,n);
    //xóa
    cout << "Nhap vi tri xoa : "; cin>> location;
    remove_array(array,n,location);
    printArray(array,n);
    //dịch phải 
    right_array(array,n);
    printArray(array,n);
    
}
void allocation_array(int *&init_array,int old_n ,int new_n) // hàm cáp phát động
// truyền vào mảng con trỏ , só lượng cũ . số lương mới muosn thay đổ
{
    int * temp = init_array;
    init_array = new int(new_n);
    for(int i = 0; i < old_n ; i ++)
    {
        init_array[i] = temp[i];
    }
    if(temp ==  NULL)
    {
        delete[]temp;
    }
}
void printArray(int *array, int amount) // truyền vào mảng con trỏ và số lượng phàn tử
{
    cout << "\n\t===========XUAT===========" << endl;
    for(int i = 0 ; i<amount ;i++)
    {
        cout << "Gia tri thu " << i << " la : " << array[i] << endl;
    }
}
void load_file (int * & array,int &n)
{
    // open file to read
    ifstream file ("input.txt");
    while(file.eof())
    {
        int x;file >> x;
        // input value file in  array

    }
    file.close();
}
void add_array(int*&array , int &n, int location , int value)
{
    allocation_array(array,n,n+1);
	for (int i = n; i > location; i--)
	{
		array[i] = array[i - 1];
	}
	array[location] = value;
	n++;
}
void remove_array(int* &array, int &n, int location)
{
	for (int i = location; i < n - 1; i++)
	{
		array[i] = array[i + 1];
	}
	allocation_array(array, n - 1, n - 1);
	n--;
}
void right_array(int* &array, int &n)
{
	int k; cout << "Nhap k: "; cin >> k;

	for (int i = 1; i <= k%n; i++)
	{
        add_array(array,n,0,array[n-1]);
        remove_array(array,n,n-1);
	}
}