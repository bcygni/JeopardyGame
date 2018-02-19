#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Clue.h"
#include "Player.h"
#include "Gameboard.h"

using namespace std;

void importClues(Category[]);
void displayPlayerScores(vector<Player> &);
void startGame(Gameboard, vector<Player> &);
void startFJ(Gameboard, vector<Player> &players);
void endGame(vector<Player> &players);

int countLines(ifstream &);
void genRandomNumbersDivisible(int[], int, int, int);
int genRandomNumber(int);
int genRandomNumber(int, int);
void genRandomNumbers(int[], int, int);

unsigned seed = time(0);

int main() {

	srand(time(NULL));

	Category categories[6];
	importClues(categories);

	char answer;
	int numOfPlayers;

	cout << "This is Jeopardy! Enter number of players (1-4): ";

	while (true) {
		while (!(cin >> numOfPlayers)) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "\nInvalid input. How many players?: ";
		}

		if (numOfPlayers > 0 && numOfPlayers < 5) {
			break;
		}
		cout << "\nPlease enter 1, 2, 3, or 4: ";
	}

	vector<Player> players;

	cin.ignore(1000, '\n');

	for (int i = 1; i <= numOfPlayers; i++) {

		string name;
		cout << "\nEnter player " << i << " name:";
		getline(cin, name);
		Player newPlayer = Player(name);
		players.push_back(newPlayer);
	}

	//Start Single Jeopardy Game
	Gameboard game = Gameboard(&categories[0], &categories[1], &categories[2], &categories[3], &categories[4], &categories[5], 0);
	startGame(game, players);

	//Start the Final Jeopardy Round
	startFJ(game, players);
	//End game
	endGame(players);
	cout << " Press enter to exit.\n";
	while (cin.get() != '\n') {};

}


void displayPlayerScores(vector<Player> &players) {

	cout << endl;

	for (unsigned int x = 0; x < players.size(); x++) {

		cout << setw(16) << players[x].getName() << ": " << players[x].getScore() << endl;

	}

	cout << endl;

}


void startGame(Gameboard game, vector<Player> &players) {

	int numOfClues = 0;
	char answer;


	while (numOfClues != 24) {

		for (int p = 0; p < Player::numOfPlayers; p++) {

			displayPlayerScores(players);
			game.display();

			cout << endl << endl << players[p].getName() << " - you get to pick a clue.";

			Clue * currentClue = nullptr;

			bool validClue = false;
			while (!validClue) {
				currentClue = game.chooseClue();

				if (currentClue->ifAnswered()) {
					cout << "\nThat one has already been answered.";
				}
				else {
					validClue = true;
					currentClue->ask(players[p], game.getRound());
					currentClue->displayChoices();

					answer = players[p].answerQuestion();

					//If the current player gets the answer correct increase score;
					if (currentClue->checkAnswer(answer)) {
						cout << "\nThat's correct!\n";
						players[p].chgScore(currentClue->getValue());
					}
					else {
						//if incorrect, decrease score
						cout << "\nSorry that's incorrect.\n";
						players[p].chgScore(-(currentClue->getValue()));

					}

					cout << " Press enter to continue.\n";
					while (cin.get() != '\n') {};
					cout << numOfClues;
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
					cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

					//End of clue
					numOfClues++;
				}
			}
		}
	}

	cout << "\n\nIt's time for Final Jeopardy!\n\n";

}


void startFJ(Gameboard game, vector<Player> &players) {

	cout << "Now it's time for Final Jeopardy! Each player will get a different question.\n";

	char answer;
	int wagers[4];
	int arr[4];
	genRandomNumbers(arr, 4, 4);

	game.display(5);

	for (int p = 0; p < Player::numOfPlayers; p++) {

		cout << players[p].getName() << " ";
		wagers[p] = players[p].getBetAmt(2);

	}

	for (int p = 0; p < Player::numOfPlayers; p++) {

		cout << players[p].getName() << ": here is your clue.\n";

		Clue * currentClue = game.chooseClue(5, arr[p]);
		currentClue->setValue(wagers[p]);
		currentClue->ask(players[p], 2);
		currentClue->displayChoices();
		answer = players[p].answerQuestion();

		if (currentClue->checkAnswer(answer)) {
			cout << "\nThat's correct!\n";
			players[p].chgScore(currentClue->getValue());
		}
		else {
			cout << "\nSorry that's incorrect.\n";
			players[p].chgScore(-(currentClue->getValue()));
		}
	}
}



