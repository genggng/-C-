#pragma once
#include<string>
#include<vector>
#include<algorithm>
#include<stdlib.h>
#include<cstring>
#include"player.h"
#include"qmaker.h"
using namespace std;

struct Word
{
	string info;
	int len;
};
struct DEBUG
{
	int wordlen[15];  //1-14���ȵ��ʵĸ���
	int wordper[15]; //1-14���ʳ��ȵ�����ռ����
};


void GetVacabulary();
void UpdateVacabulary();
void GetPlayerList();
void UpdatePlayerList();
void GetQmakerList();
void UpdateQmakerList();
bool operator ==(const struct Word& word1,const string& word2);
bool compword(const Word& a, const Word& b);
bool compplayer(Player& a, Player& b);
bool compqmaker(Qmaker& a, Qmaker& b);
