//
// Created by tianyizhang on 2020-02-27.
//260883657

#include <vector>

#ifndef ASSIGNMENT2_BLACKJACK_H
#define ASSIGNMENT2_BLACKJACK_H

#endif //ASSIGNMENT2_BLACKJACK_H

enum Rank {ACE=1,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,JACK,QUEEN,KING};
enum Type {CLUBS=1,DIAMONDS,HEARTS,SPADES};
class Card
{
private:
    Rank aRank;
    Type aType;
public:
    //constructor
    Card(enum Rank pRank,enum Type pType);
    bool operator==(const Card& obj);

    int getValue(); //return the value of the Card; ACE always returns 1
    friend std::ostream&operator<<(std::ostream& os,const Card& pCard);
    void displayCard();
};

class Hand
{
protected:
    std::vector<Card> aCards;

public:
    Hand() = default;
    virtual bool operator==(const Card& obj);
    virtual void add(Card pCard); //add a card to the hand
    virtual void clear(); //clear the vector of cards.
    virtual int getTotal() const; //return the total value of the cards in the hand. Takes into consideration whether ACE should be 1 or 11.
    friend std::ostream&operator<<(std::ostream& os,const Hand& pHand);
};

class Deck: public Hand
{
private:
    int count =0;
public:
    void populate(); //populate the Hand with all 52 cards.
    void shuffle(); //shuffle randomly, based on current clock tick
    void deal(Hand& pHand); //deal a card to a Hand.
};

class AbstractPlayer
{
protected:
    Hand aHand;
public:
    AbstractPlayer() = default;
    virtual bool isDrawing() const =0;
    virtual bool isBusted();
    Hand& getHand();
};
class ComputerPlayer: public AbstractPlayer
{
private:
public:
    ComputerPlayer() = default;
    bool isDrawing() const override;
    int getTotal();
    friend std::ostream&operator<<(std::ostream& os,const ComputerPlayer& pPlayer);

};
class HumanPlayer: public AbstractPlayer
{
private:

public:
    HumanPlayer() = default;
    bool isDrawing() const override;
    void announce(ComputerPlayer pPlayer); //announce who won. It has to take the other player (the computer) as an argument to compare the points.
    friend std::ostream&operator<<(std::ostream& os,const HumanPlayer& pPlayer);
};

class BlackJackGame
{
private:
    Deck m_deck;
    ComputerPlayer m_casino;
    HumanPlayer m_client;
public:
    BlackJackGame() = default;
    void play();
    void reinitialize(); //reinitialize m_deck, m_casino, m_client.
};


