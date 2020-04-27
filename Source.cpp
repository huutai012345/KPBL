#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
#include<time.h>.
using namespace std;
int pointer = 20;
int pointer1 = 20;
int pointer2 = 20;
int z = 0;
int delay=1000;
string strMN[] = { "Ly Thuyet","  Demo","  CODE","  Exit" };
struct list  
{
	string value;
	list *pNext;
};
void gotoXY(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x, y };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
void SetColor(WORD color)
{
	HANDLE hConsoleOutput;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void textcolor(int x)	
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau,x);
}
void noCursorType()
{
	CONSOLE_CURSOR_INFO info;
	info.bVisible = FALSE;
	info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
}
void themvaodau(list *&dau,string str)
{
	list * a = new list;
	a->pNext = NULL;
	a->value = str;
	if (dau == NULL)
	{
		dau = a;
	}
	else
	{
		a->pNext = dau;
		dau = a;
	}
}
void themvaocuoi(list *&dau, string str)
{
	list *a = new list;
	a->pNext = NULL;
	a->value = str;
	if (dau == NULL)
	{
		dau = a;
	}
	else
	{
		list *k = dau;
		while (true)
		{
			if (k->pNext == NULL)
			{
				k->pNext = a;
				break;
			}
			k = k->pNext;
		}
	}
}
void xoadau(list *&dau)
{
	list *k = NULL;
	k = dau;
	dau = dau->pNext;
	delete k;
}
void xoacuoi(list *&dau)
{
	list *k = dau;
	list *a = new list;
	while (true)
	{
		if (k->pNext == NULL)
		{
			a->pNext = NULL;
			delete k;
			break;
		}
		a = k;
		k = k->pNext;
	}
}
string docfile()
{
	string str;
	ifstream FileIn;
	FileIn.open("INPUT.txt");
	getline(FileIn, str);
	FileIn.close();
	return str;
}
void tachchuoi(string str[], string str1, int &j)
{
	bool kt = false;
	for (int i = 0; i < str1.length(); i++)
	{
		if (kt == true && str1[i] >= '0' && str1[i] <= '9')
		{
			str[j - 1] = str[j - 1] + str1[i];
		}
		else if (str1[i] >= '0' && str1[i] <= '9')
		{
			str[j++] = str1[i];
			kt = true;
		}
		else if (str1[i] == '+' || str1[i] == '-' || str1[i] == '*' || str1[i] == '/' || str1[i] == '(' || str1[i] == ')')
		{
			str[j++] = str1[i];
			kt = false;
		}
		else
			kt = false;
	}
}
bool sosanh(string str, string str1)
{
	if (str == "+" && str1 == "-" || str == "-"&&str1 == "+" || str == "*"&&str1 == "/" || str == "/"&&str1 == "*" || str == "*"&&str1 == "+" || str == "*"&&str1 == "-" || str == "/"&&str1 == "+" || str == "/"&&str1 == "-" || str == "+"&&str1 == "+" || str == "-"&&str1 == "-" || str == "*"&&str1 == "*" || str == "/"&&str1 == "/")
		return true;
	else
		return false;
}
void xuat(list *dau, list *dau1, int j, string str[], int h)
{
	gotoXY(55, 3);
	cout << "STEP 1";
	gotoXY(1, 5);
	for (int i = 0; i < j; i++)
	{
		if (i == h)
		{
			textcolor(199);
		}
		cout << str[i];
		textcolor(7);
		cout << "  ";
	}
	gotoXY(2, 7);
	cout << " STACK:";
	textcolor(2);
	for (list *k = dau; k != NULL; k = k->pNext)
	{
		cout << k->value ;
		textcolor(7);
		cout << "  ";
	}
	textcolor(7);
	gotoXY(2, 8);
	cout << " QUEUE:";
	for (list *k = dau1; k != NULL; k = k->pNext)
	{
		if (k->pNext == NULL)
		{
			textcolor(4);
			cout << k->value;
			textcolor(7);
			cout << "  ";
		}
		else
		{
			cout << k->value;
			cout << "  ";
		}
	}
	cout << endl;
	Sleep(delay);
	textcolor(7);
	system("cls");
}
void kpbl(string str[], int j, string str1)
{
	int x, a, b;
	list *dau, *dau1;
	dau = NULL;
	dau1 = NULL;
	noCursorType();

	//STEP 1
	for (int i = 0; i < j; i++)
	{
		if (str[i] == "(")
		{
			themvaodau(dau, str[i]);
			gotoXY(20, 15);
			cout << " La \" ( \" nen them vao STACK";
			xuat(dau, dau1, j, str, i);
		}
		else if (str[i] == ")")
		{
			while (true)
			{
				if (dau->value == "(")
				{
					xoadau(dau);
					gotoXY(20, 15);
					cout << "Phan tu dau STACK la \" ( \" nen dung lai vao xoa \" ( \" ";
					xuat(dau, dau1, j, str, i);
					break;
				}
				themvaocuoi(dau1, dau->value);
				xoadau(dau);
				gotoXY(20, 15);
				cout << "Lay phan tu dau STACK ra them vao QUEUE";
				xuat(dau, dau1, j, str, i);
			}
		}
		else if (str[i] == "+" || str[i] == "-" || str[i] == "*" || str[i] == "/")
		{
			if (dau == NULL)
			{
				themvaodau(dau, str[i]);
				gotoXY(20, 15);
				cout << str[i] << " La toan tu nhung STACK rong nen them vao STACK";
				xuat(dau, dau1, j, str, i);
			}
			else
			{
				while (true)
				{
					gotoXY(20, 15);
					cout << str[i] << " La toan tu va ";
					if (dau->value == "(" )
					{
						themvaodau(dau, str[i]);
						cout << "phan tu dau STACK la \" ( \" them vao STACK";
						xuat(dau, dau1, j, str, i);
						break;
					}
					if (sosanh(dau->value, str[i]) == false)
					{
						themvaodau(dau, str[i]);
						cout << "phan tu dau STACK la toan tu do uu tien thap hon nen them vao STACK";
						xuat(dau, dau1, j, str, i);
						break;
					}
					else if (sosanh(dau->value, str[i]) == true)
					{
						themvaocuoi(dau1, dau->value);
						xoadau(dau);
						cout << "phan tu dau STACK la toan tu do uu tien lon hon nen lay ra va them vao QUEUE";
						xuat(dau, dau1, j, str, i);
					}
					if (dau == NULL)
					{
						themvaodau(dau, str[i]);
						gotoXY(20, 15);
						cout << "STACK rong nen them vao STACK";
						xuat(dau, dau1, j, str, i);
						break;
					}
				}
			}
		}
		else
		{
			themvaocuoi(dau1, str[i]);
			gotoXY(20, 15);
			cout << str[i] << " La toan hang nen them QUEUE";
			xuat(dau, dau1, j, str, i);
		}
	}
	Sleep(delay);

	//STEP 2
	while (dau != NULL)
	{
		themvaocuoi(dau1, dau->value);
		xoadau(dau);
		system("cls");
		gotoXY(55, 3);
		cout << "STEP 2";
		gotoXY(1, 5);
		cout << "STACK:\t";
		for (list *k = dau; k != NULL; k = k->pNext)
		{
			cout << k->value << "  ";
		}
		cout << endl;
		cout << " QUEUE:\t";
		for (list *k = dau1; k != NULL; k = k->pNext)
		{
			cout << k->value << "  ";
		}
		gotoXY(20, 15);
		cout << "Cut tat ca cac phan tu cua STACK sang QUEUE";
		Sleep(delay);
		textcolor(7);
	}
	system("cls");
	Sleep(delay);


	//STEP 3
	while (dau1 != NULL)
	{
		system("cls");
		str1 = dau1->value;
		xoadau(dau1);
		if (str1 == "+" || str1 == "-" || str1 == "*" || str1 == "/")
		{
			a = atoi(dau->value.c_str());
			xoadau(dau);
			b = atoi(dau->value.c_str());
			xoadau(dau);
			if (str1 == "+")
			{
				x = a + b;
			}
			else if (str1 == "-")
			{
				x = b - a;
			}
			else if (str1 == "*")
			{
				x = a * b;
			}
			else if (str1 == "/")
			{
				x = b / a;
			}
			themvaodau(dau, to_string(x));
			gotoXY(55, 3);
			cout << "STEP 3";
			gotoXY(1, 5);
			cout << "STACK:\t";
			for (list *k = dau; k != NULL; k = k->pNext)
			{
				cout << k->value << "  ";
			}
			cout << endl;
			cout << " QUEUE:\t";
			textcolor(2);
			for (list *k = dau1; k != NULL; k = k->pNext)
			{
				cout << k->value;
				textcolor(7);
				cout<< "  ";
			}
			textcolor(7);
			gotoXY(20, 15);
			cout << str1 <<" La toan tu nen lay 2 phan tu dau STACK ra la " << a << " va " << b ;
			gotoXY(20, 16);
			cout<<" va thuc hien voi phep tinh cua toan tu la phep \" " <<str1<<" \" sau do them ket qua la "<<x<<" vao lai QUEUE";
			textcolor(0);
			Sleep(delay);
			textcolor(7);
		}
		else
		{
			themvaodau(dau, str1);
			gotoXY(55, 3);
			cout << "STEP 3";
			gotoXY(1, 5);
			cout << "STACK:\t";
			for (list *k = dau; k != NULL; k = k->pNext)
			{
				cout << k->value << "  ";
			}
			cout << endl;
			cout << " QUEUE:\t";
			textcolor(2);
			for (list *k = dau1; k != NULL; k = k->pNext)
			{
				cout << k->value;
				textcolor(7);
				cout << "  ";
			}
			textcolor(7);
			gotoXY(20, 15);
			cout << str1 << " La toan hang nen chuyen tu QUEUE sang lai STACK";
			Sleep(delay);
		}

		if (dau1 == NULL)
		{
			gotoXY(55, 3);
			cout << "STEP 3";
			gotoXY(1, 5);
			cout << "STACK:\t";
			for (list *k = dau; k != NULL; k = k->pNext)
			{
				cout << k->value << "  ";
			}
			cout << endl;
			cout << " QUEUE:\t";
			textcolor(2);
			for (list *k = dau1; k != NULL; k = k->pNext)
			{
				cout << k->value;
				textcolor(7);
				cout << "  ";
			}
			textcolor(7);
			gotoXY(20, 15);
			cout <<"QUEUE rong nen phan tu dau cua STACK la ket qua                           ";
			Sleep(delay);
		}
	}

	system("cls");
	Sleep(100);
	

	cout << "\n\n\t\tKET QUA CUOI CUNG LA:" << x << endl;
	system("pause");
}
void box()
{
	for (int i = 40; i < 70; i++)
	{
		gotoXY(i, 15);
		textcolor(192);
		cout << " ";
		Sleep(10);
		textcolor(7);
	}
	for (int i = 15; i < 27; i++)
	{
		gotoXY(69, i);
		textcolor(192);
		cout << " ";
		Sleep(10);
		textcolor(7);
	}
	for (int i = 69; i >= 40; i--)
	{
		gotoXY(i, 26);
		textcolor(192);
		cout << " ";
		Sleep(10);
		textcolor(7);
	}
	for (int i = 26; i >= 15; i--)
	{
		gotoXY(40, i);
		textcolor(192);
		cout << " ";
		Sleep(10);
		textcolor(7);
	}
}
void box1()
{
	for (int i = 40; i < 70; i++)
	{
		gotoXY(i, 15);
		textcolor(192);
		cout << " ";
		textcolor(7);
	}
	for (int i = 15; i < 27; i++)
	{
		gotoXY(69, i);
		textcolor(192);
		cout << " ";
		textcolor(7);
	}
	for (int i = 69; i >= 40; i--)
	{
		gotoXY(i, 26);
		textcolor(192);
		cout << " ";
		textcolor(7);
	}
	for (int i = 26; i >= 15; i--)
	{
		gotoXY(40, i);
		textcolor(192);
		cout << " ";
		textcolor(7);
	}
}
void menu()
{
	box1();
	int j = 1;
	string str1;
	ifstream FileIn;
	FileIn.open("input1.txt", ios::in);
	while (true)
	{
		gotoXY(35, j++);
		SetColor(10 + rand() % +6);
		getline(FileIn, str1);
		cout << str1 << endl;
		if (FileIn.eof())
		{
			break;
		}
		Sleep(10);
	}
	FileIn.close();
	textcolor(7);
	gotoXY(53, 18);
	cout << "MENU";
	j = 20;
	for (int i = 0; i < 4; i++)
	{
		gotoXY(51, j++);
		cout << strMN[i];
	}
}
void menu1()
{
	box1();
	int j = 1;
	string str1;
	ifstream FileIn;
	FileIn.open("input1.txt", ios::in);
	while (true)
	{
		gotoXY(35, j++);
		SetColor(10 + rand() % +6);
		getline(FileIn, str1);
		cout << str1 << endl;
		if (FileIn.eof())
		{
			break;
		}
		Sleep(10);
	}
	FileIn.close();
	textcolor(7);
	gotoXY(53, 18);
	cout << "Demo";
	gotoXY(47, 20);
	cout << " Nhap bieu thuc";
	gotoXY(47, 21);
	cout << "Bieu thuc co san";
	gotoXY(47, 22);
	cout << "      Back";
}
void menu2()
{
	box1();
	int j = 1;
	string str1;
	ifstream FileIn;
	FileIn.open("input1.txt", ios::in);
	while (true)
	{
		gotoXY(35, j++);
		SetColor(10 + rand() % +6);
		getline(FileIn, str1);
		cout << str1 << endl;
		if (FileIn.eof())
		{
			break;
		}
		Sleep(10);
	}
	FileIn.close();
	textcolor(7);
	gotoXY(48, 18);
	cout << "Nhap bieu thuc";
	gotoXY(49, 20);
	cout << "Tu ban phim";
	gotoXY(49, 21);
	cout << "  Tu FILE";
	gotoXY(49, 22);
	cout << "    Back";
}
void input2(int j,string str1,string str[100])
{
	if (GetAsyncKeyState(VK_UP))
	{
		if (pointer2 == 20)
		{
			pointer2 = 22;
		}
		else
			pointer2--;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (pointer2 == 22)
		{
			pointer2 = 20;
		}
		else
			pointer2++;
	}
	else if (GetAsyncKeyState(VK_RETURN))
	{
		system("cls");
		switch (pointer2)
		{
		case 20:
			cin.ignore();
			cin.ignore();
			cin.ignore();
			cout << "Bieu thuc:";
			getline(cin, str1);
			system("cls");
			tachchuoi(str, str1, j);
			kpbl(str, j, str1);
			break;
		case 22:
			z = 2;
			return;
		case 21:
			ifstream FileOut;
			FileOut.open("input.txt", ios::out | ios::trunc);
			FileOut.close();
			ShellExecute(NULL, "edit", "input.txt", NULL, NULL, SW_MAXIMIZE);
			cin.ignore();
			cin.ignore();
			if (GetAsyncKeyState(VK_RETURN))
			{
				system("pause");
			}
			system("cls");
			tachchuoi(str, docfile(), j);
			kpbl(str, j, str1);
			break;
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			system("cls");
			return ;
		}
	}
	gotoXY(49, pointer2);
	textcolor(2);
	switch (pointer2)
	{
	case 20:
		cout << "Tu ban phim";
		break;
	case 21:
		cout << "  Tu FILE";
		break;
	case 22:
		cout << "    Back";
		break;
	}
	textcolor(7);
}
void input1()
{
	int j = 0;
	string str1;
	string str[100];
	if (GetAsyncKeyState(VK_UP))
	{
		if (pointer1 == 20)
		{
			pointer1 = 22;
		}
		else
			pointer1--;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (pointer1 == 22)
		{
			pointer1 = 20;
		}
		else
			pointer1++;
	}
	else if (GetAsyncKeyState(VK_RETURN))
	{
		system("cls");
		switch (pointer1)
		{
		case 20:
			while (true)
			{
				menu2();
				input2(j,str1,str);
				if (z == 2)
				{
					z = 0;
					return;
				}
			}
			break;
		case 21:
			tachchuoi(str, docfile(), j);
			kpbl(str, j, str1);
			break;
		case 22:
			z = 1;
			return;
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			system("cls");
			return;
		}
	}
	gotoXY(47, pointer1);
	textcolor(2);
	switch (pointer1)
	{
	case 20:
		cout << " Nhap bieu thuc";
		break;
	case 21:
		cout << "Bieu thuc co san";
		break;
	case 22:
		cout << "      Back";
		break;
	}
	textcolor(7);
}
void run()
{

	system("cls");
	while (true)
	{
		menu1();
		input1();
		if (z == 1)
		{
			z = 0;
			system("cls");
			break;
		}
	}
}
void input()
{
	if (GetAsyncKeyState(VK_UP))
	{
		if (pointer == 20)
		{
			pointer = 23;
		}
		else
			pointer--;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (pointer == 23)
		{
			pointer = 20;
		}
		else
			pointer++;
	}
	else if (GetAsyncKeyState(VK_RETURN))
	{
		switch (pointer)
		{
		case 20:
			ShellExecute(NULL, "open", "lythuyet.txt", NULL, NULL, SW_MAXIMIZE);
			break;
		case 21:
			run();
			break;
		case 22:
			ShellExecute(NULL, "open", "Code.cpp", NULL, NULL, SW_MAXIMIZE);
			break;
		case 23:
			exit(0);
		}
		if (GetAsyncKeyState(VK_RETURN))
		{
			return;
		}
	}
	gotoXY(51, pointer);
	textcolor(2);
	switch (pointer)
	{
	case 20:
		cout << strMN[0];
		break;
	case 21:
		cout << strMN[1];
		break;
	case 22:
		cout << strMN[2];
		break;
	case 23:
		cout << strMN[3];
		break;
	}
	textcolor(7);
}
int main()
{
	srand(time(NULL));
	noCursorType();
	box();
	while (true)
	{
		menu();
		input();
	}
	system("pause");
	return 0;
}
