// ConjoinCuatroGame.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "pch.h"
#include <iostream>
using namespace std;

// function prototypes
void displayBoard(char cpyPiecesOnBoard[7][6]);
void playGame(int gameMode);
int availableSquareInColumn(int x, char cpyPiecesOnBoard[7][6]);
int blockVertical(int x, char opponentIdentity, char cpyPiecesOnBoard[7][6]);
int blockHorizontal(int X, char opponentIdentity, char cpyPiecesOnBoard[7][6]);
int blockWin(char opponentIdentity, char cpyPiecesOnBoard[7][6]);
int getWin(char opponentIdentity, char cpyPiecesOnBoard[7][6]);
int block2and5(char opponentIdentity, char cpyPiecesOnBoard[7][6]);

int main()
{
	int menuChoice;

	// - introduce the game to the user and determine whether user wants a 1- or 2-player game
	// - for a 1-player game, determine whether the user wants 1) easy, 2) medium, or 3) hard mode
	do
	{

		std::cout << "\n     *********************************************************************************\n\n"
			<< "                       _____ ____  _   _      _  ____ _____ _   _\n"
			<< "                      / ____/ __ \\| \\ | |    | |/ __ \\_   _| \\ | |\n"
			<< "                     | |   | |  | |  \\| |    | | |  | || | |  \\| |\n"
			<< "                     | |   | |  | | . ` |_   | | |  | || | | . ` |\n"
			<< "                     | |___| |__| | |\\  | |__| | |__| || |_| |\\  |\n"
			<< "                      \\_____\\____/|_| \\_|\\____/_\\____/_____|_|_\\_|\n"
			<< "                        / ____| |  | |  /\\|__   __|  __ \\ / __ \\  \n"
			<< "                       | |    | |  | | /  \\  | |  | |__) | |  | | \n"
			<< "                       | |    | |  | |/ /\\ \\ | |  |  _  /| |  | | \n"
			<< "                       | |____| |__| / ____ \\| |  | | \\ \\| |__| | \n"
			<< "                        \\_____|\\____/_/    \\_\\_|  |_|  \\_\\\\____/  \n\n\n"
			<< "     *********************************************************************************\n\n";
		std::cout << "                 Created Jan. 2019 by Chris Bryant. CLB372@cornell.edu\n\n"
			<< "                                Welcome to CONJOIN CUATRO!\n\n"
			<< "                                   Press enter to begin.\n";
		std::cin.ignore();
		system("cls");
		std::cout << "\n\n     Select an option:\n\n"
			<< "                    (1) 1-player game\n"
			<< "                    (2) 2-player game\n"
			<< "                    (3) Quit\n\n"
			<< "     Enter 1, 2, or 3: ";
		std::cin >> menuChoice;
		if (menuChoice != 3)
		{

			if (menuChoice == 1)
			{
				system("cls");
				std::cout << "\n\nSelect difficulty:\n\n"
					<< "                    (1) EASY\n\n"
					<< "                    (2) MEDIUM\n\n"
					<< "                    (3) HARD\n\n"
					<< "Enter 1, 2, or 3: ";
				std::cin >> menuChoice;
			}
			else
			{
				menuChoice = 0;
			}
			system("cls");
			// At this point, menuChoice values mean the following:
			//
			//      if = 0, then a 2-player game
			//
			//      if = 1, then a 1-player EASY game
			//      if = 2, then a 1-player MEDIUM game
			//      if = 3, then a 1-player HARD game

			switch (menuChoice)
			{
			case 0: playGame(0); break;
			case 1: playGame(1); break;
			case 2: playGame(2); break;
			case 3: playGame(3); break;
			default: break;
			}
		}
		else
		{
			menuChoice = 4;
		}
	} while (menuChoice != 4);

	system("cls");
	std::cout << "\n\n\n\n\n     Created by Chris Bryant.     CLB372@cornell.edu\n\n\n\n\n\n\n\n\n\n     OK to close window";
	std::cin.ignore(); std::cin.ignore();

	return 0;
}


