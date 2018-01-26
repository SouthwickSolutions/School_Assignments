#include "rps.h"
#include "rps.cpp"//cutout when compiling on the command line with g++
int main()
{
    int user_wins = 0;
    int user_losses = 0;
    int user_ties = 0;
    bool keepOnGoing = true;

    initializeRandomNumbers(); //only call once

    while(keepOnGoing){
        int userChoice = getUserPlayerChoice(std::cin, std::cout);
        int computerChoice = getRandomPlayerChoice();
        int winner = determineWinner(userChoice, computerChoice);
        displayMatchResults(std::cout, userChoice, computerChoice, winner);

        //calculate overall score
        if(winner == 11){ user_wins += 1; }
        else if(winner == 12){ user_losses += 1; }
        else if(winner == 13){ user_ties += 1; }

        displayStatistics(std::cout, user_wins, user_losses, user_ties);
        keepOnGoing = askUserIfGameShouldContinue(std::cin, std::cout);
    }

    return 0;
}
