//#include <string>
//#include <iostream>
//
//using namespace std;
//
//struct School
//{
//    std::string name;
//    int date;
//    int mons;
//    int year;
//
//    School* next; //��������� �� ��������� ������� ������ 
//};
//
//class Library
//{
//private:
//    School* pHead;  //"������" ������
//    School* pLast;  //"�����" ������
//    //int number;       //����� ������
//
//public:
//    Library(void);                                          //����������� , ���������� pHead , pLast � number
//    ~Library(void);
//    Library(int, int, int, std::string);                 //����������� , ��������� ������ "������" ������
//
//
//    void AddRecord(int);            //���������� ������ � ������
//    void EditRecord();             // ����� �� ����� � �������������� ������
//    void PrintList();              //����� �� ����� ������
//
//
//    void FindBirthmons(int);       //����� � ����� �� ����� ��������� ������� �� �������
//    void DeleteList();            //�������� ������ , ������ �������� ������ , ���������� ��� ������
//};
//
//Library::Library(void)
//{
//    pHead = NULL;
//    pLast = NULL;
//    //  number = 0;
//}
//
//Library::Library(int date, int mons, int year, std::string name)
//{
//    School* temp = new School;
//
//    temp->date = date;
//    temp->mons = mons;
//    temp->year = year;
//    temp->name = name;
//    temp->next = NULL;
//
//    pHead = temp;
//    pLast = temp;
//}
//
//Library::~Library(void)
//{
//    DeleteList();
//}
//
////�������� ������ , �� ���� �������� ������ , ���������� ��� ������
//void Library::DeleteList(void)
//{
//    if (pHead != NULL)
//    {
//        School* temp;
//        while (pHead != pLast)
//        {
//            temp = pHead->next;
//            delete pHead;
//            pHead = temp;
//        }
//        delete pHead;
//        pHead = NULL;
//        pLast = NULL;
//    }
//}
//
////���������� ������� � ������
//void Library::AddRecord(int n)
//{
//    for (int i = 0; i < n; i++)
//    {
//        School* temp = new School;
//
//        cout << "\n������� ������ ������� �" << i + 1 << ": \n";
//        cout << "���: ";
//        cin >> temp->name;
//        cout << "���� ��������: ";
//        cin >> temp->date;
//        cout << "����� ��������: ";
//        cin >> temp->mons;
//        cout << "��� ��������: ";
//        cin >> temp->year;
//
//        if (pHead == NULL)
//            pHead = temp;
//        else
//            pLast->next = temp;
//
//        pLast = temp;
//        pLast->next = pHead;
//    }
//}
//
//void Library::EditRecord()
//{
//    School* temp;
//    temp = pHead;
//    if (temp != NULL)
//    {
//        int flag = 0;
//        cout << "\n������� ��� �������: \n";
//        cout << "���: ";
//        string str;
//        (cin >> str).get();
//        while (1)
//        {
//            if (str != (temp->name))
//            {
//                temp = temp->next;
//                if (temp == pHead) break;
//            }
//            else
//            {
//                flag = 1;
//                cout << "\n������� ����� ������ �������: \n";
//                cout << "���� ��������: ";
//                cin >> temp->date;
//                cout << "����� ��������: ";
//                cin >> temp->mons;
//                cout << "��� ��������: ";
//                cin >> temp->year;
//                break;
//            }
//        }
//        if (flag == 0)
//        {
//            cout << "������ � ����� ������ �� ������ � ������\n\n";
//            cin.get();
//        }
//    }
//}
//
////����� �� ����� ������
//void Library::PrintList()
//{
//    School* temp;
//    temp = pHead;
//    if (temp != NULL)
//    {
//        int i = 0;
//        while (true)
//        {
//            cout << "\n������ ������� �" << i + 1 << ":\n";
//            cout << "���: " << temp->name << "; ���� ��������: " << temp->date << "." << temp->mons << "." << temp->year << ".\n";
//            temp = temp->next;
//            if (temp == pHead) break;
//            ++i;
//        }
//    }
//}
//
////����� � ����� �� ����� ��������� ������� �� �������
//void Library::FindBirthmons(int mons)
//{
//    School* temp = pHead;
//    if (temp != NULL)
//    {
//        int i = 0;
//        while (true)
//        {
//            if (temp->mons == mons)
//            {
//                cout << "\n" << i + 1 << ") " << temp->name;
//                ++i;
//            }
//            temp = temp->next;
//            if (temp == pHead) break;
//            ++i;
//        }
//    }
//}
////�������, ��������� ��������� ������ ������, �������� ����� (������� � ��������, ���� ��������, ����� ��������, ��� ��������). \
////��������� ���������, �������� ������ ��������, ��������� � ��� ������. 
//
//#include <iostream>
////#include "Library.h"
//
//int main()
//{
//    setlocale(LC_ALL, "Russian");
//    int n;
//    cout << "������� ��������� ��������� � ������: ";
//    cin >> n;
//
//    Library* list = new Library();
//
//    list->AddRecord(n);
//    list->EditRecord();
//    system("cls");
//    list->PrintList();
//    list->FindBirthmons(3);
//    list->DeleteList();
//
//    cout << endl;
//    system("pause");
//    return 0;
//}

#include "My_List.h"
#include <Windows.h>
#include "HT.h"

int task(DLIST& DL, int search)
{
	ptrNODE ptr = DL.get_begin();
	int result = 0;
	while (ptr)
	{
		if (ptr->info.get_date() == search)
			result += ptr->info.kind();
		ptr = ptr->next;
	}
	return result;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	std::ifstream file("schet.txt");
	HashTable Table(file);
	Table.print();
	std::cout << "\n========================\n";
	//Table.remove(1);
	//Table.print();
	std::ifstream file1("schet1.txt");
	Schet ptr(file1);
	Table.add(ptr);
	Table.print();
	/*if (file)
	{
		DLIST DL("schet.txt");
		DL.print();
		char choice;
		bool is_exit = false;
		while (!is_exit)
		{
			std::cout << "\n============\n ������� ����: ";
			int search;
			std::cin >> search;
			std::cout << "\n������ �� ��� ����: " << task(DL, search) << "\n";
			std::cout << "��������� ���������?(y/any): ";
			std::cin >> choice;
			if (choice == 'y')
				is_exit = true;
		}
	}*/
	std::cin.get();
}