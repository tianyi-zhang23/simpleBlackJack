//
// Created by tianyizhang on 2020-02-27.
//260883657

#include <iostream>
#include "blackjack.h"
#include <random>
#include <algorithm>

using namespace std;

Card::Card(enum Rank pRank, enum Type pType):aRank(pRank),aType(pType) {}
bool Card::operator==(const Card &obj) {return aRank==obj.aRank && aType==obj.aType;}
int Card::getValue() {
    if(aRank<=10) //returns 1 for ACE. The getTotal() method in deck will have a procedure to consider whether a ACE counts as 1 or 11.
        return aRank;
    else return 10; //for JQK, value is 10
}
std::ostream& operator<<(std::ostream& os,const Card& pCard) //overload << for Card. prints out Rank Type, eg. 1H, QS
{
    if(pCard.aRank<=10) //for 1 to 10, use numerical value of enum Rank, which starts at 1
        os<<pCard.aRank;
    else if (pCard.aRank==11) //for JQK
        os<<"J";
    else if (pCard.aRank==12)
        os<<"Q";
    else
        os<<"K";

    if(pCard.aType==1) //according to the order in enum Type. CLUBS=1
        os<<"C";
    else if(pCard.aType==2)
        os<<"D";
    else if(pCard.aType==3)
        os<<"H";
    else
        os<<"S";

    return os;

}
void Card::displayCard() {
    cout<<*this; //use overloaded <<.
}

void Hand::add(Card pCard) {aCards.push_back(pCard);}
void Hand::clear() {aCards.clear();}
int Hand::getTotal() const {
    int total=0;
    for(Card i:aCards)
        total+=i.getValue();
    for(Card j:aCards)
    {
        if(j.getValue()==1 && total<=11) //fix a hand with ACE to correct sum. For each ACE, add 10 to total if this results in total<=21
            total+=10;
    }
    return total;
}
bool Hand::operator==(const Card &obj) {return *this==obj;}

void Deck::populate() { //for each type and each rank, create a card and add it to vector aCards.
    for(int i=Type::CLUBS;i<=Type::SPADES;i++)
    {
        for(int j=Rank::ACE;j<=Rank::KING;j++)
        {
            aCards.push_back(Card(static_cast<Rank>(j), static_cast<Type>(i)));
        }
    }
}

void Deck::shuffle()
{
    auto engine = default_random_engine {}; //shuffle using current clock tick to create randomness.
    engine.seed(clock());
    std::shuffle(begin(aCards),end(aCards),engine);
}

void Deck::deal(Hand& pHand)
{
    pHand.add(aCards.at(count)); //this will not go out of bound as each game ends before every card can be dealt. BlackJackGame reinitializes its Deck each time the user restarts the game.
    count++;
}
bool AbstractPlayer::isBusted() {
    return aHand.getTotal() > 21;
}
Hand& AbstractPlayer::getHand() {return aHand;}
bool HumanPlayer::isDrawing() const {
    char input;
    cout<<"Do you want to draw? (y/n)"<<endl;
    cin>>input;
    return input=='y';
}

void HumanPlayer::announce(ComputerPlayer pPlayer) {
    if(this->isBusted())
        cout<<"The player is busted. The player loses. The computer wins"<<endl;
    else if (pPlayer.isBusted())
        cout<<"The computer busts. The computer loses. The player wins"<<endl;
    else if (aHand.getTotal() < pPlayer.getTotal())
        cout<<("The player has a lower total. The player loses. The computer wins")<<endl;
    else if (aHand.getTotal()==pPlayer.getTotal())
        cout<<("A push. No one wins.")<<endl;
    else if (aHand.getTotal()>pPlayer.getTotal())
        cout<<"The player has a higher total. The player wins. The computer loses."<<endl;

}

bool ComputerPlayer::isDrawing() const {
    return aHand.getTotal()<=16;
}

int ComputerPlayer::getTotal() {
    return aHand.getTotal();
}
ostream&operator<<(ostream& os,const Hand& pHand) //overload << for Hand
{
    for(Card i:pHand.aCards)
    {
        os<<i<<" "; //<< for Hand outputs each card followed by a space. << for Card is already overloaded.
    }
    return os;
}
ostream& operator<<(std::ostream& os,const HumanPlayer& pPlayer) //overload << for players. Output according to the example given in the PDF.
{
    os<<"Player: "<<pPlayer.aHand<<" ["<<pPlayer.aHand.getTotal()<<"]"<<endl;
    return os;
}
ostream& operator<<(std::ostream& os,const ComputerPlayer& pPlayer)
{
    os<<"Casino: "<<pPlayer.aHand<<" ["<<pPlayer.aHand.getTotal()<<"]"<<endl;
    return os;
}
void BlackJackGame::reinitialize() { //each time a new game starts, reinitialize every field to get a new Deck and new players.
    m_deck = Deck();
    m_client = HumanPlayer();
    m_casino = ComputerPlayer();
    m_deck.populate();
    m_deck.shuffle();
}
void BlackJackGame::play() {
    reinitialize();
   m_deck.deal(m_casino.getHand()); //casino gets 1 card
   m_deck.deal(m_client.getHand()); //player gets 2 cards
   m_deck.deal(m_client.getHand());
   cout<<m_casino;
   cout<<m_client;
   if(m_casino.isBusted() || m_client.isBusted()) //check if anyone already busts
   {
       m_client.announce(m_casino);
       return;
   }

       while(!m_client.isBusted() && m_client.isDrawing()) //the client draws first
       {
           m_deck.deal(m_client.getHand());
           cout<<m_client;
       }
       if(m_client.isBusted()) //if the client busts, announce and game over
       {
           m_client.announce(m_casino);
           return;
       }
       while(m_casino.isDrawing())
       {
           m_deck.deal(m_casino.getHand());
           cout<<m_casino;
       }

   m_client.announce((m_casino));


}









