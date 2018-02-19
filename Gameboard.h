#pragma once
#include "Clue.h"

struct Category {

	char col;
	Clue clues[5];
	string name;

};


class Gameboard {

protected:

	Category * categories[6];
	int round;  //0 = single jeopardy, 1 = double jeopardy, 2 = final jeopardy



public:

	Gameboard(Category*, Category*, Category*, Category*, Category*, Category *, int);
	void display();
	void display(int);
	Clue * chooseClue();
	Clue * chooseClue(int, int);
	int getRound() {
		return round;
	}

};


//Generate full gameboard with 6 categories
Gameboard::Gameboard(Category * cat1, Category * cat2, Category * cat3, Category * cat4, Category * cat5, Category * cat6, int rnd) {

	cat1->col = 'A';
	cat2->col = 'B';
	cat3->col = 'C';
	cat4->col = 'D';
	cat5->col = 'E';

	categories[0] = cat1;
	categories[1] = cat2;
	categories[2] = cat3;
	categories[3] = cat4;
	categories[4] = cat5;
	categories[5] = cat6;

	round = rnd;

}


//Display entire gameboard
void Gameboard:: display() {

	cout << endl << endl;

	//Display Category names with characters
	for (int x = 0; x < 5; x++) {
		cout << "\t" << categories[x]->col << " : " << categories[x]->name << endl;
	}

	cout << endl << endl;

	//Display Category characters at top of board
	cout << '\t';
	for (int x = 0; x < 5; x++) {
		cout << setw(3) << categories[x]->col;
		cout << "   ";
	}

	//Display clue values under the category characters
	for (int a = 0; a < 5; a++) {
		cout << endl << '\t';
		for (int b = 0; b < 5; b++) {
			(*categories)[b].clues[a].displayOnBoard();
		}
	}
}

//Display one category
void Gameboard::display(int catIndex) {

	cout << "The category is: " << categories[catIndex]->name << endl << endl;

}





//Returns a Clue pointer for the specified column and row
Clue * Gameboard::chooseClue(int col, int row) {

	Clue * cluePointer = &((*categories)[col].clues[row]);
	return cluePointer;

}


//User chooses column and row - validates input, and returns Clue pointer
Clue * Gameboard::chooseClue() {

	char col;
	int amount;
	int colNumberIndex;
	int amountIndex;

	bool valid = false;

	//First select Category
	while (!valid) {

		cout << "\nEnter category character (a, b, c, d, or e): ";
		cin >> col;
		col = toupper(col);
		cin.clear();
		cin.ignore(1000, '\n');


		switch (col) {

		case('A'):
			colNumberIndex = 0;
			valid = true;
			break;
		case('B'):
			colNumberIndex = 1;
			valid = true;
			break;
		case('C'):
			colNumberIndex = 2;
			valid = true;
			break;
		case('D'):
			colNumberIndex = 3;
			valid = true;
			break;
		case('E'):
			colNumberIndex = 4;
			valid = true;
			break;
		default:
			cout << "\nInvalid category. Please try again.";

		}
	}

	valid = false;

	//Then select Amount
	while (!valid) {

		cout << "\nWhich amount?: ";

		while (!(cin >> amount)) {
			cin.clear();
			cin.ignore(1000, '\n');
			amount = 0;
			break;
		};

		//Single Jeopardy Round
		if (round == 0 && (amount == 200 || amount == 400 || amount == 600 || amount == 800 || amount == 1000)) {

			switch (amount) {

			case(200):
				amountIndex = 0;
				valid = true;
				break;
			case(400):
				amountIndex = 1;
				valid = true;
				break;
			case(600):
				amountIndex = 2;
				valid = true;
				break;
			case(800):
				amountIndex = 3;
				valid = true;
				break;
			case(1000):
				amountIndex = 4;
				valid = true;
				break;
			}
		}
		//Double Jeopardy Round
		else if (round == 1 && (amount == 400 || amount == 800 || amount == 1200 || amount == 1600 || amount == 2000)) {

			switch (amount) {

			case(400):
				amountIndex = 0;
				valid = true;
				break;
			case(800):
				amountIndex = 1;
				valid = true;
				break;
			case(1200):
				amountIndex = 2;
				valid = true;
				break;
			case(1600):
				amountIndex = 3;
				valid = true;
				break;
			case(2000):
				amountIndex = 4;
				valid = true;
				break;
			}
		}

		else {
			cout << "\nThat's not a valid amount. Try again.";
		}

	}

	//Set cluePointer to the address of the Clue object in the colNumber and AmountIndex that was entered
	//Return pointer to that clue
	Clue * cluePointer = &((*categories)[colNumberIndex].clues[amountIndex]);
	return cluePointer;

}
