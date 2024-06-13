#include <iostream>
#include <vector>



using namespace std;

class Card {
    protected:
        int point;
        int warPoint;
    public:
        Card(int inPoint) {
            point = inPoint;
            warPoint = point;
        }
        void setPoint(int inPoint) {
            point = inPoint;
        }
        void setWarPoint(int inWarPoint) {
            warPoint = inWarPoint;
        }
        int getPoint() {
            return point;
        }
        int getWarPoint() {
            return warPoint;
        }
        void restartWarPoint() {
            warPoint = point;
        }
};

class PurpleCard : public Card {
    protected:
        string name;
        int priority;
    public:
        explicit PurpleCard(int inPoint, string inName, int inPriority) : Card(inPoint) {
                    name = inName;
                    priority = inPriority;
                 }
        void setName(int inName) {
            name = inName;
        }
        void setPriority(int inPriority) {
            priority = inPriority;
        }
        string getName() {
            return name;
        }
        int getPriority() {
            return priority;
        }
};

class Matarsag : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        int makeEffect(class Player p);


};

class Player {
private:
    int age;
    string name;
    string color;
    int signs = 5;
    bool isPassed = false;
    vector <int> yellowCards;


};

int Matarsag :: makeEffect(class Player p) {
    return 5;
}

class state {

private:
    string name;
    vector <int> PointsEarned;
    string whoCaptured = "none";
    vector <vector <int>> YellowCards;
    vector <Player> passedPlayers;
    bool warEnd = false;
};

int main()
{

    return 0;
}
