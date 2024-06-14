#include <iostream>
#include <vector>
#include <conio.h>
#include <string>
#include <typeinfo>
#include <cstdlib>
#include <time.h>




using namespace std;

class Sign {
protected:
    string color;
public:
    Sign(string inColor) {
        setColor(inColor);
    }
    void setColor(string inColor) {
        color = inColor;
    }
    string getColor() {
        return color;
    }
};


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
        Matarsag() : PurpleCard("matarsag", 0) {}
        //using PurpleCard :: PurpleCard;
        void  makeEffect(class State &s, vector <class Player> &p, int turn) override;
};

class ShirDokht : public PurpleCard {

    public:
        ShirDokht() : PurpleCard("shirdokht", 5) {}
        //using PurpleCard :: PurpleCard;
        void  makeEffect(class State &s, vector <class Player> &p, int turn) override;
};

class TablZan : public PurpleCard {

    public:
        TablZan() : PurpleCard("tablzan", 3) {}
        //using PurpleCard :: PurpleCard;
        void  makeEffect(class State &s, vector <class Player> &p, int turn) override;
};


class Zemestoon : public PurpleCard {
    public:
        Zemestoon() : PurpleCard("zemestoon", 2) {}
        //using PurpleCard :: PurpleCard;
        void  makeEffect(class State &s, vector <class Player> &p, int turn) override;
};

class Bahaar : public PurpleCard {
    public:
        Bahaar() : PurpleCard("bahaar", 4) {}
        //using PurpleCard :: PurpleCard;
        void  makeEffect(class State &s, vector <class Player> &p, int turn) override;
};



class Player {

private:
    int age;
    string name;
    Sign *sign;
    int numberOfSigns = 5;
    vector <YellowCard> yellowCards;
    vector <PurpleCard*> purpleCards;
public:
    Player(string inName, int inAge) {
        setName(inName);
        setAge(inAge);
    }
    vector <YellowCard> getYellowCards() {
        return yellowCards;
    }
    //------------------------------------------------------------------------------------------------------
    vector <PurpleCard*> getPurpleCards() {
        return purpleCards;
    }
    //------------------------------------------------------------------------------------------------------
    void setYellowCards(vector <YellowCard> in) {
        yellowCards = in;
    }
    //------------------------------------------------------------------------------------------------------
    void setPurpleCards(vector <PurpleCard*> in) {
        purpleCards = in;
    }
    //------------------------------------------------------------------------------------------------------
    void deleteYellowCard(int index) {
        yellowCards.erase(yellowCards.begin() + index);
    }
    //------------------------------------------------------------------------------------------------------
    void deletePurpleCard(int index) {
        purpleCards.erase(purpleCards.begin() + index);
    }
    //------------------------------------------------------------------------------------------------------
    void takeYellowCard(YellowCard y) {
        yellowCards.push_back(y);
    }
    //------------------------------------------------------------------------------------------------------
    YellowCard giveYellowCard(int index) {
        YellowCard Ytemp = yellowCards[index];
        deleteYellowCard(index);
        return Ytemp;
    }
    //------------------------------------------------------------------------------------------------------
    PurpleCard* givePurpleCard(int index) {
        PurpleCard *Ptemp = purpleCards[index];
        deletePurpleCard(index);
        return Ptemp;
    }
    //------------------------------------------------------------------------------------------------------
    void takePurpleCard(PurpleCard *p) {
        purpleCards.push_back(p);
    }
    //------------------------------------------------------------------------------------------------------
    void setName(string a) {
        name = a;
    }
    //------------------------------------------------------------------------------------------------------
    string getName() {
        return name;
    }
    //------------------------------------------------------------------------------------------------------
    void setSign(Sign inSign) {
        sign = &inSign;
    }
    //------------------------------------------------------------------------------------------------------
    Sign getSign() {
        return *sign;
    }
    //------------------------------------------------------------------------------------------------------
    void setAge(int inAge) {
        age = inAge;
    }
    //------------------------------------------------------------------------------------------------------
    int getAge() {
        return age;
    }
    //------------------------------------------------------------------------------------------------------
    void setNumberOfSigns(int inNumberOfSigns) {
        numberOfSigns = inNumberOfSigns;
    }
    //------------------------------------------------------------------------------------------------------
    int getNumberOfSigns() {
        return numberOfSigns;
    }
    //------------------------------------------------------------------------------------------------------
    void showCards() {
        for (int i = 0; i < yellowCards.size(); i++) {
            cout << yellowCards[i].getName() << " ";
        }
        for (int i = 0; i < purpleCards.size(); i++) {
            cout << purpleCards[i] -> getName() << " ";
        }
    }
    //------------------------------------------------------------------------------------------------------
    string choose() {
        string input;
        getline(cin, input);
        return input;
    }

};




