#include "game.h"
#include"file.h"
#include"client.h"
#include<cstdlib>
#include<ctime>
#include<Windows.h>

extern  vector<Word> Vocabulary;
extern  vector<Player> PlayerList;
extern  vector<Qmaker> QmakerList;
extern int wordper[15];

int Game::Register()
{
	string name;
	string password1;
	string password2;
	Player player;
	Qmaker qmaker;
	vector<string>ToSever;
	vector<string>FromSever;
	char flag;     //'1'��ʾ�ɹ� '0'��ʾʧ��
	cout << "#######################################" << endl;
	if (JudgeUser)
	{
		cout << "           ע������ߣ�" << endl;
	}
	else
	{
		cout << "           ע�ᴳ�����ߣ�" << endl;
	}
	cout << endl;
	cout << "�û�����";
	cin >> name;
	cout << "���룺";
	cin >> password1;
	cout << "������һ�����룺";
	cin >> password2;
	while (password1 != password2)
	{
		cout << "�����������벻һ�£����������룺" << endl;
		cout << "���룺";
		cin >> password1;
		cout << "������һ�����룺";
		cin >> password2;
	}
	ToSever.push_back(name);
	ToSever.push_back(password1);
	if (JudgeUser)
	{
		flag = Request('c', ToSever, FromSever);
		cout << flag << endl;
		while (flag != '1')
		{
			cout << "�û����Ѵ��ڣ����������룡" << endl;
			cout << "�û����� ";
			cin >> name;
			ToSever[0] = name;
			flag = Request('c', ToSever, FromSever);
		}
	}
	else
	{
		flag = Request('a', ToSever, FromSever);
		while (flag != '1')
		{
			cout << "�û����Ѵ��ڣ����������룡" << endl;
			cout << "�û����� ";
			cin >> name;
			ToSever[0] = name;
			flag = Request('a', ToSever, FromSever);
		}
	}

	cout << "ע��ɹ���" << endl;
	Sleep(1000);
	return 0;

}

int Game::Login()
{
	string name;
	string password;
	vector<string>ToSever;
	vector<string>FromSever;
	char flag;
	cout << "#######################################" << endl;
	if (JudgeUser) {
		cout << "          �����ߵ�¼��" << endl<<endl;
		cout << "�������û�����";
		cin >> name;
		cout << "���������룺";
		cin >> password;

		ToSever.push_back(name);
		ToSever.push_back(password);
		flag = Request('d', ToSever, FromSever);
		while (flag != '1')
		{
			cout << "�û��������ڻ����������" << endl;
			cout << "�û����� ";
			cin >> name;
			cout << "���������룺";
			cin >> password;
			ToSever.clear();
			FromSever.clear();
			ToSever.push_back(name);
			ToSever.push_back(password);
			flag = Request('d', ToSever, FromSever);
		}
		GetQmaker(FromSever);//���ַ�������Ϊ������
	}
	else
	{
		cout << "             �����ߵ�¼��" << endl<<endl;
		cout << "�������û�����";
		cin >> name;
		cout << "���������룺";
		cin >> password;

		ToSever.push_back(name);
		ToSever.push_back(password);
		flag = Request('b', ToSever, FromSever);
		while (flag != '1')
		{
			cout << "�û��������ڻ����������" << endl;
			cout << "�û����� ";
			cin >> name;
			cout << "���������룺";
			cin >> password;
			ToSever.clear();
			FromSever.clear();
			ToSever.push_back(name);
			ToSever.push_back(password);
			flag = Request('b', ToSever, FromSever);
		}
		GetPlayer(FromSever);//���ַ�������Ϊ������
	}
	cout << endl;
	cout << "###��¼�ɹ���" << endl;
	Sleep(1000);
	if (JudgeUser)
	{
		MakeQusetion();
	}
	else
	{
		int PlayGo = 1;
		while (PlayGo)
		{
			PlaySelect(PlayGo);
		}
			

	}
	cout << "@@@�˳���¼������" << endl;
	Sleep(2000);
	
	return 0;
}

