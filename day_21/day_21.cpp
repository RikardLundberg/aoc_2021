#include <iostream>
#include <string>

using namespace std;

void parseInput();
int playGame();
int rollDie(int &dieVal);
int dieRollCount = 0;

int player1_pos = -1, player2_pos = -1;

int main()
{
    parseInput();
    int loserPoints = playGame();


    int output = dieRollCount * loserPoints;
    std::cout << "Result: " << output;
}

int playGame()
{
    int player1_pts = 0, player2_pts = 0;
    int dieVal = 0;
    bool player1sTurn = true;

    while (true)
    {

        int totalVal = 0;
        for (int i = 0; i < 3; i++)
            totalVal += rollDie(dieVal);

        if (player1sTurn) //should be player interface w/ players.. oh, wait no, I'm not Martin
        {
            player1_pos = (player1_pos + totalVal) % 10;
            if (player1_pos == 0) player1_pos = 10;
            player1_pts += player1_pos;
        }
        else
        {
            player2_pos = (player2_pos + totalVal) % 10;
            if (player2_pos == 0) player2_pos = 10;
            player2_pts += player2_pos;
        }
        player1sTurn = !player1sTurn;


        if (player1_pts >= 1000)
            return player2_pts;
        else if (player2_pts >= 1000)
            return player1_pts;
    }




}

int rollDie(int &dieVal)
{
    dieRollCount++;
    dieVal++;
    if (dieVal > 100)
        dieVal = 1;
    return dieVal;
}

void parseInput() 
{
    string input;
    int i = 0;

    while (cin >> input && input != "eof")
    {
        i++;
        if (i % 5 == 0)
        {
            if (player1_pos == -1)
                player1_pos = stoi(input);
            else
                player2_pos = stoi(input);
        }
    }
}