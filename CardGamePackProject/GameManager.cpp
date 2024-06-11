#include <random>
#include <numeric>

#include "GameManager.h"
#include "Design.h"

#define USERNUM 3

int GameManager::getGamePrice() { return m_gamePrice; }

void GameManager::setGamePrice(int price) { m_gamePrice = price; }


// OldMaid 클래스 함수 정의
// 도둑잡기 게임의 카드 배분 로직 구현 
void OldMaid::dealCard()
{
	CardDeck card(1);

	card.suffleCards();

	// 여기 랜덤 추가 해야할듯 14,14,15
	// 1. 플레이어에게 카드 분배 : 셔플된 카드 덱에서 각 플레이어가 14장, 14장, 15장 분배
	const int cardsPerPlayer[] = { 14,14,15 };

	// 3. 카드 분배 결과 저장 : 각 플레이어가 받은 카드를 별도의 벡터나 다른 적절한 데이터 구조에 저장
	int cardIndex = 0;

	for (int card = 0; card < cardsPerPlayer[0]; card++)
	{
		player1Cards.push_back(m_cardVector[cardIndex]);
		cardIndex++;
	}

	for (int card = 0; card < cardsPerPlayer[0]; card++)
	{
		player2Cards.push_back(m_cardVector[cardIndex]);
		cardIndex++;
	}

	for (int card = 0; card < cardsPerPlayer[0]; card++)
	{
		player3Cards.push_back(m_cardVector[cardIndex]);
		cardIndex++;
	}
}

void OldMaid::removeDuplicates(std::vector<std::string>& playerCards)
{
	// 중복된 요소를 찾아 제거하는 과정
	for (int i = 0; i < playerCards.size(); i++)
	{
		for (int j = i + 1; j < playerCards.size();)
		{
			// 현재 요소와 다음 요소를 비교하여 중복 여부 확인
			if (playerCards[i] == playerCards[j])
			{
				// 중복된 경우 다음 요소를 현재 요소의 위치에 덮어씌움
				playerCards.erase(playerCards.begin() + j);
			}
			else
			{
				// 중복되지 않은 경우 다음 요소로 이동
				j++;
			}
		}
	}

	// 현재 플레이어의 카드가 비어 있는지 확인하고, 비어 있다면 m_zeroCnt 증가
	if (playerCards.empty())
	{
		m_zeroCnt++;
	}

}

void OldMaid::disCard()
{
	removeDuplicates(player1Cards);
	removeDuplicates(player2Cards);
	removeDuplicates(player3Cards);
}

void OldMaid::selectRoutine()
{
	cout << "제비뽑기로 순서를 정합니다!\n";

	// 현재 시간을 시드로 사용하여 무작위성을 증가
	srand(time(0));

	// players 벡터를 playerOrder 벡터에 복사
	playerOrder = players;

	// playerOrder 벡터를 무작위로 섞기
	random_shuffle(playerOrder.begin(), playerOrder.end());
}

void OldMaid::printSelectRoutine()
{
	// 결과 출력
	cout << "플레이어 순서:\n";
	for (int i = 0; i < playerOrder.size(); ++i)
	{
		cout << (i + 1) << "번째 : " << playerOrder[i] << "\n";
	};
}

vector<string>& OldMaid::getPlayerCards(string& player)
{
	if (player == "나")
	{
		return player1Cards;
	}

	if (player == "user1")
	{
		return player2Cards;
	}

	else
	{
		return player3Cards;
	}
}

// 1턴 기준 상대방 카드를 임의로 뽑기
void OldMaid::pickCard()
{
	// 플레이어들이 순서대로 카드를 뽑기 시작합니다.
	for (int i = 0; i < playerOrder.size(); i++)
	{
		// 현재 순서의 플레이어
		string& currentPlayer = playerOrder[i];


		// 다음 순서의 플레이어
		string& nextPlayer = playerOrder[(i + 1) % playerOrder.size()];

		cout << currentPlayer << "의 차례입니다.\n";

		// 다음 순서의 플레이어 카드 목록을 참조로 가져옵니다.
		vector<string>& nextPlayerCards = getPlayerCards(nextPlayer);

		// 다음 순서의 플레이어가 더 이상 카드를 가지고 있지 않은 경우
		if (nextPlayerCards.empty())
		{
			cout << nextPlayer << "는 더 이상 카드를 가지고 있지 않습니다.\n";
			continue;
		}

		// 랜덤 선택된 카드 가져오기
		int cardIndex = rand() % nextPlayerCards.size();
		string pickedCard = nextPlayerCards[cardIndex];

		// 현재 순서의 플레이어 카드 목록을 참조로 가져옵니다.
		vector<string>& currentPlayerCards = getPlayerCards(currentPlayer);
		// 현재 플레이어의 카드 목록에 선택된 카드를 추가합니다.
		currentPlayerCards.push_back(pickedCard);
		// 다음 플레이어의 카드 목록에서 선택된 카드를 제거합니다.
		nextPlayerCards.erase(nextPlayerCards.begin() + cardIndex);
		cout << currentPlayer << "가 " << nextPlayer << "의 카드를 뽑았습니다: " << pickedCard << "\n";
		// 중복된 카드를 제거
		removeDuplicates(currentPlayerCards);
		// pickCard() 기준으로 게임라운드 변수 증가
		m_gameRound++;
	}


}