class State {

private:
    string name;
    vector <int> pointsEarned;
    vector <vector <YellowCard>> yellowCards;
    vector <vector <PurpleCard*>> purpleCards;
    vector <PurpleCard*> allPurpleCards;
    vector <Player> passedPlayers;
    vector <PurpleCard*> removedPurpleCards;
    vector <YellowCard> removedYellowCards;
    PurpleCard *season = nullptr;
    Sign *whoCaptured = nullptr;
    bool warEnd = false;
public:
    State(string inName, int numberOfPlayers) {
        name = inName;
        pointsEarned.resize(numberOfPlayers);
        yellowCards.resize(numberOfPlayers);
        purpleCards.resize(numberOfPlayers);
    }
    //------------------------------------------------------------------------------------------------------
    vector <YellowCard> getPlayerYellowCardsInWar(int index) {
        return  yellowCards[index];
    }
    //------------------------------------------------------------------------------------------------------
    vector <PurpleCard*> getPlayerPurpleCardsInWar(int index) {
        return  purpleCards[index];
    }
    //------------------------------------------------------------------------------------------------------
    YellowCard giveYellowCard(int turn, int i) {
        YellowCard Ytemp = yellowCards[turn][i];
        yellowCards[turn].erase(yellowCards[turn].begin() + i);
        return Ytemp;
    }
    //------------------------------------------------------------------------------------------------------
    PurpleCard* givePurpleCard(int turn, int i) {
        PurpleCard *Ptemp = purpleCards[turn][i];
        purpleCards[turn].erase(purpleCards[turn].begin() + i);
        return Ptemp;
    }
    //------------------------------------------------------------------------------------------------------
    void removePurpleCard(PurpleCard *p) {
        removedPurpleCards.push_back(p);
    }
    //------------------------------------------------------------------------------------------------------
    void removeYellowCard(YellowCard y) {
        removedYellowCards.push_back(y);
    }
    //------------------------------------------------------------------------------------------------------
    void deleteYellowCard(int turn, int i) {
        yellowCards[turn].erase(yellowCards[turn].begin() + i);
    }
    //------------------------------------------------------------------------------------------------------
    void deletePurpleCard(int turn, int i) {
        purpleCards[turn].erase(purpleCards[turn].begin() + i);
    }
    //------------------------------------------------------------------------------------------------------
    void transferYCtoRemove(YellowCard y, int turn, int i) {
        removeYellowCard(y);
        deleteYellowCard(turn , i);
    }
    //------------------------------------------------------------------------------------------------------
    void transferPCtoRemove(PurpleCard *p, int turn, int i) {
        removePurpleCard(p);
        deletePurpleCard(turn, i);
    }
    //------------------------------------------------------------------------------------------------------
    void increasePlayerPoint(int turn, int amount) {
        pointsEarned[turn] += amount;
    }
    //------------------------------------------------------------------------------------------------------
    int getPlayerPointEraned(int turn) {
        return pointsEarned[turn];
    }
    //------------------------------------------------------------------------------------------------------
    void setPlayerPoint(int turn, int amount) {
        pointsEarned[turn] = amount;
    }
    //------------------------------------------------------------------------------------------------------
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
    //------------------------------------------------------------------------------------------------------
    void showMatarsagGuide() {
        cout << "matarsag: You can return one of your played yellow cards" << endl;
    }
    //------------------------------------------------------------------------------------------------------
    void showTablzanGuide() {
        cout << "tablzan: The numerical value of the soldier cards (yellow) of the player is doubled " << endl << "Just one card The drummer affects the player's cards more than a drummer card It does not affect the player's cards." << endl;
    }
    //------------------------------------------------------------------------------------------------------
    void showShirdokhtGuide() {
        cout << "shirdokht: It adds 10 points to the strength of the army and no card affects it" << endl;
    }
    //------------------------------------------------------------------------------------------------------
    void showBahaarGuide() {
        cout << "bahaar: It adds 3 points to the strength of the army of the player" << endl << " who played the highest numerical value of the yellow card" << endl;
    }
    //------------------------------------------------------------------------------------------------------
    void showZemestoonGuide() {
        cout << "zemestoon:The value of all yellow cards played becomes 1" << endl;
    }
    //------------------------------------------------------------------------------------------------------
    void showGuide() {
        showMatarsagGuide();
        showTablzanGuide();
        showShirdokhtGuide();
        showBahaarGuide();
        showZemestoonGuide();
    }
    //------------------------------------------------------------------------------------------------------
    void doWhatPlayerSaid(string command, vector <Player> &p, int turn) {
        if (command == "pass") {
            passPlayer(p[turn]);
            return;
        }
        if (command == "help") {
            system("cls");
            showGuide();
            getch();
            system("cls");
            cout << p[turn].getName() << ": ";
            p[turn].showCards();
            cout << endl;
            showPlayerAllCardsInWar(turn);
            doWhatPlayerSaid(p[turn].choose(), p, turn);
            return;
        }
        if (command == "help matarsag") {
            system("cls");
            showMatarsagGuide();
            getch();
            system("cls");
            cout << p[turn].getName() << ": ";
            p[turn].showCards();
            cout << endl;
            showPlayerAllCardsInWar(turn);
            doWhatPlayerSaid(p[turn].choose(), p, turn);
            return;
        }
        if (command == "help tablzan") {
            system("cls");
            showTablzanGuide();
            getch();
            system("cls");
            cout << p[turn].getName() << ": ";
            p[turn].showCards();
            cout << endl;
            showPlayerAllCardsInWar(turn);
            doWhatPlayerSaid(p[turn].choose(), p, turn);
            return;
        }
        if (command == "help shirdokht") {
            system("cls");
            showShirdokhtGuide();
            getch();
            system("cls");
            cout << p[turn].getName() << ": ";
            p[turn].showCards();
            cout << endl;
            showPlayerAllCardsInWar(turn);
            doWhatPlayerSaid(p[turn].choose(), p, turn);
            return;
        }
        if (command == "help bahaar") {
            system("cls");
            showBahaarGuide();
            getch();
            system("cls");
            cout << p[turn].getName() << ": ";
            p[turn].showCards();
            cout << endl;
            showPlayerAllCardsInWar(turn);
            doWhatPlayerSaid(p[turn].choose(), p, turn);
            return;
        }
        if (command == "help zemestoon") {
            system("cls");
            showZemestoonGuide();
            getch();
            system("cls");
            cout << p[turn].getName() << ": ";
            p[turn].showCards();
            cout << endl;
            showPlayerAllCardsInWar(turn);
            doWhatPlayerSaid(p[turn].choose(), p, turn);
            return;
        }
        for (int i = 0; i < p[turn].getYellowCards().size(); i++) {
            if (command == p[turn].getYellowCards()[i].getName()) {
                YellowCard desiredCard = p[turn].giveYellowCard(i);
                yellowCards[turn].push_back(desiredCard);
                return;
            }
        }
        for (int i = 0; i < p[turn].getPurpleCards().size(); i++) {
            if (command == p[turn].getPurpleCards()[i] -> getName()) {
                PurpleCard *desiredCard = p[turn].givePurpleCard(i);
                if (desiredCard -> getPriority() == 0) {
                    desiredCard -> makeEffect(*this, p, turn);
                    removePurpleCard(desiredCard);
                }
                else if (desiredCard -> getName() == "bahaar" || desiredCard -> getName() == "zemestoon") {
                    changeSeason(desiredCard);
                }
                else {
                    purpleCards[turn].push_back(desiredCard);
                }
                return;
            }
        }
        cout << "incorrect command, try again" << endl;
        doWhatPlayerSaid(p[turn].choose(), p, turn);
    }
    //------------------------------------------------------------------------------------------------------
    void sortPurpleCardsPriority(vector <int> &cardsId) {
        for (int i = 0; i < allPurpleCards.size(); i++)  {
            for (int j = 0; j < allPurpleCards.size()-1; j++)  {
                if (allPurpleCards[j] -> getPriority() > allPurpleCards[j+1] -> getPriority()) {
                    PurpleCard *Ptemp = allPurpleCards[j];
                    allPurpleCards[j] = allPurpleCards[j+1];
                    allPurpleCards[j+1] = Ptemp;

                    int temp = cardsId[j];
                    cardsId[j] = cardsId[j+1];
                    cardsId[j+1] =temp;
                }
            }
        }
    }
    //------------------------------------------------------------------------------------------------------
    void CalculatePoints(vector <Player> &p) {
        //remove additional tablzan
        for (int i = 0; i < purpleCards.size(); i++) {
            int counter = 0;
            for (int j = 0; j < purpleCards[i].size(); j++) {
                if (purpleCards[i][j] -> getName() == "tablzan") {
                    if (counter + 1 == 2) {
                        transferPCtoRemove(purpleCards[i][j], i, j);
                        j--;
                    }
                    else {
                        counter++;
                    }
                }
            }
        }

        //put all players purple cards to one vector
        vector <int> cardsId;
        for (int i = 0; i < purpleCards.size(); i++) {
            for (int j = 0; j < purpleCards[i].size(); j++) {
                allPurpleCards.push_back(purpleCards[i][j]);
                cardsId.push_back(i);
            }
        }

        //put season in vector too
        if (season != nullptr) {
            allPurpleCards.push_back(season);
            cardsId.push_back(0);
        }

        //sort purpleCards and their ids
        sortPurpleCardsPriority(cardsId);

        //calculate total yellow cards points
        for (int i = 0; i < p.size(); i++) {
            for (int j = 0; j < yellowCards[i].size(); j++) {
                pointsEarned[i] += yellowCards[i][j].getPoint();
            }
        }

        //make purple cards effect
        for (int j = 0; j < allPurpleCards.size(); j++) {
            allPurpleCards[j] -> makeEffect(*this, p, cardsId[j]);

        }

        for (int i = 0; i < pointsEarned.size(); i++) {
            cout << p[i].getName() << "| final point: " << pointsEarned[i] << endl;
        }
    }



