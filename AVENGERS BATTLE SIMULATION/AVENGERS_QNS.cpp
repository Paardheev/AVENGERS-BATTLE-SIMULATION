#include<string>
#include<vector>
#include<iostream>
#include<queue>
#include<unordered_map>

using std::cin;
using std::cout;
using std::endl ;

class QNS{
    public:
    
    // constructors - start

        QNS(int P,int D,int E,int H);

        QNS(const QNS & suit);

        QNS();
        
    // constructors - end

    // operator overloading - start
        QNS & operator+(QNS & suit);

        QNS & operator-(int X);

        QNS & operator*(int X);

        QNS & operator/(int X);
    // operator overloading - end

    // function overloading - start
        void boostPower(int factor){ // can use * operator
            *this = (*this)*factor ; // check whether this makes changes
        }
        void boostPower(QNS & othersuit){ // can use + operator
            *this = (*this)+othersuit ;
        }
    // function overloading - end

    // comparison overloading - start
        bool operator==(QNS & othersuit){ // Compares suits based on powerLevel and durability. If both are the same returns true, else return false.
            return (powerlevel == othersuit.getP()) && (durability == othersuit.getD()) ;
        }
        bool operator<(QNS & othersuit){ // Compares suit effectiveness in battles. If sum of suit1 power and durability is lesser than other return true else returns false.
            return (powerlevel+durability) < (othersuit.getP()+othersuit.getD()) ;
        }
    // comparison overloading - end

    // getters - start
        int getP(){ return powerlevel ; }
        int getD(){ return durability ; }
        int getE(){ return energystorage ;}
        int getH(){ return heatlevel ; }
    // getters - end

    // setters - start
        void setP(int X){powerlevel = X;if(X > 5000) powerlevel = 5000;}
        void setD(int X){durability = X ;}
        void setE(int X){energystorage = X ;}
        void setH(int X){heatlevel = X ;if(X < 0) heatlevel = 0 ;}
    // setters - end
    private:
        int powerlevel ; // default value 1000 , rep as P , max powerlevel is 5000
        int durability ; // default value  500 , rep as D
        int energystorage ;// default value 300, rep as E
        int heatlevel ;  // default value    0 , rep as H , check for overheat while using suit
};

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

class Battle{
    public:
        Battle(std::vector<Avenger> & a,std::unordered_map<std::string,int> & amap,std::queue<QNS> s,int noheroes );
        
        std::string startBattle();

        void printBattleLog();
        
        int calculatestrength(int i,int j);

        int findindex(std::string & s);
        
        int Result();
        
    private:
        std::vector<Avenger> Avengers ;
        int n;
        std::unordered_map<std::string,int> Avengersmap ;
        std::vector<std::string> battlelog ;
        std::queue<QNS> suits ;
};


QNS::QNS(int P,int D,int E,int H){ // parameterized constructor
    if(P > 5000) P = 5000 ;
    if(H < 0) H = 0 ;
    powerlevel = P ;
    durability = D ;
    energystorage = E ;
    heatlevel = H ;
}
QNS::QNS(const QNS & suit){ // copy constructor from another suit
    powerlevel = suit.powerlevel ;
    durability = suit.durability ;
    energystorage = suit.energystorage ;
    heatlevel = suit.heatlevel ;
}
QNS::QNS(){ // default constructor
    powerlevel = 1000 ;
    durability = 500  ;
    energystorage = 300 ;
    heatlevel = 0 ;
}
// constructors - end

// operator overloading - start
QNS & QNS::operator+(QNS & suit){ // formula : (P1, D1, E1,H1) + (P2, D2, E2,H2) = (P1 + E2, D1 + D2, E1 + P2,H1) 
    
    powerlevel += suit.getE() ;
    durability += suit.getD() ;
    energystorage += suit.getP();
    if(powerlevel > 5000) powerlevel = 5000 ;
    return *this ;

}
QNS & QNS::operator-(int X){ // formula : (P, D, E, H) - X = (P, D - X, E + X, H + X)
    
    durability -= X ;
    energystorage += X ;
    heatlevel += X ;
    return *this ;

}
QNS & QNS::operator*(int X){ // formula : (P, D, E, H) * X = (P+(P * (X/100)), D, E + 5X, H + X) 
    
    powerlevel = (powerlevel + ((powerlevel *X)/100)) ;
    energystorage += 5 * X ;
    heatlevel += X ;
    if(powerlevel > 5000) powerlevel = 5000 ;
    return *this ;

}
QNS & QNS::operator/(int X){ // formula : (P, D, E, H) / X = (P, D + X, E, H - X), reset H based on constraint
    
    durability += X ;
    heatlevel -= X ;
    if(heatlevel <= 0) heatlevel = 0 ;
    return *this ;

}


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
    if(suit.getD() > 0) suit = suit/x ;
}

void Avenger::printStatus() { //Displays the Avenger's suit details in the format <Avenger_Name> P <D> <E> <H>. 
    cout << name << " " << suit.getP() << " " << suit.getD() << " " << suit.getE() << " " << suit.getH() << endl;
}

QNS & Avenger::getsuit(){
    return suit ;
}


