#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
    Reset();
}

FBullCowGame::~FBullCowGame()
{
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const
{
    return MyHiddenWord.length();
}

void FBullCowGame::Reset()
{
    constexpr int32 MAX_TRIES = 8;
    MyMaxTries = MAX_TRIES;

    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    return;
}

bool FBullCowGame::IsGameWon() const
{
    return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (false)
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (false)
    {
        return EGuessStatus::Not_Lowercase;
    }
    else if (Guess.length() != GetHiddenWordLength())
    {
        return EGuessStatus::Wrong_Length;
    }
    else
    {
        return EGuessStatus::OK;
    }
}

// receives a VALID guess, increments turns and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
    // increment th return number
    MyCurrentTry++;

    // setup a return variable
    FBullCowCount BullCowCount;

    int32 HiddenWordLength = MyHiddenWord.length();
    for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
    {
        for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
        {
            if (Guess[GChar] == MyHiddenWord[MHWChar])
            {
                if (MHWChar == GChar)
                {
                    BullCowCount.Bulls++;
                }
                else
                {
                    BullCowCount.Cows++;
                }
            }
        }
    }

    // loop through all letters in the guess
    // compare letters against the hidden world
    return BullCowCount;
}