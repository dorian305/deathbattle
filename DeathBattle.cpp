#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "windows.h"

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

template <typename T>
T validateNum(string str = "")
{
	T x;

	while (!(cin >> x))
	{
		(str == "") ? cout << "Invalid input. Please try again: " : cout << str;
		cin.clear();
		cin.ignore(100, '\n');
	}

	return x;
}

int randomNum(int low = 0, int high = 0)
{
	if (low == 0 && high == 0) //No parameters provided
	{
		return rand() % 101;
	}

	if (low != 0 && high == 0) //Provided lower bound only
	{
		if (low > 100) //If lower > 100
		{
			return (rand() % (low - 100 + 1)) + 100; //Return integer between low = high and 100
		}

		return (rand() % (100 - low + 1)) + low; //Return random between lower and 100
	}

	return (rand() % (high - low + 1)) + low; //Bounded
}

void printDelay(string str)
{
	int i = 0;
	for (i; i < str.length(); i++)
	{
		cout << str[i];
		Sleep(0050);
	}
}

void printHealthBar(int hp)
{
	int i = 1, colorRGB = 0, hp_print = hp / 3;
	char c = 219; // █
	char d = 176; // ▒

	if (hp_print / 2 <= 4)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED); //RED
	}
	else if (hp_print / 2 <= 8)
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN); //YELLOW
	}
	else
	{
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); //GREEN
	}
	for (i; i <= 33; i++)
	{
		if (i > hp_print || hp == 0)
		{
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE); //DARKGRAY
			cout << d;
		}
		else if (i > 0 && i <= hp_print)
		{
			cout << c;
		}
	}
	SetConsoleTextAttribute(hConsole, 15);
}

void gameText(string player_name[], int player_health[], int discombobulated[], int attacks[2][12], int player_turn)
{
	cout << "===== DEATH BATTLE =====" << endl;
	cout << player_name[0] << "  vs.  " << player_name[1] << endl << endl;
	cout << player_name[0]; if (discombobulated[0] > 0) cout << " (discombobulated)"; cout << "["; printHealthBar(player_health[0]); cout << "]\t\t";
	cout << player_name[1]; if (discombobulated[1] > 0) cout << " (discombobulated)"; cout << "["; printHealthBar(player_health[1]); cout << "]";
	cout << endl << endl <<  "=== Available attacks ===" << endl;
	cout << "1. Default attack" << endl;
	cout << "2. Body slam (" << attacks[player_turn][7] << ")" << endl;
	cout << "3. Mega slap (" << attacks[player_turn][8] << ")" << endl;
	cout << "4. Fart (" << attacks[player_turn][9] << ")" << endl;
	cout << "5. Punch (" << attacks[player_turn][10] << ")" << endl;
	cout << "6. Discombobulate (" << attacks[player_turn][11] << ")" << endl << endl;
}

string playerNames(string s)
{
	string player_name = "";
	do
	{
		cout << s;
		cin.clear();
		getline(cin, player_name);

		if (player_name.size() > 15)
		{
			cout << "Nickname cannot be more than 15 characters!" << endl;
		}
		if (player_name.size() < 4)
		{
			cout << "Nickname must be at least 5 characters!" << endl;
		}
	} while (player_name.size() > 15 || player_name.size() < 4);

	return player_name;
}

