#include <iostream>
#include <string>
#include "FBullCowGame.h"

inline void PrintIntro();
void PlayGame();
FString GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game

int main(int32 argc, char const *argv[])
{
    bool bPlayAgain = false;
    do
    {
        PrintIntro();
        PlayGame();
        bPlayAgain = AskToPlayAgain();
    } while (bPlayAgain);

    return 0;
}

inline void PrintIntro()
{
    std::cout << "Welcome to Bulls and Cows, a fun word game." << std::endl;
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
    return;
}

void PlayGame()
{
    BCGame.Reset();
    int32 MaxTries = BCGame.GetMaxTries();

    // loop for the number of turns asking for guesses
    while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        FString Guess = GetValidGuess(); // TODO make loop checking valid

        // submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
    }

    // TODO summarise game
    PrintGameSummary();
    return;
}

// get a guess frıom the player
FString GetValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    FString Guess = "";
    do
    {
        int32 CurrentTry = BCGame.GetCurrentTry();
        // get a guess from the player
        std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
        std::cout << ". Enter your guess: ";
        getline(std::cin, Guess);

        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word without repeating letters.\n\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter all lower case letters.\n\n";
            break;
        default:
            // assume the guess is valid
            break;
        }
    } while (Status != EGuessStatus::OK);

    return Guess;
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again? ";
    FString Response = "";
    getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary()
{
    if (BCGame.IsGameWon())
    {
        std::cout << "WELL DONE - YOU WIN!\n\n";
    }
    else
    {
        std::cout << "better luck next time!\n\n";
    }
}