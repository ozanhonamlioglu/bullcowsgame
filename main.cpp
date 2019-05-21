#include <iostream>
#include "FBullCowGame.h"

inline void PrintIntro();
void PlayGame();
FString GetValidGuess();
bool AskToPlayAgain();
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
    for (int32 count = 1; count <= MaxTries; count++)
    {
        FString Guess = GetValidGuess(); // TODO make loop checking valid

        // submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);

        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
        std::cout << "Your guess was: " << Guess << std::endl;
    }

    // TODO summarise game

    std::cout << "\n\n";
}

// get a guess frıom the player
FString GetValidGuess()
{
    EGuessStatus Status = EGuessStatus::Invalid_Status;
    do
    {
        int32 CurrentTry = BCGame.GetCurrentTry();
        // get a guess from the player
        std::cout << "Try " << CurrentTry << ". Enter your guess: ";
        FString Guess = "";
        getline(std::cin, Guess);

        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
        case EGuessStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
            break;
        case EGuessStatus::Not_Isogram:
            std::cout << "Please enter a word without repeating letters.\n";
            break;
        case EGuessStatus::Not_Lowercase:
            std::cout << "Please enter all lower case letters.\n";
            break;
        default:
            return Guess;
        }
        std::cout << std::endl;
    } while (Status != EGuessStatus::OK);
}

bool AskToPlayAgain()
{
    std::cout << "Do you want to play again? ";
    FString Response = "";
    getline(std::cin, Response);
    return (Response[0] == 'y') || (Response[0] == 'Y');
}