    //------------------------------------------------------------------------------------------------------
    int findMaxPoint() {
        int maxPoint = pointsEarned[0];
        for (int i = 0; i < pointsEarned.size()-1; i++) {
            if (pointsEarned[i] < pointsEarned[i+1]) {
                maxPoint = pointsEarned[i+1];
            }
        }
        return maxPoint;
    }
    //------------------------------------------------------------------------------------------------------
    void determineWinner() {
        int maxPoint = findMaxPoint();
        int counter = 0;
        for (int i = 0; i < pointsEarned.size(); i++) {

        }
    }
    //------------------------------------------------------------------------------------------------------
    void passPlayer(Player p) {
        bool flag = true;
        for (int i = 0; i < passedPlayers.size(); i++) {
            if (p.getSign().getColor() == passedPlayers[i].getSign().getColor()) {
                flag = false;
            }
        }
        if (flag) {
            passedPlayers.push_back(p);
        }
        cout << "--" << p.getName() << " passed" << "--" << endl;
    }
    //------------------------------------------------------------------------------------------------------
    void changeSeason(PurpleCard *s) {
        if (season != nullptr) {
        removePurpleCard(season);
        }
        season = s;
    }
    //------------------------------------------------------------------------------------------------------
    void changeTurn(int &turn, vector <Player> &p) {
        bool flag = false;
        for (int k = 0; k < p.size(); k++) {
            turn++;
            flag = true;
            if (turn == p.size()) {
                turn = 0;
            }
            for (int i = 0; i < passedPlayers.size(); i++) {
                if (p[turn].getSign().getColor() == passedPlayers[i].getSign().getColor()) {
                    flag = false;
                }
            }
            if (flag) {
                break;
            }
        }
    }
    //------------------------------------------------------------------------------------------------------
    void showPlayerAllCardsInWar(int turn) {
        for (int i = 0; i < yellowCards[turn].size(); i++) {
            cout << yellowCards[turn][i].getName() << " ";
        }
        for (int i = 0; i < purpleCards[turn].size(); i++) {
            cout << purpleCards[turn][i] -> getName() << " ";
        }
    }
    //------------------------------------------------------------------------------------------------------
    void showPlayerYellowCardsInWar(int turn) {
        for (int i = 0; i < yellowCards[turn].size(); i++) {
            cout << yellowCards[turn][i].getName() << " ";
        }
    }
    //------------------------------------------------------------------------------------------------------
    void showPlayerPurpleCardsInWar(int turn) {
       for (int i = 0; i < purpleCards[turn].size(); i++) {
            cout << purpleCards[turn][i] -> getName() << " ";
        }
    }
    //------------------------------------------------------------------------------------------------------
    void checkForPassPlayer(Player &p) {
        if (p.getYellowCards().size() == 0 && p.getPurpleCards().size() == 0) {
            passPlayer(p);
        }
    }
    //------------------------------------------------------------------------------------------------------
    void checkForEndWar(vector <Player> &p) {
        if (p.size() == passedPlayers.size()) {
            EndWar();
        }
    }
    //------------------------------------------------------------------------------------------------------
    void EndWar() {
        warEnd = true;
    }
    //------------------------------------------------------------------------------------------------------
    void war(vector <Player> &p) {
        int turn = chooseWhoStart(p);
        while (!warEnd) {
            cout << p[turn].getName() << ": ";
            p[turn].showCards();
            cout << endl;
            showPlayerAllCardsInWar(turn);
            cout << endl;
            doWhatPlayerSaid(p[turn].choose(), p, turn);
            checkForPassPlayer(p[turn]);
            checkForEndWar(p);
            changeTurn(turn, p);
        }
        CalculatePoints(p);

    }
};





