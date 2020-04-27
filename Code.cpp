#include<iostream>
#include<fstream>
#include<string>
using namespace std;
struct NODE
{
	string data;
	NODE *pNext;
};
struct STACK
{
	NODE  *pTop;
};
struct QUEUE
{
	NODE  *pTop;
};
NODE* InitNode(string x)
{
	NODE *p = new NODE;
	p->data = x;
	p->pNext = NULL;
	return p;
}
void PushS(STACK &s, NODE *p)
{
	if (s.pTop == NULL)
	{
		s.pTop = p;
	}
	else
	{
		p->pNext = s.pTop;
		s.pTop = p;
	}
}
void PopS(STACK &s, string &x)
{
	if (s.pTop != NULL)
	{
		x = s.pTop->data;
		NODE *p = s.pTop;
		s.pTop = s.pTop->pNext;
		delete p;
	}
}
void TopS(STACK s, string &x)
{
	if (s.pTop != NULL)
	{
		x = s.pTop->data;;
	}
}
void PushQ(QUEUE &q, NODE *p)
{
	if (q.pTop == NULL)
	{
		q.pTop = p;
	}
	else
	{
		for (NODE *k = q.pTop; k != NULL; k = k->pNext)
		{
			if (k->pNext == NULL)
			{
				k->pNext = p;
				break;
			}
		}
	}
}
void PopQ(QUEUE &q, string &x)
{
	if (q.pTop != NULL)
	{
		x = q.pTop->data;
		NODE *p = q.pTop;
		q.pTop = q.pTop->pNext;
		delete p;
	}
}
void TopQ(QUEUE q, string &x)
{
	if (q.pTop != NULL)
	{
		x = q.pTop->data;
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
	bool kt = false; //ki?m tra ph?i toán h?ng hay không
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
	if (str == "+" && str1 == "-" || str == "-"&&str1 == "+" || str == "*"&&str1 == "/" || str == "/"&&str1 == "*"
		|| str == "*"&&str1 == "+" || str == "*"&&str1 == "-" || str == "/"&&str1 == "+" || str == "/"&&str1 == "-"
		|| str == "+"&&str1 == "+" || str == "-"&&str1 == "-" || str == "*"&&str1 == "*" || str == "/"&&str1 == "/")
		return true;// Ð? uu tiên l?n hon ho?c b?ng
	else
		return false;// Ð? uu tiên nh? hon
}
int main()
{
	STACK s;
	QUEUE q;
	s.pTop = NULL;
	q.pTop = NULL;
	int x, a, b;
	int j = 0; //s? lu?ng ph?n t? c?a bi?u th?c d? bài
	string str[100], str1, strtam;
	tachchuoi(str, docfile(), j);

	//Bu?c 1:
	for (int i = 0; i < j; i++)
	{
		if (str[i] == "(")
		{
			NODE *p = InitNode(str[i]);
			PushS(s, p);
		}
		else if (str[i] == ")")
		{
			while (true)
			{
				PopS(s, str1);
				if (str1 == "(")
				{
					break;
				}
				NODE *p = InitNode(str1);
				PushQ(q, p);
			}
		}
		else if (str[i] == "+" || str[i] == "-" || str[i] == "*" || str[i] == "/")
		{
			if (s.pTop == NULL)
			{
				NODE *p = InitNode(str[i]);
				PushS(s, p);
			}
			else
			{
				while (true)
				{
					TopS(s, str1);
					if (str1 == "(" || s.pTop == NULL || sosanh(str1, str[i]) == false)
					{
						NODE *p = InitNode(str[i]);
						PushS(s, p);
						break;
					}
					else if (sosanh(str1, str[i]) == true)
					{
						PopS(s, str1);
						NODE *p = InitNode(str1);
						PushQ(q, p);
					}
				}
			}
		}
		else
		{
			NODE *p = InitNode(str[i]);
			PushQ(q, p);
		}
	}

	//Bu?c 2:
	while (s.pTop != NULL)
	{
		PopS(s, str1);
		NODE *p = InitNode(str1);
		PushQ(q, p);
	}

	//Bu?c 3:
	while (q.pTop != NULL)
	{
		PopQ(q, str1);
		if (str1 == "+" || str1 == "-" || str1 == "*" || str1 == "/")
		{
			PopS(s, strtam);
			a = atoi(strtam.c_str());
			PopS(s, strtam);
			b = atoi(strtam.c_str());
			if (str1 == "+")
			{
				x = b + a;
			}
			else if (str1 == "-")
			{
				x = b - a;
			}
			else if (str1 == "*")
			{
				x = b * a;
			}
			else
			{
				x = b / a;
			}
			NODE *p = InitNode(to_string(x));
			PushS(s, p);
		}
		else
		{
			NODE *p = InitNode(str1);
			PushS(s, p);
		}
	}

	//K?t qu?
	cout << x << endl;
	system("pause");
		
	return 0;
}