void Game::PlayGame()
{

	int chapter = player.GetChapter();
	int level = player.GetLevel();
	int exp = player.GetExp();
	string guessword;
	string answer;
	string Schapter;
	char cchapter[10];
	bool go = true;  //��ʾ������Ϸ
	vector<string>ToSever;
	vector<string>FromSever;
	char flag;

	cout << "��Ϸ��ʼ����" << endl;
	while (go)
	{
		system("cls");
		cout << "#######################################" << endl;
		cout << "�����ߣ�" << player.GetName() << "  " << "�ȼ���" << player.GetLevel() << "  " << "����ֵ��" << player.GetExp() << endl<<endl;
		cout << "��Ϸ��ʼ����" << endl;
		cout << "##########################" << endl;
		cout << "CHAPTER  " << chapter << " Good Luck!" << endl;
		cout << "##########################" << endl;
		cout << endl;
		ToSever.clear();
		FromSever.clear();
		ToSever.push_back(iTOa(chapter));
		flag = Request('e', ToSever, FromSever);
		if (flag == '1')
		{
			guessword = FromSever[0];
		}
		cout << "����5s��ʱ�����������ʣ� " << guessword << '\r';
		Sleep(5000);
		cout << "ʱ�䵽!                                                        " << endl;
		cout << "�������Ĵ𰸣� ";
		cin >> answer;
		if (answer == guessword)
		{
			cout << "��ϲ�㣬�����������������" << 10 * chapter << "�㾭��ֵ��" << endl;
			exp = exp + 10 * chapter;
			while (exp >= level * (level + 1) * (2 * level + 1) + 10 * level)
			{
				level++;
				cout << "��ϲ�㣬����������ﵽ�� lv" << level << endl;
			}
			chapter++;
			if (chapter == 11)
			{
				chapter = 10;
				cout << "̫�����ˣ����Ѿ�ͨ�������йؿ����������һ������ѡ�صĻ��ᣡ" << endl;
				cout << "��������Ҫѡ��Ĺؿ���";
				LegalInput(chapter, 1, 10);

			}
			cout << "$$������һ��������1��������������0 :";
			LegalInput(go);
		}
		else
		{
			cout << "���ź��������ˣ���ȷ���ǣ� " << guessword << endl;
			cout << "$$���¿�ʼ����������1����������������0��";
			LegalInput(go);
		}
		player.SetLevel(level);
		player.SetExp(exp);
		player.SetChapter(chapter);
	}
	ToSever.clear();
	FromSever.clear();
	PutPlayer(ToSever, player);
	flag = Request('k', ToSever, FromSever);
	if (flag == '0')
	{
		cout << "��������ʧ�ܣ�" << endl;
	}
}

int Game::PlaySelect(int &PlayGo)
{
	int select;
	system("cls");
	cout << "#######################################" << endl;
	cout << "��ѡ����Ϸģʽ��" << endl;
	cout << " 0.�˳�����" << endl;
	cout << " 1.����ģʽ" << endl;
	cout << " 2.˫��ƥ���սģʽ" << endl<<endl;
	cout << "����ѡ��";
	LegalInput(select,0, 2);//���ֺϷ�������
	switch (select)
	{
	case 0:
		PlayGo = 0;
		break;
	case 1:
		PlayGame();
		break;
	case 2:
		OnlinePlay();
		break;
	}
	return 0;
}

int Game::OnlinePlay()
{
	int chapter = player.GetChapter();
	int level = player.GetLevel();
	int exp = player.GetExp();
	string guessword;
	string answer;
	char cchapter[10];
	vector<string>ToSever;
	vector<string>FromSever;
	int AddExp; //���ӻ���ٵľ���
	char flag;
	system("cls");
	cout << "#######################################" << endl;
	cout << "�����ߣ�" << player.GetName() << "  " << "�ȼ���" << player.GetLevel() << "  " << "����ֵ��" << player.GetExp() << endl<<endl;
	cout << "��ӭ����˫�������ս������" << endl;
	cout << "����ƥ����ҡ�����������" << endl;
	ToSever.push_back(iTOa(chapter));
	flag = Request('m', ToSever, FromSever);
	if (flag == '1')
	{
		cout << "ƥ��ɹ�����" << endl;
		Sleep(1000);
		guessword = FromSever[0];
	}
	else
	{
		cout << "δƥ�䵽��ң�";
		Sleep(3000);
		return -1;
	}
	cout << "����5s��ʱ�����������ʣ� " << guessword << '\r';
	Sleep(5000);
	cout << "ʱ�䵽!                                                        " << endl;
	cout << "�������Ĵ𰸣� ";
	cin >> answer;
	if (answer == guessword)
	{

		ToSever.clear();
		FromSever.clear();
		flag = Request('n', ToSever, FromSever);
		if (flag == '1')
		{
			AddExp = 120;
			cout << "��ϲ�����ȴ�ԣ����120�㾭��ֵ������" << endl;
		}
		else
		{
			AddExp = 50;
			cout << "��ϲ�����ˣ���ϧ�Է����ָ�����~~���50�㾭��ֵ��" << endl;
		}

	}
	else
	{
		flag = Request('n', ToSever, FromSever);//ֻ�Ǹ��߷����������������
		AddExp = 0;
		cout << "���ϧѽ�������ˣ�ɶҲû���ţ���������" << endl;
		cout << "��ȷ���ǣ� " << guessword << endl;
	}
	exp = exp + AddExp;
	while (exp >= level * (level + 1) * (2 * level + 1) + 10 * level)
	{
		level++;
		cout << "��ϲ�㣬����������ﵽ�� lv" << level << endl;
	}



	player.SetLevel(level);
	player.SetExp(exp);
	player.SetChapter(chapter);
	ToSever.clear();
	FromSever.clear();
	PutPlayer(ToSever, player);
	flag = Request('k', ToSever, FromSever);
	if (flag == '0')
	{
		cout << "��������ʧ�ܣ�" << endl;
	}
	Sleep(3000);
}

