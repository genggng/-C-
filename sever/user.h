#pragma once
#include<string>
using namespace std;

class User     // �û�
{
protected:
	string Name;    //�û���
	string PassWord; //����
	int Level; //�ȼ�

public:
	void SetName(string name);
	void SetPassWord(string password);
	void SetLevel(int level);
	int GetLevel();
	string GetName();
	string GetPassWord();
	bool operator ==(const string& name);
	User(int level = 1);

};
