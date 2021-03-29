#include "people.h"
#include<bits/stdc++.h>
using namespace std;
people::people(){
    landlord = false;
    money = 0;
    loses = 0;
    wins = 0;
    landlordTimes = 0;
    gameTimes = 0;
    for( int i = 0; i < 21; i++)
        cards[i] = 0;
}
people::people( long long money_){
    landlord = false;
    money = money_;
    loses = 0;
    wins = 0;
    landlordTimes = 0;
    gameTimes = 0;
    for( int i = 0; i < 21; i++)
            cards[i] = 0;
}
int people::getLoses(){
    return loses;
}
void people::changeMoney( long long money_){
    this->money+=money_;
}
bool people::buyMoney( long long secret_){
    if (secret == secret_)
        money+=100000;
    else
        cout << endl << "error." << endl;
}
int people::getWins(){
    return wins;
}
long long people::getMoney(){
    return money;
}
void people::win( int money_){
    this->wins++;
    this->gameTimes++;
    this->money+=money_;
}
void people::lose( int money_){
    this->loses++;
    this->gameTimes++;
    this->money-=money_;
}
void people::show(){
    cout << "lost : " << this->getLoses() << endl;
    cout << "won : " << this->getWins() << endl;
    cout << "money : " << this->getMoney() << endl;
}