void  Matarsag :: makeEffect(class State &s, vector <class Player> &p, int turn) {
    cout << "which card?" << endl;
    s.showPlayerYellowCardsInWar(turn);
    string input = p[turn].choose();
    for (int i = 0; i < s.getPlayerYellowCardsInWar(turn).size(); i++) {
        if (input == s.getPlayerYellowCardsInWar(turn)[i].getName()) {
            p[turn].takeYellowCard(s.giveYellowCard(turn, i));
            break;
        }
    }
}

void ShirDokht :: makeEffect(class State &s, vector <class Player> &p, int turn) {
    s.increasePlayerPoint(turn, 10);
}

void TablZan :: makeEffect(class State &s, vector <class Player> &p, int turn) {
    s.setPlayerPoint(turn, s.getPlayerPointEraned(turn)*2);
}

void Zemestoon :: makeEffect(class State &s, vector <class Player> &p, int turn) {
    for (int k = 0; k < p.size(); k++) {
        s.setPlayerPoint(k, s.getPlayerYellowCardsInWar(k).size());
    }
}

void Bahaar :: makeEffect(class State &s, vector <class Player> &p, int turn) {
    //find max yellow card point
    int maxPoint = 0;
    for (int i = 0; i < p.size(); i++) {
        for (int j = 0; j < s.getPlayerYellowCardsInWar(i).size(); j++) {
            if (s.getPlayerYellowCardsInWar(i)[j].getPoint() > maxPoint) {
                maxPoint = s.getPlayerYellowCardsInWar(i)[j].getPoint();
            }
        }
    }
    //effect to players who have max point
    for (int i = 0; i < p.size(); i++) {
        for (int j = 0; j < s.getPlayerYellowCardsInWar(i).size(); j++) {
            if (s.getPlayerYellowCardsInWar(i)[j].getPoint() == maxPoint) {
                s.increasePlayerPoint(i, 3);
            }
        }
    }
}



