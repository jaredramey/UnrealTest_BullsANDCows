#pragma once
#pragma once
#include <string>

//Unreal's var for string manipulation.
using FString = std::string;
//Unreal's var declaration for int
using int32 = int;

//All values initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows  = 0;
};

enum class EGuessStatus
{
	INVALID_STATUS,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGTH,
	NOT_LOWERCASE
};

enum class EGameStatus
{
	GAME_WON,
	GAME_LOSS,
	GAME_CONTINUE
};

class FBullCowGame
{
public:
	FBullCowGame();

	int32  GetMaxTries()   const;
	int32  GetCurrentTry() const;
	int32  GetHiddenWordLength() const;
	EGameStatus   IsGameWon()    const;
	EGuessStatus  CheckGuessValidity(FString PlayerGuess) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString PlayerGuess);

private:
	//See constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bGameIsWon = false;
	bool IsIsogram(FString playerGuess) const;
	bool IsLowercase(FString playerGuess) const;
};

