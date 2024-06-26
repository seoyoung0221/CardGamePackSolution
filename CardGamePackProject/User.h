#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <conio.h> // for _getch()

using namespace std;


class UserDataManager
{
public:
	void writeUser(vector<string> userInfo); //userInfo = [ID, password, nickname, point]
	vector<vector<string>> openUser();
	void signUp();

protected:
	string inputPassword();
};

//로그인을 하면서 생성되는 것이 좋을 것 같음
class User : public UserDataManager
{

protected:
	string m_ID;
	string m_password;
	string m_nickname;
	string m_gamePoint;

public:
	void login();

	string getID();
	string getPassword();
	string getNickname();
	string getGamePoint();

	void setID(string ID);
	void setPassword(string PW);
	void setNickname(string	Nickname);
	void setGamePoint(string GamePoint);
};