string OldMaid::determineWinner() {
	// 우승자를 저장할 변수 초기화
	string winner = "";

	// 플레이어들의 카드를 확인하여 남은 카드가 없는 플레이어를 찾음
	for (string& player : playerOrder)
	{
		vector<string>& playerCards = getPlayerCards(player);

		if (playerCards.empty()) {
			winner = player;
			break; // 남은 카드가 없는 플레이어를 찾았으므로 루프 종료
		}
	}

	// 우승자가 없는 경우 "Game is still ongoing." 반환
	if (winner.empty()) {
		return "Game is still ongoing.";
	}

	// 우승자가 있는 경우 해당 플레이어를 우승자로 선정하여 반환
	return winner + " is the Old Maid!";
}

string OldMaid::selectWinner()
{
	// 만약 m_zeroCnt가 2인 경우 (즉, 카드가 없는 플레이어가 2명 이상인 경우)
	if (m_zeroCnt == 2)
	{
		// 승자를 결정하고 반환
		return determineWinner();
	}
	// m_zeroCnt가 2가 아닌 경우, pickCard() 함수 호출
	pickCard();

	// 게임이 아직 종료되지 않았으므로 빈 문자열 반환
	return "";
}

int OldMaid::getGameRound()
{
	return m_gameRound;
}


// Holdem 클래스 함수 정의
string Holdem::selectWinner() {
	// 홀덤 게임의 승자 선택 로직 구현
	return "Holdem Winner";
}

void Holdem::dealCard()
{
	// 홀덤 게임의 카드 배분 로직 구현
	//카드 덱 생성
	CardDeck card(2); //홀덤 option == 2

	//카드 섞기 및 카드 벡터 가져오기
	card.suffleCards();
	vector<string> cardVector = card.getCardVector();

	////랜덤하게 필드카드 5장 가져오고 기존 cardVector에서 값 빼기
	//랜덤 엔진 초기화
	random_device rd;
	mt19937 g(rd());

	//벡터 인덱스
	vector<int> indices(cardVector.size());
	iota(indices.begin(), indices.end(), 0);

	//인덱스 무작위 섞기
	shuffle(indices.begin(), indices.end(), g);

	//무작위 5개의 인덱스 벡터 생성
	vector<int> selected_indices(indices.begin(), indices.begin() + 5);

	//필드에 있을 5개 카드 벡터 생성
	vector<string> fieldCard;
	for (int index : selected_indices) {
		fieldCard.push_back(cardVector[index]);
	}

	//뽑은 5개의 카드를 기존의 cardVector에서 제거
	sort(selected_indices.rbegin(), selected_indices.rend());
	for (int index : selected_indices) {
		cardVector.erase(cardVector.begin() + index);
	}

	////나머지 cardVector에서 랜덤하게 2장씩 가져와 usersCard에 넣기
	vector<vector <string>> usersCard(USERNUM);

	for (int i = 0; i < USERNUM; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			usersCard[i].push_back(cardVector.back());
			cardVector.pop_back();
		}
	}

	m_fieldCard = fieldCard;
	m_totalUserCard = usersCard;
}

void Holdem::play()
{
	// 유저 본인 카드 받기
	// 0번째턴 : 0/5 오픈
	// 배팅(프리)
	// 1번째턴 : 3/5 오픈
	// 배팅(퍼스트)
	// 2번째턴 : 4/5 오픈
	// 배팅(세컨드)
	// 3번째턴 : 5/5 오픈
	// 배팅(라스트)
}

