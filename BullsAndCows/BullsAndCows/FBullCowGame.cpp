#pragma once
#include "FBullCowGame.h"
#include <map>
//Unreal's var declaration for std::map
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries()   const { return MyMaxTries;   }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const{ return MyHiddenWord.length(); }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "donkey";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGameStatus FBullCowGame::IsGameWon() const
{
	if (GetCurrentTry() >= GetMaxTries())
	{
		return EGameStatus::GAME_LOSS;
	}
	else if (bGameIsWon == true)
	{
		return::EGameStatus::GAME_WON;
	}
	else
	{
		return EGameStatus::GAME_CONTINUE;
	}
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString PlayerGuess) const
{
	//If the guess isn't an isogram
	if (!IsIsogram(PlayerGuess))
	{
		return EGuessStatus::NOT_ISOGRAM;
	}
	//If guess isn't all lowercase
	/*else if (!IsLowercase(PlayerGuess))
	{
		return EGuessStatus::NOT_LOWERCASE;
	}*/
	//If guess isn't the same length
	else if (PlayerGuess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::WRONG_LENGTH;
	}
	//If guess is correct.
	else
	{
		return EGuessStatus::OK;
	}
}

bool FBullCowGame::IsIsogram(FString playerGuess) const
{
	//Treat 0 & 1 letter words as isograms
	if (playerGuess.length() <= 1) { return true; }

	//Setup hash table
	TMap<char, bool> LetterSeen;

	//Loop through all letters of word
	for (auto Letter : playerGuess) //This loop means for each element in the string
	{
		Letter = tolower(Letter); //Change any character to lowercase in order to handle mixed words. (ex: hApPy -> happy)
		if (LetterSeen[Letter])
		{
			return false; //we don't have an isogram at this stage
		}
		else
		{
			//Add current letter to the map as seen
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString playerGuess) const
{
	//Loop through word
	for (auto Letter : playerGuess)
	{
		//If a letter is not lowercase return false
		if (Letter != islower(Letter)) { return false; }
	}

	//If all letters are lowercase then return true
	return true;
}

//Receives valid guess, increments turn, and returns count.
FBullCowCount FBullCowGame::SubmitValidGuess(FString PlayerGuess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 WordLength   = MyHiddenWord.length(); //Assuming same length as guess
	//Compare guess to hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		for (int32 PGChar = 0; PGChar < WordLength; PGChar++)
		{
			//If the letters match
			if (PlayerGuess[PGChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == PGChar) //If they're in the same place
				{
					BullCowCount.Bulls++; //Increment bulls
				}
				else
				{
					BullCowCount.Cows++; //Must be a cow
				}
			}
		}
	}

	//If there are the same amount of bulls as the word length then it must be the right word.
	if (BullCowCount.Bulls == GetHiddenWordLength())
	{
		bGameIsWon = true;
	}

	return BullCowCount;
}