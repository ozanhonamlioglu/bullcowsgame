#include "FBullCowGame.h"

FBullCowGame::FBullCowGame()
{
    Reset();
}

FBullCowGame::~FBullCowGame()
{
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

int32 FBullCowGame::GetMaxTries() const
{
    TMap<int32, int32> WordLengthToMaxTries{{3, 5}, {4, 5}, {5, 5}, {6, 8}};
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    MyCurrentTry = 1;
    bGameIsWon = false;
    return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
    if (!IsIsogram(Guess))
    {
        return EGuessStatus::Not_Isogram;
    }
    else if (!IsLowerCase(Guess))
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
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
    // increment the return number
    MyCurrentTry++;

    // setup a return variable
    FBullCowCount BullCowCount;

    int32 WordLength = MyHiddenWord.length();
    for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
    {
        for (int32 GChar = 0; GChar < WordLength; GChar++)
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

    if (BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }

    // loop through all letters in the guess
    // compare letters against the hidden world
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
    // treat 0 or 1 letter words as isograms
    if (Word.length() <= 1)
    {
        return true;
    }

    TMap<char, bool> LetterSeen;
    for (auto Letter : Word)
    {
        Letter = tolower(Letter); // handle mixed case
        if (LetterSeen[Letter])
        {
            return false; // we dont have an isogram
        }
        else
        {
            LetterSeen[Letter] = true;
        }
    }

    return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
    for (auto Letter : Word)
    {
        if (!islower(Letter))
        {
            return false;
        }
    }

    return true;
}