void Game::MakeQusetion()
{
	string word; //��ӵĵ���
	int expectlen;
	struct Word Nword; //�µ���
	bool go = true; //�Ƿ����
	int qnumber = qmaker.GetQNumber(); //������
	int level = qmaker.GetLevel(); //�ȼ�
	vector<string>ToSever;
	vector<string>FromSever;
	char flag;


	while (go)
	{
		system("cls");
		cout << "#######################################" << endl;
		cout << "�����ߣ�" << qmaker.GetName() << "  " << "�ȼ���" << qmaker.GetLevel() << "  " << "��������" << qmaker.GetQNumber()<<endl<<endl;
		ToSever.clear();
		FromSever.clear();
		expectlen = ExpectWordLen();
		cout << "�ۣ������������������ " << expectlen << ",ֻ����ӳ���Ϊ " << expectlen << " �ĵ��ʣ��Żᱻ��¼�ɼ�Ӵ��"<<endl;
		cout << "����������Ҫ��ӵ��µ��ʣ�";
		cin >> word;
		while (word.size() != expectlen)
		{
			cout << "��������µ��ʳ��Ȳ��ԣ����ʧ�ܣ�" << endl;
			cout << "�����볤��Ϊ " << expectlen << " ���µ��ʣ�";
			cin >> word;

		}
		ToSever.push_back(word);
		flag = Request('f', ToSever, FromSever);
		if (flag == '0')
		{
			cout << "�õ����Ѵ��ڣ����ʧ�ܣ�����" << endl<<endl;
			cout << "�������������1���˳����������0��";
			LegalInput(go);
		}
		else
		{
			qnumber++;
			cout << "������ӳɹ������ۼ������" << qnumber << "�����ʣ�����" << endl;
			while (qnumber >= level * 5)
			{
				level++;
				cout << "��ϲ��������������ﵽ�� lv" << level << endl;
			}
			cout << endl;
			cout << "$$�������������1���˳����������0��";
			LegalInput(go);
		}
		qmaker.SetQNumber(qnumber); //���³�����
		qmaker.SetLevel(level);  //���µȼ�
	}


	ToSever.clear();
	FromSever.clear();
	PutQmaker(ToSever, qmaker);
	flag = Request('k', ToSever, FromSever);
	if (flag == '0')
	{
		cout << "��������ʧ�ܣ�" << endl;
	}
}

