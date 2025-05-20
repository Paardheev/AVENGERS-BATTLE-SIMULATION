#include"Avengers.cpp"

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
    for(;i<j;i++) if(Avengers[i].getsuit().getD() > 0) sum += Avengers[i].getsuit().getP()+Avengers[i].getsuit().getD();
    return sum ;
}

int Battle::findindex(std::string & s){
    return Avengersmap[s] ;
}

