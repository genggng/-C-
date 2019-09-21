#pragma once
#include<iostream>
#include"qmaker.h"
#include"player.h"
#include"file.h"

class Game
{
public:
	int Register(char* recvbuf,char* sendbuf); //ע��
	int Login(char* recvbuf, char* sendbuf);   //��¼
	void Getword(char* recvbuf, char* sendbuf);  //��õ���
	int OnlineGetWord(char* recvbuf, char* sendbuf);//˫�˶�ս��ȡ����
	int JudegeSuccess(char* SendBuf);
	int MakeQusetion(char* recvbuf, char* sendbuf); //����
	void UpdateUser(char* recvbuf, char* sendbuf);//�����û�
	int Query(char* recvbuf, char* sendbuf);   //��ѯ����
	void PutPlayer(vector<string>& ToClient, Player& player); //����������Ϣ����Ϊ�ַ���
	void PutQmaker(vector<string>& ToClient, Qmaker& qmaker);
	void GetPlayer(vector<string>& FromClient, Player& player);//���ַ�������Ϊ������
	void GetQmaker(vector<string>& FromClient, Qmaker& qmaker);
	bool GetJudegUser();
	void SetJudgeUse(bool judge);
	int GetID();
	void SetID(int id);
	vector<string> split(char* str);  //�ָ��ַ���
	void merge(vector<string>&ToClient,char* str);    //�ϲ��ַ���
private:
	bool JudgeUser;    //1��������ߣ�0��������
	int ID; //�����߻�����Ϸ��ҵ�ID

	int RadomWord(int chapter); //���ݹؿ����ѡ�񵥴�
	int ExpectWordLen(); //��������������ʳ���
	void LegalInput(int& ExpectInput, int down, int up);//���ֺϷ�������
	void LegalInput(bool& ExpectInput);

};

