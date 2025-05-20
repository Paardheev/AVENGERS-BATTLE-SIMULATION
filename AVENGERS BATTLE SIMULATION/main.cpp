#include"Battle.cpp"
int main(){
    int k,n,m; // k == no.of suits, n == no.of heroes, m == no.of enemies
    cin >> k >> n >> m ;
    // next k lines are details of the suit in format P D E H
    int P,D,E,H ;
    std::vector<Avenger> Avengers ;
    std::queue<QNS> suits ;
    for(int i = 0 ; i < k ; i++){
        cin >> P >> D >> E >> H ;
        suits.push(QNS(P,D,E,H));
    }
    // next n + m lines are heroes followed by enemies
    std::string name;
    int attack ;
    std::unordered_map<std::string,int> Avengersmap ;
    for(int i = 0 ; i < n+m ; i++){
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
    std::string command ;
    cin >> command ;
    Battle war(Avengers,Avengersmap,suits,n);
    command = war.startBattle();
}