void displayBoard(char cpyPiecesOnBoard[7][6])
{
	std::cout << "\n       1       2       3       4       5       6       7\n";
	std::cout << "   "; for(int i = 0; i < 57; i++) { std::cout << "_"; } std::cout << "\n";

	for (int j = 5; j >= 0; j--)
	{
		for (int i = 0; i < 3; i++)
		{
			if (i == 0)
			{
				std::cout << "   |       |       |       |       |       |       |       |\n";
			}
			else if (i == 2)
			{
				std::cout << "   |_______|_______|_______|_______|_______|_______|_______|\n";
			}
			else
			{
				// std::cout << " " << j+1 << " |   ";
				std::cout << "   |   ";

				for (int k = 0; k < 7; k++)
				{
					if (cpyPiecesOnBoard[k][j] == 'X')
					{
						std::cout << 'X';
					}
					else if (cpyPiecesOnBoard[k][j] == 'O')
					{
						std::cout << 'O';
					}
					else
					{
						std::cout << ' ';
					}
				
					if (k < 6)
					{
						std::cout << "   |   ";
					}
					else
					{
						// std::cout << "   | " << j+1 << "\n";
						std::cout << "   |  \n";
					}
				}

			}
		}
	}

	std::cout << "\n       1       2       3       4       5       6       7\n";
}



char winner(char cpyPiecesOnBoard[7][6])
// returns 'X' if player X has successfully conjoined 4
// returns 'O' if player O has successfully conjoined 4
// returns 'N' if there is no winner
{

	// check for horizontal wins
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cpyPiecesOnBoard[j][i] == cpyPiecesOnBoard[j+1][i]
				&& cpyPiecesOnBoard[j][i] == cpyPiecesOnBoard[j+2][i]
				&& cpyPiecesOnBoard[j][i] == cpyPiecesOnBoard[j+3][i])
			{
				if (cpyPiecesOnBoard[j][i] == 'X') { return 'X'; }
				else if (cpyPiecesOnBoard[j][i] == 'O') { return 'O'; }
			}
		}
	}

	// check for vertical wins
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (cpyPiecesOnBoard[i][j] == cpyPiecesOnBoard[i][j + 1]
				&& cpyPiecesOnBoard[i][j] == cpyPiecesOnBoard[i][j + 2]
				&& cpyPiecesOnBoard[i][j] == cpyPiecesOnBoard[i][j + 3])
			{
				if (cpyPiecesOnBoard[i][j] == 'X') { return 'X'; }
				else if (cpyPiecesOnBoard[i][j] == 'O') { return 'O'; }
			}
		}
	}

	// check for left-to-right, downward sloping diagonal wins
	for (int i = 3; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cpyPiecesOnBoard[j][i] == cpyPiecesOnBoard[j + 1][i - 1]
				&& cpyPiecesOnBoard[j][i] == cpyPiecesOnBoard[j + 2][i - 2]
				&& cpyPiecesOnBoard[j][i] == cpyPiecesOnBoard[j + 3][i - 3])
			{
				if (cpyPiecesOnBoard[j][i] == 'X') { return 'X'; }
				else if (cpyPiecesOnBoard[j][i] == 'O') { return 'O'; }
			}
		}
	}

	// check for left-to-right, upward sloping diagonal wins
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (cpyPiecesOnBoard[j][i] == cpyPiecesOnBoard[j + 1][i + 1]
				&& cpyPiecesOnBoard[j][i] == cpyPiecesOnBoard[j + 2][i + 2]
				&& cpyPiecesOnBoard[j][i] == cpyPiecesOnBoard[j + 3][i + 3])
			{
				if (cpyPiecesOnBoard[j][i] == 'X') { return 'X'; }
				else if (cpyPiecesOnBoard[j][i] == 'O') { return 'O'; }
			}
		}
	}

	return 'N';
}