class Rakab {
private:
    vector <Sign> signs;
    vector <YellowCard> yellowCards;
    vector <PurpleCard*> purpleCards;
    vector <Player> players;
    vector <State> states;
    bool gameEnd = false;
public:
    Rakab() {

    }
    int randomness(int scope, int fixer) {
        int random = (rand() % scope) + fixer;
    }
    void prepareSigns() {
        Sign yellow("yellow");
        Sign green("green");
        Sign red("red");
        Sign blue("blue");
        Sign purple("purple");
        Sign gray("gray");

        signs.push_back(yellow);
        signs.push_back(green);
        signs.push_back(red);
        signs.push_back(blue);
        signs.push_back(purple);
        signs.push_back(gray);
    }

    void prepareCards() {
        //prepare yellow cards
        YellowCard one("1", 1);
        YellowCard two("2", 2);
        YellowCard three("3", 3);
        YellowCard four("4", 4);
        YellowCard five("5", 5);
        YellowCard six("6", 6);
        YellowCard ten("10", 10);
        for (int i = 0; i < 8; i++) {
            yellowCards.push_back(one);
            yellowCards.push_back(two);
            yellowCards.push_back(three);
            yellowCards.push_back(four);
            yellowCards.push_back(five);
            yellowCards.push_back(six);
            yellowCards.push_back(ten);
        }
        yellowCards.push_back(one);
        yellowCards.push_back(one);

        //prepare purple cards
        for (int i = 0; i < 16; i++) {
            purpleCards.push_back(new Matarsag());
        }
        for (int i = 0; i < 6; i++) {
            purpleCards.push_back(new TablZan());
        }
        for (int i = 0; i < 3; i++) {
            purpleCards.push_back(new ShirDokht());
        }
        for (int i = 0; i < 3; i++) {
            purpleCards.push_back(new Bahaar());
        }
        for (int i = 0; i < 3; i++) {
            purpleCards.push_back(new Zemestoon());
        }
    }

