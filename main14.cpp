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
    public:
        explicit PurpleCard(string inName, int inPriority) : Card(inName) {
                    priority = inPriority;
                 }
        void setPriority(int inPriority) {
            priority = inPriority;
        }
        int getPriority() {
            return priority;
        }

        virtual void makeEffect(class State &s, vector <class Player> &p, int turn) = 0;

};

class Matarsag : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(class State &s, vector <class Player> &p, int turn) override;
};

class ShirDokht : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(class State &s, vector <class Player> &p, int turn) override;
};

class TablZan : public PurpleCard {

    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(class State &s, vector <class Player> &p, int turn) override;
};


class Zemestoon : public PurpleCard {
    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(class State &s, vector <class Player> &p, int turn) override;
};

class Bahaar : public PurpleCard {
    public:
        using PurpleCard :: PurpleCard;
        void  makeEffect(class State &s, vector <class Player> &p, int turn) override;
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

    vector <PurpleCard*> getPurpleCards() {
        return purpleCards;
    }

    void setYellowCards(vector <YellowCard> in) {
        yellowCards = in;
    }

    void setPurpleCards(vector <PurpleCard*> in) {
        purpleCards = in;
    }

    void deleteYellowCard(int index) {
        yellowCards.erase(yellowCards.begin() + index);
    }

    void deletePurpleCard(int index) {
        purpleCards.erase(purpleCards.begin() + index);
    }

    void takeYellowCard(YellowCard y) {
        yellowCards.push_back(y);
    }

    void takePurpleCard(PurpleCard *p) {
        purpleCards.push_back(p);
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

    void setColor(string inColor) {
        color = inColor;
    }

    string getColor()   {
        return color;
    }

    void showCards() {
        for (int i = 0; i < yellowCards.size(); i++) {
            cout << yellowCards[i].getName() << " ";
        }
        for (int i = 0; i < purpleCards.size(); i++) {
            cout << purpleCards[i] -> getName() << " ";
        }
    }

    string choose() {
        string input;
        cin >> input;
        return input;
    }

};




class State {

private:
    string name;
    vector <int> pointsEarned;
    string whoCaptured = "none";
    vector <vector <YellowCard>> yellowCards;
    vector <vector <PurpleCard*>> purpleCards;
    vector <Player> passedPlayers;
    vector <PurpleCard*> removedPurpleCards;
    vector <YellowCard> removedYellowCards;
    PurpleCard *season = nullptr;
    bool warEnd = false;
public:
    State(string inName, int numberOfPlayers) {
        name = inName;
        pointsEarned.resize(numberOfPlayers);
        yellowCards.resize(numberOfPlayers);
        purpleCards.resize(numberOfPlayers);
    }

    void removePurpleCard(PurpleCard *p) {
        removedPurpleCards.push_back(p);
    }

    void removeYellowCard(YellowCard y) {
        removedYellowCards.push_back(y);
    }

    int chooseWhoStart(vector <Player> &p) {
        int minAge = p[0].getAge();
        for (int i = 0; i < p.size() - 1; i++) {
            if (p[i+1].getAge() < p[i].getAge()) {
                minAge = p[i+1].getAge();
            }
        }

        for (int i = 0; i < p.size(); i++) {
            if (p[i].getAge() == minAge)
                return i;
        }
    }

    void doWhatPlayerSaid(string command, vector <Player> &p, int turn) {
        for (int i = 0; i < p[turn].getYellowCards().size(); i++) {
            if (command == p[turn].getYellowCards()[i].getName()) {
                YellowCard desiredCard = p[turn].getYellowCards()[i];
                yellowCards[turn].push_back(desiredCard);
                p[turn].deleteYellowCard(i);
                return;
            }
        }
        for (int i = 0; i < p[turn].getPurpleCards().size(); i++) {
            if (command == p[turn].getPurpleCards()[i] -> getName()) {
                PurpleCard *desiredCard = p[turn].getPurpleCards()[i];
                if (desiredCard -> getPriority() == 0) {
                    desiredCard -> makeEffect(*this, p, turn);
                    p[turn].deletePurpleCard(i);
                }
                else if (desiredCard -> getName() == "bahaar" || desiredCard -> getName() == "zemestoon") {
                    if (season != nullptr) {
                        removePurpleCard(season);
                        season = desiredCard;
                    }
                    else {
                        season = desiredCard;
                    }
                }
                else {
                    purpleCards[turn].push_back(desiredCard);
                }
                p[turn].deletePurpleCard(i);
                delete desiredCard;
                return;
            }
        }
        if (command == "pass") {
            passedPlayers.push_back(p[turn]);
            return;
        }
    }