int availableSquareInColumn(int colIndex, char cpyPiecesOnBoard[7][6])
// -- returns the vertical index corresponding to the vertical coordinate of the highest empty
//    square in column colIndex of the board cpyPiecesOnBoard
// -- returns the number 7 if the column is fully occupied
{
	for (int i = 0; i < 6; i++)
	{
		if (cpyPiecesOnBoard[colIndex][i] == 'E')
		{
			return i;
		}
	}
	return 7;
}


void playGame(int gameMode)
{
	char onePlayerIdentity;

	bool invalidInput;
	char playerTurn;
	int playerInput;
	int turnCount;
	char repeatGame;
	char gameWinner; // N if no winner, X if X won, O if O won
	char piecesOnBoard[7][6];
	int randNum;

	// -- outer loop contains variable initializations that are required for each game the users want to play
	// -- it also allows the users to play a new game after finishing one
	do
	{
		//1-PLAYER GAME: alert the users that the game is about to start and determine who goes 1st
		// if the user enters neither X nor O, loop until the user enters one of them
		if (gameMode != 0)
		{
			onePlayerIdentity = ' ';
			while (onePlayerIdentity != 'X' && onePlayerIdentity != 'O')
			{
				std::cout << "\n\n   X goes first.\n\n   O goes second.\n\n   Which would you like to be? [Enter X or O]\n\n";
				std::cin >> onePlayerIdentity;
				if (onePlayerIdentity == 'x') { onePlayerIdentity = 'X'; }
				if (onePlayerIdentity == 'o') { onePlayerIdentity = 'O'; }
				system("cls");
			}
		}

		// 2-PLAYER GAME: alert the users that the game is about to start
		else
		{
			std::cout << "\n\n   X goes first.\n\n   O goes second.\n\n   Press enter to begin game.\n\n";
			std::cin.ignore(); std::cin.ignore();
			system("cls");
		}


		// initialize variables
		playerTurn = 'X';
		turnCount = 0;
		gameWinner = 'N';

		// empty the game board
		for (int i = 0; i < 7; i++)
		{
			for(int j = 0; j < 6; j++)
			{
				piecesOnBoard[i][j] = 'E';
			}
		}

		// play the game! each iteration of this loop represents one player's turn
		do
		{
			// count the number of turns taken
			turnCount++;
			invalidInput = false;

			// FOR A HUMAN TAKING A TURN: display the current board to the users and ask for the next player to input his/her move
			if (gameMode == 0 || playerTurn == onePlayerIdentity)
			{
				displayBoard(piecesOnBoard);
				std::cout << "\n\n*** " << playerTurn << "'s TURN***\n\n"
					<< "Enter the column number of your desired drop.\n\n"
					<< "YOUR MOVE: ";
				std::cin >> playerInput;
				system("cls");

				// verify that the input is a number between 1 and 7
				if (!std::cin) // change non-numeric input to 0
				{
					std::cin.clear(); // reset failbit
					playerInput = 0;
				}
				if (playerInput < 1 || playerInput > 7)
				{
					invalidInput = true;
					std::cout << "\n\n     ERROR: Your input must be a number between 1 and 7, inclusive.\n\n";
				}


				// verify that the column is not yet full
				if (!invalidInput)
				{
					if (availableSquareInColumn(playerInput - 1, piecesOnBoard) == 7)
					{
						invalidInput = true;
						std::cout << "\n\n     ERROR: Column " << playerInput << " is already full.\n\n";
					}
				}
			}

			// FOR THE COMPUTER TAKING A TURN
			else
			{
				// if EASY mode, only do a smart move 25% of the time
				if (gameMode == 1)
				{
					randNum = rand() % 4; // a 1 in 4 chance
				}

				// if MEDIUM mode, do a smart move 2/3 of the time
				else if (gameMode == 2)
				{
					randNum = rand() % 100;
					if (randNum > 66)
					{
						randNum = 1;
					}
					else
					{
						randNum = 0;
					}
				}

				// if HARD mode, try to do smart moves all the time
				else
				{
					randNum = 1;
				}

					playerInput = 7;

					if (randNum == 1)
					{
						// add defensive moves here
						playerInput = getWin(onePlayerIdentity, piecesOnBoard);
						if (playerInput == 7) { playerInput = blockWin(onePlayerIdentity, piecesOnBoard); }
						if (playerInput == 7) { playerInput = block2and5(onePlayerIdentity, piecesOnBoard); }
						if (playerInput == 7) { playerInput = blockVertical(3, onePlayerIdentity, piecesOnBoard); }
						if (playerInput == 7) { playerInput = blockHorizontal(3, onePlayerIdentity, piecesOnBoard); }
						if (playerInput == 7) { playerInput = blockVertical(2, onePlayerIdentity, piecesOnBoard); }
						if (turnCount == 1) { playerInput = 3; } // if computer starts the game first, pick the middle column for the first move
					}

					// if none of the previous strategic/defensive plays yielded any useful plays,
					// pick a RANDOM move (particularly necessary for the first few moves of the game)
					if (playerInput == 7)
					{
						do
						{
							playerInput = rand() % 7;
						} while (availableSquareInColumn(playerInput, piecesOnBoard) > 6);
					}
				playerInput++;
			}



			if (invalidInput)
			{
				// skip the rest of the function if the input is invalid
				turnCount--;
				std::cout << "     Please try again. [Press enter]\n";
				std::cin.ignore();  std::cin.ignore();
			}
			else
			{

				// RECORD THE VALID MOVE INTO piecesOnBoard
				piecesOnBoard[playerInput-1][availableSquareInColumn(playerInput - 1, piecesOnBoard)] = playerTurn;


				// make it the next player's turn
				if (playerTurn == 'O') { playerTurn = 'X'; }
				else { playerTurn = 'O'; }

				// check to see whether someone has won
				gameWinner = winner(piecesOnBoard);

				// if someone has won, display the game board, notify users that the game is over, and offer the chance to replay
				if (gameWinner == 'X' || gameWinner == 'O' || turnCount == 42)
				{
					displayBoard(piecesOnBoard);
					std::cout << "\n***~~~***~~~***~~~*** ";
					if (gameWinner != 'X' && gameWinner != 'O') { std::cout << "DRAW: NO WINNER!"; }
					else
					{
						//2-player game win output
						if (gameMode == 0)
						{
							if (gameWinner == 'X') { std::cout << "WINNER: PLAYER X"; }
							else { std::cout << "WINNER PLAYER O"; }
						}
						else
						{
							if (gameWinner == onePlayerIdentity) { std::cout << "YOU WIN!!!"; }
							else { std::cout << "COMPUTER WINS"; }
						}
					}
					std::cout << " ***~~~***~~~***~~~***   " << turnCount << " turns taken\n\nPlay again? Enter Y or N: ";
					std::cin >> repeatGame;
					system("cls");
				}
			}

		} while (gameWinner != 'O' && gameWinner != 'X' && turnCount < 42);

	} while (repeatGame == 'Y' || repeatGame == 'y');
	std::cin.ignore();
}