    void showSigns() {
        for (int i = 0; i < signs.size(); i++) {
            cout << signs[i].getColor() << " ";
        }
        cout << endl;
    }

    Sign giveColor(string color) {
        for (int i = 0; i < signs.size(); i++) {
            if (color == signs[i].getColor()) {
                Sign Stemp = signs[i];
                signs.erase(signs.begin() + i);
                return Stemp;
            }
        }
    }

    YellowCard giveYellowCard(int index) {
        YellowCard Ytemp = yellowCards[index];
        yellowCards.erase(yellowCards.begin() + index);
        return Ytemp;
    }

    PurpleCard* givePurpleCard(int index) {
        PurpleCard *Ptemp = purpleCards[index];
        purpleCards.erase(purpleCards.begin() + index);
        return Ptemp;
    }

    void preparePlayers() {
        vector <Player> players;
        cout << "enter number of players (3 - 6) : ";
        int numberOfPlayers;
        cin >> numberOfPlayers;
        for (int i = 0; i < numberOfPlayers; i++) {
            system("cls");
            cout << "player_" << i+1 << " name: ";
            string name;
            cin >> name;
            cout << "player_" << i+1 << " age: ";
            int age;
            cin >> age;
            Player p(name, age);
            cout << "choose a sign: " << endl;
            showSigns();
            string color;
            cin >> color;
            Sign t = giveColor(color);
            p.setSign(t);
            cout << "player_" << i+1 <<" choosed ("  << p.getSign().getColor() <<") sign color" << endl;
            cout << "---press any kay continue..." << endl;
            getch();
            players.push_back(p);
        }
        setPlayers(players);
    }
    void setPlayers(vector <Player> inPlayers) {
        players = inPlayers;
    }
    void shuffle() {
        int ycSize = yellowCards.size();
        int pcSize = purpleCards.size();
        int randIndex;
        for (int i = 0; i < ycSize; i++) {
            randIndex = randomness(ycSize, 0);
            yellowCards.push_back(yellowCards[randIndex]);
            yellowCards.erase(yellowCards.begin() + randIndex);
        }
        for (int i = 0; i < pcSize; i++) {
            randIndex = randomness(pcSize, 0);;
            purpleCards.push_back(purpleCards[randIndex]);
            purpleCards.erase(purpleCards.begin() + randIndex);
        }
    }

