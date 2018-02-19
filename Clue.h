#pragma once
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include "Player.h"


using namespace std;

class Clue {


protected:

	string clueText;
	int value;

private:

	string choices[4];
	bool answered;
	int answerIndex;
	bool dailyDouble;

	//seed random number generator
	unsigned seed = time(0);

public:

	Clue();
	void saveClue(string, string, string, string, string);
	bool checkAnswer(char);
	void displayChoices();
	void setValue(int);
	void displayOnBoard();
	void ask(Player, int);
	bool ifAnswered();
	int getValue();
	void setDailyDouble(bool);
	void wordWrap(string);
	static void genRandomNumbers(int[], int, int);
};



//Default constructor fills clue text and choices with filler text for testing
Clue::Clue() {

	clueText = "Lorem ipsum dolor sit amet, aeterno discere aliquam nam ne.";
	choices[0] = "aliquando an";
	choices[1] = "volumus";
	choices[2] = "laboramus suscipiantur";
	choices[3] = "an apple";
	answered = false;
	answerIndex = 0;
	value = 1000;
}



//Save data in clue
void Clue::saveClue(string text, string answer, string choice1, string choice2, string choice3) {

	//Generate an array of 4 random numbers non-repeating in order to store choices at random indexes in choices array
	int numbers[4];
	genRandomNumbers(numbers, 4, 4);

	clueText = text;

	choices[numbers[0]] = answer;
	choices[numbers[1]] = choice1;
	choices[numbers[2]] = choice2;
	choices[numbers[3]] = choice3;

	answerIndex = numbers[0];

	answered = false;
	dailyDouble = false;

}


//Generates an array of random numbers between 0 and max non-repeating
//These are used to store the indexes of each choice and the correct answer
void Clue::genRandomNumbers(int numbers[], int amt, int max) {

	for (int i = 0; i < amt; i++) {

		bool flag;
		int num;

		do {

			num = rand() % max;  //generate random number

			//check if number has already been generated
			flag = true;
			for (int j = 0; j < i; j++) {
				if (num == numbers[j]) {  //if number is already being used
					flag = false;  //set flag to false so it will return to top of do loop
					break;
				}
			}
		} while (!flag); //loop until number generated is unique

		numbers[i] = num; //store the unique number in numbers
	}
}


void Clue::displayChoices() {

	cout << "a.) " << choices[0] << endl;
	cout << "b.) " << choices[1] << endl;
	cout << "c.) " << choices[2] << endl;
	cout << "d.) " << choices[3] << endl;

}


void Clue::setValue(int val) {
	value = val;
}


//Takes the user's answer as a char as a parameter and returns true if correct or false if incorrect
bool Clue::checkAnswer(char ch) {

	switch (ch) {

	case('a'):
		if (answerIndex == 0)
			return true;
		break;
	case('b'):
		if (answerIndex == 1)
			return true;
		break;
	case('c'):
		if (answerIndex == 2)
			return true;
		break;
	case('d'):
		if (answerIndex == 3)
			return true;
		break;

	}

	return false;
}


void Clue::displayOnBoard() {

	if (answered) {
		cout << setw(6) << "X";
	}
	else {
		cout << setw(6) << value;
	}


}


bool Clue::ifAnswered() {

	if (answered) {
		return true;
	}
	else {
		return false;
	}
}


void Clue::ask(Player player, int round) {

	//If single jeopardy or double jeopardy round, check if daily double
	if(round == 0 || round == 1){
		if (dailyDouble) {
			cout << "\n********You got the daily double!*********\n";
			value = player.getBetAmt(round);
		}
	}

	cout << endl;
	wordWrap(clueText);
	cout << endl;
	answered = true;

}


//Wraps clue text words so they don't get cut off at edge of console
void Clue::wordWrap(string text) {

	int length = text.size();

	if (length > 80) {

		bool wrapped = false;

		for (int i = 0; i < length; i++) {
				if (text[i] == ' ' && !wrapped && i > 65) {
					cout << '\n';
					wrapped = true;
				}
				else {
					cout << text[i];
				}
		}
	}
	else {
		cout << text;
	}
}

int Clue::getValue() {

	return value;

}

void Clue::setDailyDouble(bool val) {

	dailyDouble = val;

}