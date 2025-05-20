#include<string>
#include<vector>
#include<iostream>
#include<queue>
#include<unordered_map>

using std::cin,std::cout,std::endl ;

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

QNS::QNS(int P,int D,int E,int H){ // parameterized constructor
    if(P > 5000) P = 5000 ;
    if(H < 0) H = 0 ;
    powerlevel = P , durability = D , energystorage = E , heatlevel = H ;
}
QNS::QNS(const QNS & suit){ // copy constructor from another suit
    powerlevel = suit.powerlevel , durability = suit.durability , energystorage = suit.energystorage , heatlevel = suit.heatlevel ;
}
QNS::QNS(){ // default constructor
    powerlevel = 1000 , durability = 500 , energystorage = 300 , heatlevel = 0 ;
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