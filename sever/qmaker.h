#pragma once
#include"user.h"

class Qmaker : public User //������
{
private:
	int QNumber; //������

public:
	void SetQNumber(int qnumber);
	int GetQNumber();
	Qmaker(int qnumber=0);
};