void attackResponse(int damage, string player_name[], int player_turn, int move)
{
	int rand = 0;
	if (move == 1) //Default attack
	{
		rand = randomNum(1, 3); //Getting random response
		switch (rand)
		{
		case 1:
			(player_turn == 0) ? cout << player_name[0] << " mocks " << player_name[1] << " and it hurts him for " << damage << " damage!" << endl : cout << player_name[1] << " mocks " << player_name[0] << " and it hurts him for " << damage << " damage!" << endl;
			break;
		case 2:
			(player_turn == 0) ? cout << player_name[0] << " throws protein shake at " << player_name[1] << ", hitting the head for " << damage << " damage!" << endl : cout << player_name[1] << " throws protein shake at " << player_name[0] << ", hitting the head for " << damage << " damage!" << endl;
			break;
		case 3:
			(player_turn == 0) ? cout << player_name[0] << " shouts, and \"accidentally\" spits on " << player_name[1] << ", dealing " << damage << " damage!" << endl : cout << player_name[1] << " shouts, and \"accidentally\" spits on " << player_name[0] << ", dealing " << damage << " damage!" << endl;
			break;
		}
	}
	else if (move == 2) //Body slam
	{
		rand = randomNum(1, 3);
		switch (rand)
		{
		case 1:
			(player_turn == 0) ? cout << player_name[0] << " charges and slams into " << player_name[1] << " for " << damage << " damage!" << endl : cout << player_name[1] << " charges and slams into " << player_name[0] << " for " << damage << " damage!" << endl;
			break;
		case 2:
			(player_turn == 0) ? cout << player_name[0] << " falls off a building onto " << player_name[1] << " for " << damage << " damage!" << endl : cout << player_name[1] << " falls off a building onto " << player_name[0] << " for " << damage << " damage!" << endl;
			break;
		case 3:
			(player_turn == 0) ? cout << player_name[0] << " politely asks " << player_name[1] << " to bump into for " << damage << " damage!\n" << player_name[1] << " says yes." << endl << endl : cout << player_name[1] << " politely asks " << player_name[0] << " to bump into for " << damage << " damage!\n" << player_name[0] << " says yes." << endl;
			break;
		}
	}
	else if (move == 3) // Mega slap
	{
		rand = randomNum(1, 2);
		switch (rand)
		{
		case 1:
			(player_turn == 0) ? cout << "Seeing a dead catfish on the floor, " << player_name[0] << " picks it up and slaps " << player_name[1] << " for " << damage << " damage!" << endl : cout << "Seeing a dead catfish on the floor, " << player_name[1] << " picks it up and slaps " << player_name[0] << " for " << damage << " damage!" << endl;
			break;
		case 2:
			(player_turn == 0) ? cout << player_name[0] << " does a 360 with arms wide spread, putting " << player_name[1] << "'s, face to shame for " << damage << " damage!" << endl : cout << player_name[1] << " does a 360 with arms wide spread, putting " << player_name[0] << "'s, face to shame for " << damage << " damage!" << endl;
			break;
		}
	}
	else if (move == 4) //Fart
	{
		(player_turn == 0) ? cout << player_name[0] << " had too much fibre for lunch today, and sharted in " << player_name[1] << "'s face for " << damage << " damage!" << endl : cout << player_name[1] << " had too much fibre for lunch today, and sharted into " << player_name[0] << "'s face for " << damage << " damage!" << endl;
	}
	else if (move == 5) //Punch
	{
		rand = randomNum(1, 2);
		switch (rand)
		{
		case 1:
			(player_turn == 0) ? cout << player_name[0] << " punches " << player_name[1] << "'s head for " << damage << " damage!" << endl : cout << player_name[1] << " punches " << player_name[0] << "'s head for " << damage << " damage!" << endl;
			break;
		case 2:
			(player_turn == 0) ? cout << "Oh look, a baseball bat! " << player_name[0] << " picks it up and swings it at " << player_name[1] << " for " << damage << " damage!" << endl : cout << "Oh look, a baseball bat! " << player_name[1] << " picks it up and swings it at " << player_name[0] << " for " << damage << " damage!" << endl;
			break;
		}
	}
	else //Discombobulate
	{
		(player_turn == 0) ? cout << player_name[0] << " discombobulates " << player_name[1] << ". " << player_name[1] << " is trying to come to his senses..." << endl : cout << player_name[1] << " discombobulates " << player_name[0] << ". " << player_name[0] << " is trying to come to his senses..." << endl;
	}
}

