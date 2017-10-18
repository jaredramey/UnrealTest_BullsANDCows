/* This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic, see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

//Unreal's var for text interaction with user.
using FText = std::string;
//Unreal's var declaration for int
using int32 = int;


void PrintIntro();
FText GetValidGuess();
void PrintGuess(FText guess);
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary(EGameStatus endGameResults);

FBullCowGame BCGame; //Instantiate a new game

int main()
{
	bool bPlayGame = true;
	
	do {
		PrintIntro();
		PlayGame();
		//Once game has ended, tell the user if they won or lost.
		PrintGameSummary(BCGame.IsGameWon());
		bPlayGame = AskToPlayAgain();
	} while (bPlayGame  == true);
	//Repeat back to player

	return 0;
}

//Print the game introduction
void PrintIntro()
{
	std::cout << "             .=     ,      =. \n";
	std::cout << "     _  _   /'/   )\\,/,/(_ \\ \\    \n";
	std::cout << "      `//-.| ( ,\\\\)\\//\\)\\/_)  | \n";
	std::cout << "      //___\\ `\\\\\\/\\\\/\\/\\\\///' / \n";
	std::cout << "   , -'~`-._ `'--'_   `'''`  _ \\`''~-,_ \n";
	std::cout << "   \\       `-.  '_`.      .'_` \\ , -'~`/ \n";
	std::cout << "    `.__. - '`/ (-\\        /-) |-.__,' \n";
	std::cout << "       ||   |   \\O)   / ^\\ (O /  | \n";
	std::cout << "      `\\\\   |        /   `\\     / \n";
	std::cout << "        \\\\  \\       /      `\\  / \n";
	std::cout << "         `\\\\ `-.   /' .---.--.\\ \n";
	std::cout << "           `\\\\ / `~(, '()      (' \n";
	std::cout << "              (O) \\\\ _, . - ., _) \n";
	std::cout << "              \\\\ `\\'`          / \n";
	std::cout << "                     ''`''''~'` \n";
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game." << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << std::endl;

	return;
}

//Loop until user inputs a valid guess
FText GetValidGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	int32 MaxTries = BCGame.GetMaxTries();
	FText Guess = "";

	EGuessStatus Status = EGuessStatus::INVALID_STATUS;
	do
	{
		//Get guess
		std::cout << "Try " << CurrentTry << " of " << MaxTries <<". Enter your guess: ";
	
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::WRONG_LENGTH:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter your word in lowercase letters.\n\n";
			break;
		default:
			return Guess;
			break;
		}
	} while (Status != EGuessStatus::OK); //Keep looping until no errors

	return Guess;
}

//Print users guess
void PrintGuess(FText guess)
{
	std::cout << std::endl << "Your guess was: " << guess << "." << std::endl;
}

//Main game logic
void PlayGame()
{
	int32 MaxNumberOfTries = BCGame.GetMaxTries();

	while (BCGame.IsGameWon() != EGameStatus::GAME_WON && BCGame.IsGameWon() != EGameStatus::GAME_LOSS)
	{
		FText PlayerGuess = "";
		
		PlayerGuess = GetValidGuess();

		//Submit valid guess to the game, and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(PlayerGuess);

		PrintGuess(PlayerGuess);
		std::cout << "Bulls = "  << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}
}

//Ask if player wants to play again
bool AskToPlayAgain()
{
	FText Answer = "";

	std::cout << "Play again? (Y/N): ";
	std::getline(std::cin, Answer);
	std::cout << std::endl;

	if (Answer == "N" || Answer == "n")
	{
		return false;
	}
	else
	{
		return true;
	}
}

//Get end game status and output correct result text.
void PrintGameSummary(EGameStatus endGameResults)
{
	if (endGameResults == EGameStatus::GAME_LOSS)
	{
		std::cout << "Better luck next time!" << std::endl;
	}
	else if (endGameResults == EGameStatus::GAME_WON)
	{
		std::cout << "Congrats! You figured it out!" << std::endl;
	}
}