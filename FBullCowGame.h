#pragma once
#ifndef FBULLCOWGAME_H
#define FBULLCOWGAME_H
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EGuessStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
};

class FBullCowGame
{
public:
    FBullCowGame();  // constructor
    ~FBullCowGame(); // destructor

    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    EGuessStatus CheckGuessValidity(FString) const;

    void Reset();
    FBullCowCount SubmitValidGuess(FString Guess);

private:
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bGameIsWon;

    bool IsIsogram(FString) const;
    bool IsLowerCase(FString) const;
};

#endif // FBULLCOWGAME_H;