void endGame(vector<Player> &players) {

	cout << "\n\nHere are the final results!\n\n";

	for (int p = 0; p < Player::numOfPlayers; p++) {

		cout << players[p].getName() << ": " << players[p].getScore() << endl;

	}

}


void genRandomNumbersDivisible(int arr[], int numOfNumbers, int divisible, int max) {

	for (int i = 0; i < numOfNumbers; i++) {

		bool flag;
		int num;

		do {

			num = (rand() % max) * divisible;  //generate random number divisible by divisible argument


			flag = true;
			 //check if number is less than or equal to the max
			//if it is than set flag to false to return to top of loop

			if (num >= max)
				flag = false;

			//if flag is still true than check if the number is already in the array
			if(flag){
				for (int j = 0; j < i; j++) {
					if (num == arr[j]) {  //if number is already being used
						flag = false;  //set flag to false so it will return to top of do loop
						break;
					}
				}
			}
		} while (!flag); //loop until number generated is unique

		arr[i] = num; //store the unique number in arr
	}

}

//generate a random number between 0 and max
int genRandomNumber(int max) {

	int num;
	num = (rand() % max);

	return num;

}

//generate a random number between max and min
int genRandomNumber(int max, int min) {

	int num = max + 1;
	while (num > max) {
		num = (rand() % max) + min;
	}

	return num;

}

//generate an array of random numbers non repeating between 0 and max
void genRandomNumbers(int numbers[], int amt, int max) {

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

void importClues(Category categories[6]) {

	ifstream cluesTextFile("clues-text.txt");

	if (!cluesTextFile) {
		cout << "Error. Clue data could not be loaded. 'clues-text.txt' is required.";
	}
	else {

		int categoryLines[6];
		int numOfLines = countLines(cluesTextFile);

		//6 is the number of categories in a jeopardy game, 5 is the number of clues per category
		genRandomNumbersDivisible(categoryLines, 6, 5, numOfLines);

		string clueCategory, clueText, correct, choice1, choice2, choice3;
		string buffer;
		int clueIndex = 0;
		int categoryIndex = 0;
		int lineNumber = 0;
		int currentValue = 200;  //the value for the Clue will increase by 200 for each clue in the category
		int cat = 0; //index in the categoryLines array
		int clueCount = 0; //number of clues read in so far

		//this is the clueCount where the daily Doubles will appear
		int dailyDouble = genRandomNumber(30);

		while (cat < 6) {

			//read each line from the text file and save in the buffer string
			while (getline(cluesTextFile, buffer)) {


				//if the line number being read in matches the randomly generated category line
				if (lineNumber == categoryLines[cat]) {

					//put the line in a stringstream object
					stringstream ss(buffer);

					//create a new category and set clueCategory
					getline(ss, clueCategory, '\t');
					categories[categoryIndex].name = clueCategory;
					clueIndex = 0;

					while (clueIndex < 5) {

						stringstream ss(buffer);

						//split the string by tabs and store into each string object
						getline(ss, clueCategory, '\t');
						getline(ss, clueText, '\t');
						getline(ss, correct, '\t');
						getline(ss, choice1, '\t');
						getline(ss, choice2, '\t');
						getline(ss, choice3, '\n');

						categories[categoryIndex].clues[clueIndex].saveClue(clueText, correct, choice1, choice2, choice3);

						//if the clueCount matches one of the daily double values, make that clue a daily double!
						if (clueCount == dailyDouble) {
							categories[categoryIndex].clues[clueIndex].setDailyDouble(true);
						}

						//set values for single jeopardy round
						if (clueCount <= 30)
							categories[categoryIndex].clues[clueIndex].setValue(currentValue);

						clueIndex++;
						clueCount++;
						currentValue += 200;
						getline(cluesTextFile, buffer);  //read the next line in the file

					}

					//Finished filling the Category object so increase the index for saving in the categories array
					//and reset current value back to 200
					categoryIndex++;
					cat++;
					currentValue = 200;

					if (categoryIndex < 11) {
						//return to start of text file
						cluesTextFile.clear();
						cluesTextFile.seekg(0, ios::beg);
						lineNumber = 0;

					}
				}
				else {
					lineNumber++;
				}

			}

		}

		cluesTextFile.close();

	}//end else
}

int countLines(ifstream &file) {

	int count = 0;
	string line;

	while (getline(file, line)) {
		count++;
	}

	//return to start of text file
	file.clear();
	file.seekg(0, ios::beg);

	return count;
}
