#include"sever.h"
#include"file.h"
#include"game.h"

using namespace std;
const int PORT = 8000;
int ClientNumber = 0;    //��Ϸ�����
int Finish = 0;        //һ������Ѿ����
string OnlineWord;   //������Ϸ����
extern  vector<Word> Vocabulary;
extern  vector<Player> PlayerList;
extern  vector<Qmaker> QmakerList;

//�����߳�
DWORD WINAPI ServerThread(LPVOID lpParameter) {
	SOCKET* ClientSocket = (SOCKET*)lpParameter;
	int receByt = 0;
	char RecvBuf[MaxBufSize];
	char SendBuf[MaxBufSize];
	Game  game;

	while (true) {
		receByt = recv(*ClientSocket, RecvBuf, sizeof(RecvBuf), 0);  //���յ��ֽ���
		if (receByt > 0) {
			cout << "���յ�����Ϣ�ǣ�" << RecvBuf << "            ���Կͻ���:" << *ClientSocket << endl;
		}
		else
		{
			cout << "��"<< *ClientSocket <<"�ͻ������ӹرգ�" << endl;
			break;
		}
		Reply(RecvBuf, SendBuf,game);  //�Խ��յ��������Ӧ��
		memset(RecvBuf, 0, sizeof(RecvBuf));
		int k = 0;
		k = send(*ClientSocket, SendBuf, sizeof(SendBuf), 0);
		if (k < 0)
		{
			cout << "����ʧ��" << endl;
		}
		memset(SendBuf, 0, sizeof(SendBuf));
	}
	closesocket(*ClientSocket);
	free(ClientSocket);
	UpdateVacabulary();
	UpdatePlayerList();
	UpdateQmakerList();
	return 0;
}

void Sever() 
{
	WSAData wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN ListenAddr;       //������ַ
	HANDLE Client[10];  //�ͻ��˾��

	ListenAddr.sin_family = AF_INET;
	ListenAddr.sin_addr.S_un.S_addr = INADDR_ANY;//��ʾ���뱾��ip
	ListenAddr.sin_port = htons(PORT);

	int n;
	n = bind(ListenSocket, (LPSOCKADDR)& ListenAddr, sizeof(ListenAddr));
	if (n == SOCKET_ERROR) {
		cout << "�˿ڰ�ʧ�ܣ�" << endl;
	}
	else {
		cout << "�˿ڰ󶨳ɹ���" << PORT << endl;
	}
	int l = listen(ListenSocket, 20);  //�޴��󷵻�0 �д��󷵻�-1
	cout << "�����׼���������ȴ���������" << endl;

	while (true)
	{
		//ѭ�����տͻ����������󲢴��������߳�
		SOCKET* ClientSocket = new SOCKET;
		ClientSocket = (SOCKET*)malloc(sizeof(SOCKET));
		//���տͻ�����������
		int SockAddrlen = sizeof(sockaddr);
		*ClientSocket = accept(ListenSocket, 0, 0); //�����������Ӷ�����ȡ��һ��������׽ӿڰ� ���ظ��׽ӿ� ���п�ʱ����
		CreateThread(NULL, 0, &ServerThread, ClientSocket, 0, NULL);
	}
	closesocket(ListenSocket);
	WSACleanup();

}

void Reply(char* RecvBuf, char* SendBuf,Game &game)
{
	char flag; //�����־λ
	flag = RecvBuf[0];

	switch (flag)
	{
	case 'a':
		game.SetJudgeUse(0);
		game.Register(&RecvBuf[1], SendBuf);
		break;
	case'b':
		game.SetJudgeUse(0);
		game.Login(&RecvBuf[1], SendBuf);
		break;
	case 'c':
		game.SetJudgeUse(1);  //������
		game.Register(&RecvBuf[1], SendBuf);
		break;
	case'd':
		game.SetJudgeUse(1);
		game.Login(&RecvBuf[1], SendBuf);
		break;
	case 'e':
		game.Getword(&RecvBuf[1], SendBuf);
		break;
	case'f':
		game.MakeQusetion(&RecvBuf[1], SendBuf);
		break;
	case'g':
	case'h':
	case'i':
	case'j':
		game.Query(RecvBuf, SendBuf); //��ѯ��Ҫ����ʶλ����
		break;
	case'k':
		game.UpdateUser(RecvBuf, SendBuf); //������Ҫ�ѱ�ʾΪ����
		break;
	case'm':
		game.OnlineGetWord(&RecvBuf[1], SendBuf);
		break;
	case'n':
		game.JudegeSuccess(SendBuf);
	}
}





