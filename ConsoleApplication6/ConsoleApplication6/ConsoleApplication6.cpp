// ConsoleApplication6.cpp: ���������� ����� ����� ��� ����������� ����������.
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
		arrNet[i] = arrIp[i] & arrMask[i]; //��������� � 
		arrHost[i] = arrIp[i] & ~arrMask[i];// ��������� ��������
	}
	return true;
}


string TransferDecimalToAny(long long int number, const unsigned int &base) //������� �����������
{
	const char *DIGITS = "0123456789abcdefghijklmnopqrstuvwxyz";
	bool FlagInverse = false;
	string reversString, stringInBase; //�������� ������ � ������ � ����

	if (base < 2 || base > 36)
	{
		std::cout << "Error: ��������� ������ ���� �� 2 �� 36." << std::endl;
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
	//����� ��� �������� ������ ������ 
	for (int i = 0, j = 0; ip_[i] != '\0'; i++, j++)
	{
		if (ip_[i] != '.') //���� �� ����� 
			buff[j] = ip_[i]; // �������� ������ � ����� 
		if (ip_[i] == '.' || ip_[i + 1] == '\0')
		{
			if (ip_[i + 1] == '\0')
			{
				buff[j] = ip_[i];
				buff[j + 1] = '\0';
			}
			else buff[j] = '\0';

			// ���� ��������� ����� ��� ��������� 
			cout << atoi(buff) << endl;
			if (atoi(buff) >= 255) return NULL;
			// ��� ����� ������ 255 � ������ 
			arr[s] = (int)atoi(buff);
			s++;
			//������������� � �������� � ����� IP-������ 
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