    void sortPurpleCardsPriority() {
        for (int k = 0; k < purpleCards.size(); k++) {
            for (int i = 0; i < purpleCards[k].size(); i++) {
                for (int j = 0; j < purpleCards[k].size()-1; j++) {
                    if (purpleCards[k][j] -> getPriority() > purpleCards[k][j+1] -> getPriority()) {
                        PurpleCard *temp = purpleCards[k][j];
                        purpleCards[k][j] = purpleCards[k][j+1];
                        purpleCards[k][j+1] = temp;
                        delete temp;
                    }
                }
            }
        }
    }


    void CalculatePoints(vector <Player> &p) {
        sortPurpleCardsPriority();
        for (int i = 0; i < pointsEarned.size(); i++) {
            for (int j = 0; j < yellowCards[i].size(); j++) {
                pointsEarned[i] += yellowCards[i][j].getPoint();
            }
            for (int j = 0; j < purpleCards[i].size(); j++) {
                purpleCards[i][j] -> makeEffect(p[i], yellowCards[i], pointsEarned[i]);
            }
            cout << p[i].getName() << "| final point: " << pointsEarned[i] << endl;
        }
    }

    int findMaxPoint() {
        int maxPoint = pointsEarned[0];
        for (int i = 0; i < pointsEarned.size()-1; i++) {
            if (pointsEarned[i] < pointsEarned[i+1]) {
                maxPoint = pointsEarned[i+1];
            }
        }
        return maxPoint;
    }

    void determineWinner() {
        int maxPoint = findMaxPoint();

    }

    void passPlayer(Player p) {
        bool flag = true;
        for (int i = 0; i < passedPlayers.size(); i++) {
            if (p.getColor() == passedPlayers[i].getColor()) {
                flag = false;
            }
        }
        if (flag) {
            passedPlayers.push_back(p);
        }
        cout << "--" << p.getName() << " passed" << "--" << endl;
    }

    void changeTurn(int &turn, vector <Player> &p) {
        bool flag = false;
        for (int k = 0; k < p.size(); k++) {
            turn++;
            flag = true;
            if (turn == p.size()) {
                turn = 0;
            }
            for (int i = 0; i < passedPlayers.size(); i++) {
                if (p[turn].getColor() == passedPlayers[i].getColor()) {
                    flag = false;
                }
            }
            if (flag) {
                break;
            }
        }
    }

    void showPlayerCardsInWar(int turn) {
        for (int i = 0; i < yellowCards[turn].size(); i++) {
            cout << yellowCards[turn][i].getName() << " ";
        }
        for (int i = 0; i < purpleCards[turn].size(); i++) {
            cout << purpleCards[turn][i] -> getName() << " ";
        }
    }

    void checkForPassPlayer(Player &p) {
            if (p.getYellowCards().size() == 0 && p.getPurpleCards().size() == 0) {
                passPlayer(p);
            }
    }

    void checkForEndWar(vector <Player> &p) {
        if (p.size() == passedPlayers.size()) {
            EndWar();
        }
    }

    void EndWar() {
        warEnd = true;
    }