void playerMove(int attacks[2][12], string player_name[], int player_health[], int player_turn, int discombobulated[], bool autoplay, int total_damage[])
{
	int attack = 0, damage = 0, min_damage_amount = 5, rand = 0;

	do
	{
		//Getting attack move
		printDelay(player_name[player_turn] + ", select your move: ");
		if (autoplay) //If autoplay is enabled
		{
			Sleep(1000);
			do
			{
				attack = randomNum(1, 6); //Random attack
			} while (attacks[player_turn][(attack - 1) + 6] == 0); //Repeat until attack with available attack points is chosen
			cout << attack << endl;
		}
		else //Human players
		{
			attack = validateNum<int>(player_name[player_turn] + ", select your move: ");

			if (attacks[player_turn][(attack - 1) + 6] == 0) //No more attack points left
			{
				cout << "No more attack points left for that attack." << endl;
				Sleep(1000);
			}
		}

	} while (attack < 1 || attack > 6 || attacks[player_turn][(attack - 1) + 6] == 0);

	attacks[player_turn][(attack - 1) + 6]--; //Reduce 1 attack point

	if (player_turn == 0) //Player 1's turn
	{
		if (discombobulated[0] > 0 && randomNum(1, 100) <= 35) //Player 1 is discombobulated and 35% chance to miss
		{
			cout << player_name[0] << " missed!";
			discombobulated[0]--;
		}
		else //Player didn't miss
		{
			if (attack == 6) //Player used discombobulate
			{
				rand = randomNum(1, 3); //Getting duration of discombobulate
				discombobulated[1] = rand;
			}
			else //Other attacks
			{
				if (discombobulated[1] > 0) //Reduce enemy discombobulate counter each round
				{
					discombobulated[1]--;
					damage = randomNum(min_damage_amount, attacks[0][attack - 1]) * 1.5;
					total_damage[0] += damage;
				}
				else
				{
					damage = randomNum(min_damage_amount, attacks[0][attack - 1]);
					total_damage[0] += damage;
				}
			}

			(player_health[1] - damage < 0) ? player_health[1] = 0 : player_health[1] -= damage; //If damage causes player's HP to go below 0, set it to 0, otherwise deduct damage amount from HP
			attackResponse(damage, player_name, player_turn, attack);
		}
	}
	else //Player 2's turn
	{
		if (discombobulated[1] > 0 && randomNum(1, 100) <= 35)
		{
			cout << player_name[1] << " missed!";
			discombobulated[1]--;
		}
		else
		{
			if (attack == 6) //Player used discombobulate
			{
				rand = randomNum(1, 3); //Getting duration of discombobulate
				discombobulated[0] = rand;
			}
			else
			{
				if (discombobulated[0] > 0) //Reduce enemy discombobulate counter each round
				{
					discombobulated[0]--;
					damage = randomNum(min_damage_amount, attacks[1][attack - 1]) * 1.5;
					total_damage[1] += damage;
				}
				else
				{
					damage = randomNum(min_damage_amount, attacks[1][attack - 1]);
					total_damage[1] += damage;
				}
			}

			(player_health[0] - damage < 0) ? player_health[0] = 0 : player_health[0] -= damage;
			attackResponse(damage, player_name, player_turn, attack);
		}
	}
}