void Game::Query()
{
	int select; //������1��������2���������а�3���������а�4
	bool go = true;
	string name;
	Player playertemp;
	Qmaker qmakertemp;
	vector<string>ToSever;
	vector<string>FromSever;
	char flag;

	cout << "��ӭʹ�ò�ѯ���ܣ�" << endl;
	do
	{
		system("cls");
		cout << "#######################################" << endl;
		cout << "��ѯ�����빦����ţ� 1.������  2.������  3.�������а�  4.�������а�" << endl;
		cout << "��ѡ�񣺣�1-4��";
		LegalInput(select, 1, 4);
		switch (select)
		{
		case 1:
			cout << "������Ҫ��ѯ�Ĵ�����������";
			cin >> name;
			ToSever.clear();
			FromSever.clear();
			ToSever.push_back(name);
			flag = Request('g', ToSever, FromSever);
			if (flag == '0')
			{
				cout << "�ô����߲����ڣ�����" << endl;
			}
			else
			{
				GetPlayer(FromSever, playertemp);
				cout << "���ҵ���ش����ߣ�" << endl;
				cout << "$������" << playertemp.GetName() << endl;
				cout << "$�ȼ���" << playertemp.GetLevel() << endl;
				cout << "$���飺" << playertemp.GetExp() << endl;
				cout << "$��������" << playertemp.GetChapter() << endl << endl;
			}
			break;
		case 2:
			cout << "������Ҫ��ѯ�ĳ�����������";
			cin >> name;
			ToSever.clear();
			FromSever.clear();
			ToSever.push_back(name);
			flag = Request('h', ToSever, FromSever);
			if (flag == '0')
			{
				cout << "�ó����߲����ڣ�����" << endl;
			}
			else
			{
				GetQmaker(FromSever, qmakertemp);
				cout << "���ҵ���س����ߣ�" << endl;
				cout << "$������" << qmakertemp.GetName() << endl;
				cout << "$�ȼ���" << qmakertemp.GetLevel() << endl;
				cout << "$��������" << qmakertemp.GetQNumber() << endl << endl;
			}
			break;
		case 3:
			ToSever.clear();
			FromSever.clear();
			flag = Request('i', ToSever, FromSever);
			if (flag == '0')
			{
				cout << "��ȡ���а�����ʧ�ܣ�" << endl;
			}
			cout << "���������а�" << endl;
			cout << "###############################" << endl;
			cout << "����" << "\t����" << "\t�ȼ�" << "\t����" << "\t������" << endl;
			for (int i = 0; !FromSever.empty(); i++)
			{
				GetPlayer(FromSever, playertemp);
				cout << i + 1 << "\t" << playertemp.GetName() << "\t" << playertemp.GetLevel()
					<< "\t" << playertemp.GetExp() << "\t" << playertemp.GetChapter() << endl;
			}
			cout << "###############################" << endl;
			break;
		case 4:
			ToSever.clear();
			FromSever.clear();
			flag = Request('j', ToSever, FromSever);
			if (flag == '0')
			{
				cout << "��ȡ���а�����ʧ�ܣ�" << endl;
			}
			cout << "���������а�" << endl;
			cout << "###############################" << endl;
			cout << "����" << "\t����" << "\t�ȼ�" << "\t������" << endl;
			for (int i = 0; !FromSever.empty(); i++)
			{
				GetQmaker(FromSever, qmakertemp);
				cout << i + 1 << "\t" << qmakertemp.GetName() << "\t" << qmakertemp.GetLevel()
					<< "\t" << qmakertemp.GetQNumber() << endl;
			}
			cout << "###############################" << endl;
			break;
		}
		cout << "$$������ѯ������1���˳���ѯ������0��";
		LegalInput(go);
	} while (go);
}
void Game::PutPlayer(vector<string>& ToClient, Player& player)
{
	char level[10];
	char exp[10];
	char chapter[10];

	_itoa(player.GetLevel(), level, 10);
	_itoa(player.GetExp(), exp, 10);
	_itoa(player.GetChapter(), chapter, 10);

	string Slevel(level);
	string Sexp(exp);
	string Schapter(chapter);
	string name = player.GetName();

	ToClient.push_back(name);
	ToClient.push_back(Slevel);
	ToClient.push_back(Sexp);
	ToClient.push_back(Schapter);
}

void Game::PutQmaker(vector<string>& ToClient, Qmaker& qmaker)
{
	char level[10];
	char qnumber[10];

	_itoa(qmaker.GetLevel(), level, 10);
	_itoa(qmaker.GetQNumber(), qnumber, 10);


	string Slevel(level);
	string Sqnumber(qnumber);
	string name = qmaker.GetName();

	ToClient.push_back(name);
	ToClient.push_back(Slevel);
	ToClient.push_back(Sqnumber);

}

void Game::GetPlayer(vector<string>& ToClient)
{
	string name;
	int level;
	int exp;
	int chapter;

	name = ToClient[0];
	level = atoi(ToClient[1].c_str());
	exp = atoi(ToClient[2].c_str());
	chapter = atoi(ToClient[3].c_str());

	player.SetName(name);
	player.SetLevel(level);
	player.SetExp(exp);
	player.SetChapter(chapter);


}