    void war(vector <Player> &p) {
        int turn = chooseWhoStart(p);
        while (!warEnd) {
            cout << p[turn].getName() << ": ";
            p[turn].showCards();
            cout << endl;
            showPlayerCardsInWar(turn);
            cout << endl;
            doWhatPlayerSaid(p[turn].choose(), p[turn], turn);
            checkForPassPlayer(p[turn]);
            checkForEndWar(p);
            changeTurn(turn, p);
        }
        CalculatePoints(p);

    }
};





void  Matarsag :: makeEffect(class State &s, vector <class Player> &p, int turn) {
    cout << "which card?" << endl;
    for (int i = 0; i < playerCardsInWar.size(); i++) {
        cout << playerCardsInWar[i].getPoint() << " ";
    }
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

void ShirDokht :: makeEffect(class State &s, vector <class Player> &p, int turn) {
    PointsEarned += 10;
}

void TablZan :: makeEffect(class State &s, vector <class Player> &p, int turn) {
    PointsEarned *= 2;
}

void Bahaar :: makeEffect(class State &s, vector <class Player> &p, int turn) {

}




int main()
{

    Player p1;
    Player p2;

    p1.setName("p1");
    p1.setAge(10);
    p1.setColor("red");
    p2.setName("p2");
    p2.setAge(5);
    p2.setColor("blue");

    for (int i = 0; i < 2; i++) {
    YellowCard y("10", 10);
    p1.takeYellowCard(y);
    p2.takeYellowCard(y);
    }

    for (int i = 0; i < 1; i++) {
    p1.takePurpleCard(new Matarsag("matarsag", 0));
    p2.takePurpleCard(new Matarsag("matarsag", 0));
    }

    p1.takePurpleCard(new TablZan("tablzan", 3));
    p2.takePurpleCard(new ShirDokht("shirdokht", 5));

    vector <Player> ps;
    ps.push_back(p1);
    ps.push_back(p2);

    State s("deez", ps.size());
    s.war(ps);

    return 0;
}


    /*






    /*
    Player p;
    YellowCard y("10", 10);
    p.yellowCards.push_back(y);
    Matarsag m("matarsag", "red", 26);
    p.purpleCards.push_back(&m);
    p.showCards();
    */

/*
        if (m.getPriority() == 0) {
        cout << "yes";
    }


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











    p p1;
    p1.as.push_back(new a22());
    p1.as.push_back(new a1());
    p1.f() -> f();
    cout << endl;
    a *atemp = p1.f();

    if (atemp == a22) {
        cout << "yes";
    }






    class a {
public:
    virtual void f() {
        cout << "hi, im a";
    }
};

class a1 : public a {
public:
    void f() override {
        cout << "im a1";
    }
};

class a2 : public a {
public:
    void f() override {
        cout << "im a2";
    }
};

class a21 : public a2 {
public:
    void f() {
        cout << "im a21";
    }
};

class a22 : public a2 {
public:
    void f() {
        cout << "im a22";
    }
};

class p {
public:
    vector <a*> as;
    a* f() {
        return as[0];
    }
};














void choosing(vector <YellowCard> &cardsInWar, vector <PurpleCard*> &purpleCardsInWar, vector <Player> &passedplayers) {
        string input;
        cin >> input;
        for (int i = 0; i < yellowCards.size(); i++) {
            if (input == yellowCards[i].getName()) {
                cardsInWar.push_back(yellowCards[i]);
                yellowCards.erase(yellowCards.begin() + i);
                break;
            }
        }
        for (int i = 0; i < purpleCards.size(); i++) {
            if (input == purpleCards[i] -> getName()) {
                purpleCardsInWar.push_back(purpleCardsInWar[i]);
                purpleCards.erase(purpleCards.begin() + i);
                break;
            }
        }
        if (input == "pass") {
            passedplayers.push_back(*this);
        }
    }










    test* f() {
        return NULL;
    }

    if (f() == NULL) {
        cout << "yes";
    }



*/









/*
    Card* choose() {
        Card *temp;
        string input;
        cin >> input;
        for (int i = 0; i < yellowCards.size(); i++) {
            if (input == yellowCards[i].getName()) {
                temp = &yellowCards[i];
                yellowCards.erase(yellowCards.begin() + i);
                return temp;
            }
        }
        for (int i = 0; i < purpleCards.size(); i++) {
            if (input == purpleCards[i] -> getName()) {
                temp = purpleCards[i];
                purpleCards.erase(purpleCards.begin() + i);
                return temp;
            }
        }
        if (input == "pass") {
            delete temp;
            return NULL;
        }
    }



            Card *playerChoose = p[turn].choose();
            doPlayerChoosed(playerChoose);






    void doPlayerChoosed(Card *playerChoose, Player p, ) {

    }


*/



/*
void Zemeston :: makeEffect(vector <YellowCard> &playerCardsInWar) {
    for (int i = 0; i < playerCardsInWar.size(); i++) {
        playerCardsInWar[i].setWarPoint(1);
    }
}






































    void choosing(vector <YellowCard> &cardsInWar, vector <PurpleCard*> &purpleCardsInWar, vector <Player> &passedplayers) {
        string input;
        cin >> input;
        for (int i = 0; i < yellowCards.size(); i++) {
            if (input == yellowCards[i].getName()) {
                cardsInWar.push_back(yellowCards[i]);
                yellowCards.erase(yellowCards.begin() + i);
                break;
            }
        }
        for (int i = 0; i < purpleCards.size(); i++) {
            if (input == purpleCards[i] -> getName()) {
                purpleCardsInWar.push_back(purpleCards[i]);
                purpleCards.erase(purpleCards.begin() + i);
                break;
            }
        }
        if (input == "pass") {
            passedplayers.push_back(*this);
        }
    }







*/
