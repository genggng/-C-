#pragma once
#include"user.h"

class  Player : public User //������
{
private:
	int Exp;    //����ֵ
	int Chapter;  //��Ϸ�ؿ�

public:
	void SetChapter(int chapter );
	int GetChapter();
	void SetExp(int exp);
	int GetExp();
	Player(int exp = 0, int chapter = 1);

};