Battle::Battle(std::vector<Avenger> & a,std::unordered_map<std::string,int> & amap,std::queue<QNS> s,int noheroes ){ // parameterized constructor
    
    Avengers = a ;
    
    Avengersmap = amap ;
    
    suits = s ;
    
    n = noheroes ; // n is number of heroes
}

int Battle::Result(){ // if heroes are likely to win returns 1, if enemies are likely to win then return -1, returns 0 if its a tie.
    
    int heroresult,enemyresult ;
    
    heroresult = calculatestrength(0,n) ;
    
    enemyresult = calculatestrength(n,int(Avengers.size())) ;
    
    if(heroresult > enemyresult) return 1 ;
    else if (heroresult < enemyresult) return -1 ;
    else return 0 ;

}

std::string Battle::startBattle(){ //  flag to start the battle
    
    std::string command ;
    
    cin >> command ;
    
    std::string Av1,Av2 ;
    
    while(command != "End"){
        // write log appropiately
        if(command == "Attack"){
            
            cin >> Av1 >> Av2 ;
            // Av1 attacks Av2
            int i = findindex(Av1), j = findindex(Av2) ;
            if(!Avengers[i].attack(Avengers[j])){ cin >> command; continue;}
            std::string s = Av1 + " attacks " + Av2 ;
            battlelog.push_back(s);
            if(Avengers[j].getsuit().getD() <= 0) {s = Av2 + " suit destroyed"; battlelog.push_back(s);}
            else if(Avengers[j].getsuit().getH() > 500) {s = Av2 + " suit overheated"; battlelog.push_back(s);}
        }
        else if (command == "Repair"){
            
            int x;
            cin >> Av1 >> x ;
            // repair Av1's suit ;
            int i = findindex(Av1);
            Avengers[i].repair(x);
            battlelog.push_back(Av1 + " repaired");
        }
        else if (command == "BoostPowerByFactor"){
            
            int x;
            cin >> Av1 >> x ;
            // use boostpower function in QNS
            int i = findindex(Av1);
            Avengers[i].getsuit().boostPower(x);
            battlelog.push_back(Av1 + " boosted");
            if(Avengers[i].getsuit().getH() > 500) battlelog.push_back(Av1 + " suit overheated");
        }
        else if (command == "BoostPower"){
            
            int P,D,E,H;
            cin >> Av1 >> P >> D >> E >> H ;
            // use boostpower function in QNS
            int i = findindex(Av1);
            QNS A(P,D,E,H);
            Avengers[i].getsuit().boostPower(A);
            battlelog.push_back(Av1 + " boosted");
            if(Avengers[i].getsuit().getH() > 500) battlelog.push_back(Av1 + " suit overheated");
        }
        else if (command == "AvengerStatus"){
            
            cin >> Av1 ;
            // print Avenger stats
            int i = findindex(Av1);
            Avengers[i].printStatus();
        }
        else if (command == "Upgrade"){
            
            cin >> Av1 ;
            // upgrade if extra suits are available
            int i = findindex(Av1);
            if(!suits.empty()){
                Avengers[i].upgradeSuit(suits.front());
                suits.pop();
                battlelog.push_back(Av1 + " upgraded");
            }
            else battlelog.push_back( Av1 + " upgrade Fail");

        }
        else if (command == "PrintBattleLog"){
            
            printBattleLog();

        }
        else if (command == "BattleStatus" ){

            int result = Result() ;
            if(result == 1) cout << "heroes are winning\n" ;
            else if (result == -1) cout << "enemies are winning\n" ;
            else if (result == 0) cout << "tie\n" ;

        }

        cin >> command ;
    }
    return command ;
}

void Battle::printBattleLog(){ // Shows battle history

    for(auto & x : battlelog) cout << x << endl ;

}

int Battle::calculatestrength(int i,int j){
    
    int sum = 0 ;
    for(;i<j;i++){
        if(Avengers[i].getsuit().getD() > 0){
            sum += Avengers[i].getsuit().getP()+Avengers[i].getsuit().getD();
        }
    }
    return sum ;

}

int Battle::findindex(std::string & s){

    return Avengersmap[s] ;

}


int main(){
    int k,n,m,P,D,E,H; // k == no.of suits, n == no.of heroes, m == no.of enemies

    std::vector<Avenger> Avengers ;
    
    std::string name,command;
    
    int attack ;
    
    std::unordered_map<std::string,int> Avengersmap ;
    
    std::queue<QNS> suits ;
    
    cin >> k >> n >> m ; 
    
    for(int i = 0 ; i < k ; i++){// next k lines are details of the suit in format P D E H
        cin >> P >> D >> E >> H ;
        suits.push(QNS(P,D,E,H));
    }
    
    for(int i = 0 ; i < n+m ; i++){// next n + m lines are heroes followed by enemies
        cin >> name >> attack ;
        if(!suits.empty()){
            QNS suit = suits.front();
            suits.pop();
            Avengersmap[name] = i ;
            Avengers.push_back(Avenger (name,suit,attack));
        }
        else{
            cout << name << " is out of fight\n" ;
        }
    }
    
    cin >> command ;
    
    Battle war(Avengers,Avengersmap,suits,n);
    
    command = war.startBattle();
}