int blockVertical(int x, char opponentIdentity, char cpyPiecesOnBoard[7][6])
// -- This function returns the column index of an available square that will
//    block an opponent's vertical stack. (A stack of length x)
//
// -- If blocking an opponent's vertical stack is not possible, the function
//    will return the number 7.
{
	bool rowFound = false;

	// i goes column by column
	for (int i = 0; i < 7; i++)
	{
		// j goes up, row by row, within column i
		for (int j = 0; j < 3; j++)
		{
			// now that we're at point (i,j), k extends up from this point to a length of x
			// and tests whether the squares all equal each other and are all occupied by the opponent
			rowFound = true;
			for (int k = 1; k < x; k++)
			{
				if (cpyPiecesOnBoard[i][j] != cpyPiecesOnBoard[i][j + k] || cpyPiecesOnBoard[i][j] != opponentIdentity)
				{
					rowFound = false;
				}
			}

			if (rowFound && availableSquareInColumn(i,cpyPiecesOnBoard) == j + x)
			{
				return i;
			}
		}
	}

	return 7;
}


int blockHorizontal(int x, char opponentIdentity, char cpyPiecesOnBoard[7][6])
// -- This function returns the column index of an available square that will
//    block an opponent's horizontal row of pieces. (A row of length x)
//
// -- If blocking an opponent's horizontal row is not possible, the function
//    will return the number 7.
{
	bool rowFound = false;
	int j_limit;
	switch (x)
	{
		case 2: j_limit = 6; break;
		case 3: j_limit = 5; break;
		default: j_limit = 7; break;
	}
	char theoreticalBoard[7][6];


	// i goes through the game board row by row
	for (int i = 0; i < 6; i++)
	{
		// j goes right, column by column, through row i
		for (int j = 0; j < j_limit; j++)
		{
			// now that we're at point (j,i), k extends rightward from this point to a length of x
			// and tests whether the squares all equal each other and are all occupied by the opponent
			rowFound = true;
			for (int k = 1; k < x; k++)
			{
				if (cpyPiecesOnBoard[j][i] != cpyPiecesOnBoard[j + k][i] || cpyPiecesOnBoard[j][i] != opponentIdentity)
				{
					rowFound = false;
				}
			}

			// if we've found a valid opponent row that could potentially be blocked...
			if (rowFound)
			{
				// if the row is at the extreme left of the game board, only test for
				// an available space to the right of the row
				if (j == 0)
				{
					if (availableSquareInColumn(j + x, cpyPiecesOnBoard) == i)
					{
						return j + x;
					}
				}

				// if the row is at the extreme right of the game board, only test for
				// an available space to the left of the row
				else if (j == j_limit - 1)
				{
					if (availableSquareInColumn(j - 1, cpyPiecesOnBoard) == i)
					{
						return j - 1;
					}
				}

				// if the row is neither at the extreme left nor extreme right of the game board,
				// FIRST test whether there's an available space to the left or right of it
				// that would make the opponent win if he/she moves there the next round -- if so, block that space.
				// If no such space exists, then SECOND, test for an available space immediately to the left and right 
				// of the row and block the row
				else
				{
					// copy the contents of cpyPiecesOnBoard to theoreticalBoard
					for (int a = 0; a < 7; a++) { for (int b = 0; b < 6; b++) { theoreticalBoard[a][b] = cpyPiecesOnBoard[a][b]; } }
					// test for a winning space to the left -- if it exists, move there
					if (availableSquareInColumn(j - 1, theoreticalBoard) == i)
					{
						theoreticalBoard[j - 1][i] = opponentIdentity;
						if (winner(theoreticalBoard))
						{
							return j - 1;
						}
					}

					// copy the contents of cpyPiecesOnBoard to theoreticalBoard
					for (int a = 0; a < 7; a++) { for (int b = 0; b < 6; b++) { theoreticalBoard[a][b] = cpyPiecesOnBoard[a][b]; } }
					// test for a winning space to the right -- if it exists, move there
					if (availableSquareInColumn(j + x, theoreticalBoard) == i)
					{
						theoreticalBoard[j + x][i] = opponentIdentity;
						if (winner(theoreticalBoard))
						{
							return j + x;
						}
					}
					

					if (rand() % 2 == 1)
					{
						if (availableSquareInColumn(j - 1, cpyPiecesOnBoard) == i)
						{
							// only move to the left of the opponent's row if it's not
							// a stupid move (i.e. don't "block" opponent's ability to
							// continue building his/her row when it's only possible for
							// the user to build out a 3-piece long row already
							if (j - 2 >= 0)
							{
								if (cpyPiecesOnBoard[j - 2][i] == opponentIdentity || availableSquareInColumn(j - 2, cpyPiecesOnBoard) == i)
								{
									return j - 1;
								}
							}
							else if (j + 3 <= 6)
							{
								if (cpyPiecesOnBoard[j + 3][i] != opponentIdentity && availableSquareInColumn(j + 3, cpyPiecesOnBoard) != i)
								{
									return j - 1;
								}
							}
						}
						else if(availableSquareInColumn(j+x,cpyPiecesOnBoard) == i)
						{
							// only move to the right of the opponent's row if it's not
							// a stupid move (i.e. don't "block" opponent's ability to
							// continue building his/her row when it's only possible for
							// the user to build out a 3-piece long row already
							if (j + x + 1 <= 6)
							{
								if (cpyPiecesOnBoard[j + x + 1][i] == opponentIdentity || availableSquareInColumn(j + x + 1, cpyPiecesOnBoard) == i)
								{
									return j + x;
								}
							}
							else if (j -2 >= 0)
							{
								if (cpyPiecesOnBoard[j - 2][i] != opponentIdentity && availableSquareInColumn(j - 2, cpyPiecesOnBoard) != i)
								{
									return j + x;
								}
							}
						}
					}
					else
					{
						if (availableSquareInColumn(j + x, cpyPiecesOnBoard) == i)
						{
							// only move to the right of the opponent's row if it's not
							// a stupid move (i.e. don't "block" opponent's ability to
							// continue building his/her row when it's only possible for
							// the user to build out a 3-piece long row already
							if (j + x + 1 <= 6)
							{
								if (cpyPiecesOnBoard[j + x + 1][i] == opponentIdentity || availableSquareInColumn(j + x + 1, cpyPiecesOnBoard) == i)
								{
									return j + x;
								}
							}
							else if (j - 2 >= 0)
							{
								if (cpyPiecesOnBoard[j - 2][i] != opponentIdentity && availableSquareInColumn(j - 2, cpyPiecesOnBoard) != i)
								{
									return j + x;
								}
							}
						}
						else if (availableSquareInColumn(j - 1, cpyPiecesOnBoard) == i)
						{
							// only move to the left of the opponent's row if it's not
							// a stupid move (i.e. don't "block" opponent's ability to
							// continue building his/her row when it's only possible for
							// the user to build out a 3-piece long row already
							if (j - 2 >= 0)
							{
								if (cpyPiecesOnBoard[j - 2][i] == opponentIdentity || availableSquareInColumn(j - 2, cpyPiecesOnBoard) == i)
								{
									return j - 1;
								}
							}
							else if (j + 3 <= 6)
							{
								if (cpyPiecesOnBoard[j + 3][i] != opponentIdentity && availableSquareInColumn(j + 3, cpyPiecesOnBoard) != i)
								{
									return j - 1;
								}
							}
						}
					}
				}
			}
		}
	}

	return 7;
}


