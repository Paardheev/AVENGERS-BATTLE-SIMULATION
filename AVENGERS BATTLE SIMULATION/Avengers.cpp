#include"QNS.cpp"
class Avenger
{
    public:
        Avenger(std::string avName, QNS avSuit, int strength);

        Avenger(const Avenger& other);
    // methods -start
        bool attack(Avenger& enemy);

        void upgradeSuit(QNS & extrasuit );

        void repair(int x);

        void printStatus();

        QNS & getsuit();

    // methods - end
    protected:
        std::string name ;
        QNS suit ;
        int attackstrength ;
};

Avenger::Avenger(std::string avName, QNS avSuit, int strength){ // parameterised-constructor
    name = avName ;
    suit = avSuit ;
    attackstrength = strength ;
}

Avenger::Avenger(const Avenger& other){
    *this = other ;
}

bool Avenger::attack(Avenger& enemy){ //  Damages the enemy's durability by a factor of <Avenger_attackStrength>.
    if(suit.getD() > 0 && suit.getH() <= 500){
        enemy.suit = enemy.suit - attackstrength;
        return true ;
    }
    return false ;
}

void Avenger::upgradeSuit(QNS & extrasuit ){ // If any extra suit is left out, transfer power to their suit in First come First serve order [can use + operator] from the extra suit and it can't be further used.
    suit = suit + extrasuit ;
}

void Avenger::repair(int x){ // Restores some durability to their suit by cooling down the suit by factor x.
    if(suit.getD() > 0)
    suit = suit/x ;
}

void Avenger::printStatus() { //Displays the Avenger's suit details in the format <Avenger_Name> P <D> <E> <H>. 
    cout << name << " " << suit.getP() << " " << suit.getD() << " " << suit.getE() << " " << suit.getH() << endl;
}

QNS & Avenger::getsuit(){
    return suit ;
}