    void chargePlayerCards() {
        for (int k = 0; k < players.size(); k++) {
            int StatesCaptured = (5 - players[k].getNumberOfSigns());
            int numberOfCards = 10 + StatesCaptured;
            for (int i = 0; i < numberOfCards; i++) {
                int coin = randomness(2, 0);
                if (coin == 0)
                    players[k].takeYellowCard(giveYellowCard(yellowCards.size() - 1));
                else
                    players[k].takePurpleCard(givePurpleCard(purpleCards.size() - 1));
            }
        }
    }

    void prepareStates() {

    }

    void showAllPlayersCards() {
        for (int i = 0; i < players.size(); i++) {
            players[i].showCards();
            cout << endl;
        }
    }
};

void run() {
    srand(time(0));
    Rakab R;
    R.prepareCards();
    R.prepareSigns();
    R.preparePlayers();
    R.shuffle();
    R.chargePlayerCards();
    R.showAllPlayersCards();

}


int main()
{
    run();
    return 0;
}








/*
class Rakab {
private:
    vector <Player> Players;
    vector <State> states;
    bool gameEnd = false;
public:
    Rakab() {

    }
    void preparePlayers() {

    }
    void prepareStates() {

    }
};
*/





    /*
    Player p1;
    Player p2;
    Player p3;

    p1.setName("p1");
    p1.setAge(10);
    p1.setColor("red");
    p2.setName("p2");
    p2.setAge(5);
    p2.setColor("blue");
    p3.setName("p3");
    p3.setAge(2);
    p3.setColor("green");

    for (int i = 0; i < 2; i++) {
    YellowCard y("10", 10);
    p1.takeYellowCard(y);
    p2.takeYellowCard(y);
    }

    for (int i = 0; i < 1; i++) {
    p1.takePurpleCard(new Matarsag());
    p2.takePurpleCard(new Matarsag());
    }

    p1.takePurpleCard(new TablZan());
    p1.takePurpleCard(new TablZan());
    p2.takePurpleCard(new ShirDokht());
    p2.takePurpleCard(new Bahaar());
    p2.takePurpleCard(new Zemestoon());
    p3.takePurpleCard(new Bahaar());
    p3.takePurpleCard(new ShirDokht());
    YellowCard y2("2", 2);
    p3.takeYellowCard(y2);


    vector <Player> ps;
    ps.push_back(p1);
    ps.push_back(p2);
    ps.push_back(p3);

    State s("deez", ps.size());
    s.war(ps);
    */




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
