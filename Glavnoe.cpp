#include<windows.h>
#include<iostream>
#include"TimeIgor.h"
using namespace std;
using namespace timeIgor;
int main() {
	setlocale(LC_ALL, "rus");
	Time t1 = 20, t2 = 25;//создаём два объекта, инициализируем (смотрите код из TimeIgor.h)
	cout << t2 - t1 << endl;//вывод 00:00:05, что верно, ведь из 25 секунд вычесть 20 - будет 5 секунд!
	Date d1 = 20, d2 = 25;//делаем всё то же самое для Date (код в TimeIgor.h так же практически идентичен)
	cout << d2 - d1 << endl;//но при выводе он берёт рандомное число! (в моём случае всегда выводит -20:03:2351845)
}