void Game::GetQmaker(vector<string>& ToClient)
{
	string name;
	int level;
	int qnumber;

	name = ToClient[0];
	level = atoi(ToClient[1].c_str());
	qnumber = atoi(ToClient[2].c_str());

	qmaker.SetName(name);
	qmaker.SetLevel(level);
	qmaker.SetQNumber(qnumber);

}

void Game::GetPlayer(vector<string>& FromClient, Player& temp)
{
	string name;
	int level;
	int exp;
	int chapter;

	name = FromClient[0];
	level = atoi(FromClient[1].c_str());
	exp = atoi(FromClient[2].c_str());
	chapter = atoi(FromClient[3].c_str());

	temp.SetName(name);
	temp.SetLevel(level);
	temp.SetExp(exp);
	temp.SetChapter(chapter);


	FromClient.erase(FromClient.begin(), FromClient.begin() + 4);
}

void Game::GetQmaker(vector<string> & FromClient, Qmaker & temp)
{
	string name;
	int level;
	int qnumber;

	name = FromClient[0];
	level = atoi(FromClient[1].c_str());
	qnumber = atoi(FromClient[2].c_str());

	temp.SetName(name);
	temp.SetLevel(level);
	temp.SetQNumber(qnumber);

	FromClient.erase(FromClient.begin(), FromClient.begin() + 3);
}

string Game::iTOa(int x)
{
	char str[10];
	itoa(x, str, 10);
	string ret(str);
	return ret;
}

bool Game::GetJudegUser()
{
	return JudgeUser;
}
void Game::SetJudgeUser(bool judge)
{
	JudgeUser = judge;
}
void Game::SetSocket(SOCKET socket)
{
	SocketClient = socket;
}
SOCKET Game::GetSocket()
{
	return SocketClient;
}
vector<string> Game::split(char* str)
{
	vector<string> res;
	char* temp = strtok(str, "#");
	while (temp != NULL)
	{
		res.push_back(string(temp));
		temp = strtok(NULL, "#");
	}
	return res;
}

void Game::merge(vector<string> & ToClient, char* str)
{
	string sstr;
	for (auto p = ToClient.begin(); p != ToClient.end(); p++)
	{
		sstr += *p;
		if (p < ToClient.end() - 1)
		{
			sstr.push_back('#');
		}
	}
	strcpy(str, sstr.c_str());
}

int Game::RadomWord(int chapter)
{
	srand(int(time(0)));
	int random;//1-1000���������
	int ret; //���Ѷ������ڵ�һ�������
	int len = Vocabulary.size() / 10; //�ʻ���һ���Ѷ����䳤�� ��10���Ѷ�

	random = rand() % 1000 + 1;
	ret = random * len / 1000;
	return ret + (chapter - 1) * len;  //��������ĵ������
}

int Game::ExpectWordLen()
{
	srand(int(time(0)));
	int random;//1-1000���������

	random = rand() % 1000 + 1;
	for (int i = 1; i < 15; i++)
	{
		if (random > wordper[i - 1] && random <= wordper[i])
			return i; //���������ĵ��ʳ���
	}
}
void Game::LegalInput(int& ExpectInput, int down, int up)
{
	int number;

	while (!(cin >> number) || number < down || number>up)
	{
		cout << "�Ƿ����룡" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "���������룺��" << down << "-" << up << ")" << endl;
	}
	ExpectInput = number;
}
void Game::LegalInput(bool& ExpectInput)
{
	int flag;
	while (!(cin >> flag) || (flag != 0 && flag != 1))
	{
		cout << "�Ƿ����룡" << endl;
		cin.clear();
		cin.ignore(1024, '\n');
		cout << "���������룺�� 0 ���� 1)" << endl;
	}
	ExpectInput = flag;
}

char Game::Request(char flag, vector<string> & ToSever, vector<string> & FromSever)
{
	char SendBuff[MaxBufSize], RecvBuff[MaxBufSize];
	int sflag, rflag;

	SendBuff[0] = flag;

	merge(ToSever, &SendBuff[1]);
	sflag = send(SocketClient, SendBuff, sizeof(SendBuff), 0);
	if (sflag < 0)
	{
		cout << "����ʧ��" << endl;
	}
	rflag = recv(SocketClient, RecvBuff, sizeof(RecvBuff), 0);
	if (rflag < 0)
	{
		cout << "������������쳣��" << endl;
	}
//	cout << "���յ����Է���������Ϣ�ǣ�" << RecvBuff << endl;
	FromSever = split(&RecvBuff[1]);
	return RecvBuff[0];

}