#pragma once
#include "Clue.h"

using namespace std;

class Player {




private:

	string playerName;
	int score;

public:

	Player(string);
	char answerQuestion();
	int getBetAmt(int);
	static int numOfPlayers;
	int getScore();
	void chgScore(int);
	string getName();

};

int Player::numOfPlayers = 0;


Player::Player(string name) {

	playerName = name;
	score = 0;
	numOfPlayers++;

}


char Player::answerQuestion() {

	char answer;

	while (true) {
		cout << ": ";
		cin >> answer;
		answer = tolower(answer);
		cin.clear();
		cin.ignore(1000, '\n');

		if (answer == 'a' || answer == 'b' || answer == 'c' || answer == 'd')
			return answer;
		else
			cout << "\nInvalid input. Please enter either a, b, c, or d.\n";
	}
}




int Player::getBetAmt(int round) {

	int bet;
	bool validBet = false;

	while(!validBet) {

		cout << "\nEnter wager amount: ";

		while (!(cin >> bet)) {
			cin.clear();
			cin.ignore();
			cout << "\nInvalid input. How much will you wager? ";
		}

			if (round == 0) {	//single jeopardy round
				//if the player has more than 1000 and the bet is greater than the
				//score the Player has or if the bet is less than 5 then the bet is invalid
				if ((score > 1000 && bet > score) || bet < 5)
					cout << "\nThat's an invalid wager. Please try again.";
				//if player's score is less than 1000, they can bet up to 1000
				else if (score < 1000 && bet <= 1000) {
					validBet = true;
					cout << "\nOK for $" << bet << " here is the clue.\n";
				}
				else {
					validBet = true;
					cout << "\nOK for $" << bet << " here is the clue.\n";
				}
			}

			else if (round == 1) {  //double jeopardy round
				//if the player has more than 2000 and the bet is greater than the
				//score the Player has or if the bet is less than 5.
				if ((score > 2000 && bet > score) || bet < 5)
					cout << "\nThat's an invalid wager. Please try again.\n";
				//if player's score is less than 2000, they can bet up to 2000
				else if (score < 2000 && bet <= 2000) {
					validBet = true;
					cout << "\nOK for $" << bet << " here is the clue.\n\n\n";
				}
				else {
					validBet = true;
					cout << "\nOK for $" << bet << " here is the clue.\n\n\n";
					}
				}
			else if (round == 2) {	//final jeopardy round

				if ((score > 0 && bet <= score))
					validBet = true;
				else if (score <= 0) {
					cout << "\nSince you have a negative amount. You cannot wager anything in final jeopardy.\n\n\n";
					bet = 0;
					validBet = true;
				}
				else
					cout << "\nThat's an invalid wager. Please try again.\n";
			}
		}

	return bet;

}


int Player::getScore() {

	return score;

}

string Player::getName() {

	return playerName;

}

void Player::chgScore(int amt) {

	score += amt;

}