int blockWin(char opponentIdentity, char cpyPiecesOnBoard[7][6])
// -- This function returns the column index of an available square that will
//    BLOCK an opponent's impending WIN. (A row of length x)
//
// -- If there is no immediate win to block, the function
//    will return the number 7.
{
	char theoreticalBoard[7][6];

	// test the board for a WIN that the COMPUTER can achieve RIGHT NOW -- if it's there, make that move!
	for (int i = 0; i < 7; i++)
	{
		// copy the real board to the theoreticalBoard
		for (int a = 0; a < 7; a++) { for (int b = 0; b < 6; b++) { theoreticalBoard[a][b] = cpyPiecesOnBoard[a][b]; } }

		// test each of the opponent's next possible moves for a WIN
		if (availableSquareInColumn(i, cpyPiecesOnBoard) != 7)
		{
			theoreticalBoard[i][availableSquareInColumn(i, cpyPiecesOnBoard)] = opponentIdentity;
			if (winner(theoreticalBoard) == opponentIdentity)
			{
				return i;
			}
		}
	}
	return 7;
}



int getWin(char opponentIdentity, char cpyPiecesOnBoard[7][6])
// -- This function returns the column index of an available square that will
//    WIN THE GAME for the computer.
//
// -- If there is no immediate win available, the function will return the number 7.
{
	char theoreticalBoard[7][6];
	char computerIdentity;
	if (opponentIdentity == 'X') { computerIdentity = 'O'; }
	else { computerIdentity = 'X'; }

	// test the board for a WIN that the COMPUTER can achieve RIGHT NOW -- if it's there, make that move!
	for (int i = 0; i < 7; i++)
	{
		// copy the real board to the theoreticalBoard
		for (int a = 0; a < 7; a++) { for (int b = 0; b < 6; b++) { theoreticalBoard[a][b] = cpyPiecesOnBoard[a][b]; } }

		// test each of the computer's next possible moves for a WIN
		if (availableSquareInColumn(i, cpyPiecesOnBoard) != 7)
		{
			theoreticalBoard[i][availableSquareInColumn(i, cpyPiecesOnBoard)] = computerIdentity;
			if (winner(theoreticalBoard) == computerIdentity)
			{
				return i;
			}
		}
	}
	return 7;
}


