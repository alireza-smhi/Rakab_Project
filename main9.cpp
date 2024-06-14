#include <iostream>
#include <vector>
#include <string>
#include <typeinfo>




using namespace std;


class Card {
    protected:
        string name;
    public:
        Card(string inName) {
            name = inName;
        }
        void setName(string inName) {
            name = inName;
        }
        string getName() {
            return name;
        }
};

class YellowCard : public Card {
protected:
    int point;
public:
    YellowCard(string inName, int inPoint) : Card(inName) {
        point = inPoint;
    }
    void setPoint(int inPoint) {
        point = inPoint;
    }
    int getPoint() {
        return point;
    }
};

class PurpleCard : public Card {
    protected:
        int priority;
        int ownedBy;
    public:
        explicit PurpleCard(string name, int inOwnedBy, int inPriority) : Card(name) {
                    ownedBy = inOwnedBy;
                    priority = inPriority;
                 }
        void setPriority(int inPriority) {
            priority = inPriority;
        }
        int getPriority() {
            return priority;
        }

        virtual void makeEffect(class Player &p, vector <YellowCard> &playerCardsInWar, int &PointsEarned);

};

class Matarsag : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(class Player &p, vector <YellowCard> &playerCardsInWar, int &PointsEarned) override;
};

class ShirDokht : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(class Player &p, vector <YellowCard> &playerCardsInWar, int &PointsEarned) override;
};

class TablZan : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(class Player &p, vector <YellowCard> &playerCardsInWar, int &PointsEarned) override;
};





class Player {

private:
    int age;
    string name;
    string color;
    int signs = 5;
    bool isPassed = false;

public:
    vector <YellowCard> yellowCards;
    vector <PurpleCard*> purpleCards;

    vector <YellowCard> getYellowCards() {
        return yellowCards;
    }

    void setName(string a) {
        name = a;
    }
    string getName() {
        return name;
    }

    void setAge(int inAge) {
        age = inAge;
    }
    int getAge() {
        return age;
    }

    void showCards() {
        for (int i = 0; i < yellowCards.size(); i++) {
            cout << yellowCards[i].getName() << " ";
        }
        for (int i = 0; i < purpleCards.size(); i++) {
            cout << purpleCards[i] -> getName() << " ";
        }
    }

    void choosing(vector <YellowCard> &cardsInWar, vector <PurpleCard*> &purpleCardsInWar, vector <Player> &passedplayers) {
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

void  Matarsag :: makeEffect(class Player &p, vector <YellowCard> &playerCardsInWar, int &PointsEarned) {
    cout << "which card?" << endl;
    for (int i = 0; i < playerCardsInWar.size(); i++) {
    cout << playerCardsInWar[i].getPoint() << " ";
    }
    cout << endl;
    int input;
    cin >> input;
    for (int i = 0; i < playerCardsInWar.size(); i++) {
        if (input == playerCardsInWar[i].getPoint()) {
            p.yellowCards.push_back(playerCardsInWar[i]);
            playerCardsInWar.erase(playerCardsInWar.begin() + i);
            break;
        }
    }
}

void  ShirDokht :: makeEffect(class Player &p, vector <YellowCard> &playerCardsInWar, int &PointsEarned) {
    PointsEarned += 10;
}

void TablZan :: makeEffect(class Player &p, vector <YellowCard> &playerCardsInWar, int &PointsEarned) {
    PointsEarned *= 2;
}

/*
void Zemeston :: makeEffect(vector <YellowCard> &playerCardsInWar) {
    for (int i = 0; i < playerCardsInWar.size(); i++) {
        playerCardsInWar[i].setWarPoint(1);
    }
}
*/

class state {

private:
    string name;
    vector <int> pointsEarned;
    string whoCaptured = "none";
    vector <vector <YellowCard>> yellowCards;
    vector <PurpleCard*> purpleCards;
    vector <Player> passedPlayers;
    bool warEnd = false;
public:
    int chooseWhoStart(vector <Player> &p) {
        int minAge = p[0].getAge();
        for (int i = 0; i < p.size() - 1; i++) {
            if (p[i+1].getAge() < p[i].getAge()) {
                minAge = p[i+1].getAge();
            }
        }
        return minAge;
    }

    void game(vector <Player> &p) {
        int teenager = chooseWhoStart(p);
        while (!warEnd) {
            cout << p[teenager].getName() << ": ";
            p[teenager].showCards();
            p[teenager].choosing(yellowCards[teenager], purpleCards, passedPlayers);

        }
    }
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







        virtual void makeEffect(class Player &p, vector <YellowCard> &playerCardsInWar) {}
        virtual void makeEffect(int &PointsEarned) {}
        virtual void makeEffect(vector <Card> &playerCardsInWar) {}











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











/*
    vector <PurpleCard*> pc;
    pc.push_back(new Matarsag(10,  "un", 5));
    pc.push_back(new ShirDokht(8,  "unknown", 7));

    for (int i = 0; i < pc.size(); i++) {
        for (int j = 0; j < pc.size()-1; j++) {
            if (pc[j] -> getPriority() > pc[j] -> getPriority()) {}
        }
    }
*/



