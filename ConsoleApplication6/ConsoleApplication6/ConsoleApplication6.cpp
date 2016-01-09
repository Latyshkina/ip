// ConsoleApplication6.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
using namespace std;


int * ActetIp = new int[4];
int * ActetMask = new int[4];
int * ActetSubmet = new int[4];
int * ActetHost = new int[4];



bool Calculator(int * arrIp, int * arrMask, int * arrNet, int * arrHost)
{
	for (int i = 0; i < 4; i++)
	{
		arrNet[i] = arrIp[i] & arrMask[i]; //побитовое и 
		arrHost[i] = arrIp[i] & ~arrMask[i];// побитовая инверсия
	}
	return true;
}


string TransferDecimalToAny(long long int number, const unsigned int &base) //перевод десятичного
{
	const char *DIGITS = "0123456789abcdefghijklmnopqrstuvwxyz";
	bool FlagInverse = false;
	string reversString, stringInBase; //обратная строка и строка в базе

	if (base < 2 || base > 36)
	{
		std::cout << "Error: основание должно быть от 2 до 36." << std::endl;
		return "-1";
	}
	if (number < 0)
	{
		FlagInverse = true;
		number *= -1;
	}

	stringInBase += DIGITS[number % base];
	number = number / base;
	while (number)
	{
		stringInBase += DIGITS[number % base];
		number = number / base;
	}

	if (FlagInverse == true)
		reversString = "-";

	for (int i = stringInBase.length() - 1; i >= 0; i--)
		reversString += stringInBase[i];

	return reversString;
}

bool CheckMask(int * arr)
{
	bool flag = false;
	for (int i = 0; i < 4; i++)
	{
		string str = TransferDecimalToAny(arr[i], 2);
		for (int x = 0; str[x] != '\0'; x++)
		{
			if (str[x] == '0')
			{
				flag = true;
			}
			if (str[x] == '1' && flag)
			{
				return false;
			}
		}
	}
	return true;
}


bool CharToULong(char* ip_, int *arr)
{
	char *buff;
	buff = new char[3];
	int s = 0;
	//буфер для хранения одного октета 
	for (int i = 0, j = 0; ip_[i] != '\0'; i++, j++)
	{
		if (ip_[i] != '.') //если не точка 
			buff[j] = ip_[i]; // записать символ в буфер 
		if (ip_[i] == '.' || ip_[i + 1] == '\0')
		{
			if (ip_[i + 1] == '\0')
			{
				buff[j] = ip_[i];
				buff[j + 1] = '\0';
			}
			else buff[j] = '\0';

			// если следующий октет или последний 
			cout << atoi(buff) << endl;
			if (atoi(buff) >= 255) return NULL;
			// ели октет больше 255 – ошибка 
			arr[s] = (int)atoi(buff);
			s++;
			//преобразовать и добавить к числу IP-адреса 
			j = -1;
		};
	}
	return true;
}



void main()
{
	char * myip = new char[255];
	char * mymask = new char[255];
	cout << "IP > ";
	(cin >> myip).get();
	//	cout << endl;
	cout << "MASK > ";
	(cin >> mymask).get();
	cout << endl;
	if (!CharToULong(myip, ActetIp))
	{
		cout << "Error IP" << endl;
		return;
	}
	if (!CharToULong(mymask, ActetMask))
	{
		cout << "Error MASK" << endl;
		return;
	}
	if (!CheckMask(ActetMask))
	{
		cout << "Error mask" << endl;
		return;
	}
	Calculator(ActetIp, ActetMask, ActetSubmet, ActetHost);
	cout << "NETWORK ID ";
	for (int i = 0; i < 4; i++)
		cout << ActetSubmet[i] << ".";
	cout << endl;
	cout << "HOST ID ";
	for (int i = 0; i < 4; i++)
		cout << ActetHost[i] << ".";
	cout << endl;
	system("pause");
}