int main()
{
	SetConsoleTextAttribute(hConsole, 15);
	srand(time(NULL));
	string player_name[]{ "", "" };
	fstream file;
	bool autoplay = false;
	int player_turn = 0, player_health[]{ 100, 100 }, attacks[2][12]{ {10, 40, 24, 19, 28, 0, 1000, 5, 5, 5, 5, 3}, {10, 40, 24, 19, 28, 0, 1000, 5, 5, 5, 5, 3} }, player_discombobulated[]{ 0, 0 }, choice = 0, total_damage[]{ 0, 0 };

	//Choosing nicknames
	player_name[0] = playerNames("Player 1, input your nickname: ");
	player_name[1] = playerNames("Player 2, input your nickname: ");

	do
	{
		//Clearing screen
		system("CLS");

		//Menu
		cout << "Death Battle simulator\nCreated by Dorian (manjaricdorian0@gmail.com)\nMade on April, 2020\n\n";
		cout << "1. Start the battle" << endl;
		cout << "2. Start the battle (automatic)" << endl;
		cout << "3. Read the tutorial" << endl;
		cout << "Input: ";
		choice = validateNum<int>();

		if (choice == 2)
		{
			autoplay = true;
		}
		else if (choice == 3)
		{
			system("CLS");

			cout << "Players participate in a death battle." << endl;
			cout << "Each player starts with 100 health points and have 5 attacks to choose from." << endl;
			cout << endl;
			cout << "== Attack ==" << endl;
			cout << "DEFAULT ATTACK: the only thing you're left with when you use up all the other attack points. Deals max " << attacks[0][0] << " damage." << endl;
			cout << "BODY SLAM: literally what the name says. " << attacks[0][7] << " attack points. Deals max. " << attacks[0][1] << " damage." << endl;
			cout << "MEGA SLAP: slap the opponent. " << attacks[0][8] << " attack points. Deals max. " << attacks[0][2] << " damage." << endl;
			cout << "FART: releases very toxic, damaging gas at the opponent. " << attacks[0][9] << " attack points. Deals max. " << attacks[0][3] << " damage." << endl;
			cout << "PUNCH: punch the opponent with whatever you got. " << attacks[0][10] << " attack points. Deals max. " << attacks[0][4] << " damage." << endl;
			cout << "DISCOMBOBULATE: stun the opponent. This attack leaves the enemy confused\nfor up to 3 rounds, making him miss 35% of the attacks. " << attacks[0][11] << " attack points. " << endl << endl;

			do
			{
				cout << "Press 0 to return to menu: ";
				choice = validateNum<int>("Press 0 to return to menu: ");
			} while (choice != 0);
		}
	} while (choice != 1 && choice != 2);

	//Clearing screen
	system("CLS");

	//Player taking turns
	do
	{
		//Game text
		gameText(player_name, player_health, player_discombobulated, attacks, player_turn);

		//Player taking moves
		playerMove(attacks, player_name, player_health, player_turn, player_discombobulated, autoplay, total_damage);

		//Changing player turns
		(player_turn == 0) ? player_turn = 1 : player_turn = 0;

		//Deciding the winner
		if (player_health[0] == 0) //Player 1 died
		{
			Sleep(3000);
			system("CLS");
			cout << "===== DEATH BATTLE =====" << endl << endl;
			cout << player_name[0] << "["; printHealthBar(player_health[0]); cout << "]" << endl;
			cout << player_name[1] << "["; printHealthBar(player_health[1]); cout << "]" << endl;
			cout << endl << "The winner is: " << player_name[1] << "!!!" << endl << endl;
			cout << "Total damage dealt" << endl;
			cout << player_name[0] << ": " << total_damage[0] << endl;
			cout << player_name[1] << ": " << total_damage[1] << endl << endl;
			file.open("deathbattle_history.txt", ios::app);
			file << player_name[0] << " vs. " << player_name[1] << endl
				<< "Winner: " << player_name[1] << endl << "-" << endl
				<< "Total damage dealt" << endl << player_name[0] << ": " << total_damage[0] << endl
				<< player_name[1] << ": " << total_damage[1] << endl << "--------------------" << endl;
			break;
		}
		else if (player_health[1] == 0) //Player 2 died
		{
			Sleep(3000);
			system("CLS");
			cout << "===== DEATH BATTLE =====" << endl << endl;
			cout << player_name[0] << "["; printHealthBar(player_health[0]); cout << "]" << endl;
			cout << player_name[1] << "["; printHealthBar(player_health[1]); cout << "]" << endl;
			cout << endl << "The winner is: " << player_name[0] << "!!!" << endl << endl;;
			cout << "Total damage dealt" << endl;
			cout << player_name[0] << ": " << total_damage[0] << endl;
			cout << player_name[1] << ": " << total_damage[1] << endl << endl;
			file.open("deathbattle_history.txt", ios::app);
			file << player_name[0] << " vs. " << player_name[1] << endl
				<< "Winner: " << player_name[0] << endl << "-" << endl
				<< "Total damage dealt" << endl << player_name[0] << ": " << total_damage[0] << endl
				<< player_name[1] << ": " << total_damage[1] << endl << "--------------------" << endl;
			break;
		}
		else
		{
			Sleep(3000);
			system("CLS");
		}

	} while (player_health[0] != 0 || player_health[1] != 0);

	file.close();

	system("pause");
	return 0;
}