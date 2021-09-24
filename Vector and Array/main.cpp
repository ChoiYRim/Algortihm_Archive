#include <iostream>
#include <vector>
#include <array>
#include <sstream>
#include <algorithm>
#include <random>
#include <chrono>

struct Card
{
	int number;

	enum _suit
	{
		HEART,
		SPADE,
		CLUB,
		DIAMOND
	}Suit;

	std::string to_string() const
	{
		std::ostringstream os;

		if(number > 0 && number <= 10)
			os << number;
		else
		{
			switch(number)
			{
				case 1:
					os << "Ace";
					break;
				case 2:
					os << "Jack";
					break;
				case 3:
					os << "Queen";
					break;
				case 4:
					os << "King";
					break;
				default:
					return "Invalid Card";
			}
		}

		os << " of ";

		switch(Suit)
		{
			case HEART:
				os << "hearts";
				break;
			case SPADE:
				os << "spades";
				break;
			case CLUB:
				os << "clubs";
				break;
			case DIAMOND:
				os << "diamonds";
				break;
		}

		return os.str();
	}
};

struct Game
{
	std::array<Card,52> deck;
	std::vector<Card> player1, player2, player3, player4;

	// Card 구성함수(초기화)
	void BuildDeck()
	{
		for(int i = 0; i < 13; i++)
		{
			deck[i] = Card{i+1,Card::HEART};
			deck[i+13] = Card{i+1,Card::SPADE};
			deck[i+26] = Card{i+1,Card::CLUB};
			deck[i+39] = Card{i+1,Card::DIAMOND};
		}
	}

	// Card 뿌리기 
	void DealCards()
	{
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(deck.begin(),deck.end(),std::default_random_engine(seed));

		player1 = {deck.begin(),deck.begin()+13};
		player2 = {deck.begin()+13,deck.begin()+26};
		player3 = {deck.begin()+26,deck.begin()+39};
		player4 = {deck.begin()+39,deck.end()};
	}

	// 두 플레이어의 카드 숫자가 같으면 제거
	bool CompareAndRemove(std::vector<Card>& p1, std::vector<Card>& p2)
	{
		if(p1.back().number == p2.back().number)
		{
			p1.pop_back();
			p2.pop_back();
			return true;
		}
		return false;
	}

	void PlayOneRound()
	{
		if(CompareAndRemove(player1,player2))
		{
			CompareAndRemove(player3,player4);
			return;
		}
		else if(CompareAndRemove(player1,player3))
		{
			CompareAndRemove(player2,player4);
			return;
		}
		else if(CompareAndRemove(player1,player4))
		{
			CompareAndRemove(player2,player3);
			return;
		}
		else if(CompareAndRemove(player2,player3))
			return;
		else if(CompareAndRemove(player2,player4))
			return;
		else if(CompareAndRemove(player3,player4))
			return;

		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(player1.begin(),player1.end(),std::default_random_engine(seed));
		std::shuffle(player2.begin(),player2.end(),std::default_random_engine(seed));
		std::shuffle(player3.begin(),player3.end(),std::default_random_engine(seed));
		std::shuffle(player4.begin(),player4.end(),std::default_random_engine(seed));
	}

	bool IsGameComplete() const
	{
		return player1.empty() || player2.empty() || player3.empty() || player4.empty();
	}

	void PlayGame()
	{
		while(not IsGameComplete())
			PlayOneRound();
	}

	int GetWinner() const
	{
		if(player1.empty())
			return 1;
		if(player2.empty())
			return 2;
		if(player3.empty())
			return 3;
		if(player4.empty())
			return 4;
		return 0;
	}
};

int main(int argc,char* argv[])
{
	Game newGame;
	newGame.BuildDeck();
	newGame.DealCards();
	newGame.PlayGame();

	auto winner = newGame.GetWinner();
	std::cout << "Player" << winner << " is victory!\n";
	return 0;
}