int block2and5(char opponentIdentity, char cpyPiecesOnBoard[7][6])
// -- This function detects a situation where 5 consecutive horizontal squares
//    are all either available or occupied by the opponent AND the opponent occupies
//    2 of those squares consecutively. It blocks the opponent from forming a
//    3-piece row in the next round with available squares on both the left and right
//    of it (which would thereby guarantee an easy victory for the opponent).
//    If this pattern is detected, this function has the computer fill one of the
//    empty squares out of the 5 and return the column index of the column in which
//    the computer will move.
// -- If this pattern does not exist in the board, this function will return 7.
{
	int countAvailable;
	int countOccupied;
	int indicesOfAvailableSquares[5];
	bool consecutiveOccupation;
	int randNum;

	// i goes row by row
	for (int i = 0; i < 6; i++)
	{
		// j goes rightward, column by column, within row i
		for (int j = 0; j < 3; j++)
		{
			// if the 5 squares from j to j+4 in row i have 2 consecuctive
			// squares occupied by the opponent, wih the other 3 available
			// for a move, move into one of the 3 available squares (on a
			// random basis)
			countAvailable = 0;
			countOccupied = 0;
			consecutiveOccupation = false;
			for (int a = 0; a < 5; a++) { indicesOfAvailableSquares[a] = 7; }
			for (int k = 0; k < 5; k++)
			{
				if (cpyPiecesOnBoard[j + k][i] == opponentIdentity)
				{
					countOccupied++;

					// if this is the 2nd opponent-occupied square in this set of 5 squares,
					// and if the previous square that was tested was the occupied square,
					// then the 2 occupied squares are CONSECUTIVE in this row
					if (countOccupied == 2)
					{
						if (cpyPiecesOnBoard[j + k - 1][i] == opponentIdentity)
						{
							consecutiveOccupation = true;
						}
					}
				}
				else if(availableSquareInColumn(j+k,cpyPiecesOnBoard) == i)
				{
					indicesOfAvailableSquares[countAvailable] = j + k;
					countAvailable++;
				}
			}

			// if all the criteria fit, then randomly move into one of the 3 available squares
			if (countOccupied == 2 && countAvailable == 3 && consecutiveOccupation)
			{
				randNum = rand() % 3;
				return indicesOfAvailableSquares[randNum];
			}

		}
	}
	return 7;
}