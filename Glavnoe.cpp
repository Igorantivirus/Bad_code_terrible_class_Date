#include<windows.h>
#include<iostream>
#include"TimeIgor.h"
using namespace std;
using namespace timeIgor;
int main() {
	setlocale(LC_ALL, "rus");
	Time t1 = 20, t2 = 25;//������ ��� �������, �������������� (�������� ��� �� TimeIgor.h)
	cout << t2 - t1 << endl;//����� 00:00:05, ��� �����, ���� �� 25 ������ ������� 20 - ����� 5 ������!
	Date d1 = 20, d2 = 25;//������ �� �� �� ����� ��� Date (��� � TimeIgor.h ��� �� ����������� ���������)
	cout << d2 - d1 << endl;//�� ��� ������ �� ���� ��������� �����! (� ��� ������ ������ ������� -20:03:2351845)
}
