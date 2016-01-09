// ConsoleApplication11.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;

bool CheckAddress(char* ip_);
bool CheckMask(char* mask_);
unsigned long long CharToULong(char* ip_);
void ULongToChar(unsigned long long  n, unsigned  long long m);

int main()
{
	setlocale(0, "");

	unsigned long long ip, mask;
	char *cIP, *cMask;

	cIP = new char[16];
	cMask = new char[16];

	cout << setiosflags(ios::left) << setw(20) << "IP:";
	cin >> cIP;
	cout << setiosflags(ios::left) << setw(20) << "Маска:";
	cin >> cMask;

	if (CheckAddress(cIP))
	{
		ip = CharToULong(cIP);
	//	cout << ip << endl;
		if (CheckMask(cMask))
		{
			mask = CharToULong(cMask);
		//	cout << mask << endl;

			ULongToChar(ip, mask);
		}
		else
		{
			cout << "Неправильно введена маска\n";
		}
	}
	else
	{
		cout << "Неправильно введен IP\n";
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------
bool CheckAddress(char* ip_)//Проверка диапазона октетов 0..255
{
	int points = 0,//Количество точек
		numbers = 0;//значение октета (число символов в 10 с/с)
	char* buff;//содержимое одного октета (буфер)
	buff = new char[3];//Выделяем память только под 3 символа

	for (int i = 0; ip_[i] != '\0'; i++)//Для всего IP целиком
	{
		if (ip_[i] <= '9' && ip_[i] >= '0')//Если рассматриваемый символ - цифра
		{
			if (numbers > 3)	return false;//если подряд больше 3 цифр, то ошибка
			buff[numbers++] = ip_[i];//занести символ в буфер октета
		}
		else if (ip_[i] == '.')//Если рассматриваемый символ - точка
		{
			if (atoi(buff) > 255)	return false;//Преобразуем буфер в число типа int и если оно больше 255, то ошибка
			if (numbers == 0)	return false;//Если идут две точки подряд (числа нет), то ошибка
			numbers = 0;//После точки начинается новый октет, поэтому обнуляем счетчик цифр
			points++;//Увеличиваем счетчик точек
			delete buff;//Удаляем и создаем заново, что бы очистить имеющуюся в буфере информацию
			buff = new char[3];
		}
		else return false;//Если рассматриваемый символ - не цифра и не точка, то ошибка
	}

	if (points != 3) return false;//Если в IP число точек больше 3, то ошибка
	return true;//Если IP удовлетворяет всем условиям, то возвращаем true
}
//----------------------------------------------------------------------------------------------------------------------------------------
unsigned long long CharToULong(char* ip_)//Возвращает IP в unsigned long long и без точек
{
	unsigned long long out = 0;//Число для IP-адреса
	char* buff;//содержимое одного октета (буфер)
	buff = new char[3];//Выделяем память только под 3 символа

	for (int i = 0, j = 0; ip_[i] != '\0'; i++, j++)//Проходим по всему IP, i-индекс символа в строке хранящей IP, j-индекс символа в буфере октета
	{
		if (ip_[i] != '.')//если не точка
		{
			buff[j] = ip_[i];//записываем символ в буфер октета
		}
		if (ip_[i] == '.' || ip_[i + 1] == '\0')//Если стоит точка или если это следующего символа нет (конец строки)
		{
			out = out * 1000;//Сдвигаем то число которое у нас уже записано в out
			//на 8 символов влево, что бы в конец записать содержимое текущего октета
			out += (unsigned long long)atoi(buff);//записываем в конец переменной out содержимое октета

			delete buff;//Удаляем и создаем заново, что бы очистить имеющуюся в буфере информацию
			buff = new char[3];
			j = -1;//на следующем шаге цикла j будет равно 0 и запись в буфер октета начнется сначала
		}
	}

	return out;
}

//----------------------------------------------------------------------------------------------------------------------------------------
bool CheckMask(char* mask_)//Проверка диапазона октетов 0..255
{
	bool zero = false;//флаг для обнаружения прерывания последовательности единиц
	int points = 0,//Количество точек
		oct,//число содержащееся в буфере будет заносится сюда
		broadscast = 0,//считаем сколько октетов состоит из 255
		numbers = 0;//значение октета (число символов в 10 с/с)
	char* buff;//содержимое одного октета (буфер)
	buff = new char[3];//Выделяем память только под 3 символа

	for (int i = 0; mask_[i] != '\0'; i++)//Для всей маски целиком
	{
		if ((mask_[i] <= '9' && mask_[i] >= '0') && (mask_[i + 1] != '\0'))//Если рассматриваемый символ - цифра
		{
			if (numbers > 3)	return false;//если подряд больше 3 цифр, то ошибка
			buff[numbers++] = mask_[i];//занести символ в буфер октета
		}
		else if ((mask_[i] == '.') || (mask_[i + 1] == '\0'))//Если рассматриваемый символ - точка, или это конец строки
		{
			if (mask_[i + 1] == '\0')//для последнего октета заносим отдельно
			{
				if (numbers > 3)	return false;//если подряд больше 3 цифр, то ошибка
				buff[numbers++] = mask_[i];//занести символ в буфер октета
			}
			oct = atoi(buff);//число в буфере преобразуем в int
			//проверим на то что маска правильная
			switch (oct)
			{
			case 0:
				zero = true;
				break;
			case 128:
				if (zero == false)
				{
					zero = true;
				}
				else
				{
					return false;
				}
				break;
			case 192:
				if (zero == false)
				{
					zero = true;
				}
				else
				{
					return false;
				}
				break;
			case 224:
				if (zero == false)
				{
					zero = true;
				}
				else
				{
					return false;
				}
				break;
			case 240:
				if (zero == false)
				{
					zero = true;
				}
				else
				{
					return false;
				}
				break;
			case 248:
				if (zero == false)
				{
					zero = true;
				}
				else
				{
					return false;
				}
				break;
			case 252:
				if (zero == false)
				{
					zero = true;
				}
				else
				{
					return false;
				}
				break;
			case 254:
				if (zero == false)
				{
					zero = true;
				}
				else
				{
					return false;
				}
				break;
			case 255:
				if (zero == false)
				{
					broadscast++;
				}
				else
				{
					return false;
				}
				break;
			default:
				return false;
			}

			delete buff;//Удаляем и создаем заново, что бы очистить имеющуюся в буфере информацию
			buff = new char[3];
			numbers = 0;//После точки начинается новый октет, поэтому обнуляем счетчик цифр
			points++;//Увеличиваем счетчик точек
			if (mask_[i + 1] == '\0')//если это был последний октет
			{
				points--;//Уменьшаем счетчик точек
			}
		}
		else return false;//Если рассматриваемый символ - не цифра и не точка, то ошибка
	}

	if (broadscast == 4)//если все цифры маски - единицы
	{
		return false;
	}
	if (points != 3) return false;//Если в маске число точек больше 3, то ошибка
	return true;//Если маска удовлетворяет всем условиям, то возвращаем true
}
//----------------------------------------------------------------------------------------------------------------------------------------
void ULongToChar(unsigned long long n, unsigned long long m)//Подсчет и вывод на экран Network ID и HOST ID
{
	int oneN = n / 1000000000;
	int twoN = (n / 1000000) - (oneN * 1000);
	int threeN = (n / 1000) - (oneN * 1000000) - (twoN * 1000);
	int fourN = n - (oneN * 1000000000) - (twoN * 1000000) - (threeN * 1000);

	int oneM = m / 1000000000;
	int twoM = (m / 1000000) - (oneM * 1000);
	int threeM = (m / 1000) - (oneM * 1000000) - (twoM * 1000);
	int fourM = m - (oneM * 1000000000) - (twoM * 1000000) - (threeM * 1000);

	int oneS = oneN & oneM;
	int twoS = twoN & twoM;
	int threeS = threeN & threeM;
	int fourS = fourN & fourM;

	int oneH = oneN & ~oneM;
	int twoH = twoN & ~twoM;
	int threeH = threeN & ~threeM;
	int fourH = fourN & ~fourM;

	cout << setiosflags(ios::left) << setw(20) << "ID подсети:";
	cout << oneS << "." << twoS << "." << threeS << "." << fourS << endl;
	cout << setiosflags(ios::left) << setw(20) << "ID хоста:";
	cout << oneH << "." << twoH << "." << threeH << "." << fourH << endl;

	system("pause");
}