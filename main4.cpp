#include <iostream>
#include <vector>
#include <typeinfo>




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
        virtual void makeEffect(class Player &p, vector <int> &playerCardsInWar) {
        }
};

class Matarsag : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(class Player &p, vector <int> &playerCardsInWar) override;
};

class ShirDokht : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        void makeEffect(class Player &p, vector <int> &playerCardsInWar) override {
            cout << "hi";
        }


};



class Player {
private:
    int age;
    string name;
    string color;
    int signs = 5;
    bool isPassed = false;
    vector <Card> yellowCards;
    vector <PurpleCard*> purpleCards;
public:
    vector getPurpleCards() {
        return yellowCards;
    }


};

void  Matarsag :: makeEffect(class Player &p, vector <int> &playerCardsInWar) {

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


    /*
    vector <PurpleCard*> pc;
    pc.push_back(new Matarsag(10,  "un", 5));
    pc.push_back(new ShirDokht(8,  "unknown", 7));
    pc[1] -> makeEffect();
    */


    /*
    Player p;
    p.purpleCards.push_back(new Matarsag(8, "matarsag", 0));
    p.purpleCards[0]->makeEffect();
    */


    //template <class T> class PurpleCard
