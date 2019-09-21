#pragma once
#include<iostream>
#include"qmaker.h"
#include"player.h"
#include"file.h"
#include<WinSock2.h>

class Game
{
public:
	int Register(); //ע��
	int Login();   //��¼
	void PlayGame();  //����Ϸ
	int PlaySelect(int &PlayGo);//ѡ�񵥻����Ƕ�ս
	int OnlinePlay();//������ս
	void MakeQusetion(); //����
	void Query();   //��ѯ����
	void PutPlayer(vector<string>& ToClient, Player& player); //����������Ϣ����Ϊ�ַ���
	void PutQmaker(vector<string>& ToClient, Qmaker& qmaker);
	void GetPlayer(vector<string>& FromClient);//���ַ�������Ϊ������
	void GetQmaker(vector<string>& FromClient);
	void GetPlayer(vector<string>& FromClient,Player &temp);//���ַ�������Ϊ������
	void GetQmaker(vector<string>& FromClient,Qmaker &temp);
	string iTOa(int x); //����ת��Ϊstring��
	bool GetJudegUser();
	void SetJudgeUser(bool judge);
	void SetSocket(SOCKET socket);
	SOCKET GetSocket();
	vector<string> split(char* str);  //�ָ��ַ���
	void merge(vector<string>& ToClient, char* str);    //�ϲ��ַ���
	char Request(char flag, vector<string>&ToSever, vector<string>&FromSever);  //�ͻ�������
	void LegalInput(int& ExpectInput, int down, int up);//���ֺϷ�������
	void LegalInput(bool& ExpectInput);
private:
	bool JudgeUser;    //1��������ߣ�0��������
	Player player;
	Qmaker qmaker;
	int RadomWord(int chapter); //���ݹؿ����ѡ�񵥴�
	int ExpectWordLen(); //��������������ʳ���
	SOCKET SocketClient;


};

