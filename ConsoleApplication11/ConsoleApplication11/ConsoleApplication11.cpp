// ConsoleApplication11.cpp: ���������� ����� ����� ��� ����������� ����������.
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
	cout << setiosflags(ios::left) << setw(20) << "�����:";
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
			cout << "����������� ������� �����\n";
		}
	}
	else
	{
		cout << "����������� ������ IP\n";
	}
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------
bool CheckAddress(char* ip_)//�������� ��������� ������� 0..255
{
	int points = 0,//���������� �����
		numbers = 0;//�������� ������ (����� �������� � 10 �/�)
	char* buff;//���������� ������ ������ (�����)
	buff = new char[3];//�������� ������ ������ ��� 3 �������

	for (int i = 0; ip_[i] != '\0'; i++)//��� ����� IP �������
	{
		if (ip_[i] <= '9' && ip_[i] >= '0')//���� ��������������� ������ - �����
		{
			if (numbers > 3)	return false;//���� ������ ������ 3 ����, �� ������
			buff[numbers++] = ip_[i];//������� ������ � ����� ������
		}
		else if (ip_[i] == '.')//���� ��������������� ������ - �����
		{
			if (atoi(buff) > 255)	return false;//����������� ����� � ����� ���� int � ���� ��� ������ 255, �� ������
			if (numbers == 0)	return false;//���� ���� ��� ����� ������ (����� ���), �� ������
			numbers = 0;//����� ����� ���������� ����� �����, ������� �������� ������� ����
			points++;//����������� ������� �����
			delete buff;//������� � ������� ������, ��� �� �������� ��������� � ������ ����������
			buff = new char[3];
		}
		else return false;//���� ��������������� ������ - �� ����� � �� �����, �� ������
	}

	if (points != 3) return false;//���� � IP ����� ����� ������ 3, �� ������
	return true;//���� IP ������������� ���� ��������, �� ���������� true
}
//----------------------------------------------------------------------------------------------------------------------------------------
unsigned long long CharToULong(char* ip_)//���������� IP � unsigned long long � ��� �����
{
	unsigned long long out = 0;//����� ��� IP-������
	char* buff;//���������� ������ ������ (�����)
	buff = new char[3];//�������� ������ ������ ��� 3 �������

	for (int i = 0, j = 0; ip_[i] != '\0'; i++, j++)//�������� �� ����� IP, i-������ ������� � ������ �������� IP, j-������ ������� � ������ ������
	{
		if (ip_[i] != '.')//���� �� �����
		{
			buff[j] = ip_[i];//���������� ������ � ����� ������
		}
		if (ip_[i] == '.' || ip_[i + 1] == '\0')//���� ����� ����� ��� ���� ��� ���������� ������� ��� (����� ������)
		{
			out = out * 1000;//�������� �� ����� ������� � ��� ��� �������� � out
			//�� 8 �������� �����, ��� �� � ����� �������� ���������� �������� ������
			out += (unsigned long long)atoi(buff);//���������� � ����� ���������� out ���������� ������

			delete buff;//������� � ������� ������, ��� �� �������� ��������� � ������ ����������
			buff = new char[3];
			j = -1;//�� ��������� ���� ����� j ����� ����� 0 � ������ � ����� ������ �������� �������
		}
	}

	return out;
}

//----------------------------------------------------------------------------------------------------------------------------------------
bool CheckMask(char* mask_)//�������� ��������� ������� 0..255
{
	bool zero = false;//���� ��� ����������� ���������� ������������������ ������
	int points = 0,//���������� �����
		oct,//����� ������������ � ������ ����� ��������� ����
		broadscast = 0,//������� ������� ������� ������� �� 255
		numbers = 0;//�������� ������ (����� �������� � 10 �/�)
	char* buff;//���������� ������ ������ (�����)
	buff = new char[3];//�������� ������ ������ ��� 3 �������

	for (int i = 0; mask_[i] != '\0'; i++)//��� ���� ����� �������
	{
		if ((mask_[i] <= '9' && mask_[i] >= '0') && (mask_[i + 1] != '\0'))//���� ��������������� ������ - �����
		{
			if (numbers > 3)	return false;//���� ������ ������ 3 ����, �� ������
			buff[numbers++] = mask_[i];//������� ������ � ����� ������
		}
		else if ((mask_[i] == '.') || (mask_[i + 1] == '\0'))//���� ��������������� ������ - �����, ��� ��� ����� ������
		{
			if (mask_[i + 1] == '\0')//��� ���������� ������ ������� ��������
			{
				if (numbers > 3)	return false;//���� ������ ������ 3 ����, �� ������
				buff[numbers++] = mask_[i];//������� ������ � ����� ������
			}
			oct = atoi(buff);//����� � ������ ����������� � int
			//�������� �� �� ��� ����� ����������
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

			delete buff;//������� � ������� ������, ��� �� �������� ��������� � ������ ����������
			buff = new char[3];
			numbers = 0;//����� ����� ���������� ����� �����, ������� �������� ������� ����
			points++;//����������� ������� �����
			if (mask_[i + 1] == '\0')//���� ��� ��� ��������� �����
			{
				points--;//��������� ������� �����
			}
		}
		else return false;//���� ��������������� ������ - �� ����� � �� �����, �� ������
	}

	if (broadscast == 4)//���� ��� ����� ����� - �������
	{
		return false;
	}
	if (points != 3) return false;//���� � ����� ����� ����� ������ 3, �� ������
	return true;//���� ����� ������������� ���� ��������, �� ���������� true
}
//----------------------------------------------------------------------------------------------------------------------------------------
void ULongToChar(unsigned long long n, unsigned long long m)//������� � ����� �� ����� Network ID � HOST ID
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

	cout << setiosflags(ios::left) << setw(20) << "ID �������:";
	cout << oneS << "." << twoS << "." << threeS << "." << fourS << endl;
	cout << setiosflags(ios::left) << setw(20) << "ID �����:";
	cout << oneH << "." << twoH << "." << threeH << "." << fourH << endl;

	system("pause");
}