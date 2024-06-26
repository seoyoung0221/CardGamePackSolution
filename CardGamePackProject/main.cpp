#include <windows.h>
#include <ctime>

#include "CardDeck.h"
#include "User.h"
#include "GameManager.h"
#include "Design.h"
int main()
{
	UserDataManager manager;
	User user;
	
	//회원가입, 로그인 선택
	while (true)
	{
		system("cls");
		cout << "♠CARD GAME♠\n";
		string option = "0";
		cout << "1. 회원가입 2. 로그인 3. 프로그램 종료 \n";
		cin >> option;
		if (option == "1")
		{
			manager.signUp();
		}
		else if (option == "2")
		{
			user.login();
			break;
		}

		else if (option == "3")
		{
			cout << "프로그램을 종료합니다.\n";
			return 0;
		}
		else
		{
			cout << "잘못된 입력입니다.\n";
			Sleep(2000);
		}
	}
	
	cout << user.getGamePoint() << endl;

	int botton;
	while (true)
	{
		string option;
		system("cls");
		cout << "게임을 선택하세요." << endl;
		cout << "1. 도둑잡기 2. 홀덤 3. 게임 종료" << endl;
		cin >> option;
		if (option == "1")
		{
			system("cls");
			//도둑잡기
			OldMaid game1;
			game1.play(user);

			continue;

		}
		else if (option == "2")
		{
			system("cls");
			//홀덤
			cout << "홀덤을 시작합니다." << endl;
			Holdem holdem;

			cout << "카드를 섞어 배분합니다." << endl;
			holdem.dealCard();

			cout << "홀덤을 시작합니다." << endl;
			holdem.play(user);
			cout << "게임을 선택하려면 아무 버튼이나 눌러주세요!";
			cin >> botton;
		}

		else if (option == "3")
		{
			cout << "프로그램을 종료합니다." << endl;
			return 0;
		}
		else
		{
			cout << "잘못된 입력입니다." << endl;
			Sleep(2000);
		}
  }
}