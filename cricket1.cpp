#include <iostream>
#include <limits>
#include <list>
#include <stdlib.h>

using namespace std;

class Batting
{
private:
    string name, status;
    int score, numberOfFours, numberOfSixs, balls;

public:
    Batting()
    {
        name = "";
        score = 0;
        numberOfFours = 0;
        numberOfSixs = 0;
        balls = 0;
        status = "Not Out";
    }

    void addName(string inputName)
    {
        name = inputName;
    }

    int addRecord(string inputScore)
    {
        int runs = stoi(inputScore);
        if (runs == 4)
            numberOfFours++;
        if (runs == 6)
            numberOfSixs++;
        score += runs;
        balls++;
        return runs;
    }

    void changeStatus()
    {
        status = "Out";
        balls++;
    }

    void viewScoreCard(bool isOnGround)
    {
        if (isOnGround)
            cout << name << "*\t\t" << score << "\t" << numberOfFours << "\t" << numberOfSixs << "\t" << balls << endl;
        else
            cout << name << "\t\t" << score << "\t" << numberOfFours << "\t" << numberOfSixs << "\t" << balls << endl;
    }
};

class Team
{
public:
    int teamScore, teamWickets;

    Team()
    {
        teamScore = 0;
        teamWickets = 0;
    }

    bool isInList(string input, list<string> validList)
    {
        for (list<string>::iterator item = validList.begin(); item != validList.end(); item++)
        {
            if (input == *item)
                return true;
        }
        return false;
    }

    bool isValidScore(string inputScore)
    {
        list<string> validScore = {"W", "Wd", "1", "2", "3", "4", "6"};
        return isInList(inputScore, validScore);
    }

    void changeStrike(Batting **batsman, Batting **runner)
    {
        Batting *temp;
        temp = *batsman;
        *batsman = *runner;
        *runner = temp;
    }

    int teamRecord(int numberOfPlayers, int numberOfOvers, int target, int teamNumber)
    {
        Batting player[numberOfPlayers];
        cout << "Batting Order for team " << teamNumber << " :" << endl;
        for (int playerNumber = 0; playerNumber < numberOfPlayers; playerNumber++)
        {
            string inputName;
            cin >> inputName;
            player[playerNumber].addName(inputName);
        }
        Batting *batsman = &player[0], *runner = &player[1];
        int nextPlayerIndex = 2;
        float over = 0;
        while (over < numberOfOvers)
        {
            cout << "Over " << over + 1 << endl;
            int balls = 0;
            while (balls < 6)
            {
                if (teamWickets >= numberOfPlayers - 1 || teamScore > target)
                {
                    break;
                }
                string inputScore;
                cin >> inputScore;
                if (isValidScore(inputScore))
                {
                    if (inputScore == "Wd")
                    {
                        teamScore++;
                    }
                    else if (inputScore == "W")
                    {
                        teamWickets++;
                        batsman->changeStatus();
                        batsman = &player[nextPlayerIndex++];
                        balls++;
                    }
                    else
                    {
                        int runs = batsman->addRecord(inputScore);
                        if (runs % 2 != 0)
                        {
                            changeStrike(&batsman, &runner);
                        }
                        balls++;
                        teamScore += runs;
                    }
                }
                else
                {
                    cout << "Invalid entry" << endl;
                }
            }
            cout << "Scorecard for Team " << teamNumber << endl;
            cout << "Player Name\tScore\t4s\t6s\tBalls" << endl;
            for (int playerNumber = 0; playerNumber < numberOfPlayers; playerNumber++)
            {
                if (batsman == &player[playerNumber] || runner == &player[playerNumber])
                    player[playerNumber].viewScoreCard(true);
                else
                    player[playerNumber].viewScoreCard(false);
            }
            cout << "Total:" << teamScore << "/" << teamWickets << endl;
            if (balls == 6)
            {
                changeStrike(&batsman, &runner);
                over++;
                cout << "Overs: " << over << endl;
            }
            else
            {
                over += balls / 10.0;
                cout << "Overs: " << over << endl;
                break;
            }
        }
        return teamScore;
    }
};

int main()
{
    int numberOfPlayers, numberOfOvers;
    cout << "No. of players for each team:";
    cin >> numberOfPlayers;
    cout << "No. of overs:";
    cin >> numberOfOvers;
    Team team[2];
    int target = numeric_limits<int>::max();
    for (int teamNumber = 0; teamNumber < 2; teamNumber++)
    {
        target = team[teamNumber].teamRecord(numberOfPlayers, numberOfOvers, target, teamNumber + 1);
    }
    if (team[0].teamScore > team[1].teamScore)
    {
        cout << "Result : Team 1 won the match by " << team[0].teamScore - team[1].teamScore << " runs";
    }
    else
    {
        cout << "Result : Team 2 won the match by " << numberOfPlayers - team[1].teamWickets << " wickets";
    }
}