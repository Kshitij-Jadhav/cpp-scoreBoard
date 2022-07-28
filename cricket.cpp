#include <iostream>

using namespace std;

class Batting {
private:
    string name;
    int score, numberOfFours, numberOfSixs, balls;
public:
    Batting() {
        name = "";
        score = 0;
        numberOfFours = 0;
        numberOfSixs = 0;
        balls = 0;
    }

    void addName(string inputName) {
        name = inputName;
    }
    int addScore(string inputScore) {
        if (inputScore == "Wd") {
            return 5;
        }
        else if (inputScore == "W") {
            balls++;
            return 7;
        }
        else {
            int runs = stoi(inputScore);
            if (runs >= 0 && runs <= 6 && runs != 5){
                if (runs == 4){
                    numberOfFours++;
                }
                if (runs == 6) {
                    numberOfSixs++;
                }
                score += runs;
                balls++;
                return runs;
            }
            else {
                return 15;
            }
        }
    }
    void viewScoreCard() {
        cout << name << "\t\t" << score << "\t" << numberOfFours << "\t" << numberOfSixs << "\t" << balls << endl; 
    }
};
int main() {
    int numberOfPlayers, numberOfOvers, teamScore[2] = {0, 0}, teamWickets[2] ={0, 0}; 
    cout << "No. of players for each team:";
    cin >> numberOfPlayers;
    cout << "No. of overs:";
    cin >> numberOfOvers;
    for (int team = 1; team <= 2; team++){
        Batting player[numberOfPlayers];
        cout << "Batting Order for team"<< team << ":" << endl;
        for (int playerNumber = 0; playerNumber < numberOfPlayers; playerNumber++) {
            string inputName;
            cin >>inputName;
            player[playerNumber].addName(inputName);
        }
        Batting *batsman = &player[0], *runner = &player[1];
        int nextPlayerIndex = 2;
        float over = 0;
        while (over < numberOfOvers) {
            cout << "Over" << over+1 << endl;
            int b = 0;
            while (b < 6) {
                if (teamWickets[team - 1] >= numberOfPlayers - 1) {
                    break;
                }
                if (teamScore[1] > teamScore[0]){
                    break;
                }
                string inputScore;
                cin >> inputScore;
                int c = batsman->addScore(inputScore);
                if (c == 5){
                    teamScore[team - 1]++;
                }
                else if (c == 7){
                    teamWickets[team - 1]++;
                    batsman = &player[nextPlayerIndex++];
                    b++;
                }
                else if(c == 15) {
                    cout << "Invalid Score" << endl;
                }
                else {
                    teamScore[team - 1] += c;
                    b++;
                    if (c % 2 != 0){
                        Batting *temp;
                        temp = batsman;
                        batsman = runner;
                        runner = temp;  
                    }
                }
            }
            cout << "Scorecard for Team " << team << endl;
            cout << "Player Name\tScore\t4s\t6s\tBalls" << endl;
            for (int playerNumber = 0; playerNumber < numberOfPlayers; playerNumber++) {
                player[playerNumber].viewScoreCard();
            }
            cout << "Total:" << teamScore[team - 1] << "/" << teamWickets[team - 1] << endl;
            if(b == 6) {
                Batting *temp;
                temp = batsman;
                batsman = runner;
                runner = temp;
                over++;
                cout << "Overs: " << over << endl;
            }
            else {
                over += b/10.0;
                cout << "Overs: " << over << endl;
                break;
            }
        }
    }
    if (teamScore[0] > teamScore [1]){
        cout << "Team 1 won the match by " <<teamScore[0] - teamScore[1] <<" runs";
    }
    else {
        cout << "Team 2 won the match by " << numberOfPlayers - teamWickets[1] << " wickets";
    }
}