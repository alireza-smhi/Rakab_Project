#include <iostream>
#include <vector>
#include <string>
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
        int ownedBy;
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
        virtual void makeEffect(class Player &p, vector <Card> &playerCardsInWar) {}
        virtual void makeEffect(int &PointsEarned) {}
        virtual void makeEffect(vector <Card> &playerCardsInWar) {}

};

class Matarsag : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(class Player &p, vector <Card> &playerCardsInWar) override;
};

class ShirDokht : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(int &PointsEarned) override;
};

class TablZan : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(int &PointsEarned) override;
};

class Zemeston : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(vector <Card> &playerCardsInWar) override;
};



class Player {

private:
    int age;
    string name;
    string color;
    int signs = 5;
    bool isPassed = false;

public:
    vector <Card> yellowCards;
    vector <PurpleCard*> purpleCards;

    vector <Card> getYellowCards() {
        return yellowCards;
    }

    void setN(string a) {
        name = a;
    }
    string getN() {
        return name;
    }

    void choosing(vector <Card> &cardsInWar, vector <PurpleCard*> &purpleCardsInWar, vector <Player> &passedplayers) {
        string input;
        cin >> input;
        for (int i = 0; i < yellowCards.size(); i++) {
            if (input == to_string(yellowCards[i].getPoint())) {
                cardsInWar.push_back(yellowCards[i]);
                yellowCards.erase(yellowCards.begin() + i);
            }
        }
        for (int i = 0; i < purpleCards.size(); i++) {
            if (input == purpleCards[i] -> getName()) {
                purpleCardsInWar.push_back(purpleCardsInWar[i]);
                purpleCards.erase(purpleCards.begin() + i);
            }
        }
        if (input == "pass") {
            passedplayers.push_back(*this);
        }
    }
};

void  Matarsag :: makeEffect(class Player &p, vector <Card> &playerCardsInWar) {
    cout << "which card?" << endl;
    for (int i = 0; i < playerCardsInWar.size(); i++) {
    cout << playerCardsInWar[i].getPoint() << " ";
    }
    cout << endl;
    int input;
    cin >> input;
    for (int i = 0; i < playerCardsInWar.size(); i++) {
        if (input == playerCardsInWar[i].getPoint()) {
            p.yellowCards.push_back(playerCardsInWar[i].getPoint());
            playerCardsInWar.erase(playerCardsInWar.begin() + i);
            break;
        }
    }
}

void  ShirDokht :: makeEffect(int &playerPoint) {
    playerPoint += 10;
}

void TablZan :: makeEffect(int &playerPoint) {
    playerPoint *= 2;
}


void Zemeston :: makeEffect(vector <Card> &playerCardsInWar) {
    for (int i = 0; i < playerCardsInWar.size(); i++) {
        playerCardsInWar[i].setWarPoint(1);
    }
}


class state {

private:
    string name;
    vector <int> pointsEarned;
    string whoCaptured = "none";
    vector <vector <Card>> YellowCards;
    vector <PurpleCard*> purpleCards;
    vector <Player> passedPlayers;
    bool warEnd = false;
public:
    void game(vector <Player> &p) {
        while (!warEnd) {



        }
    }
};




int main()
{

    vector <PurpleCard*> pc;
    pc.push_back(new Matarsag(10,  "un", 5));
    pc.push_back(new ShirDokht(8,  "unknown", 7));

    for (int i = 0; i < pc.size(); i++) {
        for (int j = 0; j < pc.size()-1; j++) {
            if (pc[j] -> getPriority() > pc[j] -> getPriority()) {}
        }
    }



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


    /*
    void tester(int &a) {
    a++;
    }
    vector <int> test = {1, 2, 3};
    tester(test[0]);
    cout << test[0];
    cout << test[1];
    cout << test[2];
    */


        /*
    vector <Player> ps;
    vector <Card> cardsInWar;
    vector <PurpleCard*> purpleCardsInWar;
    Player p1;
    p1.setN("haya");
    p1.choosing(cardsInWar, purpleCardsInWar, ps);
    Player p2;
    p2.setN("deeeeeeeeeeeez");
    p2.choosing(cardsInWar, purpleCardsInWar, ps);
    cout << ps.size() << endl;
    cout << ps[0].getN();
    */
