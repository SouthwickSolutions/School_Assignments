#include "rps.h"
//#include "rps.cpp" //get rid when compiling on the command line with g++

//This function must initialize the pseudo-random
//number system using the current time
void initializeRandomNumbers(){
    //get a seed
    int seed = std::time(0);

    //apply the seed
    std::srand(seed);
}

//This function must return a randomly selected
//integer. 1 == ROCK, 2 == PAPER, 3 == SCISSORS
int getRandomPlayerChoice( ){
    int how_many = 3;
    int smallest = 1;
    int r;

    r = std::rand();
    r = r % how_many; //to make random number 1-3
    r += smallest; //to make it 1-3 instead of 0-2

    return r;
}

//This function must prompt the user for a choice
//between rock, paper and scissors. The user must
//type one of those strings. The function will then
//return an integer that corresponds to the user’s
//choice, using the same system as the previous
//function. If the user gives any response other
//than the 3 acceptable options, the user must be
//prompted again, until a valid choice is selected.
//The function must read from input_stream and write
//to output_stream for communication with the user.
int getUserPlayerChoice( std::istream& input_stream, std::ostream& output_stream ){
    std::string str;
    int rValue;

    std::cout << "Enter your choice (rock, paper, scissors): ";
    while(input_stream >> str){
        output_stream << std::endl;
        if(str == "rock" || str == "paper" || str == "scissors"){
            break;
        }else{
            std::cout << "Please enter an acceptable input: ";
            continue;
        }
    }
    if(str == "rock"){ rValue = 1; }
    else if(str == "paper"){ rValue = 2; }
    else if(str == "scissors"){ rValue = 3;}

    return rValue;
}

//This function will return an integer 11 == USER,
//12 == RANDOM_PLAYER, 13 == TIE for which player
//won the match. user_choice and random_choice are
//values as described in getRandomPlayerChoice( )
int determineWinner(int user_choice, int random_choice){
    int rValue;

    if(user_choice == 1 && random_choice == 1){ rValue = 13; }
    else if(user_choice == 1 && random_choice == 2){ rValue = 12; }
    else if(user_choice == 1 && random_choice == 3){ rValue = 11; }
    else if(user_choice == 2 && random_choice == 1){ rValue = 11; }
    else if(user_choice == 2 && random_choice == 2){ rValue = 13; }
    else if(user_choice == 2 && random_choice == 3){ rValue = 12; }
    else if(user_choice == 3 && random_choice == 1){ rValue = 12; }
    else if(user_choice == 3 && random_choice == 2){ rValue = 11; }
    else if(user_choice == 3 && random_choice == 3){ rValue = 13; }

    return rValue;
}

//This function must display a message to
//output_stream that contains information on what
//the user’s choice was, what the random player’s
//choice was and who won
void displayMatchResults(std::ostream& output_stream, int user_choice, int random_choice, int winner){

    output_stream << std::endl;

    if(user_choice == 1){output_stream << "You chose rock and "; }
    else if(user_choice == 2){output_stream << "You chose paper and "; }
    else if(user_choice == 3){output_stream << "You chose scissors and "; }

    if(random_choice == 1){output_stream << "computer chose rock."; }
    else if(random_choice == 2){output_stream << "computer chose paper."; }
    else if(random_choice == 3){output_stream <<"computer chose scissors."; }

    output_stream << std::endl;

    if(winner == 11){output_stream << std::endl << "YOU WIN!"; }
    if(winner == 12){output_stream << std::endl << "Computer wins..."; }
    if(winner == 13){output_stream << std::endl << "Tie. You should play again."; }

    output_stream << std::endl;
}

//This function must display a message to
//output_stream that contains information on how
//many matches the user has won, lost and tied
void displayStatistics(std::ostream& output_stream, int number_user_wins, int number_user_losses, int number_user_ties){

    output_stream << std::endl;
    output_stream << "Wins: " << number_user_wins << " ... Losses: " << number_user_losses << " ... Ties: " << number_user_ties;
    output_stream << std::endl;
    output_stream << std::endl;
}

//This function must display a prompt to the
//output_stream asking if the user would like to
//continue. This function must read from the
//input_stream. If the word read begins with a y or
//a Y, then the function must return true.
//Any other input should cause the function to
//return false
bool askUserIfGameShouldContinue(std::istream& input_stream, std::ostream& output_stream){
    bool rValue;
    char ch;

    output_stream << "Would you like to play again (yes/no)?";
    input_stream >> ch;
    if(ch == 'y' || ch == 'Y'){ rValue = true; }
    else{ rValue == false;}

    input_stream.ignore(100, '\n');

    return rValue;
}
